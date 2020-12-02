import numpy as np

x = 5
y = 3
z = 1

x2 = 300
y2 = 0


L1= 500
L2= 300
theta1 = 22 *(np.pi/180)
theta2 = -55 *(np.pi/180)

point = np.array((x,y,z)).transpose()
# point_2 = np.array((x2,y2,z)).transpose()


def real_rotation():
    rotation = np.array([[L2*np.cos(theta1 + theta2) + L1*np.cos(theta1)], [L2*np.sin(theta1 + theta2) + L1*np.sin(theta1)]])
    return rotation


# Create XYZ rotation matrix from ax, ay, az (radian) rotations
def rot2D(az):

    az = az *(np.pi/180)
    print("AZ: ", az)
    # cos and sin defines
    sz = np.sin(az) 
    cz = np.cos(az) 

    print("S: {} C: {}".format(sz, cz))

    # Define 2D rotation matricies
   # Define 2D rotation matricies
    Rot_z = np.array([[cz,-sz,0], [sz,cz,0], [0,0,1]])
    print(Rot_z)
    
    # Combine all 3 in (x -> y -> z) order
    # Rot = Rot_z @ Rot_y @ Rot_x
    # print("ROTATION:")
    # print(Rot_z)
    return Rot_z
# def rot2D2(az):

#     az = az *(np.pi/180)
#     print("AZ: ", az)
#     # cos and sin defines
#     sz = np.sin(az) 
#     cz = np.cos(az) 

#     print("S: {} C: {}".format(sz, cz))

#     # Define 2D rotation matricies
#    # Define 2D rotation matricies
#     Rot_z = np.array([[cz,-sz,500], [sz,cz,0], [0,0,0]])
#     print(Rot_z)
    
#     # Combine all 3 in (x -> y -> z) order
#     # Rot = Rot_z @ Rot_y @ Rot_x
#     # print("ROTATION:")
#     # print(Rot_z)
#     return Rot_z

# def rotationMatrix(ax, ay, az):
#     # cos and sin defines
#     sx, sy, sz = np.sin(ax), np.sin(ay), np.sin(az)
#     cx, cy, cz = np.cos(ax), np.cos(ay), np.cos(az)

#     # Define 2D rotation matricies
#     Rot_x = np.array(((1,0,0), (0,cx,-sx), (0,sx,cx)))
#     Rot_y = np.array(((cy,0,sy), (0,1,0), (-sy,0,cy)))
#     Rot_z = np.array(((cz,-sz,0), (sz,cz,0), (0,0,1)))

#     # Combine all 3 in (x -> y -> z) order
#     Rot = Rot_z @ Rot_y @ Rot_x
#     print("ROTATION:")
#     print(Rot)
#     return Rot

def main():
    rotation1 = rot2D(-30)
    # rotation2 = rot2D2(30)
    # final_rotation = rotation1 @ rotation2 

    # step_1 = rotation1 @ point_1
    # step_2 = rotation2 @ step_1
    # rotation = rotationMatrix(-30,0,0)
    new = rotation1 @ point

    # rotation = real_rotation()

    # print(rotation)
    print(new)


if __name__ == "__main__":
    main()
