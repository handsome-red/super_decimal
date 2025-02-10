#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    zero(dst);
    set_sign(&src, dst);
    dst -> bits[0] = src;
    return 0; 
}