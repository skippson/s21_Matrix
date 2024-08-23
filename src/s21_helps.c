#include "s21_matrix.h"

bool valid_matrix(matrix_t *a) {
  int res = false;
  if (a != NULL && a->matrix != NULL && a->rows >= 1 && a->columns >= 1) {
    res = true;
  } else {
    res = false;
  }
  return res;
}

int s21_sum_and_sub(matrix_t *a, matrix_t *b, matrix_t *result,
                    const char operator) {
  bool status = OK;
  bool flag = false;
  if (a != NULL && b != NULL && valid_matrix(a) && valid_matrix(b) &&
      result != NULL) {
    if ((a->rows == b->rows) && (a->columns == b->columns)) {
      flag = true;
    } else
      status = ERROR_MATH;
  } else
    status = ERROR_TYPE;

  if (flag == true) {
    s21_create_matrix(a->rows, a->columns, result);
    for (int i = 0; i < a->rows; i++) {
      for (int j = 0; j < a->columns; j++) {
        switch (operator) {
          case '+':
            result->matrix[i][j] = a->matrix[i][j] + b->matrix[i][j];
            break;
          case '-':
            result->matrix[i][j] = a->matrix[i][j] - b->matrix[i][j];
          default:
            break;
        }
      }
    }
  }
  return status;
}

void new_pointer(double **a, double *b) { *a = b; }

double det(double **a, int n) {
  if (n == 1) {
    return a[0][0];
  }
  if (n == 2) {
    return a[0][0] * a[1][1] - a[0][1] * a[1][0];
  }
  int number = 0;
  double sum = 0;
  double **temp = malloc((n - 1) * sizeof(double *));
  for (int i = 0; i < n; i++) {
    number = 0;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      new_pointer(&temp[number++], a[j]);
    }
    sum += pow(-1, i + n - 1) * a[i][n - 1] * det(temp, n - 1);
  }
  free(temp);
  return sum;
}

void make_minor(matrix_t *A, int row, int column, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (i != row && j != column) {
        result->matrix[i - (i > row)][j - (j > column)] = A->matrix[i][j];
      }
    }
  }
}

void alg_dop(matrix_t *a, matrix_t *result) {
  if (a->rows == 1) {
    s21_determinant(a, &result->matrix[0][0]);
  } else {
    for (int i = 0; i < a->rows; i++) {
      for (int j = 0; j < a->columns; j++) {
        matrix_t minor = {0};
        s21_create_matrix(a->rows - 1, a->columns - 1, &minor);
        make_minor(a, i, j, &minor);
        s21_determinant(&minor, &result->matrix[i][j]);
        result->matrix[i][j] *= pow(-1, i + j);
        s21_remove_matrix(&minor);
      }
    }
  }
}

void invers(matrix_t *a, matrix_t *result) {
  double deter = 0;
  s21_determinant(a, &deter);
  matrix_t dop = {0};
  matrix_t tran = {0};
  s21_calc_complements(a, &dop);
  s21_transpose(&dop, &tran);
  s21_mult_number(&tran, 1.0 / deter, result);
  s21_remove_matrix(&tran);
  s21_remove_matrix(&dop);
}