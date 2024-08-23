#include "s21_matrix.h"

int s21_eq_matrix(matrix_t* A, matrix_t* B) {
  int status = FAILURE;
  if (A != NULL && B != NULL && valid_matrix(A) == SUCCESS &&
      valid_matrix(B) == SUCCESS) {
    if (A->rows == B->rows && A->columns == B->columns) {
      status = SUCCESS;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) {
            status = FAILURE;
          }
        }
      }
    }
  }
  return status;
}