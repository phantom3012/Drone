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

#ifndef SANITIZE_H
#define SANITIZE_H

#include <stdint.h>

typedef struct
{
    int32_t lat_dege6;
    int32_t lon_dege6;
    int32_t is_valid;
} GpsData_t;

int parse_gps(char *gps_string, GpsData_t *gps_data);

#endif

/* [] END OF FILE */
