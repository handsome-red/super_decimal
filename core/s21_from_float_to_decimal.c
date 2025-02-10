#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    zero(dst);
    char ch_num[30] = {0};
    char ch_degree[10] = {0};
    sprintf(ch_num, "%+e\n\n", src);
    strncat(ch_degree, ch_num + 10, 3);

    for(int i = 2; i < 8; i++) {
        ch_num[i] = ch_num[i + 1];
    }
    ch_num[8] = '\0';
    int num = atoi(ch_num);
    
    int degree = atoi(ch_degree) - 6;
   
    set_sign(&num, dst);

    while(num % 10 == 0 && degree != 0) {
        num /= 10;
        degree += 1;
    }
    dst -> bits[0] = num;
    dst -> bits[3] |= (abs(degree) & 255) << 16; 
    return 0;
}