# take inputs: head wind, right wind (from env.py), yaw, pitch,\\
# roll (from mux.py)
# spit forward speed and right speed
# forward and right speed is fed to the motors through the motor controller
# pitch and roll are directly forwarded to the path controller
# calculate fwd speed/ right speed as the relative speed of the drone

# implement yaw to heading conversion
# spit new yaw
# this yaw should be fed to virus
