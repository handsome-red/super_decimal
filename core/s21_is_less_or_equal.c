#include "../s21_decimal.h"

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2){
    return ((comparison(value_1, value_2) >> 1) & 1);
}  