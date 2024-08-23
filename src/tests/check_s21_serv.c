#include "check_s21_serv.h"

START_TEST(test_s21_create_matrix) {
  matrix_t a;
  int result = 0;
  result = s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(NULL);
  result = s21_create_matrix(3, 3, &a);
  ck_assert_int_eq(result, 0);
  if (result == 0) {
    s21_remove_matrix(&a);
  }
  result = s21_create_matrix(0, 3, &a);
  ck_assert_int_eq(result, 1);
  if (result == 0) {
    s21_remove_matrix(&a);
  }
  result = s21_create_matrix(0, 0, &a);
  ck_assert_int_eq(result, 1);
  if (result == 0) {
    s21_remove_matrix(&a);
  }
  result = s21_create_matrix(3, 0, &a);
  ck_assert_int_eq(result, 1);
  if (result == 0) {
    s21_remove_matrix(&a);
  }
  result = s21_create_matrix(-1, 5, &a);
  ck_assert_int_eq(result, 1);
  if (result == 0) {
    s21_remove_matrix(&a);
  }
  result = s21_create_matrix(5, -1, &a);
  ck_assert_int_eq(result, 1);
  if (result == 0) {
    s21_remove_matrix(&a);
  }
  result = s21_create_matrix(-1, -1, &a);
  ck_assert_int_eq(result, 1);
  if (result == 0) {
    s21_remove_matrix(&a);
  }

  matrix_t my_matrix;
  int ret = s21_create_matrix(4, 4, &my_matrix);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&my_matrix);

  ret = s21_create_matrix(-4, 4, &my_matrix);
  ck_assert_int_eq(ret, 1);

  ret = s21_create_matrix(-4, 0, &my_matrix);
  ck_assert_int_eq(ret, 1);
}
END_TEST

Suite *s21_service() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("create, delete");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_create_matrix);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_serv() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = s21_service();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}