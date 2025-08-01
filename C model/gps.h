/* ========================================
 * gps_parser.h
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
#ifndef GPS_PARSER_H
#define GPS_PARSER_H

#include <stdint.h> // For int32_t
#include <stdbool.h> // For bool

/**
 * @brief Holds parsed and validated GPS data.
 *
 * Latitude and longitude are stored as signed 32-bit integers in
 * scaled degrees (degrees * 1,000,000). This avoids floating-point
 * math and provides precision to ~11cm.
 *
 * Example: 43.123456 degrees becomes 43123456.
 * A negative value indicates South/West hemisphere.
 */
typedef struct {
    uint32_t latitude_dege6;
    uint32_t longitude_dege6;
    bool is_valid;
} GpsData_t;

/**
 * @brief Parses a raw NMEA $GNGLL sentence.
 *
 * @param nmea_sentence The null-terminated string containing the full NMEA sentence.
 * @param gps_data Pointer to a GpsData_t struct where the parsed data will be stored.
 * @return true if parsing was successful and the data is valid ('A').
 * @return false if the sentence is malformed or the data is invalid ('V').
 */
bool gps_parse_gngll(const char* nmea_sentence, GpsData_t* gps_data);


#endif /* GPS_PARSER_H */

/* [] END OF FILE */

