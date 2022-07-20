#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cfiles.h"


unsigned int scan_vertexes(char *str, float *vertexes) {
    unsigned int result = 0;
    char* start = str + 1;
    char* endptr;
    while (*start) {
        for (; *start == ' ' && (*start != 0); start++) {}
        if (*start != 0) {
            if (vertexes != NULL) {
                vertexes[result] = strtod(start, &endptr);
                start = endptr;
            }
            result++;
        }
        for (; (*start != ' ') && (*start != 0); start++) {}
    }
    return result;
}


unsigned int scan_faces(char *str, unsigned int *faces) {
    unsigned int result = 0;
    char* start = str + 1;
    char* endptr = str + strlen(str) - 1;
    for (; (*endptr < '0') && (*endptr != 0); *endptr-- = 0) {}
    while (*start) {
        for (; *start == ' ' && (*start != 0); start++) {}
        if (*start != 0) {
            if (faces != NULL) {
                faces[result] = (unsigned int)strtol(start, &endptr, 10) - 1;
                start = endptr;
            }
            result++;
        }
        for (; (*start != ' ') && (*start != 0); start++) {}
    }
    return result;
}


model load_model(const char *filename) {
    char record[RECORD_SIZE];
    model result = { 0, 0, NULL, NULL };
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
            v_ptr += scan_vertexes(record, v_ptr);
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
    printf("Vertexes: %u\n", result.v_num);
    printf("Faces: %u\n", result.f_num);
    fclose(model_fp);
    return result;
}


model load_model_tr(const char *filename) {
    char record[RECORD_SIZE];
    model result = { 0, 0, NULL, NULL };
    FILE *model_fp = fopen(filename, "r");
    // вычисляем размер массива
    while (fgets(record, RECORD_SIZE - 1, model_fp) != NULL) {
        if (record[0] == 'v' && record[1] == ' ') {
            result.v_num += scan_vertexes(record, NULL);
        }
        if (record[0] == 'f' && record[1] == ' ') {
            unsigned int f_num = scan_faces(record, NULL);
            if (f_num > 2) {
                result.f_num += 3 * (scan_faces(record, NULL) - 2);
            } else {
                result.f_num += 3;
            }
        }
    }
    // считываем данные
    fseek(model_fp, 0, SEEK_SET);
    result.vertexes = calloc(result.v_num, sizeof(float));
    result.faces = calloc(result.f_num, sizeof(unsigned int));
    unsigned pos = 0;
    float *v_ptr = result.vertexes;
    while (fgets(record, RECORD_SIZE - 1, model_fp) != NULL) {
        if (record[0] == 'v' && record[1] == ' ') {
            v_ptr += scan_vertexes(record, v_ptr);
        }
        if (record[0] == 'f' && record[1] == ' ') {
            // manually generate a triangle-fan
            unsigned int tmp[100];
            unsigned int f_num = scan_faces(record, tmp);
            if (f_num > 2) {
                for (unsigned int x = 1; x < (f_num - 1); x++) {
                    result.faces[pos++] = tmp[0];
                    result.faces[pos++] = tmp[x];
                    result.faces[pos++] = tmp[x + 1];
                }
            } else {
                result.faces[pos++] = tmp[0];
                result.faces[pos++] = tmp[1];
                result.faces[pos++] = tmp[0];
            }
        }
    }
    printf("Vertexes: %u\n", result.v_num);
    printf("Faces: %u\n", result.f_num);
    fclose(model_fp);
    return result;
}
// void main() {
//     model model = load_model("/Users/farfetch/OpenGL/models/cube.obj");
//     for (int i = 0; i < model.v_num; i++) {
//         printf("%f ", model.vertexes[i]);
//         if ((i + 1) % 3 == 0) printf("\n");
//     }
//     for (int i = 0; i < model.f_num; i++) {
//         printf("%d ", model.faces[i]);
//         if ((i + 1) % 2 == 0) printf("\n");
//     }
// }
