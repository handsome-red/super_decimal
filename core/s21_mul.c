#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (result == NULL) return puts("erorr");
    if (checking_3_bytes(value_1) || checking_3_bytes(value_2)) return puts("erorr");
    zero(result); 
    if (checking_for_zero(value_1) || checking_for_zero(value_2)) return 0;

    s21_big_decimal temp1 = bringing_to_big(value_1);
    s21_big_decimal temp2 = {0};
    s21_big_decimal temp_res = {0};
    int sign = check_sign(value_1) ^ check_sign(value_2) ? 1 : 0;
    int deg = degree(value_1) + degree(value_2);

    for (int i = 0; i < 96; i++) { 
        if ((value_2.bits[i / 32] >> i % 32) & 1) {
            big_zero(&temp2); 
            incomplete_work(&temp2, temp1, i);
            add(temp_res, temp2, &temp_res);
        }
    }

    rounding_up(&temp_res, &deg);

    s21_big_decimal temp_res_big = {{0, 0, 0, 1, 0, 0, 0, 0}};
    s21_big_decimal temp_res_NULL = {{0, 0, 0, 0, 0, 0, 0, 0}};

    if ((deg < 0 && sign) || (unsigned_comparison(temp_res, temp_res_NULL) == 26 && deg >= 28)
    || (unsigned_comparison(temp_res_big, temp_res) == 26 && sign) || deg > 28) return 2;
    if ((deg < 0 && !sign) || (unsigned_comparison(temp_res_big, temp_res) == 26 && !sign)) return 1;

    *result = reducing_to_less(temp_res, deg, sign);
    
    return 0;
}