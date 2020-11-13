from rot2D import *

input_theta = 3.926


rot = rot2D(input_theta)
print(rot)


input_theta = 0


rot_tmp = rot2D(input_theta)
print(rot_tmp)

final_rot = rot @ rot_tmp
print("Final")
print(final_rot)
