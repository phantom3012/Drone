import math
import time
from gps import GPS

# --- PID Controller Class ---


class SimplePID:
    """A simple Proportional-Integral-Derivative (PID) controller."""

    def __init__(self, kp, ki, kd, setpoint,
                 output_limits=(-1.0, 1.0),
                 integral_limits=(-1.0, 1.0),
                 name="PID"):
        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.setpoint = setpoint
        self.output_limits = output_limits
        self.integral_limits = integral_limits
        self.name = name
        self._integral = 0.0
        self._previous_error = 0.0
        self._last_time = None

    def update(self, current_value, dt=None):
        """Calculates PID output."""
        if dt is None:
            current_time = time.monotonic()
            # On the first call, dt is unknown. Skip the update this frame.
            if self._last_time is None:
                self._last_time = current_time
                return 0.0
            dt_calc = current_time - self._last_time
            self._last_time = current_time
            dt_to_use = max(dt_calc, 1e-6)
        else:
            dt_to_use = dt

        if dt_to_use <= 0:
            return 0.0

        error = self.setpoint - current_value
        p_out = self.kp * error
        self._integral += error * dt_to_use
        self._integral = self._clamp(self._integral, self.integral_limits)
        i_out = self.ki * self._integral
        derivative = (error - self._previous_error) / dt_to_use
        d_out = self.kd * derivative
        output = p_out + i_out + d_out
        output = self._clamp(output, self.output_limits)
        self._previous_error = error
        return output

    def reset(self):
        """Resets the PID controller's internal states."""
        self._integral = 0.0
        self._previous_error = 0.0
        self._last_time = None

    def _clamp(self, value, limits):
        """Clamps a value between lower and upper limits."""
        lower, upper = limits
        return max(lower, min(value, upper))

# --- Drone Navigation Controller (Fixed Yaw) ---


class DroneNavigator:
    """Navigates a drone with a fixed yaw to target GPS coordinates."""

    def __init__(self, target_lat, target_lon, control_gain,
                 max_pitch_cmd=15.0,
                 max_roll_cmd=15.0,
                 distance_threshold=5.0):
        self.target_lat = target_lat
        self.target_lon = target_lon
        self.control_gain = control_gain  # New single gain parameter
        self.max_pitch_cmd = max_pitch_cmd
        self.max_roll_cmd = max_roll_cmd
        self.distance_threshold = distance_threshold

    def update(self, current_lat, current_lon,
               fixed_drone_heading_degrees, dt_external=None):
        """Calculates pitch and roll commands to navigate."""
        distance = GPS.haversine_distance(
            current_lat, current_lon, self.target_lat, self.target_lon)
        if distance < self.distance_threshold:
            return 0.0, 0.0, True

        bearing_to_target_deg = GPS.calculate_bearing(
            current_lat, current_lon, self.target_lat, self.target_lon
        )
        bearing_rad = math.radians(bearing_to_target_deg)
        heading_rad = math.radians(fixed_drone_heading_degrees)

        relative_bearing_rad = math.atan2(
            math.sin(bearing_rad - heading_rad),
            math.cos(bearing_rad - heading_rad))

        error_forward = distance * math.cos(relative_bearing_rad)
        error_right = distance * math.sin(relative_bearing_rad)

        # --- Non-linear atan() control law ---
        # Use atan to convert large error distances into a bounded, normalized
        # command. The output of atan(x) is in radians [-pi/2, pi/2].
        # We normalize it to [-1, 1] by dividing by (pi/2).
        pitch_norm = (
            math.atan(self.control_gain * error_forward) / (math.pi / 2)
        )
        roll_norm = math.atan(self.control_gain * error_right) / (math.pi / 2)

        # Scale the normalized command to the desired angle
        pitch_cmd = pitch_norm * self.max_pitch_cmd
        roll_cmd = roll_norm * self.max_roll_cmd

        return pitch_cmd, roll_cmd, False
