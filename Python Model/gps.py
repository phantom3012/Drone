# spit out a fixed GPS value
# Will be set to const for now but can be modelled to grab input from the GPS\\
# module later

import random
import math


def generate_random_coordinate_within_500m():
    """
    Generates a random latitude and longitude within 500 meters of the origin:
    Origin: 43.0653950N, 89.2803402W
    Returns:
        tuple: (latitude, longitude)
    """
    # Earth's radius in meters
    R = 6378137
    # Origin coordinates in degrees
    origin_lat = 43.0653950
    origin_lon = -89.2803402

    # Random distance in meters (0 to 500)
    distance = random.uniform(0, 500)
    # Random bearing in radians (0 to 2*pi)
    bearing = random.uniform(0, 2 * math.pi)

    # Convert origin latitude to radians
    lat1 = math.radians(origin_lat)
    lon1 = math.radians(origin_lon)

    # Calculate new latitude
    lat2 = math.asin(
        math.sin(lat1) * math.cos(distance / R) +
        math.cos(lat1) * math.sin(distance / R) * math.cos(bearing)
    )

    # Calculate new longitude
    lon2 = lon1 + math.atan2(
        math.sin(bearing) * math.sin(distance / R) * math.cos(lat1),
        math.cos(distance / R) - math.sin(lat1) * math.sin(lat2)
    )

    # Convert back to degrees
    new_lat = math.degrees(lat2)
    new_lon = math.degrees(lon2)

    return (new_lat, new_lon)
