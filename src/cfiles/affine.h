#ifndef _AFFINE_H_
#define _AFFINE_H_
#include "objfiles.h"

void moveXYZ(model *model, double ax, double ay, double az);
void rotationX(model *model, double angle);
void rotationY(model *model, double angle);
void rotationZ(model *model, double angle);
void scale(model *model, double s);

#endif  // _AFFINE_H_
