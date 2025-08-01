/* ========================================
 * gps_parser.c
 * ========================================
*/
#include "gps.h"
#include <string.h>  // For strtok_r, strchr
#include <stdlib.h>  // For strtol, labs
#include <stdio.h>

#define TEST 0
/**
 * @brief Converts an NMEA coordinate part (DDMM.MMMM or DDDMM.MMMM) to scaled degrees.
 * @param nmea_coord The string part, e.g., "4303.9581".
 * @return The coordinate in scaled degrees (degrees * 1,000,000).
 */
static uint32_t convert_nmea_coord_to_dege6(const char* nmea_coord) {
    if (nmea_coord == NULL || *nmea_coord == '\0') {
        return 0;
    }

    // Find the decimal point
    const char* dot = strchr(nmea_coord, '.');
    if (dot == NULL) {
        return 0; // Malformed
    }

    // --- Extract Degrees ---
    // The minutes part always starts 2 characters before the dot.
    int minute_start_idx = (int)(dot - nmea_coord) - 2;
    char deg_str[5] = {0}; // Max DDD for longitude + null terminator
    strncpy(deg_str, nmea_coord, minute_start_idx);
    int32_t degrees = (int32_t)strtol(deg_str, NULL, 10);

    // --- Extract Decimal Minutes and convert to scaled degrees ---
    // Example: "03.9581" minutes -> we want 39581
    char min_str[8] = {0};
    strncpy(min_str, nmea_coord + minute_start_idx, 2); // "03"
    strncpy(min_str + 2, dot + 1, 4);                  // "9581" -> "039581"
    uint32_t decimal_minutes_scaled = (uint32_t)strtol(min_str, NULL, 10);

    // Convert minutes to degrees, scaled by 1,000,000, avoiding large intermediate values
    // We have minutes scaled by 10^4. We want to convert to degrees scaled by 10^6.
    // The formula is: (minutes_val / 60) * 10^6
    // With our scaled value: ((decimal_minutes_scaled / 10^4) / 60) * 10^6 = (decimal_minutes_scaled * 10) / 6
    uint32_t minutes_as_dege6 = (decimal_minutes_scaled * 10L) / 6;

    return (degrees * 1000000L) + minutes_as_dege6;
}

bool gps_parse_gngll(const char* nmea_sentence, GpsData_t* gps_data) {
    if (nmea_sentence == NULL || gps_data == NULL) {
        return false;
    }

    // Make a mutable copy for strtok_r
    char buffer[100];
    strncpy(buffer, nmea_sentence, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char* saveptr; // For strtok_r
    char* token;

    // 1. Type ($GNGLL)
    token = strtok_r(buffer, ",", &saveptr);
    if (token == NULL || strcmp(token, "$GNGLL") != 0) return false;

    // 2. Latitude (DDMM.MMMM)
    char* lat_str = strtok_r(NULL, ",", &saveptr);

    // 3. N/S Indicator
    char* ns_str = strtok_r(NULL, ",", &saveptr);

    // 4. Longitude (DDDMM.MMMM)
    char* lon_str = strtok_r(NULL, ",", &saveptr);

    // 5. E/W Indicator
    char* ew_str = strtok_r(NULL, ",", &saveptr);

    // 6. UTC Time
    strtok_r(NULL, ",", &saveptr); // Skip

    // 7. Status (A/V)
    // The next field is the status. The final field before the '*' is the mode indicator.
    char* status_str = strtok_r(NULL, ",", &saveptr);
    if (status_str == NULL || *status_str != 'A') {
        gps_data->is_valid = false;
        return false;
    }

    gps_data->latitude_dege6 = convert_nmea_coord_to_dege6(lat_str);
    if (ns_str != NULL && *ns_str == 'S') gps_data->latitude_dege6 *= -1;

    gps_data->longitude_dege6 = convert_nmea_coord_to_dege6(lon_str);
    if (ew_str != NULL && *ew_str == 'W') gps_data->longitude_dege6 *= -1;

    gps_data->is_valid = true;
    return true;
}


int main(void) {
    GpsData_t gps_data;

    char *nmea_sentence = "$GNGLL,4303.9579,N,08916.7900,W,232342.46,A,02";
    gps_parse_gngll(nmea_sentence, &gps_data);
    printf("%d\n",gps_data.latitude_dege6);
    printf("%d\n",gps_data.longitude_dege6);

    char *valid;
    valid = (gps_data.is_valid ? "Valid" : "Invalid");
    printf("%s\n", valid);
    return 0;
}
/* [] END OF FILE */
