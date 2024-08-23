#include "check_s21_arithmetics.h"

START_TEST(test_s21_sum_matrix) {
  matrix_t a;
  matrix_t b;
  matrix_t result;
  matrix_t expected;
  int return_code = 0;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(2, 2, &expected);
  for (int i = 0; i < a.rows; i++) {
    for (int j = 0; j < a.columns; j++) {
      expected.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
    }
  }
  return_code = s21_sum_matrix(&a, &b, &result);
  ck_assert_int_eq(return_code, 0);
  return_code = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(return_code, SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_s21_sub_matrix) {
  matrix_t a;
  matrix_t b;
  matrix_t result;
  matrix_t expected;
  int return_code = 0;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(2, 2, &expected);
  for (int i = 0; i < a.rows; i++) {
    for (int j = 0; j < a.columns; j++) {
      expected.matrix[i][j] = a.matrix[i][j] - b.matrix[i][j];
    }
  }
  return_code = s21_sub_matrix(&a, &b, &result);
  ck_assert_int_eq(return_code, 0);
  return_code = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(return_code, SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_s21_mult_number) {
  matrix_t a;
  matrix_t result;
  matrix_t expected;
  double number = 0;
  int return_code = 0;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a.matrix[i][i] = i * 2 + j + 1;
      expected.matrix[i][i] = (i * 2 + j + 1) * 2;
    }
  }
  number = 2;
  return_code = s21_mult_number(&a, number, &result);
  ck_assert_int_eq(return_code, 0);
  return_code = s21_mult_number(NULL, number, &result);
  ck_assert_int_eq(return_code, 1);
  return_code = s21_mult_number(&a, number, NULL);
  ck_assert_int_eq(return_code, 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_s21_mult_matrix) {
  matrix_t a;
  matrix_t b;
  matrix_t result;
  matrix_t expected;
  int return_code = 0;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      double temp = i * 2 + j + 1;
      a.matrix[i][j] = temp;
      b.matrix[i][j] = temp;
    }
  }
  expected.matrix[0][0] = 7;
  expected.matrix[0][1] = 10;
  expected.matrix[1][0] = 15;
  expected.matrix[1][1] = 22;
  return_code = s21_mult_matrix(&a, &b, &result);
  ck_assert_int_eq(return_code, 0);
  a.columns = 3;
  return_code = s21_mult_matrix(&a, &b, &result);
  ck_assert_int_eq(return_code, 2);
  a.columns = 2;
  return_code = s21_mult_matrix(NULL, &b, &result);
  ck_assert_int_eq(return_code, 1);
  return_code = s21_mult_matrix(&a, NULL, &result);
  ck_assert_int_eq(return_code, 1);
  return_code = s21_mult_matrix(&a, &b, NULL);
  ck_assert_int_eq(return_code, 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_s21_sum_matrix1) {
  matrix_t matrix_1, matrix_2, res_my, res_org;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  int ret = s21_sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_sum_matrix(NULL, NULL, &res_my);
  ck_assert_int_eq(ret, 1);
  ret = s21_sum_matrix(NULL, &matrix_1, &res_my);
  ck_assert_int_eq(ret, 1);
  ret = s21_sum_matrix(&matrix_1, NULL, &res_my);
  ck_assert_int_eq(ret, 1);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 5, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  ret = s21_sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(4, 5, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  ret = s21_sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      res_org.matrix[i][j] = i + j;
    }
  }
  ret = s21_sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      matrix_2.matrix[i][j] = i + j;
      res_org.matrix[i][j] = (i + j) * 2;
    }
  }
  ret = s21_sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_sub_matrix1) {
  matrix_t matrix_1, matrix_2, res_my, res_org;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  int ret = s21_sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  ret = s21_sub_matrix(NULL, NULL, &res_my);
  ck_assert_int_eq(ret, 1);
  ret = s21_sub_matrix(NULL, &matrix_1, &res_my);
  ck_assert_int_eq(ret, 1);
  ret = s21_sub_matrix(&matrix_1, NULL, &res_my);
  ck_assert_int_eq(ret, 1);
  ret = s21_sub_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(ret, 1);
  ret = s21_sub_matrix(NULL, &matrix_1, NULL);
  ck_assert_int_eq(ret, 1);
  ret = s21_sub_matrix(&matrix_1, NULL, NULL);
  ck_assert_int_eq(ret, 1);

  s21_create_matrix(4, 5, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  ret = s21_sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(4, 4, &matrix_2);
  ret = s21_sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      res_org.matrix[i][j] = i + j;
    }
  }
  ret = s21_sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      matrix_2.matrix[i][j] = i + j;
    }
  }
  ret = s21_sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_mult_number1) {
  matrix_t matrix_1, res_my, res_org;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &res_org);
  int ret = s21_mult_number(&matrix_1, 5, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      res_org.matrix[i][j] = (i + j) * (-3);
    }
  }
  ret = s21_mult_number(&matrix_1, -3, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
    }
  }
  ret = s21_mult_number(&matrix_1, 0, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_mult_matrix1) {
  matrix_t mat_1, mat_2, res_mat, res_org;

  s21_create_matrix(2, 2, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  s21_create_matrix(2, 2, &res_org);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      mat_1.matrix[i][j] = i + j + 1;
      mat_2.matrix[i][j] = i + j + 1;
    }
  }
  res_org.matrix[0][0] = 5;
  res_org.matrix[0][1] = 8;
  res_org.matrix[1][0] = 8;
  res_org.matrix[1][1] = 13;
  int ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  s21_create_matrix(3, 2, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  s21_create_matrix(3, 2, &res_org);
  ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  s21_create_matrix(2, 7, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
}
END_TEST

Suite *s21_ari() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("sum, sub, mul by number and mul by matrix, divide");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_sum_matrix);
  tcase_add_test(tc_core, test_s21_sum_matrix1);
  tcase_add_test(tc_core, test_s21_sub_matrix);
  tcase_add_test(tc_core, test_s21_sub_matrix1);
  tcase_add_test(tc_core, test_s21_mult_number);
  tcase_add_test(tc_core, test_s21_mult_number1);
  tcase_add_test(tc_core, test_s21_mult_matrix);
  tcase_add_test(tc_core, test_s21_mult_matrix1);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_arithmetics() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = s21_ari();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}