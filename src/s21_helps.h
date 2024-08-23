#ifndef s21_HELPS_H
#define s21_HELPS_H

#include "s21_matrix.h"

bool valid_matrix(matrix_t *matrix);

int s21_sum_and_sub(matrix_t *a, matrix_t *b, matrix_t *result,
                    const char operator);

void new_pointer(double **a, double *b);

double det(double **a, int n);

void make_minor(matrix_t *A, int row, int column, matrix_t *result);

void alg_dop(matrix_t *a, matrix_t *result);

void invers(matrix_t *a, matrix_t *result);

#endif