#include "s21_matrix.h"

void print_matrix(matrix_t *matrix) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      printf("%.7f ", matrix->matrix[i][j]);
    }
    printf("\n");
  }
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = 1;

  result->rows = rows;
  result->columns = columns;

  if ((result->rows > 0) && (result->columns > 0)) {
    result->matrix = (double **)malloc(rows * columns * sizeof(double) +
                                       rows * sizeof(double));
    double *matrix_ptr = (double *)(result->matrix + rows);
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = matrix_ptr + columns * i;
    }
  } else {
    result->matrix = NULL;
  }

  if (result->matrix == NULL) {
    status = 1;
  } else {
    // printf("create\n");
    status = 0;
    double count = 0;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = count;
        // count++;
      }
    }
  }

  return status;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    // printf("free\n");
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = SUCCESS;

  if (check_matrix(A) && check_matrix(B) && matrix_size_comparison(A, B)) {
    for (int i = 0; i < A->rows && status; i++) {
      for (int j = 0; j < A->columns && status; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          status = FAILURE;
          break;
        }
      }
    }
  } else {
    status = FAILURE;
  }

  return status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0;

  status = s21_create_matrix(A->rows, A->columns, result);

  if (!check_matrix(A) || !check_matrix(B) || !check_matrix(result)) {
    status = 1;
  }

  if (status == 0) {
    if (!matrix_size_comparison(A, B) || !matrix_size_comparison(A, result)) {
      status = 2;
    }
  }

  if (status == 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = (A->matrix[i][j] + B->matrix[i][j]);
      }
    }
  }

  return status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0;

  status = s21_create_matrix(A->rows, A->columns, result);

  if (!check_matrix(A) || !check_matrix(B) || !check_matrix(result)) {
    status = 1;
  }

  if (status == 0) {
    if (!matrix_size_comparison(A, B) || !matrix_size_comparison(A, result)) {
      status = 2;
    }
  }

  if (status == 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = (A->matrix[i][j] - B->matrix[i][j]);
      }
    }
  }

  return status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = 0;

  status = s21_create_matrix(A->rows, A->columns, result);

  if (!check_matrix(A) || !check_matrix(result)) {
    status = 1;
  }

  // if (status == 0) {
  //   if (!matrix_size_comparison(A, result)) {
  //     status = 2;
  //   }
  // }

  if (status == 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = (A->matrix[i][j] * number);
      }
    }
  }

  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0;

  status = s21_create_matrix(A->rows, B->columns, result);

  if (!check_matrix(A) || !check_matrix(B) || !check_matrix(result)) {
    status = 1;
  }
  /*
  Произведением матрицы A = m × k на матрицу B = k × n называется матрица C = m
  × n = A × B размера m × n
  */

  if (status == 0) {
    if (A->columns != B->rows) {
      status = 2;
    }
  }

  if (status == 0) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        double res = 0;
        for (int k = 0; k < A->columns; k++) {
          res += A->matrix[i][k] * B->matrix[k][j];
        }
        result->matrix[i][j] = res;
      }
    }
  }

  return status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = 0;

  status = s21_create_matrix(A->columns, A->rows, result);

  if (!check_matrix(A) || !check_matrix(result)) {
    status = 1;
  }

  // if (status == 0) {
  //   if (A->rows != result->columns || A->columns != result->rows) {
  //     status = 2;
  //   }
  // }

  if (status == 0) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }

  return status;
}

int s21_determinant(matrix_t *A, double *result) {
  int status = 0;

  if (!check_matrix(A)) {
    status = 1;
  }

  if (status == 0) {
    if (A->rows != A->columns) {
      status = 2;
    }
  }

  // https://ru.wikipedia.org/wiki/Определитель

  if (A->rows == 1) *result = A->matrix[0][0];
  if (A->rows == 2) {
    *result = (A->matrix[0][0] * A->matrix[1][1]) -
              (A->matrix[0][1] * A->matrix[1][0]);
  }

  if (status == 0) {
    matrix_t temp;
    status = s21_create_matrix(A->rows, A->columns, &temp);
    s21_copy_matrix(&temp, A);
    double delim = 0;
    double determ = 1;

    // matrix[stroka][kolonka]
    for (int j = 0; j < A->columns - 1; j++) {  // collums
      // printf("----------j = %d------------\n", j);
      // print_matrix(&temp);
      // printf("----------------------\n");
      for (int i = 1 + j; i < A->rows; i++) {  // rows
        if (temp.matrix[j][j] == 0) {
          // try swap string
          if (!s21_swap_string(&temp, j, j)) {
            *result = 0;
            return status;
          } else {
            determ *= -1;
            continue;
          }
        }

        delim = temp.matrix[i][j] / temp.matrix[j][j];
        // printf("delim %f, j = %d, i = %d\n", delim, j, i);
        s21_sub_string_mult_by_delim(&temp, i, j, delim);
      }
      // print_matrix(&temp);
    }

    for (int i = 0; i < temp.rows; i++) {
      determ *= temp.matrix[i][i];
    }
    *result = determ;
    s21_remove_matrix(&temp);
  }

  return status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = 0;

  status = s21_create_matrix(A->rows, A->columns, result);

  if (!check_matrix(A) || !check_matrix(result)) {
    status = 1;
  }

  if (status == 0) {
    if (A->rows != result->columns || A->columns != result->rows) {
      status = 2;
    }
  }

  if (status == 0) {
    status = s21_minor_matrix(A, result);
  }

  if (status == 0) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] *= pow(-1, i + j);
      }
    }
  }

  return status;
}

int s21_minor_matrix(matrix_t *origin, matrix_t *minor) {
  int status = 0;

  matrix_t temp;

  status = s21_create_matrix(origin->rows - 1, origin->columns - 1, &temp);

  if (status == 0) {
    if (!check_matrix(origin) || !check_matrix(minor)) {
      status = 1;
    }
  }

  if (status == 0) {
    if (!matrix_size_comparison(origin, minor)) {
      status = 2;
    }
  }

  if (minor->rows - 1 <= 0 || minor->columns <= 0) {
    status = 2;
  }

  if (status == 0) {
    for (int i = 0; i < origin->rows; i++) {
      for (int j = 0; j < origin->columns; j++) {
        // printf("-------- i = %d j = %d\n", i, j);
        get_dec_matrix(origin, &temp, i, j);
        status = s21_determinant(&temp, &minor->matrix[i][j]);
        // print_matrix(&temp);
      }
    }
  }
  s21_remove_matrix(&temp);
  return status;
}

int get_dec_matrix(matrix_t *matrix, matrix_t *result, int row, int column) {
  int status = 0;

  for (int i = 0, a = 0; i < matrix->rows; i++) {
    if (row != i) {
      for (int j = 0, b = 0; j < matrix->rows; j++) {
        if (column != j) {
          result->matrix[a][b] = matrix->matrix[i][j];
          b++;
        }
      }
      a++;
    }
  }

  return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = 0;

  // status = s21_create_matrix(A->rows, A->columns, result);

  if (!check_matrix(A)) {
    status = 1;
    // printf("yop\n");
  }

  if (status == 0) {
    if (A->rows != A->columns) {
      status = 2;
    }
  }

  double det = 0;
  if (status == 0) {
    s21_determinant(A, &det);
    // printf("det inv %f\n", det);
    if (fabs(det) < EPS) {
      status = 2;
    }
  }

  // printf("status inv %d\n", status);

  matrix_t temp;
  matrix_t temp1;

  temp.matrix = NULL;
  temp1.matrix = NULL;
  // s21_create_matrix(result->rows, result->columns, &temp);
  // s21_create_matrix(result->rows, result->columns, &temp1);

  if (status == 0) {
    status = s21_calc_complements(A, &temp);
    // printf("================= calc inv ============\n");
    // print_matrix(&temp);
    // printf("================= calc inv ============\n");
  }

  if (status == 0) {
    status = s21_transpose(&temp, &temp1);
    // print_matrix(&temp1);
  }

  if (status == 0) {
    status = s21_mult_number(&temp1, 1.0 / det, result);
  }

  // printf("================= remove inv ============\n");
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp1);
  // printf("================= remove inv  ============\n");

  return status;
}

int s21_sub_string_mult_by_delim(matrix_t *matrix, int origin, int sub,
                                 double delim) {
  int status = 0;

  for (int i = 0; i < matrix->columns; i++) {
    matrix->matrix[origin][i] -= matrix->matrix[sub][i] * delim;
  }

  return status;
}

int check_matrix(matrix_t *matrix) {
  int status = FAILURE;
  if (matrix != NULL && matrix->matrix != NULL && matrix->rows > 0 &&
      matrix->columns > 0) {
    status = SUCCESS;
  }
  return status;
}

int matrix_size_comparison(matrix_t *A, matrix_t *B) {
  int status = FAILURE;
  if (A->rows == B->rows && A->columns == B->columns) {
    status = SUCCESS;
  }
  return status;
}

// not safe
int s21_copy_matrix(matrix_t *A, matrix_t *B) {
  int status = 1;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = B->matrix[i][j];
    }
  }

  return status;
}

int s21_swap_string(matrix_t *A, int rows, int columns) {
  int status = FAILURE;

  for (int i = rows + 1; i < A->rows; i++) {
    if (A->matrix[i][columns] != 0) {
      status = SUCCESS;
      double temp = 0;
      for (int j = 0; j < A->columns; j++) {
        temp = A->matrix[rows][j];
        A->matrix[rows][j] = A->matrix[i][j];
        A->matrix[i][j] = temp;
      }
      break;
    }
  }

  return status;
}

// void fill_matrix(matrix_t *matrix, double num) {
//   for (int i = 0; i < matrix->rows; i++) {
//     for (int j = 0; j < matrix->columns; j++) {
//       matrix->matrix[i][j] = num;
//     }
//   }
// }
