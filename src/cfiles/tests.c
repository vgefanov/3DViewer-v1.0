#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "affine.c"
#include "objfiles.c"

float move_pack[1000] = {
    0.55,   0.66,  0.77,   0.55,  0.66,  0.77,   0.55,  0.66,   1.77,   0.55,
    1.66,   0.77,  0.55,   1.66,  1.77,  1.55,   0.66,  0.77,   1.55,   0.66,
    1.77,   1.55,  1.66,   0.77,  1.55,  1.66,   1.77,  0,      0,      0,
    0,      0,     0,      0,     0,     1,      0,     1,      0,      0,
    1,      1,     1,      0,     0,     1,      0,     1,      1,      1,
    0,      1,     1,      1,     0,     0,      123,   0,      0,      123,
    0,      0,     124,    0,     1,     123,    0,     1,      124,    1,
    0,      123,   1,      0,     124,   1,      1,     123,    1,      1,
    124,    0,     -0.999, 0,     0,     -0.999, 0,     0,      -0.999, 1,
    0,      0.001, 0,      0,     0.001, 1,      1,     -0.999, 0,      1,
    -0.999, 1,     1,      0.001, 0,     1,      0.001, 1};

START_TEST(test_move) {
  model testModel;
  for (int i = 0; i < 4; i++) {
    testModel = load_model("../models/small/cube.obj");
    moveXYZ(&testModel, move_pack[i * 24 + 3 * i],
            move_pack[i * 24 + 3 * i + 1], move_pack[i * 24 + 3 * i + 2]);
    for (int j = 0; j < 24; j++) {
      ck_assert_float_eq_tol(testModel.vertexes[j],
                             *(move_pack + (i * 24 + 3 * i) + j + 3), 0.000001);
    }
  }
}
END_TEST

START_TEST(test_rotationX) {
  model testModel;

  testModel = load_model("../models/small/cube.obj");
  rotationX(&testModel, M_PI / 2);
  float standart[24] = {0.0,  0.0, 0.0,  0.0, -1.0, 0.0, 0.0,  0.0,
                        1.0,  0.0, -1.0, 1.0, 1.0,  0.0, 0.0,  1.0,
                        -1.0, 0.0, 1.0,  0.0, 1.0,  1.0, -1.0, 1.0};

  for (int i = 0; i < 24; i++) {
    ck_assert_float_eq_tol(standart[i], testModel.vertexes[i], 0.000001);
  }
}
END_TEST

START_TEST(test_rotationY) {
  model testModel;

  testModel = load_model("../models/small/cube.obj");
  rotationY(&testModel, M_PI);
  float standart[24] = {0.0, 0.0,  0.0,  0.0,  0.0,  -1.0, 0.0, 1.0,
                        0.0, 0.0,  1.0,  -1.0, -1.0, 0.0,  0.0, -1.0,
                        0.0, -1.0, -1.0, 1.0,  0.0,  -1.0, 1.0, -1.0};

  for (int i = 0; i < 24; i++) {
    ck_assert_float_eq_tol(standart[i], testModel.vertexes[i], 0.000001);
  }
}
END_TEST

START_TEST(test_rotationZ) {
  model testModel;

  testModel = load_model("../models/small/cube.obj");
  rotationY(&testModel, 3 * M_PI / 4);
  float standart[24] = {0.0,       0.0, 0.0,       0.707107, 0.0, -0.707107,
                        0.0,       1.0, 0.0,       0.707107, 1.0, -0.707107,
                        -0.707107, 0.0, -0.707107, 0.0,      0.0, -1.414214,
                        -0.707107, 1.0, -0.707107, 0.0,      1.0, -1.414214};

  for (int i = 0; i < 24; i++) {
    ck_assert_float_eq_tol(standart[i], testModel.vertexes[i], 0.000001);
  }
}
END_TEST

START_TEST(test_scale) {
  model testModel;

  testModel = load_model("../models/small/cube.obj");
  scale(&testModel, 2);
  float standart[24] = {0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 2, 2,
                        2, 0, 0, 2, 0, 2, 2, 2, 0, 2, 2, 2};

  for (int i = 0; i < 24; i++) {
    ck_assert_float_eq_tol(standart[i], testModel.vertexes[i], 0.000001);
  }
}
END_TEST

START_TEST(test_load) {
  model testModel;

  testModel = load_model("../models/small/cube.obj");
  float standart[24] = {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1,
                        1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1};

  for (int i = 0; i < 24; i++) {
    ck_assert_float_eq_tol(standart[i], testModel.vertexes[i], 0.000001);
  }
}
END_TEST

START_TEST(test_scan_faces) {
  model testModel;

  testModel = load_model("../models/small/cube.obj");
  int standart[72] = {0, 6, 6, 4, 4, 0, 0, 2, 2, 6, 6, 0, 0, 3, 3, 2, 2, 0,
                      0, 1, 1, 3, 3, 0, 2, 7, 7, 6, 6, 2, 2, 3, 3, 7, 7, 2,
                      4, 6, 6, 7, 7, 4, 4, 7, 7, 5, 5, 4, 0, 4, 4, 5, 5, 0,
                      0, 5, 5, 1, 1, 0, 1, 5, 5, 7, 7, 1, 1, 7, 7, 3, 3, 1};

  for (int i = 0; i < 73; i++) {
    ck_assert_int_eq(standart[i], testModel.faces[i]);
  }
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
  tcase_add_test(tc, test_scan_faces);

  srunner_run_all(sr, CK_ENV);
  int failed_count = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed_count != 0) ? 1 : 0;
}
