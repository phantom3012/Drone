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

    def get_random_start_position(self, min_radius_meters=100,
                                  max_radius_meters=300):
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

    @staticmethod
    def haversine_distance(lat1, lon1, lat2, lon2):
        """
        Calculate the great circle distance in meters between two points
        on the earth (specified in decimal degrees).
        """
        radius_earth = 6371000  # In meters
        phi1 = math.radians(lat1)
        phi2 = math.radians(lat2)
        delta_phi = math.radians(lat2 - lat1)
        delta_lambda = math.radians(lon2 - lon1)

        a = (math.sin(delta_phi / 2.0)**2 +
             math.cos(phi1) * math.cos(phi2) *
             math.sin(delta_lambda / 2.0)**2)
        c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
        distance = radius_earth * c
        return distance

    @staticmethod
    def calculate_bearing(lat1, lon1, lat2, lon2):
        """
        Calculates the initial bearing in degrees from point 1 to point 2.
        """
        phi1 = math.radians(lat1)
        lambda1 = math.radians(lon1)
        phi2 = math.radians(lat2)
        lambda2 = math.radians(lon2)
        y = math.sin(lambda2 - lambda1) * math.cos(phi2)
        x = (math.cos(phi1) * math.sin(phi2) -
             math.sin(phi1) * math.cos(phi2) * math.cos(lambda2 - lambda1))
        return (math.degrees(math.atan2(y, x)) + 360) % 360
