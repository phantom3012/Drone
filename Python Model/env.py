import random

# Define the maximum wind speed cap based on previous conversion
# (500 cm/s is approx. 11.18 mph)
MAX_ALLOWABLE_WIND_MPH = 11.18


class Pilot:
    """
    Simulates a human pilot providing smoothly changing pitch and roll
    commands.
    """
    def __init__(self, max_pitch=15.0, max_roll=15.0,
                 pitch_slew_rate=10.0, roll_slew_rate=15.0):
        """
        Initializes the pilot with command limits and slew rates.
        """
        self.max_pitch = max_pitch
        self.max_roll = max_roll
        self.pitch_slew_rate = pitch_slew_rate  # deg/s
        self.roll_slew_rate = roll_slew_rate    # deg/s

        # Initialize current and target commands
        self.current_pitch = random.uniform(-self.max_pitch, self.max_pitch)
        self.current_roll = random.uniform(-self.max_roll, self.max_roll)
        self.target_pitch = self.current_pitch
        self.target_roll = self.current_roll

    def update_commands(self, dt):
        """
        Updates the pilot's commands for the current time step, moving
        them smoothly towards a new random target.
        :param dt: Time delta for the update.
        :return: A tuple of (current_pitch, current_roll).
        """
        # Small chance to pick a new target command on each step
        if random.random() < 0.05:  # 5% chance per step
            self.target_pitch = random.uniform(-self.max_pitch, self.max_pitch)
            self.target_roll = random.uniform(-self.max_roll, self.max_roll)

        # --- Apply Slew Rate Limiting ---
        pitch_error = self.target_pitch - self.current_pitch
        roll_error = self.target_roll - self.current_roll

        max_pitch_change = self.pitch_slew_rate * dt
        max_roll_change = self.roll_slew_rate * dt

        pitch_change = max(-max_pitch_change,
                           min(pitch_error, max_pitch_change))
        roll_change = max(-max_roll_change,
                          min(roll_error, max_roll_change))

        self.current_pitch += pitch_change
        self.current_roll += roll_change

        return self.current_pitch, self.current_roll


class WindModel:
    """
    Simulates gradually changing wind speed and direction.
    """
    def __init__(self, min_speed_mph=5.0, max_speed_mph=10.0,
                 speed_slew_rate=0.2, bearing_slew_rate=3.0):
        """
        Initializes the wind model.
        :param min_speed_mph: Minimum wind speed in mph.
        :param max_speed_mph: Maximum wind speed in mph.
        :param speed_slew_rate: Max change in speed per second (mph/s).
        :param bearing_slew_rate: Max change in bearing per second (deg/s).
        """
        self.min_speed = min_speed_mph
        self.max_speed = max_speed_mph
        self.speed_slew_rate = speed_slew_rate
        self.bearing_slew_rate = bearing_slew_rate

        # Initialize current and target values
        self.current_speed_mph = random.uniform(self.min_speed, self.max_speed)
        self.current_bearing_deg = random.uniform(0, 359)
        self.target_speed_mph = self.current_speed_mph
        self.target_bearing_deg = self.current_bearing_deg

    def update(self, dt):
        """Updates wind, moving smoothly towards a new random target."""
        # Small chance to pick a new target
        if random.random() < 0.01:  # 1% chance per step
            self.target_speed_mph = random.uniform(
                self.min_speed, self.max_speed
            )
            self.target_bearing_deg = random.uniform(0, 359)

        # Slew speed towards target
        speed_error = self.target_speed_mph - self.current_speed_mph
        max_speed_change = self.speed_slew_rate * dt
        speed_change = max(
            -max_speed_change,
            min(speed_error, max_speed_change)
        )
        self.current_speed_mph += speed_change

        # Slew bearing towards target, handling 360-degree wraparound
        bearing_error = self.target_bearing_deg - self.current_bearing_deg
        if bearing_error > 180:
            bearing_error -= 360
        elif bearing_error < -180:
            bearing_error += 360

        max_bearing_change = self.bearing_slew_rate * dt
        bearing_change = max(
            -max_bearing_change,
            min(bearing_error, max_bearing_change)
        )
        self.current_bearing_deg = (
            self.current_bearing_deg + bearing_change + 360
        ) % 360

        return self.current_speed_mph, self.current_bearing_deg


def generate_environment_inputs():
    """
    Generates random environmental parameters for the simulation start.
    Returns:
        A dictionary containing:
        - 'initial_heading': Random drone orientation as an integer (0-359).
        - 'wind_model': An instance of the WindModel for dynamic wind.
    """
    initial_heading = random.randint(0, 359)

    return {
        'initial_heading': initial_heading,
        'wind_model': WindModel(),
    }
