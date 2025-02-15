#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    zero(result); 
    s21_big_decimal temp1 = bringing_to_big(value_1);
    s21_big_decimal temp2 = {0};
    s21_big_decimal temp_res = {0};
    for (int i = 0; i < 96; i++) { 
        if ((value_2.bits[i / 32] >> i % 32) & 1) {
            big_zero(&temp2); 
            incomplete_work(&temp2, temp1, i);
            add(temp_res, temp2, &temp_res);
        }
    }
    *result = reducing_to_less(temp_res);
    if (check_sign(value_1) ^ check_sign(value_2)) result -> bits[3] = (1 << 31);
    result -> bits[3] |= (degree(value_1) + degree(value_2)) << 16; 
    return 0;
}