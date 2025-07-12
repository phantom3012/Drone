/**
 * @file algorithm.h
 * @brief Public API for the drone navigation controller.
 *
 * This header defines the primary data structures and the main function
 * for the navigation algorithm. It provides a clean interface for getting
 * pitch and roll commands from GPS data.
 */
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdbool.h> // For bool type

// --- Public Constants and Utilities ---
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define DEGREES_TO_RADIANS(deg) ((deg) * M_PI / 180.0)
#define EARTH_RADIUS_METERS 6371000.0

// --- Public Data Structures ---

/**
 * @struct GPSCoordinate_t
 * @brief Holds a single GPS coordinate (latitude and longitude in degrees).
 * This structure is the primary input for the navigation system.
 */
typedef struct {
    double lat;
    double lon;
} GPSCoordinate_t;


/**
 * @struct DroneNavigator_t
 * @brief Holds the state and parameters for the navigation controller.
 */
typedef struct {
    // --- Configuration ---
    GPSCoordinate_t target_pos;
    double p_gain;
    double max_pitch_cmd;
    double max_roll_cmd;
    double distance_threshold;
} DroneNavigator_t;

// --- Public Function Prototypes ---

/**
 * @brief Calculates the distance between two GPS coordinates using the Haversine formula.
 */
double haversine_distance(GPSCoordinate_t pos1, GPSCoordinate_t pos2);

/**
 * @brief Initializes the drone navigation controller.
 */
void navigator_init(DroneNavigator_t *nav, double target_lat, double target_lon,
                    double p_gain, double max_pitch,
                    double max_roll, double dist_thresh);

/**
 * @brief Updates the controller and calculates new pitch/roll commands.
 * @return true if the target has been reached, false otherwise.
 */
bool navigator_update(DroneNavigator_t *nav, GPSCoordinate_t current_pos,
                      double drone_heading_degrees, double dt,
                      double *out_pitch_cmd, double *out_roll_cmd);

#endif // ALGORITHM_H
