#ifndef SRC_CFILES_AFFINE_H_
#define SRC_CFILES_AFFINE_H_
#include "objfiles.h"

void moveXYZ(model *model, double ax, double ay, double az);
void rotationX(model *model, double angle);
void rotationY(model *model, double angle);
void rotationZ(model *model, double angle);
void scale(model *model, double s);

#endif  // SRC_CFILES_AFFINE_H_
