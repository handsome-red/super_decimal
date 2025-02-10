#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int flag = 0;
    flag = logic(value_1, value_2, result);

    if (((flag >> 0 & 1) ^ (flag >> 1 & 1) ^ (flag >> 2 & 1)) == 0) {
        zero(result);
        int prev_ch = 0, cur_ch = 0;
        
        for (int i = 0; i < 96; i++) {
            int x = ((value_1.bits[i / 32] >> (i % 32)) & 1);
            int y = ((value_2.bits[i / 32] >> (i % 32)) & 1);
            cur_ch = x ^ y ^ prev_ch;
            result -> bits[i / 32] |= (cur_ch << (i % 32));
            prev_ch = (x + y + prev_ch > 1) ? 1 : 0;
        }  

        result -> bits[3] = (0 << 31);
        if (flag &= 4) result -> bits[3] = (1 << 31);
    } else {
        result -> bits[3] ^= (1 << 31);
        s21_sub(value_1, value_2, result);
    }

    return 0;
}