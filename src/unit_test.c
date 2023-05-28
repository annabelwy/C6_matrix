#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_matrix.h"
#define OK 0
#define INCORR_MATRIX_ERROR 1
#define CALC_ERROR 2
void s21_fill_matrix(int count, matrix_t *matrix) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      matrix->matrix[i][j] = count++;
    }
  }
}

START_TEST(s21_create_matrix_1) {  // создание матриц
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  ck_assert_int_eq(s21_create_matrix(4, 4, &matrix), OK);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_create_matrix_2) {  // создание матриц
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  ck_assert_int_eq(s21_create_matrix(0, 5, &matrix), INCORR_MATRIX_ERROR);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_create_matrix_3) {  // создание матриц
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  ck_assert_int_eq(s21_create_matrix(-1, 5, &matrix), INCORR_MATRIX_ERROR);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_create_matrix_4) {  // создание матриц
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  ck_assert_int_eq(s21_create_matrix(-5, -5, &matrix), INCORR_MATRIX_ERROR);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_eq_matrix_1) {  // сравнение матриц
  matrix_t matrixA = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t matrixB = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(2, 8, &matrixA);
  s21_create_matrix(2, 8, &matrixB);
  s21_fill_matrix(1, &matrixA);
  s21_fill_matrix(1, &matrixB);
  ck_assert_int_eq(s21_eq_matrix(&matrixA, &matrixB), SUCCESS);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
}
END_TEST

START_TEST(s21_eq_matrix_2) {  // сравнение матриц
  matrix_t matrixA = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t matrixB = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(2, 8, &matrixA);
  s21_create_matrix(2, 8, &matrixB);
  s21_fill_matrix(-1, &matrixA);
  s21_fill_matrix(5, &matrixB);
  ck_assert_int_eq(s21_eq_matrix(&matrixA, &matrixB), FAILURE);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
}
END_TEST

START_TEST(s21_eq_matrix_3) {  // сравнение матриц
  matrix_t matrixA = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t matrixB = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(2, 3, &matrixA);
  s21_create_matrix(3, 2, &matrixB);
  s21_fill_matrix(1, &matrixA);
  s21_fill_matrix(1, &matrixB);
  ck_assert_int_eq(s21_eq_matrix(&matrixA, &matrixB), FAILURE);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
}
END_TEST

START_TEST(s21_sum_matrix_1) {  // сложение матриц
  matrix_t matrixA = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t matrixB = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(2, 8, &matrixA);
  s21_create_matrix(2, 8, &matrixB);
  s21_fill_matrix(1.986875765, &matrixA);
  s21_fill_matrix(5.9867576, &matrixB);
  ck_assert_int_eq(s21_sum_matrix(&matrixA, &matrixB, &result), OK);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_2) {
  matrix_t matrixA = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t matrixB = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(2, 8, &matrixA);
  s21_fill_matrix(1, &matrixA);
  s21_create_matrix(0, 8, &matrixB);
  ck_assert_int_eq(s21_sum_matrix(&matrixA, &matrixB, &result),
                   INCORR_MATRIX_ERROR);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_3) {
  matrix_t matrixA = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t matrixB = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(2, 8, &matrixA);
  s21_create_matrix(2, 7, &matrixB);
  s21_fill_matrix(1, &matrixA);
  s21_fill_matrix(2, &matrixB);
  ck_assert_int_eq(s21_sum_matrix(&matrixA, &matrixB, &result), CALC_ERROR);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_1) {  // вычитание матриц
  matrix_t matrixA = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t matrixB = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(4, 3, &matrixA);
  s21_create_matrix(4, 3, &matrixB);
  s21_fill_matrix(2.987865, &matrixA);
  s21_fill_matrix(6.098686564653, &matrixB);
  ck_assert_int_eq(s21_sub_matrix(&matrixA, &matrixB, &result), OK);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_2) {
  matrix_t matrixA = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t matrixB = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(0, 3, &matrixA);
  s21_fill_matrix(0, &matrixA);
  s21_create_matrix(4, 3, &matrixB);
  s21_fill_matrix(-4, &matrixB);
  ck_assert_int_eq(s21_sub_matrix(&matrixA, &matrixB, &result),
                   INCORR_MATRIX_ERROR);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_3) {
  matrix_t matrixA = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t matrixB = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(2, 5, &matrixA);
  s21_create_matrix(4, 5, &matrixB);
  s21_fill_matrix(9, &matrixA);
  s21_fill_matrix(0, &matrixB);
  ck_assert_int_eq(s21_sub_matrix(&matrixA, &matrixB, &result), CALC_ERROR);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_1) {  // умножение матрицы на скаляр
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(3, 3, &matrix);
  s21_fill_matrix(-1, &matrix);
  ck_assert_int_eq(s21_mult_number(&matrix, 2, &result), OK);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_2) {
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(0, 3, &matrix);
  ck_assert_int_eq(s21_mult_number(&matrix, 2, &result), INCORR_MATRIX_ERROR);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_3) {
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(1, 3, &matrix);
  s21_fill_matrix(1, &matrix);
  ck_assert_int_eq(s21_mult_number(&matrix, 2.2222222, &result), OK);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_1) {  // умножение двух матриц
  matrix_t matrixA = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t matrixB = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(7, 4, &matrixA);
  s21_create_matrix(4, 3, &matrixB);
  s21_fill_matrix(9, &matrixA);
  s21_fill_matrix(6, &matrixB);
  ck_assert_int_eq(s21_mult_matrix(&matrixA, &matrixB, &result), OK);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_2) {
  matrix_t matrixA = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t matrixB = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(4, 3, &matrixA);
  s21_fill_matrix(1, &matrixA);
  s21_create_matrix(-3, 5, &matrixB);
  s21_fill_matrix(6, &matrixB);
  ck_assert_int_eq(s21_mult_matrix(&matrixA, &matrixB, &result),
                   INCORR_MATRIX_ERROR);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_3) {
  matrix_t matrixA = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t matrixB = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(2, 8, &matrixA);
  s21_create_matrix(4, 5, &matrixB);
  s21_fill_matrix(2, &matrixA);
  s21_fill_matrix(5, &matrixB);
  ck_assert_int_eq(s21_mult_matrix(&matrixA, &matrixB, &result), CALC_ERROR);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_4) {
  matrix_t matrixA = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t matrixB = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(4, 6, &matrixA);
  s21_create_matrix(3, 4, &matrixB);
  s21_fill_matrix(-5, &matrixA);
  s21_fill_matrix(6, &matrixB);
  ck_assert_int_eq(s21_mult_matrix(&matrixA, &matrixB, &result), CALC_ERROR);
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&matrixB);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_1) {  // транспонирование
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(3, 5, &matrix);
  s21_fill_matrix(-1.75756, &matrix);
  ck_assert_int_eq(s21_transpose(&matrix, &result), OK);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_2) {  // транспонирование
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(-5, 5, &matrix);
  s21_fill_matrix(14, &matrix);
  ck_assert_int_eq(s21_transpose(&matrix, &result), INCORR_MATRIX_ERROR);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_3) {  // транспонирование
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(1, 1, &matrix);
  s21_fill_matrix(13, &matrix);
  ck_assert_int_eq(s21_transpose(&matrix, &result), OK);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_1) {  // минор матрицы и матрицы алгебраических
                                      // дополнений
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(5, 5, &matrix);
  s21_fill_matrix(13, &matrix);
  ck_assert_int_eq(s21_calc_complements(&matrix, &result), OK);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_2) {  // минор матрицы и матрицы алгебраических
                                      // дополнений
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(5, 7, &matrix);
  s21_fill_matrix(2, &matrix);
  ck_assert_int_eq(s21_calc_complements(&matrix, &result), CALC_ERROR);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_3) {  // минор матрицы и матрицы алгебраических
                                      // дополнений
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(0, 0, &matrix);
  s21_fill_matrix(1, &matrix);
  ck_assert_int_eq(s21_calc_complements(&matrix, &result), INCORR_MATRIX_ERROR);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_determinant_1) {  // определитель матрицы
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  double result;
  s21_create_matrix(5, 5, &matrix);
  s21_fill_matrix(-1, &matrix);
  ck_assert_int_eq(s21_determinant(&matrix, &result), 0);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant_2) {  // определитель матрицы
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  double result;
  s21_create_matrix(6, 4, &matrix);
  s21_fill_matrix(-1.676675645, &matrix);
  ck_assert_int_eq(s21_determinant(&matrix, &result), CALC_ERROR);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant_3) {  // определитель матрицы
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  double result;
  s21_create_matrix(0, 4, &matrix);
  ck_assert_int_eq(s21_determinant(&matrix, &result), INCORR_MATRIX_ERROR);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant_4) {  // определитель матрицы
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  double result = 0;
  s21_create_matrix(2, 2, &matrix);
  s21_fill_matrix(5, &matrix);
  ck_assert_int_eq(s21_determinant(&matrix, &result), OK);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant_5) {  // определитель матрицы
  double result = 0;
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(4, 4, &matrix);
  matrix.matrix[0][0] = 9;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 2;
  matrix.matrix[0][3] = 4;

  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 4;
  matrix.matrix[1][3] = 4;

  matrix.matrix[2][0] = 4;
  matrix.matrix[2][1] = 4;
  matrix.matrix[2][2] = 9;
  matrix.matrix[2][3] = 9;

  matrix.matrix[3][0] = 1;
  matrix.matrix[3][1] = 1;
  matrix.matrix[3][2] = 5;
  matrix.matrix[3][3] = 1;
  s21_determinant(&matrix, &result);
  ck_assert_int_eq(result, -578);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_inverse_matrix_1) {  // обратная матрица
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 8;
  matrix.matrix[0][2] = 2;
  matrix.matrix[1][0] = 8;
  matrix.matrix[1][1] = 2;
  matrix.matrix[1][2] = 8;
  matrix.matrix[2][0] = 2;
  matrix.matrix[2][1] = -8;
  matrix.matrix[2][2] = -2;
  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), OK);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_2) {  // обратная матрица
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(6, 8, &matrix);
  s21_fill_matrix(5, &matrix);
  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), CALC_ERROR);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_3) {  // обратная матрица
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(0, 0, &matrix);
  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), INCORR_MATRIX_ERROR);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_4) {  // обратная матрица
  matrix_t matrix = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t result = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(2, 2, &matrix);
  s21_fill_matrix(7, &matrix);
  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), OK);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

int main(void) {
  int number_failed = 0;  // для хранения количества неудачных тестов
  Suite *s;  // указатель на suite
  s = suite_create(
      "matrix");  // вызываем функцию, чтобы создать и вернуть test suite
  SRunner *sr;    // указатель на srunner
  sr = srunner_create(
      s);  // используем test suite и передаем их функции srunner_create, чтобы
           // получить указатель на test suite runner

  TCase *tc_create = tcase_create("s21_create_matrix");
  suite_add_tcase(s, tc_create);
  tcase_add_test(tc_create, s21_create_matrix_1);
  tcase_add_test(tc_create, s21_create_matrix_2);
  tcase_add_test(tc_create, s21_create_matrix_3);
  tcase_add_test(tc_create, s21_create_matrix_4);

  TCase *tc_eq_matrix = tcase_create("s21_eq_matrix");
  suite_add_tcase(s, tc_eq_matrix);
  tcase_add_test(tc_eq_matrix, s21_eq_matrix_1);
  tcase_add_test(tc_eq_matrix, s21_eq_matrix_2);
  tcase_add_test(tc_eq_matrix, s21_eq_matrix_3);

  TCase *tc_sum_matrix = tcase_create("s21_sum_matrix");
  suite_add_tcase(s, tc_sum_matrix);
  tcase_add_test(tc_sum_matrix, s21_sum_matrix_1);
  tcase_add_test(tc_sum_matrix, s21_sum_matrix_2);
  tcase_add_test(tc_sum_matrix, s21_sum_matrix_3);

  TCase *tc_sub_matrix = tcase_create("s21_sub_matrix");
  suite_add_tcase(s, tc_sub_matrix);
  tcase_add_test(tc_sub_matrix, s21_sub_matrix_1);
  tcase_add_test(tc_sub_matrix, s21_sub_matrix_2);
  tcase_add_test(tc_sub_matrix, s21_sub_matrix_3);

  TCase *tc_mult_number = tcase_create("s21_mult_number");
  suite_add_tcase(s, tc_mult_number);
  tcase_add_test(tc_mult_number, s21_mult_number_1);
  tcase_add_test(tc_mult_number, s21_mult_number_2);
  tcase_add_test(tc_mult_number, s21_mult_number_3);

  TCase *tc_mult_matrix = tcase_create("s21_mult_matrix");
  suite_add_tcase(s, tc_mult_matrix);
  tcase_add_test(tc_mult_matrix, s21_mult_matrix_1);
  tcase_add_test(tc_mult_matrix, s21_mult_matrix_2);
  tcase_add_test(tc_mult_matrix, s21_mult_matrix_3);
  tcase_add_test(tc_mult_matrix, s21_mult_matrix_4);

  TCase *tc_transpose = tcase_create("s21_transpose");
  suite_add_tcase(s, tc_transpose);
  tcase_add_test(tc_transpose, s21_transpose_1);
  tcase_add_test(tc_transpose, s21_transpose_2);
  tcase_add_test(tc_transpose, s21_transpose_3);

  TCase *tc_calc_complements = tcase_create("s21_calc_complements");
  suite_add_tcase(s, tc_calc_complements);
  tcase_add_test(tc_calc_complements, s21_calc_complements_1);
  tcase_add_test(tc_calc_complements, s21_calc_complements_2);
  tcase_add_test(tc_calc_complements, s21_calc_complements_3);

  TCase *tc_determinant = tcase_create("s21_determinant");
  suite_add_tcase(s, tc_determinant);
  tcase_add_test(tc_determinant, s21_determinant_1);
  tcase_add_test(tc_determinant, s21_determinant_2);
  tcase_add_test(tc_determinant, s21_determinant_3);
  tcase_add_test(tc_determinant, s21_determinant_4);
  tcase_add_test(tc_determinant, s21_determinant_5);

  TCase *tc_inverse_matrix = tcase_create("s21_inverse_matrix");
  suite_add_tcase(s, tc_inverse_matrix);
  tcase_add_test(tc_inverse_matrix, s21_inverse_matrix_1);
  tcase_add_test(tc_inverse_matrix, s21_inverse_matrix_2);
  tcase_add_test(tc_inverse_matrix, s21_inverse_matrix_3);
  tcase_add_test(tc_inverse_matrix, s21_inverse_matrix_4);

  srunner_run_all(sr, CK_NORMAL);  // распечатывает все неудачные тесты
  number_failed =
      srunner_ntests_failed(sr);  // вызываем srunner_ntests_failed чтобы
                                  // получить количество неудачных тестов
  srunner_free(sr);
  return (number_failed == 0)
             ? EXIT_SUCCESS
             : EXIT_FAILURE;  // успешно возвращаемся, если количество неудачных
                              // тестов равно 0, иначе мы не проходим тест
}