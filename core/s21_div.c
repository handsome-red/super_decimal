#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    zero(result);
    s21_decimal divisible = value_1;
    s21_decimal reduced = {{0, 0, 0, 0}};
    s21_decimal deductible = value_2; 

    if (degree(divisible) < degree(deductible)) {
        reduction_of_degrees(&divisible, &deductible);
    }
    int deg = abs(degree(deductible) - degree(divisible));

    divisible.bits[3] = 0;
    deductible.bits[3] = 0;
    
    int bit_pos = used_bits(divisible);
    
    while (bit_pos >= 0) {

        if (unsigned_comparison(divisible, deductible) & 20)  {
            SAR(&reduced, divisible, deductible, &bit_pos, result);
            s21_sub(reduced, deductible, &reduced);
        } else { 
            mul_by_10(&divisible);
            bit_pos = used_bits(divisible);
        }

        if (bit_pos <= 0 && used_bits(reduced) != 0 && (unsigned_comparison(reduced, deductible) >> 5 & 1) && degree(divisible) < 5) {
            mul_by_10(&divisible);
            bit_pos = used_bits(divisible);
            zero(result);
            zero(&reduced);
        }
    }

    result -> bits[3] |= (deg + degree(divisible)) << 16;             
    if (check_sign(value_1) ^ check_sign(value_2)) result -> bits[3] |= (1 << 31);
    
    return 0; 
}