#include "objfiles.h"

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int scan_vertexes(char *str, float *vertexes) {
  unsigned int result = 0;
  char *start = str + 1;
  char *endptr;
  while (*start) {
    for (; *start == ' ' && (*start != 0); start++) {
    }
    if (*start != 0) {
      if (vertexes != NULL) {
        vertexes[result] = strtod(start, &endptr);
        start = endptr;
      }
      result++;
    }
    for (; (*start != ' ') && (*start != 0); start++) {
    }
  }
  return result;
}

unsigned int scan_faces(char *str, unsigned int *faces) {
  unsigned int result = 0;
  char *start = str + 1;
  char *endptr = str + strlen(str) - 1;
  for (; (*endptr < '0') && (*endptr != 0); *endptr-- = 0) {
  }
  while (*start) {
    for (; *start == ' ' && (*start != 0); start++) {
    }
    if (*start != 0) {
      if (faces != NULL) {
        faces[result] = (unsigned int)strtol(start, &endptr, 10) - 1;
        start = endptr;
      }
      result++;
    }
    for (; (*start != ' ') && (*start != 0); start++) {
    }
  }
  return result;
}

model load_model(const char *filename) {
  char record[RECORD_SIZE];
  model result = {0,       0,       NULL,    NULL,    FLT_MAX,
                  FLT_MIN, FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN};
  FILE *model_fp = fopen(filename, "r");
  // вычисляем размер массива
  while (fgets(record, RECORD_SIZE - 1, model_fp) != NULL) {
    if (record[0] == 'v' && record[1] == ' ') {
      result.v_num += scan_vertexes(record, NULL);
    }
    if (record[0] == 'f' && record[1] == ' ') {
      result.f_num += scan_faces(record, NULL) * 2;
    }
  }
  // считываем данные
  fseek(model_fp, 0, SEEK_SET);
  result.vertexes = calloc(result.v_num, sizeof(float));
  result.faces = calloc(result.f_num, sizeof(unsigned int));
  float *v_ptr = result.vertexes;
  unsigned pos = 0;
  while (fgets(record, RECORD_SIZE - 1, model_fp) != NULL) {
    if (record[0] == 'v' && record[1] == ' ') {
      unsigned int v_num = scan_vertexes(record, v_ptr);
      if (v_ptr[0] < result.x_min) result.x_min = v_ptr[0];
      if (v_ptr[0] > result.x_max) result.x_max = v_ptr[0];
      if (v_ptr[1] < result.y_min) result.y_min = v_ptr[1];
      if (v_ptr[1] > result.y_max) result.y_max = v_ptr[1];
      if (v_ptr[2] < result.z_min) result.z_min = v_ptr[2];
      if (v_ptr[2] > result.z_max) result.z_max = v_ptr[2];
      v_ptr += v_num;
    }
    if (record[0] == 'f' && record[1] == ' ') {
      unsigned int tmp[100];
      unsigned int f_num = scan_faces(record, tmp);
      for (unsigned int i = 0; i < f_num; i++) {
        result.faces[pos + 2 * i] = *(tmp + i);
        result.faces[pos + 2 * i + 1] = *(tmp + (i + 1) % f_num);
      }
      pos += f_num * 2;
    }
  }
  fclose(model_fp);
  return result;
}

void release_model(model model) {
    if (model.vertexes) {
        free(model.vertexes);
    }
    if (model.faces) {
        free(model.faces);
    }
}
