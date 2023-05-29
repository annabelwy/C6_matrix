#include "s21_matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int s21_calc_complements(matrix_t *A,
                         matrix_t *result) 
{
  int ret = 0;
  if (WrongMatrix(A) == 0) {
    if (A->rows == A->columns) {
      ret = s21_create_matrix(A->rows, A->columns, result);
      if (ret == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            matrix_t res;
            double resuult = 0;

            MatrWithout(A, &res, i,
                        j);  // получаем новую матрицу для поиска минора, сейчас
                             // надо посчитать его детерминант
            ret = s21_determinant(
                &res, &resuult);  // посчитали значение определителя этой
                                  // матрицы, вернули его в resuult
            if (ret == 0) {
              result->matrix[i][j] =
                  resuult * pow(-1, j + i);  // алгебраич доп-ие
            }
            s21_remove_matrix(&res);
          }
        }
      }
    } else {
      ret = 2;
    }
  } else {
    ret = 1;
  }
  return ret;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 1;
  if (WrongMatrix(A) == 0) {
    res = 2;
    double resuult;  // тут убрала обнуление
    res = s21_determinant(A, &resuult);
    if (res == 0) {
      if (fabs(resuult) > 1e-07) {
        matrix_t for_alg_ext;
        res = s21_calc_complements(A, &for_alg_ext);
        if (res == 0) {
          matrix_t for_transp;
          res = s21_transpose(&for_alg_ext, &for_transp);
          if (res == 0) {
            res = s21_mult_number(&for_transp, 1.0 / resuult, result);
          }
          s21_remove_matrix(&for_transp);
        }
        s21_remove_matrix(&for_alg_ext);
      }
    }
  }
  return res;
}

int WrongMatrix(matrix_t *result) {
  int res = 1;
  if (result->columns > 0 && result->rows > 0 && result->matrix != NULL &&
      result != NULL)  // поменять, тк налл  не равен налл
    res = 0;
  return res;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;

    // Создаем двумерный массив
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows && res != 1; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          res = 1;
          s21_remove_matrix(result);
        }
      }
    }
  } else {
    res = 1;
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (WrongMatrix(A) == 0) {
    for (int i = 0; i < A->rows && A->matrix[i] != NULL; i++) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  A->columns = 0;
  A->rows = 0;
}

double Value(matrix_t *A, int row, int colummn) {
  return A->matrix[row]
                  [colummn];  // значение в этом месте возвращаем, отсчет с нуля
}

int CheckSize(matrix_t *A, matrix_t *B) {
  int res = 0;
  if (A->rows == B->rows && A->columns == B->columns) {
    res = 1;
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (WrongMatrix(A) == 0 &&
      WrongMatrix(B) == 0) {  // если нет ошибок  в матрицах(не отриц колонки)
    if (CheckSize(A, B)) {
      res = s21_create_matrix(A->rows, A->columns, result);
      if (res == 0) {
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            result->matrix[i][j] = Value(A, i, j) - Value(B, i, j);
          }
        }
      }
    } else {
      res = 2;
    }
  } else {
    res = 1;
  }

  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (WrongMatrix(A) == 0 &&
      WrongMatrix(B) == 0) {  // если нет ошибок  в матрицах(не отриц колонки)
    if (CheckSize(A, B)) {
      res = s21_create_matrix(A->rows, A->columns, result);
      if (res == 0) {
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            result->matrix[i][j] = Value(A, i, j) + Value(B, i, j);
          }
        }
      }
    } else {
      res = 2;
    }
  } else {
    res = 1;
  }

  return res;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < A->rows && res != FAILURE; i++) {
      for (int j = 0; j < A->columns && res != FAILURE; j++) {
        double eps = fabs(Value(A, i, j) - Value(B, i, j));
        if (eps < 1e-7)  // вывести  в даубл
        {
          res = SUCCESS;
        } else {
          res = FAILURE;
        }
      }
    }
  } else {
    res = FAILURE;
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = 0;
  if (WrongMatrix(A) == 0) {
    res = s21_create_matrix(A->rows, A->columns, result);
    if (res == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = Value(A, i, j) * number;
        }
      }
    }
  } else {
    res = 1;
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (WrongMatrix(A) == 0 && WrongMatrix(B) == 0) {
    if (A->columns == B->rows) {
      res = s21_create_matrix(A->rows, B->columns, result);
      if (res == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            // int kol = 0;
            double mult = 0;
            for (int kol = 0; kol < B->rows; kol++) {
              mult = (Value(A, i, kol) * Value(B, kol, j)) + mult;
            }
            result->matrix[i][j] = mult;
          }
        }
      }
    } else {
      res = 2;
    }
  } else {
    res = 1;
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (WrongMatrix(A) == 0) {
    res = s21_create_matrix(A->columns, A->rows, result);
    if (res == 0) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    }
  } else {
    res = 1;
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = 0;
  *result = 0;
  if (WrongMatrix(A) == 0) {
    if (A->columns == A->rows) {
      if (A->rows == 1) {
        *result = Value(A, 0, 0);
      } else if (A->rows == 2) {
        *result =
            Value(A, 0, 0) * Value(A, 1, 1) - (Value(A, 0, 1) * Value(A, 1, 0));
      } else if (A->rows > 2) {
        for (int i = 0; i < A->rows && res == 0; i++) {
          matrix_t resuult;
          MatrWithout(A, &resuult, i, 0);
          double M = 0;
          res = s21_determinant(&resuult, &M);
          if (res == 0) {
            *result = *result + pow(-1, i + 2) * Value(A, i, 0) * M;
          }
          s21_remove_matrix(&resuult);
        }
      }
    } else
      res = 2;
  } else
    res = 1;
  return res;
}

void MatrWithout(matrix_t *mas, matrix_t *result, int i,
                 int j) {  // для опред(без строчки и столбца)
  s21_create_matrix(mas->rows - 1, mas->columns - 1, result);
  int for_rows = 0, for_columns = 0;
  for (int row = 0; row < mas->rows; row++) {
    if (row != i) {
      for (int col = 0; col < mas->columns; col++) {
        if (col != j) {
          result->matrix[for_rows][for_columns] = mas->matrix[row][col];
          for_columns++;
        }
      }
      for_columns = 0;
      for_rows++;
    }
  }
}
