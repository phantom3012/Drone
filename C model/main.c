
#include <stdbool.h> // For the 'true' keyword
#include <stdio.h>   // For printf
#include <math.h>    // For sin, cos, sqrt
#include <stdlib.h>  // For rand()
#include <time.h>    // For srand()
#include "algorithm.h"

// --- Simulation Constants ---
#define DRONE_MASS_KG 0.350
#define GRAVITY_MPS2 9.81
#define K_DRAG_COEFFICIENT 0.014
#define DT_S 0.1 // Simulation time step: 10 Hz

// --- Simulation State ---
typedef struct {
    GPSCoordinate_t pos;
    double heading_deg;
    double velocity_fwd_mps;
    double velocity_right_mps;
} DroneSimState_t;

// --- Simulation Physics (Simplified from Python) ---
void drone_sim_update_physics(DroneSimState_t *drone, double pitch_cmd, double roll_cmd) {
    double weight_N = DRONE_MASS_KG * GRAVITY_MPS2;

    // Forces
    double thrust_fwd_N = sin(DEGREES_TO_RADIANS(pitch_cmd)) * weight_N;
    double thrust_right_N = sin(DEGREES_TO_RADIANS(roll_cmd)) * weight_N;

    // Drag (ignoring wind for this barebones simulation)
    double drag_fwd_N = -copysign(1.0, drone->velocity_fwd_mps) *
                        K_DRAG_COEFFICIENT * (drone->velocity_fwd_mps * drone->velocity_fwd_mps);
    double drag_right_N = -copysign(1.0, drone->velocity_right_mps) *
                          K_DRAG_COEFFICIENT * (drone->velocity_right_mps * drone->velocity_right_mps);

    double net_force_fwd_N = thrust_fwd_N + drag_fwd_N;
    double net_force_right_N = thrust_right_N + drag_right_N;

    // Acceleration & Velocity
    drone->velocity_fwd_mps += (net_force_fwd_N / DRONE_MASS_KG) * DT_S;
    drone->velocity_right_mps += (net_force_right_N / DRONE_MASS_KG) * DT_S;

    // Position
    double dist_fwd_m = drone->velocity_fwd_mps * DT_S;
    double dist_strafe_m = drone->velocity_right_mps * DT_S;
    double heading_rad = DEGREES_TO_RADIANS(drone->heading_deg);

    double delta_n = (dist_fwd_m * cos(heading_rad)) - (dist_strafe_m * sin(heading_rad));
    double delta_e = (dist_fwd_m * sin(heading_rad)) + (dist_strafe_m * cos(heading_rad));

    drone->pos.lat += delta_n / 111000.0;
    drone->pos.lon += delta_e / (111000.0 * cos(DEGREES_TO_RADIANS(drone->pos.lat)));
}

// --- Helper to get a random starting position ---
void get_random_start_pos(GPSCoordinate_t target, double min_dist_m, double max_dist_m, DroneSimState_t *drone) {
    double dist = min_dist_m + (rand() / (double)RAND_MAX) * (max_dist_m - min_dist_m);
    double bearing_rad = (rand() / (double)RAND_MAX) * 2.0 * M_PI;
    double lat_rad = DEGREES_TO_RADIANS(target.lat);
    double lon_rad = DEGREES_TO_RADIANS(target.lon);

    double start_lat_rad = asin(sin(lat_rad) * cos(dist / EARTH_RADIUS_METERS) +
                                cos(lat_rad) * sin(dist / EARTH_RADIUS_METERS) * cos(bearing_rad));
    double start_lon_rad = lon_rad + atan2(sin(bearing_rad) * sin(dist / EARTH_RADIUS_METERS) * cos(lat_rad),
                                           cos(dist / EARTH_RADIUS_METERS) - sin(lat_rad) * sin(start_lat_rad));

    drone->pos.lat = start_lat_rad * 180.0 / M_PI;
    drone->pos.lon = start_lon_rad * 180.0 / M_PI;
}

int main(void) {
    srand(time(NULL)); // Seed random number generator

    // --- Initialization ---
    DroneNavigator_t navigator;
    DroneSimState_t drone_sim;

    // Controller Configuration (matches Python)
    const double TARGET_LAT = 43.06;
    const double TARGET_LON = -89.28;
    const double INITIAL_HEADING = 45.0;

    navigator_init(&navigator, TARGET_LAT, TARGET_LON,
                   0.6,    // p_gain
                   15.0,   // max_pitch_cmd
                   15.0,   // max_roll_cmd
                   5.0);   // distance_threshold

    // Drone Simulation Setup
    drone_sim.heading_deg = INITIAL_HEADING;
    drone_sim.velocity_fwd_mps = 0.0;
    drone_sim.velocity_right_mps = 0.0;
    get_random_start_pos(navigator.target_pos, 100, 300, &drone_sim);

    printf("--- C Drone Simulation Testbench ---\n");
    printf("Target: %.4f, %.4f\n", navigator.target_pos.lat, navigator.target_pos.lon);
    printf("Start:  %.4f, %.4f | Heading: %.1f deg\n\n", drone_sim.pos.lat, drone_sim.pos.lon, drone_sim.heading_deg);

    // --- Simulation Loop ---
    for (int step = 0; step < 2000; ++step) { //TODO: make this a while loop instead
        double pitch_cmd, roll_cmd;
        bool target_reached = navigator_update(&navigator, drone_sim.pos, drone_sim.heading_deg, DT_S, &pitch_cmd, &roll_cmd);

        drone_sim_update_physics(&drone_sim, pitch_cmd, roll_cmd);

        // --- Visualization: Print Status ---
        double dist_to_target = haversine_distance(drone_sim.pos, navigator.target_pos);
        printf("Step %4d | Dist: %6.1f m | Fwd Spd: %5.2f m/s | Right Spd: %5.2f m/s | Pitch: %5.2f | Roll: %5.2f\r",
               step,
               dist_to_target,
               drone_sim.velocity_fwd_mps,
               drone_sim.velocity_right_mps,
               pitch_cmd,
               roll_cmd);
        // fflush(stdout); // Make sure the line updates correctly

        if (target_reached) {
            printf("\n\n--- Target Reached in %d steps! ---\n", step);
            break;
        }

        if (step == 1999) {
            printf("\n\n--- Simulation timed out. ---\n");
        }
    }

    return 0;
}