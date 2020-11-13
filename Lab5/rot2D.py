import numpy as np

# Create XYZ rotation matrix from ax, ay, az (radian) rotations
def rot2D(az):
    # cos and sin defines
    sz = np.sin(az)
    cz = np.cos(az)

    # print("S: {} C: {}".format(sz, cz))

    # Define 2D rotation matricies
    Rot_z = np.array([[cz,-sz], [sz,cz]])

    
    # Combine all 3 in (x -> y -> z) order
    # Rot = Rot_z @ Rot_y @ Rot_x
    # print("ROTATION:")
    # print(Rot_z)
    return Rot_z