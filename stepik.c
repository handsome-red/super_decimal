#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned int bits[4];
} s21_decimal;


//Арифметические операторы
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); //  +
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); //  -
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); //  *
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); //  :


//Операторы сравнения
int s21_is_less(s21_decimal, s21_decimal);                  //  <
int s21_is_less_or_equal(s21_decimal, s21_decimal);         //  <=
int s21_is_greater(s21_decimal, s21_decimal);               //  />
int s21_is_greater_or_equal(s21_decimal, s21_decimal);                      //  />=
int s21_is_equal(s21_decimal, s21_decimal);                                 //  ==
int s21_is_not_equal(s21_decimal, s21_decimal);                             //  !=
// Возвращаемое значение:
// - 0 — FALSE
// - 1 — TRUE

//Преобразователи
int s21_from_int_to_decimal(int src, s21_decimal *dst);                     //  Из int
int s21_from_float_to_decimal(float src, s21_decimal *dst);                 //  Из float
int s21_from_decimal_to_int(s21_decimal src, int *dst);                     //  В int
int s21_from_decimal_to_float(s21_decimal src, float *dst);                 //  В float
// Возвращаемое значение — код ошибки:
// - 0 — OK
// - 1 — ошибка конвертации

// *Уточнение про преобразование числа типа float:*
// - *Если числа слишком малы (0 < |x| < 1e-28), возвращай ошибку и значение, равное 0*.
// - *Если числа слишком велики (|x| > 79,228,162,514,264,337,593,543,950,335) или равны бесконечности, возвращай ошибку*.
// - *При обработке числа с типом float преобразовывай все содержащиеся в нём значимые десятичные цифры. Если таких цифр больше 7,
// то значение числа должно округляться к ближайшему, у которого не больше 7 значимых цифр.*

// *Уточнение про преобразование из числа типа decimal в тип int:*
// - *Если в числе типа decimal есть дробная часть, то её следует отбросить (например, 0.9 преобразуется 0)*.

int s21_floor(s21_decimal value, s21_decimal *result);
//  Округляет указанное Decimal число до ближайшего целого числа в сторону отрицательной бесконечности
int s21_round(s21_decimal value, s21_decimal *result);
//  Округляет Decimal до ближайшего целого числа
int s21_truncate(s21_decimal value, s21_decimal *result);
//  Возвращает целые цифры указанного Decimal числа; любые дробные цифры отбрасываются, включая конечные нули.
int s21_negate(s21_decimal value, s21_decimal *result);
//  Возвращает результат умножения указанного Decimal на -1.



//  Дополнительные функции:

char* inside(s21_decimal dst);
//  Функция перевода битов в понятный вид
int check_sign(s21_decimal dst);
//  Функция проверки знака(плюс или минус)
int degree(s21_decimal dst);
//  Функция вытаскивания степени из децимала
int last_number(s21_decimal dst);
//  Функция определения последней цифры для округления
int comparison(s21_decimal value_1, s21_decimal value_2);
int unsigned_comparison(s21_decimal value_1, s21_decimal value_2);
void zero(s21_decimal *dst);
void inside2(s21_decimal dst);
void mull_by_10(s21_decimal *dst);
int occupied_bits(s21_decimal dst);
void incomplete_work(s21_decimal *dst, s21_decimal dst2, int n);


int main ( ) {
    char str[100] = {0};
    s21_decimal dst_y = {0};

    s21_decimal value_1 = {0};//{{0xFFFFFFFF, 0, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {0};//{{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_decimal result_plus = {0};
    s21_decimal result_minus = {0};

    int x = -30;
    int x2 = 10;
    //float y = 0.00000000000000000000000000000001;
    //float y = 10.00;
    float y = -0.003;

    s21_from_int_to_decimal(x, &value_1);
    s21_from_int_to_decimal(x2, &value_2);
    //value_1.bits[1] = 2;
    // value_2.bits[1] = 3;
    s21_add(value_1, value_2, &result_plus);
    s21_sub(value_1, value_2, &result_minus);
    

    printf("Число:   %d\n", x);
    printf("%s\n\n", inside(value_1));
    printf("Число:   %d\n", x2);
    printf("%s\n\n", inside(value_2));


    printf("%+d + (%+d) = %c%d\n", x, x2, (check_sign(result_plus)) ? '-' : '+', result_plus.bits[0]);
    printf("%s\n\n", inside(result_plus));
    printf("%+d - (%+d) = %c%d\n", x, x2, (check_sign(result_minus)) ? '-' : '+', result_minus.bits[0]);
    printf("%s\n\n", inside(result_minus));

// for (int i = -30; i < 31; i ++) {
//     zero(&result_minus);
//     zero(&result_plus);
// s21_from_int_to_decimal(i, &value_1);
//     s21_from_int_to_decimal(10, &value_2);
// s21_sub(value_1, value_2, &result_minus);
//     printf("%+d - (%+d) = %c%d\n", i, 10, (check_sign(result_minus)) ? '-' : '+', result_minus.bits[0]);
// }
    
    
// for (int i = -30; i < 31; i ++) {
//     zero(&result_minus);
//     zero(&result_plus);
// s21_from_int_to_decimal(10, &value_1);
//     s21_from_int_to_decimal(i, &value_2);
// s21_sub(value_1, value_2, &result_minus);
//     printf("%+d - (%+d) = %c%d\n", 10, i, (check_sign(result_minus)) ? '-' : '+', result_minus.bits[0]);
// }


    sprintf(str, "%e\n", y);
    s21_from_float_to_decimal(y, &dst_y);

    printf("Число:   %de%+d\n",dst_y.bits[0], degree(dst_y));
    
    printf("%s\n\n", inside(dst_y));
    

    puts("Проверка степени:");
    printf("%e\n", y);
    printf("%de%+d\n\n",dst_y.bits[0], degree(dst_y));

    puts("Функции сравнения:");
    printf("%d %s %d\n", x, (s21_is_less(value_1, value_2)) ? "< " : "  ", x2);
    printf("%d %s %d\n", x, (s21_is_less_or_equal(value_1, value_2)) ? "<=" : "  ", x2);
    printf("%d %s %d\n", x, (s21_is_greater(value_1, value_2)) ? "> " : "  ", x2);
    printf("%d %s %d\n", x, (s21_is_greater_or_equal(value_1, value_2)) ? ">=" : "  ", x2);
    printf("%d %s %d\n", x, (s21_is_equal(value_1, value_2)) ? "==" : "  ", x2);
    printf("%d %s %d\n", x, (s21_is_not_equal(value_1, value_2)) ? "!=" : "  ", x2);
    
    puts("Функция определения последних двух цифр для округления:");
    printf(" Число: %d \n Последние две цифры: %d\n\n", value_1.bits[0], last_number(value_1));


    zero(&result_plus);
    zero(&result_minus);
    s21_from_int_to_decimal(10, &value_1);
    s21_from_int_to_decimal(5, &value_2);
    s21_add(value_1, value_2, &result_plus);
    printf("%+d + (%+d) = %c%d\n", 10, 5, (check_sign(result_plus)) ? '-' : '+', result_plus.bits[0]);
    zero(&result_plus);
    s21_from_int_to_decimal(5, &value_1);
    s21_from_int_to_decimal(10, &value_2);
    s21_add(value_1, value_2, &result_plus);    
    printf("%+d + (%+d) = %c%d\n", 5, 10, (check_sign(result_plus)) ? '-' : '+', result_plus.bits[0]);
    zero(&result_minus);
    s21_from_int_to_decimal(10, &value_1);
    s21_from_int_to_decimal(-5, &value_2);
    s21_sub(value_1, value_2, &result_minus);
    printf("%+d - (%+d) = %c%d\n", 10, -5, (check_sign(result_minus)) ? '-' : '+', result_minus.bits[0]);
    zero(&result_minus);
    s21_from_int_to_decimal(5, &value_1);
    s21_from_int_to_decimal(-10, &value_2);
    s21_sub(value_1, value_2, &result_minus);
    printf("%+d - (%+d) = %c%d\n", 5, -10, (check_sign(result_minus)) ? '-' : '+', result_minus.bits[0]);
    zero(&result_plus);
    s21_from_int_to_decimal(10, &value_1);
    s21_from_int_to_decimal(-5, &value_2);
    s21_add(value_1, value_2, &result_plus);
    printf("%+d + (%+d) = %c%d\n", 10, -5, (check_sign(result_plus)) ? '-' : '+', result_plus.bits[0]);
    zero(&result_minus);
    s21_from_int_to_decimal(10, &value_1);
    s21_from_int_to_decimal(5, &value_2);
    s21_sub(value_1, value_2, &result_minus);
    printf("%+d - (%+d) = %c%d\n", 10, 5, (check_sign(result_minus)) ? '-' : '+', result_minus.bits[0]);
    zero(&result_plus);
    s21_from_int_to_decimal(-5, &value_1);
    s21_from_int_to_decimal(10, &value_2);
    s21_add(value_1, value_2, &result_plus);
    printf("%+d + (%+d) = %c%d\n", -5, 10, (check_sign(result_plus)) ? '-' : '+', result_plus.bits[0]);
    zero(&result_minus);
    s21_from_int_to_decimal(-5, &value_1);
    s21_from_int_to_decimal(-10, &value_2);
    s21_sub(value_1, value_2, &result_minus);
    printf("%+d - (%+d) = %c%d\n", -5, -10, (check_sign(result_minus)) ? '-' : '+', result_minus.bits[0]);
    zero(&result_plus);
    s21_from_int_to_decimal(-10, &value_1);
    s21_from_int_to_decimal(5, &value_2);
    s21_add(value_1, value_2, &result_plus);
    printf("%+d + (%+d) = %c%d\n", -10, 5, (check_sign(result_plus)) ? '-' : '+', result_plus.bits[0]);
    zero(&result_minus);
    s21_from_int_to_decimal(-10, &value_1);
    s21_from_int_to_decimal(-5, &value_2);
    s21_sub(value_1, value_2, &result_minus);
    printf("%+d - (%+d) = %c%d\n", -10, -5, (check_sign(result_minus)) ? '-' : '+', result_minus.bits[0]);
    zero(&result_plus);
    s21_from_int_to_decimal(5, &value_1);
    s21_from_int_to_decimal(-10, &value_2);
    s21_add(value_1, value_2, &result_plus);
    printf("%+d + (%+d) = %c%d\n", 5, -10, (check_sign(result_plus)) ? '-' : '+', result_plus.bits[0]);
    zero(&result_minus);
    s21_from_int_to_decimal(5, &value_1);
    s21_from_int_to_decimal(10, &value_2);
    s21_sub(value_1, value_2, &result_minus);
    printf("%+d - (%+d) = %c%d\n", 5, 10, (check_sign(result_minus)) ? '-' : '+', result_minus.bits[0]);
    zero(&result_plus);
    s21_from_int_to_decimal(-10, &value_1);
    s21_from_int_to_decimal(-5, &value_2);
    s21_add(value_1, value_2, &result_plus);
    printf("%+d + (%+d) = %c%d\n", -10, -5, (check_sign(result_plus)) ? '-' : '+', result_plus.bits[0]);
    zero(&result_minus);
    s21_from_int_to_decimal(-10, &value_1);
    s21_from_int_to_decimal(5, &value_2);
    s21_sub(value_1, value_2, &result_minus);
    printf("%+d - (%+d) = %c%d\n", -10, 5, (check_sign(result_minus)) ? '-' : '+', result_minus.bits[0]);
    zero(&result_plus);
    s21_from_int_to_decimal(-5, &value_1);
    s21_from_int_to_decimal(-10, &value_2);
    s21_add(value_1, value_2, &result_plus);
    printf("%+d + (%+d) = %c%d\n", -5, -10, (check_sign(result_plus)) ? '-' : '+', result_plus.bits[0]);
    zero(&result_minus);
    s21_from_int_to_decimal(-5, &value_1);
    s21_from_int_to_decimal(10, &value_2);
    s21_sub(value_1, value_2, &result_minus);
    printf("%+d - (%+d) = %c%d\n", -5, 10, (check_sign(result_minus)) ? '-' : '+', result_minus.bits[0]);

    // int z = 5;
    // z = z << 4;
    // printf("%d\n", z); 
    s21_decimal result_mul = {0};
    for(int i = 1; i < 11; i++) {
        for(int j = 1; j < 11; j++) {
            zero(&value_1);
            zero(&value_2);
            s21_from_int_to_decimal(i, &value_1);
            s21_from_int_to_decimal(j, &value_2);
            s21_mul(value_1, value_2, &result_mul);
            printf(" %d ", result_mul.bits[0]);
        }
        puts("\n");
    }
    

    s21_decimal result_div = {0};
    zero(&value_1);
    zero(&value_2);
    zero(&result_div);

            s21_from_float_to_decimal(-30.3, &value_1);   
            s21_from_int_to_decimal(-3, &value_2);
            s21_div(value_1, value_2, &result_div);
    
    inside2(result_div);
    
    return 0;
}

void mull_by_10(s21_decimal *dst) {
    s21_decimal ten = {0};
    s21_from_int_to_decimal(10, &ten);
    s21_mul(*dst, ten, dst);
    dst -> bits[3] = (degree(*dst) + 1) << 16;
}

int occupied_bits(s21_decimal dst) {
    int bit = 0;
    for (int i = 95; i >= 0 && !bit; i--) {
        if (dst.bits[i / 32] >> i & 1) bit = i;
    }
    return bit;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_decimal temp1 = value_1;
    s21_decimal temp2 = value_2;
    temp1.bits[3] |= 0 << 31;
    temp2.bits[3] |= 0 << 31;

    //temp1.bits[1] |= 15 << 4;

    while (unsigned_comparison(temp1, temp2) == 35) {
        mull_by_10(&temp1);
    }

    printf("%d\n", occupied_bits(temp1));
    printf("%d\n", occupied_bits(value_2));
    int bit1 = occupied_bits(temp1);
    int bit2 = occupied_bits(value_2);

    s21_decimal temp1_1 = {0};
    for (int i = bit1; i >= 0 && bit2 >= 0; i--) {
        if ((temp1.bits[i / 32] >> i % 32) & 1) {
            temp1_1.bits[bit2 / 32] |= 1 << bit2 % 32;
        }
         bit2--;
    }

    //temp1_1.bits[(bit1 - bit2) / 32] = temp1.bits[(bit1 - bit2) / 32] >> (bit1 - bit2) % 32;

    inside2(temp1);
    inside2(value_2);
    inside2(temp1_1);
    

    // for (int i = 95; i >= 0; i++) {
        
    // }
    *result = temp1;
    
    return 0; 
}

void incomplete_work(s21_decimal *dst, s21_decimal dst2, int n) {
    for (int i = 0; i < 96; i++) {
        if ((dst2.bits[i / 32] >> i % 32) & 1) {
            dst -> bits[(i + n) / 32] |= 1 << (i + n) % 32;
        }
    }
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    zero(result);
    s21_decimal temp1 = {0};
    s21_decimal temp2 = {0};

    for (int i = 0; i < 96; i++) {
        if ((value_2.bits[i / 32] >> i % 32) & 1) {
            zero(&temp1);
            zero(&temp2);
            incomplete_work(&temp1, value_1, i); 
            temp2 = *result;

            zero(result);
            s21_add(temp1, temp2, result);
        }
    }
    if (check_sign(value_1) ^ check_sign(value_2)) result -> bits[3] = (1 << 31);
    result -> bits[3] = degree(value_1) << 16; 
    return 0;
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
        int x = (check_sign(value_1)) ? -(value_1.bits[i / 32] >> i % 32): value_1.bits[i / 32] >> i % 32;
        int y = (check_sign(value_2)) ? -(value_2.bits[i / 32] >> i % 32): value_2.bits[i / 32] >> i % 32;
        if (x < y) flag = 35;
        if (x > y) flag = 44;
    }  
    if (!flag) flag = 26;
    return flag;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    return ((comparison(value_1, value_2) >> 0) & 1);
}    

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2){
    return ((comparison(value_1, value_2) >> 1) & 1);
}   

int s21_is_greater(s21_decimal value_1, s21_decimal value_2){
    return ((comparison(value_1, value_2) >> 2) & 1);
}    

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2){
    return ((comparison(value_1, value_2) >> 3) & 1);
}   

int s21_is_equal(s21_decimal value_1, s21_decimal value_2){
    return ((comparison(value_1, value_2) >> 4) & 1);
}  

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2){
    return ((comparison(value_1, value_2) >> 5) & 1);
}

int unsigned_comparison(s21_decimal value_1, s21_decimal value_2) {
    int flag = 0;
    for (int i = 95; i >= 0 && flag == 0; i--) {
        int x = (value_1.bits[i / 32] >> (i % 32) & 1);
        int y = (value_2.bits[i / 32] >> (i % 32) & 1);
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

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int flag = 0;
    flag = logic(value_1, value_2, result);
    // ((check_sign(value_1) ^ check_sign(value_2) ^ check_sign(*result)) == 0)
    if (((flag >> 0 & 1) ^ (flag >> 1 & 1) ^ (flag >> 2 & 1)) == 0) {
    //if (flag == 0 || flag == 8 || flag == 3 || flag == 5 || flag == 6 || flag == 11 || flag == 13 || flag == 14) {
        
        int prev_ch = 0, cur_ch = 0;  //previous_char //current_char
        for (int i = 0; i < 96; i++) {
            int x = ((value_1.bits[i / 32] >> (i % 32)) & 1);
            int y = ((value_2.bits[i / 32] >> (i % 32)) & 1);
            cur_ch = x ^ y ^ prev_ch;
            result -> bits[i / 32] |= (cur_ch << (i % 32));
            prev_ch = (x + y + prev_ch > 1) ? 1 : 0;
        }  
        result -> bits[3] = (0 << 31);
        if (flag &= 4) result -> bits[3] = (1 << 31); //(check_sign(value_1) == 1)
    } else {
        result -> bits[3] ^= (1 << 31);
        s21_sub(value_1, value_2, result);
    }

    return 0;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
     int flag = 0;
     result -> bits[3] ^= (1 << 31);
     flag = logic(value_1, value_2, result);
    // ((check_sign(value_1) ^ check_sign(value_2) ^ check_sign(*result)) == 1)
    if (((flag >> 0 & 1) ^ (flag >> 1 & 1) ^ (flag >> 2 & 1)) == 1) {
    //if (flag == 1|| flag == 2 || flag == 4 || flag == 7 || flag == 9|| flag == 10 || flag == 12 || flag == 15) {
        int prev_ch = 0;  //prev_char
        for (int i = 0, x = 0, y = 0; i < 96; i++) {
            if (flag >> 3 & 1) {
                x = ((value_1.bits[i / 32] >> (i % 32)) & 1);
                y = ((value_2.bits[i / 32] >> (i % 32)) & 1);
            } else {
                x = ((value_2.bits[i / 32] >> (i % 32)) & 1);
                y = ((value_1.bits[i / 32] >> (i % 32)) & 1);
            }
            //int x = ((flag >> 3) & 1) ? ((value_1.bits[i / 32] >> (i % 32)) & 1) : ((value_2.bits[i / 32] >> (i % 32)) & 1);
            //int y = ((flag >> 3) & 1) ? ((value_2.bits[i / 32] >> (i % 32)) & 1) : ((value_1.bits[i / 32] >> (i % 32)) & 1);
            if (prev_ch < 0) x -= 1;
            prev_ch = x - y;
            if (prev_ch && prev_ch != -2) result -> bits[i / 32] |= (1 << (i % 32));
            //result -> bits[i / 32] |= (prev_ch && prev_ch != -2) ? (1 << (i % 32)) : (0 << (i % 32));
        }
        result -> bits[3] = (0 << 31);
        //if (check_sign(value_2) &&  ||
        //    check_sign(*result) ||
        //   (check_sign(value_1) && flag) ||
        //    )
        if (flag < 3 || flag > 11) result -> bits[3] = (1 << 31); 
        //if (flag == 1 || flag == 2 || flag == 12 || flag == 15) result -> bits[3] = (1 << 31); 
     } else {
        s21_add(value_1, value_2, result);
     }
    return 0;
}

// Побитовые операции И ( & ), ИЛИ ( | ), ИСКЛЮЧАЮЩЕЕ ИЛИ ( ^ ), НЕ ( ~ )

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    zero(dst);
    set_sign(&src, dst);
    dst -> bits[0] = src;
    return 0; 
}

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
    while(!(num % 10)) {
        num /= 10;
        degree += 1;
    }

    dst -> bits[0] = num;
    dst -> bits[3] |= (abs(degree) & 255) << 16; 
    return 0;
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