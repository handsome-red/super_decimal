#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_big_decimal temp1 = bringing_to_big(value_1);
    s21_big_decimal temp2 = bringing_to_big(value_2);
    s21_big_decimal temp_res = {0};

    reduction_of_degrees(&temp1, &temp2);
    int flag = 0;
    flag = logic(temp1, temp2, *result);

    if (((flag >> 0 & 1) ^ (flag >> 1 & 1) ^ (flag >> 2 & 1)) == 0) {
        zero(result);
        add(temp1, temp2, &temp_res);
        temp_res.bits[7] = big_degree(temp1) << 16;
        if (flag &= 4) temp_res.bits[7] = (1 << 31);
        *result = reducing_to_less(temp_res);
    } else {
        result -> bits[3] ^= (1 << 31);
        s21_sub(value_1, value_2, result);
    } 
    return 0;
}