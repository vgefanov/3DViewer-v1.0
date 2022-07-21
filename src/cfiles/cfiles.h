#ifndef _USERS_FARFETCH_OPENGL_INCLUDES_INCLUDES_H_
#define _USERS_FARFETCH_OPENGL_INCLUDES_INCLUDES_H_

#define RECORD_SIZE 1000


typedef struct {
    unsigned int v_num;
    unsigned int f_num;
    float *vertexes;
    unsigned int *faces;
    float min_x;
    float max_x;
    float min_y;
    float max_y;
    float min_z;
    float max_z;
} model;


unsigned int scan_vertexes(char *str, float* vertexes);
unsigned int scan_faces(char *str, unsigned int *faces);
model load_model(const char *filename);
model load_model_tr(const char *filename);

#endif  // _USERS_FARFETCH_OPENGL_INCLUDES_INCLUDES_H_
