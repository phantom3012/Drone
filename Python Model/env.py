# take no inputs
# spit out a random yaw
# spit out a random pitch and roll to mux.py
# spit out a random headwind and right wind

import random


def generate_environment():
    """
    Generates random environmental parameters:
    - yaw: float in [0, 360)
    - pitch: float in [-15, 15)
    - roll: float in [-25, 25)
    - headwind: float in [0, 50)
    - right_wind: float in [-10, 10)
    Returns:
        dict: {'yaw', 'pitch', 'roll', 'headwind', 'right_wind'}
    """
    yaw = random.randint(0, 359)
    pitch = random.uniform(-15, 15)
    roll = random.uniform(-25, 25)
    headwind = random.uniform(0, 50)
    right_wind = random.uniform(-10, 10)
    return {
        'yaw': yaw,
        'pitch': pitch,
        'roll': roll,
        'headwind': headwind,
        'right_wind': right_wind
    }
