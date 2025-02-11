#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_decimal temp1 = value_1;
    s21_decimal temp2 = value_2;
    reduction_of_degrees(&temp1, &temp2);
    int flag = 0;
    flag = logic(temp1, temp2, result);

    if (((flag >> 0 & 1) ^ (flag >> 1 & 1) ^ (flag >> 2 & 1)) == 0) {
        zero(result);
        int prev_ch = 0, cur_ch = 0;
        
        for (int i = 0; i < 96; i++) {
            int x = ((temp1.bits[i / 32] >> (i % 32)) & 1);
            int y = ((temp2.bits[i / 32] >> (i % 32)) & 1);
            cur_ch = x ^ y ^ prev_ch;
            result -> bits[i / 32] |= (cur_ch << (i % 32));
            prev_ch = (x + y + prev_ch > 1) ? 1 : 0;
        }  

        result -> bits[3] = degree(temp1) << 16;
        if (flag &= 4) result -> bits[3] = (1 << 31);
    } else {
        result -> bits[3] ^= (1 << 31);
        s21_sub(temp1, temp2, result);
    }

    return 0;
}