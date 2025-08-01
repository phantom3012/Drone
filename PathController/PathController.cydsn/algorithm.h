#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdbool.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define DEGREES_TO_RADIANS(deg) ((deg) * M_PI / 180.0)
#define EARTH_RADIUS_METERS 6371000.0

typedef struct
{
    double lat;
    double lon;
} GPSCoordinate_t;

typedef struct
{
    GPSCoordinate_t target_pos;
    double p_gain;
    double max_pitch_cmd;
    double max_roll_cmd;
    double distance_threshold;
} DroneNavigator_t;

double haversine_distance(GPSCoordinate_t pos1, GPSCoordinate_t pos2);

void navigator_init(DroneNavigator_t *nav, double target_lat, double target_lon, double p_gain, double max_pitch, double max_roll, double dist_thresh);

bool navigator_update(DroneNavigator_t *nav, GPSCoordinate_t current_pos, double drone_heading_degress, double dt, double *out_pitch_cmd, double *out_roll_cmd);

#endif