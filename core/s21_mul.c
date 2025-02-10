#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    zero(result); 
    s21_decimal temp1 = {0}; 
    s21_decimal temp2 = {0};
   
    for (int i = 0; i < 96; i++) { 
        if ((value_2.bits[i / 32] >> i % 32) & 1) {
            zero(&temp1);
            zero(&temp2); 
            incomplete_work(&temp1, value_1, i);
            temp2 = *result; 
            
            zero(result);
            s21_add(temp1, temp2, result);
        }
    }
    if (check_sign(value_1) ^ check_sign(value_2)) result -> bits[3] = (1 << 31);
    result -> bits[3] |= (degree(value_1) + degree(value_2)) << 16; 
    return 0;
}