from rot2D import rot2D
import numpy as np

def trans2D(theta, x,y):
    rotation_mat = rot2D(theta)

    # Get the x, y translation in column form
    translation_vector = np.array([[x,y]]).transpose()

    # Transformation Matrix 3x3
    transformation_mat = np.block([[rotation_mat, translation_vector],[0,0,1]])

    return transformation_mat