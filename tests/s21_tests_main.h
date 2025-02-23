#ifndef TESTS_MAIN_H
#define TESTS_MAIN_H
#define ARITHMETIC_CALCULATION_OK 0
#define TOO_LARGE 1
#define TOO_LEAST 2
#define DIV_BY_ZERO 3
#define COMPARISON_TRUE 1
#define COMPARISON_FALSE 0
#define OTHER_CALCULATION_OK 0
#define OTHER_CALCULATION_FAIL 1
#define CONVERSION_ERROR 1
#define CONVERSION_OK 0
#define ZERO 0
#define SIGN_MASK 1U << 31

#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_decimal.h"


Suite *add_suite1(void);
Suite *div_suite0(void);
Suite *div_suite1(void);
Suite *mul_suite0(void);
Suite *mul_suite1(void);
Suite *sub_suite1(void);

Suite *is_equal_suite1(void);
Suite *is_greater_suite1(void);
Suite *is_greater_or_equal_suite1(void);
Suite *is_less_suite1(void);
Suite *is_less_or_equal_suite1(void);
Suite *is_not_equal_suite1(void);

Suite *negate_suite1(void);
Suite *truncate_suite1(void);
Suite *floor_suite1(void);
Suite *round_suite1(void);

Suite *from_int_to_decimal_suite(void);
Suite *from_float_to_decimal_suite(void);
Suite *from_decimal_to_float_suite0(void);
Suite *from_decimal_to_float_suite1(void);
Suite *from_decimal_to_int_suite0(void);
Suite *from_decimal_to_int_suite1(void);
Suite *from_decimal_to_int_suite2(void);
Suite *test_from_float_to_decimal_s(void);




Suite *add_suite(void);
Suite *sub_suite(void);
Suite *mul_suite(void);
Suite *div_suite(void);



void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_div_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_div_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check);
void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_mul_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_mul_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check);
void test_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check);

void test_is_equal(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_greater(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_greater_or_equal(s21_decimal decimal1, s21_decimal decimal2,
                              int check);
void test_is_less(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_less_or_equal(s21_decimal decimal1, s21_decimal decimal2,
                           int check);
void test_is_not_equal(s21_decimal decimal1, s21_decimal decimal2, int check);

void test_negate(s21_decimal decimal, s21_decimal decimal_check);
void test_truncate(s21_decimal decimal, s21_decimal decimal_check);
void test_floor(s21_decimal decimal, s21_decimal decimal_check);
void test_round(s21_decimal decimal, s21_decimal decimal_check);

int s21_get_decimal_sign(s21_decimal value);

void test_from_int_to_decimal(int n, s21_decimal dcml);
void test_from_float_to_decimal(int f, s21_decimal decimal_check);
void test_from_decimal_to_float(s21_decimal decimal, int check);
void test_from_decimal_to_int(s21_decimal decimal, int check);
void test_from_decimal_to_int_fail(s21_decimal decimal);

#endif