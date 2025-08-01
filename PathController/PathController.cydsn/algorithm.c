
#include "algorithm.h"
#include "cordic.h" 
#include <math.h>

static inline double clamp(double value, double min_val, double max_val) {
    if (value < min_val) return min_val;
    if (value > max_val) return max_val;
    return value;
}

double haversine_distance(GPSCoordinate_t pos1, GPSCoordinate_t pos2) {
    double sin_delta_phi_half, cos_delta_phi_half;
    double sin_delta_lambda_half, cos_delta_lambda_half;
    double sin_phi1, cos_phi1;
    double sin_phi2, cos_phi2;

    double delta_phi = DEGREES_TO_RADIANS(pos2.lat - pos1.lat);
    double delta_lambda = DEGREES_TO_RADIANS(pos2.lon - pos1.lon);

    fast_sincos(delta_phi / 2.0, &sin_delta_phi_half, &cos_delta_phi_half);
    fast_sincos(delta_lambda / 2.0, &sin_delta_lambda_half, &cos_delta_lambda_half);
    fast_sincos(DEGREES_TO_RADIANS(pos1.lat), &sin_phi1, &cos_phi1);
    fast_sincos(DEGREES_TO_RADIANS(pos2.lat), &sin_phi2, &cos_phi2);

    double a = sin_delta_phi_half * sin_delta_phi_half +
               cos_phi1 * cos_phi2 *
               sin_delta_lambda_half * sin_delta_lambda_half;
    
    a = clamp(a, 0.0, 1.0);

    double c = 2.0 * fast_atan2(sqrt(a), sqrt(1.0 - a));
    return EARTH_RADIUS_METERS * c;
}

static double calculate_bearing(GPSCoordinate_t pos1, GPSCoordinate_t pos2) { //TODO: verify logic with
    double sin_phi1, cos_phi1;
    double sin_phi2, cos_phi2;
    double sin_delta_lambda, cos_delta_lambda;

    double phi1 = DEGREES_TO_RADIANS(pos1.lat);
    double lambda1 = DEGREES_TO_RADIANS(pos1.lon);
    double phi2 = DEGREES_TO_RADIANS(pos2.lat);
    double lambda2 = DEGREES_TO_RADIANS(pos2.lon);

    // Use fast_sincos for all trigonometric calculations
    fast_sincos(phi1, &sin_phi1, &cos_phi1);
    fast_sincos(phi2, &sin_phi2, &cos_phi2);
    fast_sincos(lambda2 - lambda1, &sin_delta_lambda, &cos_delta_lambda);

    double y = sin_delta_lambda * cos_phi2;
    double x = cos_phi1 * sin_phi2 - sin_phi1 * cos_phi2 * cos_delta_lambda;
    
    double theta = fast_atan2(y, x); 
    return fmod((theta * 180.0 / M_PI + 360.0), 360.0);
}


void navigator_init(DroneNavigator_t *nav, double target_lat, double target_lon,
                    double p_gain, double max_pitch,
                    double max_roll, double dist_thresh) {
    nav->target_pos.lat = target_lat;
    nav->target_pos.lon = target_lon;
    nav->p_gain = p_gain;
    nav->max_pitch_cmd = max_pitch;
    nav->max_roll_cmd = max_roll;
    nav->distance_threshold = dist_thresh;
}

bool navigator_update(DroneNavigator_t *nav, GPSCoordinate_t current_pos,
                      double drone_heading_degrees, double dt,
                      double *out_pitch_cmd, double *out_roll_cmd) {

    double distance = haversine_distance(current_pos, nav->target_pos);
    if (fabs(distance) < nav->distance_threshold) {
        *out_pitch_cmd = 0.0;
        *out_roll_cmd = 0.0;
        return true;
    }

    double bearing_to_target_deg = calculate_bearing(current_pos, nav->target_pos);
    double bearing_rad = DEGREES_TO_RADIANS(bearing_to_target_deg);
    double heading_rad = DEGREES_TO_RADIANS(drone_heading_degrees);

    double sin_arg, cos_arg;
    fast_sincos(bearing_rad - heading_rad, &sin_arg, &cos_arg);
    double relative_bearing_rad = fast_atan2(sin_arg, cos_arg);

    double error_forward = distance * cos_arg; 
    double error_right = distance * sin_arg;   

    double pitch_p_term = (fast_atan2(nav->p_gain * error_forward, distance) / (M_PI / 2.0)) * nav->max_pitch_cmd;
    double roll_p_term = (fast_atan2(nav->p_gain * error_right, distance) / (M_PI / 2.0)) * nav->max_roll_cmd;

    // --- Final Command ---
    double final_pitch = pitch_p_term;
    double final_roll = roll_p_term;

    // Clamp to absolute limits
    *out_pitch_cmd = clamp(final_pitch, -nav->max_pitch_cmd, nav->max_pitch_cmd);
    *out_roll_cmd = clamp(final_roll, -nav->max_roll_cmd, nav->max_roll_cmd);

    return false;
}
