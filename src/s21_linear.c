#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  bool status = OK;
  if ((A != NULL) && (valid_matrix(A) == true) && (result != NULL)) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    status = ERROR_TYPE;
  }

  return status;
}

int s21_determinant(matrix_t *A, double *result) {
  bool status = OK;
  if ((A != NULL) && (valid_matrix(A) == true) && (result != NULL)) {
    if (A->rows == A->columns) {
      *result = det(A->matrix, A->rows);
    } else
      status = ERROR_MATH;
  } else
    status = ERROR_TYPE;

  return status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  bool status = OK;
  if ((A != NULL) && (result != NULL)) {
    if (A->rows == A->columns) {
      if (valid_matrix(A) == true) {
        s21_create_matrix(A->rows, A->columns, result);
        alg_dop(A, result);
      } else
        status = ERROR_TYPE;
    } else
      status = ERROR_MATH;
  } else
    status = ERROR_TYPE;

  return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  bool status = OK;
  if ((A != NULL) && (result != NULL)) {
    if (A->rows == A->columns) {
      if (valid_matrix(A) == true) {
        double deter = 0;
        s21_determinant(A, &deter);
        if (fabs(deter - 0) > 1E-7) {
          invers(A, result);
        } else
          status = ERROR_MATH;
      } else
        status = ERROR_TYPE;
    } else
      status = ERROR_MATH;
  } else
    status = ERROR_TYPE;

  return status;
}