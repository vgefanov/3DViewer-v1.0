#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "includes.h"


typedef struct {
    char str[100];
    unsigned int result;
    unsigned int faces[10];
} faces_struct;

faces_struct faces_pack[] = {
    { "f 1 7 5", 3, { 0, 6, 4 } },
    { "f  1/2  7/2  5/2", 3, { 0, 6, 4 } },
    { "f  1/2/2  7/2/2  5/2/2", 3, { 0, 6, 4 } },
    { "f  1//2  7//2  5//2", 3, { 0, 6, 4 } },
};


START_TEST(test_scan_vertexes) {
    double vertexes[10];
    unsigned int result = scan_vertexes("v  1.0  2.0  3.0", vertexes);
    ck_assert_uint_eq(result, 3);
    ck_assert_double_eq(vertexes[0], 1);
    ck_assert_double_eq(vertexes[1], 2);
    ck_assert_double_eq(vertexes[2], 3);
}
END_TEST


START_TEST(test_scan_faces) {
    unsigned int faces[10];;
    unsigned int result = scan_faces(faces_pack[_i].str, faces);
    ck_assert_uint_eq(result, faces_pack[_i].result);
    for (int i = 0; i < result; i++) {
        ck_assert_uint_eq(faces[i], faces_pack[_i].faces[i]);
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

    tcase_add_test(tc, test_scan_vertexes);
    tcase_add_loop_test(tc, test_scan_faces, 0, sizeof(faces_pack) / sizeof(faces_struct));

    srunner_run_all(sr, CK_ENV);
    int failed_count = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (failed_count != 0) ? 1 : 0;
}
