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
            if self._last_time is None:
                dt_calc = 0.01
            else:
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

    def __init__(self, target_lat, target_lon,
                 kp_pitch, ki_pitch, kd_pitch,
                 kp_roll, ki_roll, kd_roll,
                 max_pitch_cmd=15.0,
                 max_roll_cmd=15.0,
                 distance_threshold=5.0):
        self.target_lat = target_lat
        self.target_lon = target_lon
        self.max_pitch_cmd = max_pitch_cmd
        self.max_roll_cmd = max_roll_cmd
        self.distance_threshold = distance_threshold

        self.pitch_pid = SimplePID(
            kp_pitch, ki_pitch, kd_pitch, setpoint=0.0,
            output_limits=(-1.0, 1.0), integral_limits=(-50.0, 50.0),
            name="Pitch (Forward Error)"
        )
        self.roll_pid = SimplePID(
            kp_roll, ki_roll, kd_roll, setpoint=0.0,
            output_limits=(-1.0, 1.0), integral_limits=(-50.0, 50.0),
            name="Roll (Rightward Error)"
        )

    def update(self, current_lat, current_lon,
               fixed_drone_heading_degrees, dt_external=None):
        """Calculates pitch and roll commands to navigate."""
        dt = dt_external if dt_external is not None else 0.1
        distance = GPS.haversine_distance(
            current_lat, current_lon, self.target_lat, self.target_lon)
        if distance < self.distance_threshold:
            self.pitch_pid.reset()
            self.roll_pid.reset()
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

        pitch_norm = self.pitch_pid.update(error_forward, dt=dt)
        pitch_cmd = -pitch_norm * self.max_pitch_cmd

        roll_norm = self.roll_pid.update(error_right, dt=dt)
        roll_cmd = -roll_norm * self.max_roll_cmd

        return pitch_cmd, roll_cmd, False
