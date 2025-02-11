#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_decimal temp1 = value_1;
    s21_decimal temp2 = value_2;
    reduction_of_degrees(&temp1, &temp2);
    int flag = 0;
    result -> bits[3] ^= (1 << 31);
    flag = logic(temp1, temp2, result);
    
   if (((flag >> 0 & 1) ^ (flag >> 1 & 1) ^ (flag >> 2 & 1)) == 1) {
       zero(result);
       int prev_ch = 0;
       for (int i = 0, x = 0, y = 0; i < 96; i++) {
           if (flag >> 3 & 1) {
               x = ((temp1.bits[i / 32] >> (i % 32)) & 1);
               y = ((temp2.bits[i / 32] >> (i % 32)) & 1);
           } else {
               x = ((temp2.bits[i / 32] >> (i % 32)) & 1);
               y = ((temp1.bits[i / 32] >> (i % 32)) & 1);
           }
           if (prev_ch < 0) x -= 1;
           prev_ch = x - y;
           if (prev_ch && prev_ch != -2) result -> bits[i / 32] |= (1 << (i % 32));
       }

       result -> bits[3] = degree(temp1) << 16;
       if (flag < 3 || flag > 11) result -> bits[3] |= (1 << 31);  
    } else {
       s21_add(temp1, temp2, result);
    }
   return 0;
}