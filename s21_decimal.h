#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H


#include <iso646.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "limits.h"
#include <check.h>

typedef struct {
    unsigned int bits[4];
} s21_decimal;

typedef struct {
    unsigned int bits[8];
} s21_big_decimal;


int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);


int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);              
int s21_is_equal(s21_decimal, s21_decimal);                             
int s21_is_not_equal(s21_decimal, s21_decimal);                          


int s21_from_int_to_decimal(int src, s21_decimal *dst);                   
int s21_from_float_to_decimal(float src, s21_decimal *dst);                
int s21_from_decimal_to_int(s21_decimal src, int *dst);                     
int s21_from_decimal_to_float(s21_decimal src, float *dst);               


int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);




int check_sign(s21_decimal dst);
int degree(s21_decimal dst);
int last_number(s21_big_decimal dst, int last);
int comparison(s21_decimal value_1, s21_decimal value_2);
void zero(s21_decimal *dst);
void inside2(s21_decimal dst);
void inside3(s21_big_decimal dst);
void div_by_10(s21_big_decimal *dst);
int set_sign(int *src, s21_decimal *dst);

s21_big_decimal bringing_to_big(s21_decimal temp);
void add(s21_big_decimal temp1, s21_big_decimal temp2, s21_big_decimal *result);
void sub(s21_big_decimal temp1, s21_big_decimal temp2, s21_big_decimal *result);

int logic(s21_big_decimal value_1, s21_big_decimal value_2, s21_decimal result);
int big_check_sign(s21_big_decimal dst);
int big_degree(s21_big_decimal dst);
void reduction_of_degrees(s21_big_decimal *temp1, s21_big_decimal *temp2);
void big_zero(s21_big_decimal *dst);
s21_decimal reducing_to_less(s21_big_decimal big);
int unsigned_comparison(s21_big_decimal value_1, s21_big_decimal value_2);
void incomplete_work(s21_big_decimal *dst, s21_big_decimal dst2, int n);
int used_bits(s21_big_decimal dst);
void SAR(s21_big_decimal *reduced, s21_big_decimal divisible, s21_big_decimal deductible, int *bit_pos, s21_big_decimal *result);
void offse_by_one(s21_big_decimal *dst);
void mul_by_10(s21_big_decimal *dst);
int checking_for_zero(s21_decimal dst);


#endif