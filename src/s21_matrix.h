#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-7

#define OK 0
#define ERROR_MATRIX_INCORRECT 1
#define ERROR_MATRIX_CALCULATE 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Создание матриц (create_matrix)
int s21_create_matrix(int rows, int columns, matrix_t *result);
// Очистка матриц (remove_matrix)
void s21_remove_matrix(matrix_t *A);
// Сравнение матриц (eq_matrix)
int s21_eq_matrix(matrix_t *A, matrix_t *B);
// Сложение (sum_matrix)
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// вычитание матриц (sub_matrix)
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Умножение матрицы на число (mult_number)
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
// Умножение двух матриц (mult_matrix)
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Транспонирование матрицы (transpose)
int s21_transpose(matrix_t *A, matrix_t *result);
// Определитель матрицы (determinant)
int s21_determinant(matrix_t *A, double *result);
// Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result);
// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// helper functions
void print_matrix(matrix_t *matrix);
// checks the matrix for validity
int check_matrix(matrix_t *matrix);
// compares the dimensions of the matrix
int matrix_size_comparison(matrix_t *A, matrix_t *B);
// counts the string multiplied by the divisor
int s21_sub_string_mult_by_delim(matrix_t *matrix, int origin, int sub,
                                 double delim);
// copy
int s21_copy_matrix(matrix_t *A, matrix_t *B);
/*
search for a non-zero string below, if it matches, then changes
*/
int s21_swap_string(matrix_t *A, int rows, int columns);
// minor matrix
int s21_minor_matrix(matrix_t *origin, matrix_t *minor);
// результат обрезанная матрица
int get_dec_matrix(matrix_t *matrix, matrix_t *result, int row, int column);
// заполнить матрицу
// void fill_matrix(matrix_t *matrix, double num);

#endif  // SRC_S21_MATRIX_H_

/*
Реализовать основные действия с матрицами(частично описанные выше)
    : create_matrix(создание);
      remove_matrix(очистка и уничтожение),
      eq_matrix(сравнение),
      sum_matrix(сложение),
      sub_matrix(вычитание),
      mult_matrix(умножение),
      mult_number(умножение на число),
      transpose(транспонирование),
      determinant(вычисление определителя),
      calc_complements(вычисление матрицы алгребраический дополнений),
      inverse_matrix(поиск обратной матрицы).

      */

/*
Все операции (кроме сравнения матриц) должны возвращать результирующий код:

0 - OK
1 - Ошибка, некорректная матрица
2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя
провести вычисления и т.д.)
*/
