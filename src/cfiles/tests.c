#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "affine.h"
#include "objfiles.h"

typedef struct {
    char str[100];
    unsigned int result;
    unsigned int faces[10];
} faces_struct;

float move_pack[1000] = {0.55, 0.66,   0.77, 0.55, 0.66,   0.77, 0.55, 0.66,  1.77, 0.55, 1.66,   0.77,
                         0.55, 1.66,   1.77, 1.55, 0.66,   0.77, 1.55, 0.66,  1.77, 1.55, 1.66,   0.77,
                         1.55, 1.66,   1.77, 0,    0,      0,    0,    0,     0,    0,    0,      1,
                         0,    1,      0,    0,    1,      1,    1,    0,     0,    1,    0,      1,
                         1,    1,      0,    1,    1,      1,    0,    0,     123,  0,    0,      123,
                         0,    0,      124,  0,    1,      123,  0,    1,     124,  1,    0,      123,
                         1,    0,      124,  1,    1,      123,  1,    1,     124,  0,    -0.999, 0,
                         0,    -0.999, 0,    0,    -0.999, 1,    0,    0.001, 0,    0,    0.001,  1,
                         1,    -0.999, 0,    1,    -0.999, 1,    1,    0.001, 0,    1,    0.001,  1};

faces_struct faces_pack[] = {
    {"f 1 7 5", 3, {0, 6, 4}},
    {"f  1/2  7/2  5/2", 3, {0, 6, 4}},
    {"f  1/2/2  7/2/2  5/2/2", 3, {0, 6, 4}},
    {"f  1//2  7//2  5//2", 3, {0, 6, 4}},
};

START_TEST(test_move) {
    model testModel;
    for (int i = 0; i < 4; i++) {
        testModel = load_model("models/small/cube.obj");
        moveXYZ(&testModel, move_pack[i * 24 + 3 * i], move_pack[i * 24 + 3 * i + 1],
                move_pack[i * 24 + 3 * i + 2]);
        for (int j = 0; j < 24; j++) {
            ck_assert_float_eq_tol(testModel.vertexes[j], *(move_pack + (i * 24 + 3 * i) + j + 3), 0.000001);
        }
    }
    release_model(testModel);
}
END_TEST

START_TEST(test_rotationX) {
    model testModel;

    testModel = load_model("models/small/cube.obj");
    rotationX(&testModel, M_PI / 2);
    float standart[24] = {0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0, 1.0,
                          1.0, 0.0, 0.0, 1.0, -1.0, 0.0, 1.0, 0.0, 1.0, 1.0, -1.0, 1.0};

    for (int i = 0; i < 24; i++) {
        ck_assert_float_eq_tol(standart[i], testModel.vertexes[i], 0.000001);
    }
    release_model(testModel);
}
END_TEST

START_TEST(test_rotationY) {
    model testModel;

    testModel = load_model("models/small/cube.obj");
    rotationY(&testModel, M_PI);
    float standart[24] = {0.0,  0.0, 0.0, 0.0,  0.0, -1.0, 0.0,  1.0, 0.0, 0.0,  1.0, -1.0,
                          -1.0, 0.0, 0.0, -1.0, 0.0, -1.0, -1.0, 1.0, 0.0, -1.0, 1.0, -1.0};
    for (int i = 0; i < 24; i++) {
        ck_assert_float_eq_tol(standart[i], testModel.vertexes[i], 0.000001);
    }
    release_model(testModel);
}
END_TEST

START_TEST(test_rotationZ) {
    model testModel;

    testModel = load_model("models/small/cube.obj");
    rotationZ(&testModel, 3 * M_PI / 4);
    float standart[24] = {0.0,      0.0,       0.0,       0.0, 0.0,       1.0,       -0.707107, -0.707107,
                          0.0,      -0.707107, -0.707107, 1.0, -0.707107, 0.707107,  0.0,       -0.707107,
                          0.707107, 1.0,       -1.414214, 0.0, 0.0,       -1.414214, 0.0,       1.0};
    for (int i = 0; i < 24; i++) {
        ck_assert_float_eq_tol(standart[i], testModel.vertexes[i], 0.000001);
    }
    release_model(testModel);
}
END_TEST

START_TEST(test_scale) {
    model testModel;

    testModel = load_model("models/small/cube.obj");
    scale(&testModel, 2);
    float standart[24] = {0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 2, 2, 2, 0, 0, 2, 0, 2, 2, 2, 0, 2, 2, 2};

    for (int i = 0; i < 24; i++) {
        ck_assert_float_eq_tol(standart[i], testModel.vertexes[i], 0.000001);
    }
    release_model(testModel);
}
END_TEST

START_TEST(test_load) {
    model testModel;
    testModel = load_model("models/small/cube.obj");
    float standart[24] = {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1};
    for (int i = 0; i < 24; i++) {
        ck_assert_float_eq_tol(standart[i], testModel.vertexes[i], 0.000001);
    }
    release_model(testModel);
}
END_TEST

START_TEST(test_load2) {
    model testModel;

    testModel = load_model("models/small/cube.obj");
    int standart[72] = {0, 6, 6, 4, 4, 0, 0, 2, 2, 6, 6, 0, 0, 3, 3, 2, 2, 0, 0, 1, 1, 3, 3, 0,
                        2, 7, 7, 6, 6, 2, 2, 3, 3, 7, 7, 2, 4, 6, 6, 7, 7, 4, 4, 7, 7, 5, 5, 4,
                        0, 4, 4, 5, 5, 0, 0, 5, 5, 1, 1, 0, 1, 5, 5, 7, 7, 1, 1, 7, 7, 3, 3, 1};

    for (int i = 0; i < 72; i++) {
        ck_assert_int_eq(standart[i], testModel.faces[i]);
    }
    release_model(testModel);
}
END_TEST

START_TEST(test_scan_faces) {
    unsigned int faces[10];
    unsigned int result = scan_faces(faces_pack[_i].str, faces);
    ck_assert_uint_eq(result, faces_pack[_i].result);
    for (unsigned int i = 0; i < result; i++) {
        ck_assert_uint_eq(faces[i], faces_pack[_i].faces[i]);
    }
}
END_TEST

START_TEST(test_scan_vertexes) {
    float vertexes[10];
    unsigned int result = scan_vertexes("v  1.0  2.0  3.0", vertexes);
    ck_assert_uint_eq(result, 3);
    ck_assert_double_eq(vertexes[0], 1);
    ck_assert_double_eq(vertexes[1], 2);
    ck_assert_double_eq(vertexes[2], 3);
}
END_TEST

int main() {
    Suite *s = suite_create("tests");
    SRunner *sr = srunner_create(s);
    srunner_set_fork_status(sr, CK_NOFORK);
    TCase *tc = tcase_create("case");
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 10);

    tcase_add_test(tc, test_move);
    tcase_add_test(tc, test_rotationX);
    tcase_add_test(tc, test_rotationY);
    tcase_add_test(tc, test_rotationZ);
    tcase_add_test(tc, test_scale);
    tcase_add_test(tc, test_load);
    tcase_add_test(tc, test_load2);
    tcase_add_test(tc, test_scan_faces);
    tcase_add_test(tc, test_scan_vertexes);

    srunner_run_all(sr, CK_ENV);
    int failed_count = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (failed_count != 0) ? 1 : 0;
}
