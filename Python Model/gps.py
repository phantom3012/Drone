import random
import math


class GPS:
    """
    A class to simulate a GPS module. It provides a fixed target
    coordinate and can generate random starting positions.
    """

    def __init__(self):
        """Initializes the GPS with a fixed target coordinate."""
        # Target is a fixed point (e.g., a landmark in Madison, WI)
        self.target_lat = 43.074722
        self.target_lon = -89.384167

    def get_target_coordinates(self):
        """
        Returns the fixed target GPS coordinates.
        :return: A tuple of (latitude, longitude).
        """
        return self.target_lat, self.target_lon

    def get_random_start_position(self, min_radius_meters=3,
                                  max_radius_meters=10):
        """
        Generates a random latitude and longitude within a specified
        distance range of the target coordinate.
        :param min_radius_meters: The minimum distance from the target.
        :param max_radius_meters: The maximum distance from the target.
        :return: A tuple of (latitude, longitude).
        """
        # Earth's radius in meters
        R = 6378137
        origin_lat = self.target_lat
        origin_lon = self.target_lon

        # Random distance and bearing
        distance = random.uniform(min_radius_meters, max_radius_meters)
        bearing = random.uniform(0, 2 * math.pi)

        # Convert origin to radians
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

        return math.degrees(lat2), math.degrees(lon2)
