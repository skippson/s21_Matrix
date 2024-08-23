#include "tests/check_s21_arithmetics.h"
#include "tests/check_s21_comparison.h"
#include "tests/check_s21_linear.h"
#include "tests/check_s21_serv.h"

int main() {
  int no_failed = 0;

  no_failed |= test_arithmetics();
  no_failed |= test_compare();
  no_failed |= test_linear();
  no_failed |= test_serv();

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
