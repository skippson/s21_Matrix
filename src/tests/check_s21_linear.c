#include "check_s21_linear.h"

START_TEST(test_s21_transpose_matrix) {
  matrix_t a;
  matrix_t result;
  matrix_t expected;
  int return_code = 0;
  s21_create_matrix(3, 2, &a);
  s21_create_matrix(2, 3, &expected);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      a.matrix[i][j] = i * 2 + j + 1;
    }
  }
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 3;
  expected.matrix[0][2] = 5;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = 4;
  expected.matrix[1][2] = 6;
  return_code = s21_transpose(&a, &result);
  ck_assert_int_eq(return_code, 0);
  a.rows = -2;
  return_code = s21_transpose(&a, &result);
  ck_assert_int_eq(return_code, 1);
  return_code = s21_transpose(&a, NULL);
  ck_assert_int_eq(return_code, 1);
  return_code = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(return_code, SUCCESS);
  return_code = s21_transpose(NULL, &result);
  ck_assert_int_eq(return_code, 1);
  return_code = s21_transpose(&a, NULL);
  ck_assert_int_eq(return_code, 1);
}
END_TEST

START_TEST(test_s21_determinant) {
  matrix_t a;
  double result = 0;
  int return_code = 0;
  s21_create_matrix(3, 3, &a);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      a.matrix[i][j] = i * 3 + j + 1;
    }
  }
  return_code = s21_determinant(&a, &result);
  ck_assert_int_eq(return_code, 0);
  ck_assert_double_eq(result, 0);
  a.rows = 2;
  return_code = s21_determinant(&a, &result);
  ck_assert_int_eq(return_code, 2);
  a.rows = 3;
  return_code = s21_determinant(NULL, &result);
  ck_assert_int_eq(return_code, 1);
  return_code = s21_determinant(&a, NULL);
  ck_assert_int_eq(return_code, 1);
  s21_remove_matrix(&a);
  s21_create_matrix(1, 1, &a);
  a.matrix[0][0] = 1;
  return_code = s21_determinant(&a, &result);
  ck_assert_int_eq(return_code, 0);
  ck_assert_double_eq(result, 1);
}
END_TEST

START_TEST(test_s21_calc_complements) {
  matrix_t a;
  matrix_t result;
  matrix_t expected;
  int return_code = 0;
  s21_create_matrix(3, 3, &a);
  s21_create_matrix(3, 3, &expected);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[1][0] = 0;
  a.matrix[1][1] = 4;
  a.matrix[1][2] = 2;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = 2;
  a.matrix[2][2] = 1;
  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;
  return_code = s21_calc_complements(&a, &result);
  ck_assert_int_eq(return_code, 0);
  return_code = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(return_code, SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_create_matrix(1, 1, &a);
  s21_create_matrix(1, 1, &result);
  a.matrix[0][0] = 1;
  return_code = s21_calc_complements(&a, &result);
  ck_assert_int_eq(return_code, 0);
  ck_assert_int_eq(result.matrix[0][0], 1);
  a.rows = 2;
  return_code = s21_calc_complements(&a, &result);
  ck_assert_int_eq(return_code, 2);
  a.rows = 1;
  return_code = s21_calc_complements(NULL, &result);
  ck_assert_int_eq(return_code, 1);
  return_code = s21_calc_complements(&a, NULL);
  ck_assert_int_eq(return_code, 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);

  matrix_t g = {0};
  matrix_t res;
  int ans = 0;
  g.rows = 3;
  g.columns = 3;
  ans = s21_calc_complements(&g, &res);
  ck_assert_int_eq(ans, 1);
}
END_TEST

//      2  5  7
// A =  6  3  4
//      5 -2 -3

START_TEST(test_s21_inverse_matrix) {
  matrix_t a;
  matrix_t result;
  matrix_t expected;
  int return_code = 0;
  s21_create_matrix(3, 3, &a);
  s21_create_matrix(3, 3, &expected);
  a.matrix[0][0] = 2;
  a.matrix[0][1] = 5;
  a.matrix[0][2] = 7;
  a.matrix[1][0] = 6;
  a.matrix[1][1] = 3;
  a.matrix[1][2] = 4;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = -2;
  a.matrix[2][2] = -3;
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;
  return_code = s21_inverse_matrix(&a, &result);
  ck_assert_int_eq(return_code, 0);
  return_code = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(return_code, SUCCESS);
  a.rows = 4;
  return_code = s21_inverse_matrix(&a, &result);
  ck_assert_int_eq(return_code, 2);
  a.rows = 3;
  return_code = s21_inverse_matrix(NULL, &result);
  ck_assert_int_eq(return_code, 1);
  return_code = s21_inverse_matrix(&a, NULL);
  ck_assert_int_eq(return_code, 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
  s21_create_matrix(3, 3, &a);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      a.matrix[i][j] = i * 3 + j + 1;
    }
  }
  return_code = s21_inverse_matrix(&a, &result);
  ck_assert_int_eq(return_code, 2);

  matrix_t g = {0};
  matrix_t res;
  int ans = 0;
  g.rows = 3;
  g.columns = 3;
  ans = s21_inverse_matrix(&g, &res);
  ck_assert_int_eq(ans, 1);
}
END_TEST

//         -1   1  -1
// М^T. =  38 -41  34
//        -27  29 -24

START_TEST(test_s21_transpose) {
  matrix_t mat_1, res_mat, res_org;

  s21_create_matrix(2, 2, &mat_1);
  s21_create_matrix(2, 2, &res_org);
  mat_1.matrix[0][0] = 1;
  mat_1.matrix[0][1] = 2;
  mat_1.matrix[1][0] = 3;
  mat_1.matrix[1][1] = 4;
  res_org.matrix[0][0] = 1;
  res_org.matrix[0][1] = 3;
  res_org.matrix[1][0] = 2;
  res_org.matrix[1][1] = 4;
  int ret = s21_transpose(&mat_1, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  double matrix[2][2] = {
      {1, 2},
      {3, 4},
  };
  double res[2][2] = {{1, 3}, {2, 4}};
  s21_create_matrix(2, 2, &mat_1);
  s21_create_matrix(2, 2, &res_org);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      mat_1.matrix[i][j] = matrix[i][j];
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      res_org.matrix[i][j] = res[i][j];
    }
  }
  ret = s21_transpose(&mat_1, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_determinant1) {
  matrix_t matrix;
  s21_create_matrix(3, 3, &matrix);
  int count = 1;
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = count++;
    }
  }
  matrix.matrix[2][2] = 10;
  double res;
  int ret = s21_determinant(&matrix, &res);
  ck_assert_int_eq(res, -3);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_calc_complements1) {
  double m[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double r[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  matrix_t matrix, res_org, res_my;
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = s21_calc_complements(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_inverse_matrix1) {
  double m[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double r[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  matrix_t matrix, res_org, res_my;
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = s21_inverse_matrix(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

Suite *s21_linear() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("linear");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_transpose_matrix);
  tcase_add_test(tc_core, test_s21_transpose);
  tcase_add_test(tc_core, test_s21_determinant);
  tcase_add_test(tc_core, test_s21_determinant1);
  tcase_add_test(tc_core, test_s21_calc_complements);
  tcase_add_test(tc_core, test_s21_calc_complements1);
  tcase_add_test(tc_core, test_s21_inverse_matrix);
  tcase_add_test(tc_core, test_s21_inverse_matrix1);

  suite_add_tcase(s, tc_core);

  return s;
}

int test_linear() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = s21_linear();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}