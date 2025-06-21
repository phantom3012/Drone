class Mux:
    """
    A multiplexer to select between pilot commands and autopilot (VIRUS)
    commands.
    """

    def __init__(self):
        """Initializes the Mux."""
        # No state is needed for a simple command selector.
        pass

    def select_commands(self, pilot_pitch, pilot_roll,
                        virus_pitch, virus_roll,
                        autopilot_enabled):
        """
        Selects the pitch and roll commands based on autopilot status.

        :param pilot_pitch: The pitch command from the pilot/environment.
        :param pilot_roll: The roll command from the pilot/environment.
        :param virus_pitch: The pitch command from the VIRUS controller.
        :param virus_roll: The roll command from the VIRUS controller.
        :param autopilot_enabled: A boolean to switch between modes.
        :return: A tuple of the selected (pitch, roll) commands.
        """
        if autopilot_enabled:
            # If autopilot is on, use commands from the VIRUS system
            return virus_pitch, virus_roll
        else:
            # If autopilot is off, use commands from the pilot
            return pilot_pitch, pilot_roll
