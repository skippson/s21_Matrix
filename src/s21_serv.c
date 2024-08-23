#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;
  if ((rows > 0) && (columns > 0) && (result != NULL)) {
    result->matrix = (double **)malloc(rows * sizeof(double *));
    result->rows = rows;
    result->columns = columns;
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
    }
    for (int i = 0; i < rows && status == OK; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = 0;
      }
    }
  } else {
    status = ERROR_TYPE;
  }
  return status;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && valid_matrix(A) == SUCCESS) {
    for (int i = 0; i < A->rows; i++) {
      void *temp = A->matrix[i];
      free(temp);
      A->matrix[i] = NULL;
    }
    void *temp = A->matrix;
    free(temp);
    A->matrix = NULL;
  }
}
