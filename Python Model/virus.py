import math
from gps import GPS

# --- Drone Navigation Controller (Fixed Yaw) ---


class DroneNavigator:
    """Navigates a drone with a fixed yaw to target GPS coordinates."""

    def __init__(self, target_lat, target_lon, p_gain, ki_gain,
                 max_pitch_cmd=15.0,
                 max_roll_cmd=15.0,
                 distance_threshold=5.0,
                 max_i_contribution_ratio=0.75):
        self.target_lat = target_lat
        self.target_lon = target_lon
        self.p_gain = p_gain      # Proportional gain for the atan() term
        self.ki_gain = ki_gain    # Gain for the non-linear tanh() integral term
        self.max_i_contribution_ratio = max_i_contribution_ratio
        self.max_pitch_cmd = max_pitch_cmd
        self.max_roll_cmd = max_roll_cmd
        self.distance_threshold = distance_threshold

        # Integral state variables
        self._integral_forward = 0.0
        self._integral_right = 0.0
        self._is_active = False  # Controller is inactive by default

    def _clamp(self, value, limits):
        """Clamps a value between lower and upper limits."""
        lower, upper = limits
        return max(lower, min(value, upper))

    def reset(self):
        """Resets the controller's integral states."""
        self._integral_forward = 0.0
        self._integral_right = 0.0

    def set_active(self, is_active):
        """
        Activates or deactivates the controller. Resets integral state upon
        activation to ensure a clean start.
        """
        if is_active and not self._is_active:
            self.reset()
        self._is_active = is_active

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

        # --- Proportional-Integral (PI) Control Law ---

        # P-Term: Non-linear proportional term using atan()
        # This provides a responsive but bounded command.
        pitch_p_term = (
            math.atan(self.p_gain * error_forward) / (math.pi / 2)
        ) * self.max_pitch_cmd
        roll_p_term = (
            math.atan(self.p_gain * error_right) / (math.pi / 2)
        ) * self.max_roll_cmd

        # I-Term: Accumulate error over time to overcome steady-state error
        # The tanh function provides a slow, smooth rise and natural anti-windup.
        # Accumulation only happens when the controller is active.
        if self._is_active and dt_external and dt_external > 0:
            self._integral_forward += error_forward * dt_external
            self._integral_right += error_right * dt_external

        # The I-term's output is shaped by tanh and scaled. Its maximum
        # authority is limited by max_i_contribution_ratio to leave
        # headroom for the P-term.
        max_pitch_i_cmd = self.max_pitch_cmd * self.max_i_contribution_ratio
        max_roll_i_cmd = self.max_roll_cmd * self.max_i_contribution_ratio

        pitch_i_term = max_pitch_i_cmd * math.tanh(
            self.ki_gain * self._integral_forward)
        roll_i_term = max_roll_i_cmd * math.tanh(
            self.ki_gain * self._integral_right)

        # Final command is the sum of P and I terms, clamped to max limits
        pitch_cmd = self._clamp(pitch_p_term + pitch_i_term,
                                (-self.max_pitch_cmd, self.max_pitch_cmd))
        roll_cmd = self._clamp(roll_p_term + roll_i_term,
                               (-self.max_roll_cmd, self.max_roll_cmd))

        return pitch_cmd, roll_cmd, False
