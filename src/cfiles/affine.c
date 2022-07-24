#include "affine.h"

#include <math.h>

#include "objfiles.h"

void moveXYZ(model *model, double ax, double ay, double az) {
  if (ax) {
    for (int i = 0; i < model->v_num / 3; i++) {
      model->vertexes[3 * i] += ax;
    }
  }
  if (ay) {
    for (int i = 0; i < model->v_num / 3; i++) {
      model->vertexes[3 * i + 1] += ay;
    }
  }
  if (az) {
    for (int i = 0; i < model->v_num / 3; i++) {
      model->vertexes[3 * i + 2] += az;
    }
  }
}

void rotationX(model *model, double angle) {
  for (int i = 0; i < model->v_num / 3; i++) {
    double y = model->vertexes[3 * i + 1];
    double z = model->vertexes[3 * i + 2];
    model->vertexes[3 * i + 1] = cos(angle) * y - sin(angle) * z;
    model->vertexes[3 * i + 2] = sin(angle) * y + cos(angle) * z;
  }
}

void rotationY(model *model, double angle) {
  for (int i = 0; i < model->v_num / 3; i++) {
    double x = model->vertexes[3 * i];
    double z = model->vertexes[3 * i + 2];
    model->vertexes[3 * i] = cos(angle) * x + sin(angle) * z;
    model->vertexes[3 * i + 2] = -sin(angle) * x + cos(angle) * z;
  }
}

void rotationZ(model *model, double angle) {
  for (int i = 0; i < model->v_num / 3; i++) {
    double x = model->vertexes[3 * i];
    double y = model->vertexes[3 * i + 1];
    model->vertexes[3 * i] = cos(angle) * x - sin(angle) * y;
    model->vertexes[3 * i + 1] = cos(angle) * y + sin(angle) * x;
  }
}

void scale(model *model, double s) {
  for (int i = 0; i < model->v_num; i++) {
    model->vertexes[i] *= s;
  }
}
