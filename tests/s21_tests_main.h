#ifndef TESTS_MAIN_H
#define TESTS_MAIN_H

#define COMPARISON_TRUE 1
#define COMPARISON_FALSE 0

#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_decimal.h"

Suite *add_suite(void);
Suite *sub_suite(void);
Suite *mul_suite(void);
Suite *div_suite(void);

Suite *is_equal_suite1(void);
Suite *is_greater_suite1(void);
Suite *is_greater_or_equal_suite1(void);
Suite *is_less_suite1(void);
Suite *is_less_or_equal_suite1(void);
Suite *is_not_equal_suite1(void);

void test_is_equal(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_greater(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_greater_or_equal(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_less(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_less_or_equal(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_not_equal(s21_decimal decimal1, s21_decimal decimal2, int check);


#endif