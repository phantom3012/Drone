/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
 */

#include "sanitize.h"
#include <string.h>
#include <stdlib.h>

int32_t convert_coord_dege6(const char *coord)
{
    if (coord == NULL || *coord == '\0')
    {
        return 0;
    }
    const char *dot = strchr(coord, '.');
    if (dot == NULL)
    {
        return 0;
    }

    int min_start = (int)(dot - coord) - 2;
    char deg_str[5] = {0};
    strncpy(deg_str, coord, min_start);
    int32_t degrees = (int32_t)strtol(deg_str, NULL, 10);

    char min_str[8] = {0};
    strncpy(min_str, coord + min_start, 2);
    strncpy(min_str + 2, dot + 1, 4);
    int32_t decimal_mins_scaled = (int32_t)strtol(min_str, NULL, 10);
    int32_t minutes_as_dege6 = (decimal_mins_scaled * 10L) / 6;

    return (degrees * 1000000L) + minutes_as_dege6;
}

int parse_gps(char *gps_string, GpsData_t *gps_data)
{
    if (gps_string == NULL || gps_data == NULL)
    {
        return 0;
    }

    char buffer[100];
    strncpy(buffer, gps_string, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char *saveptr;
    char *token;

    token = strtok_r(buffer, ",", &saveptr);
    if (token == NULL || strcmp(token, "$GNGLL") != 0)
    {
        return 0;
    }

    char *lat_str = strtok_r(NULL, ",", &saveptr);
    char *ns_str = strtok_r(NULL, ",", &saveptr);
    char *lon_str = strtok_r(NULL, ",", &saveptr);
    char *ew_str = strtok_r(NULL, ",", &saveptr);
    strtok_r(NULL, ",", &saveptr);

    char *status = strtok_r(NULL, ",", &saveptr);
    if (status == NULL || *status != 'A' || lat_str == NULL || lon_str == NULL || lat_str[0] == '\0' || lon_str[0] == '\0')
    {
        gps_data->is_valid = 0;
        gps_data->lat_dege6 = 0;
        gps_data->lon_dege6 = 0;
        return 0;
    }

    gps_data->lat_dege6 = convert_coord_dege6(lat_str);
    if (ns_str != NULL && *ns_str == 'S')
        gps_data->lat_dege6 *= -1;

    gps_data->lon_dege6 = convert_coord_dege6(lon_str);
    if (ew_str != NULL && *ew_str == 'W')
        gps_data->lon_dege6 *= -1;

    if (gps_data->lat_dege6 == 0 || gps_data->lon_dege6 == 0)
    {
        gps_data->is_valid = 0;
        gps_data->lat_dege6 = 0;
        gps_data->lon_dege6 = 0;
        return 0;
    }

    gps_data->is_valid = 1;
    return 1;
}

/* [] END OF FILE */
