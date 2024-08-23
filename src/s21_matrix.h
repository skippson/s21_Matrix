#include <math.h>
#include <stdlib.h>

#include "s21_helps.h"

#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#define true 1
#define false 0

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define ERROR_TYPE 1
#define ERROR_MATH 2

typedef int bool;

typedef struct matrix_t {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Создание матрицы(выделение памяти)
int s21_create_matrix(int rows, int columns, matrix_t *result);

// Удаление матрицы(чистка памяти)
void s21_remove_matrix(matrix_t *A);

// Сравнение двух матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Сумма двух матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Вычитание двух матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

// Умножение двух матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Транспонирование матрицы(замена строк столбцами)
int s21_transpose(matrix_t *A, matrix_t *result);

// Минор матрицы и матрица алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result);

// Определитель матрицы
int s21_determinant(matrix_t *A, double *result);

// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif