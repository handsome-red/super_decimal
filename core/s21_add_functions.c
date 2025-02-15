#include "../s21_decimal.h"


void div_by_10(s21_big_decimal *dst) {
    s21_big_decimal divisible = *dst;
    big_zero(dst);
    s21_big_decimal deductible = {{10, 0, 0, 0, 0, 0, 0, 0}};
    s21_big_decimal reduced = {0};
    int deg_sign = dst -> bits[7];
    
    int bit_pos = used_bits(divisible);
    while (bit_pos >= 0) {
        if (unsigned_comparison(divisible, deductible) & 20)  {
            SAR(&reduced, divisible, deductible, &bit_pos, dst);
            sub(reduced, deductible, &reduced);
        }
    }
    dst -> bits[7] = deg_sign;
}

void offse_by_one(s21_big_decimal *dst) {  
    s21_big_decimal temp = *dst;
    big_zero(dst);
    for (int i = 0; i + 1 < 224; i++) {
        if (temp.bits[i / 32] >> (i % 32) & 1) {
            dst -> bits[(i + 1) / 32] |= 1 << (i + 1) % 32;
        }
    } 
    dst -> bits[7] = temp.bits[7];
} 

void mul_by_10(s21_big_decimal *dst) {  
    s21_big_decimal temp1 = {0};
    s21_big_decimal temp2 = {0};
    temp1.bits[7] = dst -> bits[7];
    for (int i = 0; i + 3 < 224; i++) {
        if (dst -> bits[i / 32] >> (i % 32) & 1) {
            temp1.bits[(i + 1) / 32] |= 1 << (i + 1) % 32;
            temp2.bits[(i + 3) / 32] |= 1 << (i + 3) % 32;
        }
    } 
    add(temp1, temp2, dst);
    dst -> bits[7] = temp1.bits[7];
    dst -> bits[7] = (dst -> bits[7] & ~ (0x2F << 16)) | ((big_degree(temp1) + 1) << 16);
}

int used_bits(s21_big_decimal dst) {
    int bit = 0;
    for (int i = 223; i >= 0 && !bit; i--) {
        if (dst.bits[i / 32] >> i & 1) bit = i + 1;
    }
    return bit;
}

void SAR(s21_big_decimal *reduced, s21_big_decimal divisible, s21_big_decimal deductible, int *bit_pos, s21_big_decimal *result) {
    int flag = 0;
    for (int i = *bit_pos; i >= 0 && !flag && *bit_pos >= 0; i--) {

        offse_by_one(reduced);
        if ((divisible.bits[i / 32] >> i % 32) & 1) reduced -> bits[0] |= 1 << 0;
          
        offse_by_one(result);     
        if (unsigned_comparison(*reduced, deductible) & 20) {
            flag = 1;
            result -> bits[0] |= 1 << 0;
        }
        (*bit_pos)--;
    }
} 

void incomplete_work(s21_big_decimal *dst, s21_big_decimal dst2, int n) {
    for (int i = 0; i + n < 224; i++) {
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

void big_zero(s21_big_decimal *dst) {
    for (int i = 0; i < 8; i++) {
        dst -> bits[i] = 0;
    }
}

int last_number(s21_decimal dst, int last, int size) {
    int x = 0, tmp = 1, remains = 0, cycle = 0;
    if (last == 1) remains = 10;
    if (last == 2) remains = 100;
    if (size == 1) cycle  = 96;
    if (size == 2) cycle  = 224;

    for(int i = 0; i < cycle && remains && cycle; i++) {
        if ((dst.bits[i / 32] >> i) & 1) x = (x + tmp) % remains; 
        tmp = (tmp * 2) % remains;
    }
    return x;
}

int degree(s21_decimal dst) {
    char z = 0;
    z = dst.bits[3] >> 16;
    return (int)z;
}

int big_degree(s21_big_decimal dst) {
    char z = 0;
    z = dst.bits[7] >> 16;
    return (int)z;
}

int check_sign(s21_decimal dst) {
    int flag = 0;
    flag = ((dst.bits[3] >> 31) & 1) ? 1 : 0;
    return flag;
}

int big_check_sign(s21_big_decimal dst) {
    int flag = 0;
    flag = ((dst.bits[7] >> 31) & 1) ? 1 : 0;
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
    s21_big_decimal temp1 = bringing_to_big(value_1);
    s21_big_decimal temp2 = bringing_to_big(value_2);
    reduction_of_degrees(&temp1, &temp2);
    int flag = 0;
    for (int i = 223; i >= 0 && !flag; i--) {

        int x = (temp1.bits[i / 32] >> (i % 32)) & 1;
        int y = (temp2.bits[i / 32] >> (i % 32)) & 1;

        if (big_check_sign(temp1)) x *= -1;
        if (big_check_sign(temp2)) y *= -1; 

        if (x < y) flag = 35;
        if (x > y) flag = 44;
    }  
    if (!flag) flag = 26;

    return flag;
}

int unsigned_comparison(s21_big_decimal value_1, s21_big_decimal value_2) {
    int flag = 0;
    for (int i = 223; i >= 0 && flag == 0; i--) {

        int x = (value_1.bits[i / 32] >> (i % 32)) & 1;
        int y = (value_2.bits[i / 32] >> (i % 32)) & 1;

        if (x < y) flag = 35;
        if (x > y) flag = 44;
        
    }
    if (!flag) flag = 26;

    return flag;
}

int logic(s21_big_decimal value_1, s21_big_decimal value_2, s21_decimal result) {
    int flag = 0;
    if (big_check_sign(value_1)) flag |= 4;
    if (big_check_sign(value_2)) flag |= 1;
    if (check_sign(result)) flag |= 2;
    if ((unsigned_comparison(value_1, value_2) >> 2 & 1)) flag |= 8;

    return flag;
}

void inside2(s21_decimal dst) {
    printf(" Число:   %c%de-%.2d\n", dst.bits[3] & 1 << 31 ? '-' : ' ', dst.bits[0], degree(dst));
    for(int i = 0; i <= 128; i++) {
        if (i > 31 && i % 32 == 0) printf("   bits[%d]\n", i / 32 - 1);
        if (i % 8 == 0) printf(" ");
        if (i < 128)printf("%d", dst.bits[i / 32] >> (31 - i % 32) & 1);
    }
    puts("\n");
}

void reduction_of_degrees(s21_big_decimal *temp1, s21_big_decimal *temp2) {
    int x = big_degree(*temp1);
    int y = big_degree(*temp2);
    while (x != y) {
        if (x > y) {
            mul_by_10(temp2);
            y++;
        } else if (x < y) {
            mul_by_10(temp1);
            x++;
        }
    }
}

void inside3(s21_big_decimal dst) {
    printf(" Число:   %c%d\n", dst.bits[6] & 1 << 31 ? '-' : ' ', dst.bits[0]);
    for(int i = 0; i <= 256; i++) {
        if (i > 31 && i % 32 == 0) printf("   bits[%d]\n", i / 32 - 1);
        if (i % 8 == 0) printf(" ");
        if (i < 256)printf("%d", dst.bits[i / 32] >> (31 - i % 32) & 1);
    }
    puts("\n");
}

s21_big_decimal bringing_to_big(s21_decimal less) {
    s21_big_decimal big = {0};
    big.bits[0] = less.bits[0];
    big.bits[1] = less.bits[1];
    big.bits[2] = less.bits[2];
    big.bits[7] = less.bits[3];
    return big;
}

s21_decimal reducing_to_less(s21_big_decimal big) {
    s21_decimal less = {0};
    less.bits[0] = big.bits[0];
    less.bits[1] = big.bits[1];
    less.bits[2] = big.bits[2];
    less.bits[3] = big.bits[7];
    return less;
}

void add(s21_big_decimal temp1, s21_big_decimal temp2, s21_big_decimal *result) {
    big_zero(result);
    int prev_ch = 0, cur_ch = 0;        
    for (int i = 0; i < 224; i++) {
        int x = ((temp1.bits[i / 32] >> (i % 32)) & 1);
        int y = ((temp2.bits[i / 32] >> (i % 32)) & 1);
        cur_ch = x ^ y ^ prev_ch;

        result -> bits[i / 32] |= (cur_ch << (i % 32));
        prev_ch = (x + y + prev_ch > 1) ? 1 : 0;
    }  
}

void sub(s21_big_decimal temp1, s21_big_decimal temp2, s21_big_decimal *result) {
    big_zero(result);
    int prev_ch = 0;
    for (int i = 0, x = 0, y = 0; i < 224; i++) {
        if ((unsigned_comparison(temp1, temp2) >> 2 & 1)) {
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
}

int checking_for_zero(s21_decimal dst) {
    int flag = (!dst.bits[0] && !dst.bits[1] && !dst.bits[2]) ? 1 : 0;
    return flag;
}