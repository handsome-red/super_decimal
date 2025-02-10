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


//Арифметические операторы
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); //  +
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); //  -
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); //  *
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); //  :

//Операторы сравнения
int s21_is_less(s21_decimal, s21_decimal);                                  //  <
int s21_is_less_or_equal(s21_decimal, s21_decimal);                         //  <=
int s21_is_greater(s21_decimal, s21_decimal);                               //  />
int s21_is_greater_or_equal(s21_decimal, s21_decimal);                      //  />=
int s21_is_equal(s21_decimal, s21_decimal);                                 //  ==
int s21_is_not_equal(s21_decimal, s21_decimal);                             //  !=

//Преобразователи
int s21_from_int_to_decimal(int src, s21_decimal *dst);                     //  Из int
int s21_from_float_to_decimal(float src, s21_decimal *dst);                 //  Из float
int s21_from_decimal_to_int(s21_decimal src, int *dst);                     //  В int
int s21_from_decimal_to_float(s21_decimal src, float *dst);                 //  В float


int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);



//  Дополнительные функции:
char* inside(s21_decimal dst);
//  Функция перевода битов в понятный вид
int check_sign(s21_decimal dst);
//  Функция проверки знака(плюс или минус)
int degree(s21_decimal dst);
//  Функция вытаскивания степени из децимала
int last_number(s21_decimal dst);
//  Функция определения последней цифры для округления
int comparison(s21_decimal value_1, s21_decimal value_2);
int unsigned_comparison(s21_decimal value_1, s21_decimal value_2);
void zero(s21_decimal *dst);
void inside2(s21_decimal dst);
void mul_by_10(s21_decimal *dst);
int set_sign(int *src, s21_decimal *dst);
int logic(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int used_bits(s21_decimal dst);
void incomplete_work(s21_decimal *dst, s21_decimal dst2, int n);
void SAR(s21_decimal *reduced, s21_decimal divisible, s21_decimal deductible, int *bit_pos, s21_decimal *result);

#endif