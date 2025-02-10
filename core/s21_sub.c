#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int flag = 0;
    result -> bits[3] ^= (1 << 31);
    flag = logic(value_1, value_2, result);
    
   if (((flag >> 0 & 1) ^ (flag >> 1 & 1) ^ (flag >> 2 & 1)) == 1) {
       zero(result);
       int prev_ch = 0;
       for (int i = 0, x = 0, y = 0; i < 96; i++) {
           if (flag >> 3 & 1) {
               x = ((value_1.bits[i / 32] >> (i % 32)) & 1);
               y = ((value_2.bits[i / 32] >> (i % 32)) & 1);
           } else {
               x = ((value_2.bits[i / 32] >> (i % 32)) & 1);
               y = ((value_1.bits[i / 32] >> (i % 32)) & 1);
           }
           if (prev_ch < 0) x -= 1;
           prev_ch = x - y;
           if (prev_ch && prev_ch != -2) result -> bits[i / 32] |= (1 << (i % 32));
       }
       result -> bits[3] = (0 << 31);
       if (flag < 3 || flag > 11) result -> bits[3] |= (1 << 31);  
    } else {
       s21_add(value_1, value_2, result);
    }
   return 0;
}