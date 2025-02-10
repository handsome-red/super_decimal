#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_decimal divisible = value_1;
    s21_decimal reduced = {0};
    s21_decimal deductible = value_2; 
    
    if (check_sign(divisible)) divisible.bits[3] ^= 1 << 31;
    if (check_sign(deductible)) deductible.bits[3] ^= 1 << 31;
    
    int bit_pos = used_bits(divisible);
    
    while (bit_pos >= 0) {
        if (degree(divisible) < degree(deductible)) {
            mul_by_10(&divisible);
            bit_pos = used_bits(divisible);
            zero(result);
            zero(&reduced);
        }
        if (unsigned_comparison(divisible, deductible) == 44)  {
            SAR(&reduced, divisible, deductible, &bit_pos, result);
            s21_sub(reduced, deductible, &reduced);
        } else mul_by_10(&divisible);

        if (bit_pos <= 0 && used_bits(reduced) != 0 && (unsigned_comparison(reduced, deductible) >> 5 & 1) && degree(divisible) < 5) {
            mul_by_10(&divisible);
            bit_pos = used_bits(divisible);
            zero(result);
            zero(&reduced);
        }
    }

    int deg = -degree(divisible) - (-degree(deductible));
    result -> bits[3] |= abs(deg) << 16;                   
   
    if (check_sign(value_1) ^ check_sign(value_2)) result -> bits[3] |= (1 << 31);
    inside2(divisible);
    inside2(deductible);
    
    return 0; 
}