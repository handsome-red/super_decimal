#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (checking_for_zero(value_2)) return 3;
    zero(result);
    s21_big_decimal divisible = bringing_to_big(value_1);
    s21_big_decimal deductible = bringing_to_big(value_2);
    s21_big_decimal reduced = {0};
    s21_big_decimal temp_res = {0};

    if (big_degree(divisible) < big_degree(deductible)) {
        reduction_of_degrees(&divisible, &deductible);
    }
    int deg = abs(big_degree(deductible) - big_degree(divisible));

    divisible.bits[7] = 0;
    deductible.bits[7] = 0;
    
    int bit_pos = used_bits(divisible);
    while (bit_pos >= 0) {

        if (unsigned_comparison(divisible, deductible) & 20)  {
            SAR(&reduced, divisible, deductible, &bit_pos, &temp_res);
            sub(reduced, deductible, &reduced);
        } else { 
            mul_by_10(&divisible);
            bit_pos = used_bits(divisible);
        }
        if (bit_pos <= 0 && used_bits(reduced) != 0 && (unsigned_comparison(reduced, deductible) >> 5 & 1) && big_degree(divisible) < 28) {
            mul_by_10(&divisible);
            bit_pos = used_bits(divisible);
            big_zero(&temp_res);
            big_zero(&reduced);
        }
    }
    *result = reducing_to_less(temp_res);
    result -> bits[3] |= (deg + big_degree(divisible)) << 16;             
    if (check_sign(value_1) ^ check_sign(value_2)) result -> bits[3] |= (1 << 31);
    
    return 0; 
}