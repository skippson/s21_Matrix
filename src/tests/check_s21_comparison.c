#include "check_s21_comparison.h"

START_TEST(test_s21_eq_matrix) {
  matrix_t a;
  matrix_t b;
  int result = 0;
  s21_create_matrix(3, 3, &a);
  s21_create_matrix(3, 3, &b);
  result = s21_eq_matrix(&a, &b);
  ck_assert_int_eq(result, SUCCESS);
  a.matrix[0][0] = 5;
  result = s21_eq_matrix(&a, &b);
  ck_assert_int_eq(result, FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_create_matrix(3, 3, &a);
  result = s21_eq_matrix(NULL, &a);
  ck_assert_int_eq(result, FAILURE);
  result = s21_eq_matrix(&a, NULL);
  ck_assert_int_eq(result, FAILURE);
  s21_create_matrix(3, 3, &b);
  b.rows = 0;
  result = s21_eq_matrix(&a, &b);
  ck_assert_int_eq(result, FAILURE);
}
END_TEST

START_TEST(test_s21_eq_matrix1) {
  matrix_t matrix_1, matrix_2;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  int ret = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  ret = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, 0);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(10, 10, &matrix_2);
  ret = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  matrix_1.matrix[2][3] = -7;
  ret = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  matrix_1.matrix[2][3] = -7;
  matrix_2.matrix[2][3] = -7;
  ret = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

Suite *s21_comparison() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("compare");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_eq_matrix);
  tcase_add_test(tc_core, test_s21_eq_matrix1);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_compare() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = s21_comparison();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}