#ifndef _OBJFILES_H_
#define _OBJFILES_H_

#define RECORD_SIZE 1000


typedef struct {
    // количество вершин и отрезков
    unsigned int v_num;
    unsigned int f_num;
    // массивы вершин и отрезков
    float *vertexes;
    unsigned int *faces;
    // границы размеров
    float x_min;
    float x_max;
    float y_min;
    float y_max;
    float z_min;
    float z_max;
} model;


unsigned int scan_vertexes(char *str, float* vertexes);
unsigned int scan_faces(char *str, unsigned int *faces);
model load_model(const char *filename);

#endif  // _OBJFILES_H_
