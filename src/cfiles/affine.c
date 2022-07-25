/**
 * @file affine.c
 * @brief Affine transformations of matrices
 * @version 0.1
 * @date 2022-07-25
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "affine.h"

#include <math.h>

#include "objfiles.h"

/**
 * @param brief Model shift along the X, Y, Z axes
 *
 * @param model 3D model
 * @param ax X offset
 * @param ay Y offset
 * @param az Z offset
 *
 */
void moveXYZ(model *model, double ax, double ay, double az) {
    if (ax) {
        for (unsigned int i = 0; i < model->v_num / 3; i++) {
            model->vertexes[3 * i] += ax;
        }
    }
    if (ay) {
        for (unsigned int i = 0; i < model->v_num / 3; i++) {
            model->vertexes[3 * i + 1] += ay;
        }
    }
    if (az) {
        for (unsigned int i = 0; i < model->v_num / 3; i++) {
            model->vertexes[3 * i + 2] += az;
        }
    }
}

/**
 * @brief Rotation of the model around the X axis
 *
 * @param model 3D model
 * @param angle angle of rotation in radians
 */
void rotationX(model *model, double angle) {
    for (unsigned int i = 0; i < model->v_num / 3; i++) {
        double y = model->vertexes[3 * i + 1];
        double z = model->vertexes[3 * i + 2];
        model->vertexes[3 * i + 1] = cos(angle) * y - sin(angle) * z;
        model->vertexes[3 * i + 2] = sin(angle) * y + cos(angle) * z;
    }
}

/**
 * @brief Rotation of the model around the Y axis
 *
 * @param model 3D model
 * @param angle angle of rotation in radians
 */
void rotationY(model *model, double angle) {
    for (unsigned int i = 0; i < model->v_num / 3; i++) {
        double x = model->vertexes[3 * i];
        double z = model->vertexes[3 * i + 2];
        model->vertexes[3 * i] = cos(angle) * x + sin(angle) * z;
        model->vertexes[3 * i + 2] = -sin(angle) * x + cos(angle) * z;
    }
}

/**
 * @brief Rotation of the model around the Z axis
 *
 * @param model 3D model
 * @param angle angle of rotation in radians
 */
void rotationZ(model *model, double angle) {
    for (unsigned int i = 0; i < model->v_num / 3; i++) {
        double x = model->vertexes[3 * i];
        double y = model->vertexes[3 * i + 1];
        model->vertexes[3 * i] = cos(angle) * x - sin(angle) * y;
        model->vertexes[3 * i + 1] = cos(angle) * y + sin(angle) * x;
    }
}

/**
 * @brief Model scaling by a value
 *
 * @param model 3D model
 * @param s scale value
 */
void scale(model *model, double s) {
    for (unsigned int i = 0; i < model->v_num; i++) {
        model->vertexes[i] *= s;
    }
}
