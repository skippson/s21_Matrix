#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  bool status = OK;
  if ((A == NULL) || (valid_matrix(A) == false) || (result == NULL)) {
    status = ERROR_TYPE;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  bool status = OK;
  bool flag = false;
  if ((A == NULL) || (B == NULL) || (valid_matrix(A) == false) ||
      valid_matrix(B) == false || result == NULL) {
    status = ERROR_TYPE;
  } else {
    if (A->columns != B->rows) {
      status = ERROR_MATH;
    } else {
      flag = true;
    }
  }
  if (flag == true) {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_sum_and_sub(A, B, result, '+');
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_sum_and_sub(A, B, result, '-');
}