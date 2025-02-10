#include "../s21_decimal.h"

void mul_by_10(s21_decimal *dst) {  
    s21_decimal ten = {{10, 0, 0, 0}};
    int sign = 0;
    if (check_sign(*dst)) sign = 1;
    s21_mul(*dst, ten, dst);
    dst -> bits[3] = (degree(*dst) + 1) << 16;
    if (sign) dst -> bits[3] |= 1 << 31;
}

int used_bits(s21_decimal dst) {
int bit = 0;
for (int i = 95; i >= 0 && !bit; i--) {
    if (dst.bits[i / 32] >> i & 1) bit = i + 1;
}
return bit;
}

void SAR(s21_decimal *reduced, s21_decimal divisible, s21_decimal deductible, int *bit_pos, s21_decimal *result) {
    s21_decimal two = {{2, 0, 0, 0}};
    int flag = 0;
    for (int i = *bit_pos; i >= 0 && !flag; i--) {

        if ((divisible.bits[i / 32] >> i % 32) & 1) {
            s21_mul(*reduced, two, reduced);
            reduced -> bits[0] |= 1 << 0;
        } else s21_mul(*reduced, two, reduced);

        
        if (unsigned_comparison(*reduced, deductible) & 20) {
            flag = 1;
            s21_mul(*result, two, result);
            result -> bits[0] |= 1 << 0;
        } else s21_mul(*result, two, result);

        *bit_pos = *bit_pos - 1;
    }
}    

void incomplete_work(s21_decimal *dst, s21_decimal dst2, int n) {
    for (int i = 0; i + n < 96; i++) {
        if ((dst2.bits[i / 32] >> i % 32) & 1) {
            dst -> bits[(i + n) / 32] |= 1 << (i + n) % 32;
        }
    } 
}

void zero(s21_decimal *dst) {
    for (int i = 0; i < 4; i++) {
        dst -> bits[i] = 0;
    }
}

int last_number(s21_decimal dst) {
    int x = 0, tmp = 1;
    for(int i = 0; i < 96; i++) {
        if ((dst.bits[i / 32] >> i) & 1) x = (x + tmp) % 100; 
        tmp = (tmp * 2) % 100;
    }
    return x;
}

int degree(s21_decimal dst) {
    char z = 0;
    z = dst.bits[3] >> 16;
    return (int)z;
}

int check_sign(s21_decimal dst) {
    int flag = 0;
    flag = ((dst.bits[3] >> 31) & 1) ? 1 : 0;
    return flag;
}

int set_sign(int *src, s21_decimal *dst) {
    int flag = 0;
    if (*src < 0) {
        dst -> bits[3] = (1 << 31);
        flag = 1;
        *src = -*src;
    }
    return flag;
}

int comparison(s21_decimal value_1, s21_decimal value_2) {
    int flag = 0;
    for (int i = 95; i >= 0 && !flag; i--) {

        int x = (value_1.bits[i / 32] >> (i % 32)) & 1;
        int y = (value_2.bits[i / 32] >> (i % 32)) & 1;

        if (check_sign(value_1)) x *= -1;
        if (check_sign(value_2)) y *= -1; 

        if (x < y) flag = 35;
        if (x > y) flag = 44;
    }  
    if (!flag) flag = 26;

    return flag;
}

int unsigned_comparison(s21_decimal value_1, s21_decimal value_2) {
    int flag = 0;
    for (int i = 95; i >= 0 && flag == 0; i--) {

        int x = (value_1.bits[i / 32] >> (i % 32)) & 1;
        int y = (value_2.bits[i / 32] >> (i % 32)) & 1;

        if (x < y) flag = 35;
        if (x > y) flag = 44;
        
    }
    if (!flag) flag = 26;

    return flag;
}

int logic(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int flag = 0;
    if (check_sign(value_1)) flag |= 4;
    if (check_sign(value_2)) flag |= 1;
    if (check_sign(*result)) flag |= 2;
    if ((unsigned_comparison(value_1, value_2) >> 2 & 1)) flag |= 8;

    return flag;
}

char* inside(s21_decimal dst) {
    
    char* str = (char*)malloc(140 * sizeof(char));
    int str_index = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 31; j >= 0; j--) {   
            str[str_index++] = ((dst.bits[i] >> j) & 1) + '0';
        }
        str[str_index++] = '\n';
    }
    
    str[str_index] = '\0';

    return str;
}

void inside2(s21_decimal dst) {
    printf(" Число:  %d\n", dst.bits[0]);
    for(int i = 0; i <= 128; i++) {
        if (i > 31 && i % 32 == 0) printf("   bits[%d]\n", i / 32 - 1);
        if (i % 8 == 0) printf(" ");
        if (i < 128)printf("%d", dst.bits[i / 32] >> (31 - i % 32) & 1);
    }
    puts("\n");
}