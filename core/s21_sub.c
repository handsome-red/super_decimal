#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_big_decimal temp1 = bringing_to_big(value_1);
    s21_big_decimal temp2 = bringing_to_big(value_2);
    s21_big_decimal temp_res = bringing_to_big(*result);
    reduction_of_degrees(&temp1, &temp2);
    result -> bits[3] ^= (1 << 31);
    int flag = 0;
    flag = logic(temp1, temp2, *result);

   if (((flag >> 0 & 1) ^ (flag >> 1 & 1) ^ (flag >> 2 & 1)) == 1) {
       zero(result);
       sub(temp1, temp2, &temp_res);
       temp_res.bits[7] = big_degree(temp1) << 16;
       if (flag < 3 || flag > 11) temp_res.bits[7] = (1 << 31);
       *result = reducing_to_less(temp_res);
    } else {
       s21_add(value_1, value_2, result);
    }
   return 0;
}