#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned int bits[4];
} s21_decimal;

typedef struct {
    s21_decimal decimals[2];
} s21_big_decimal;

//Арифметические операторы
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result_plus); //  +
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result_plus); //  -
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result_plus); //  *
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result_plus); //  :


//Операторы сравнения
int s21_is_less(s21_decimal value_1, s21_decimal value_2);                  //  <
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);         //  <=
int s21_is_greater(s21_decimal, s21_decimal);                               //  />
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

int s21_floor(s21_decimal value, s21_decimal *result_plus);
//  Округляет указанное Decimal число до ближайшего целого числа в сторону отрицательной бесконечности
int s21_round(s21_decimal value, s21_decimal *result_plus);
//  Округляет Decimal до ближайшего целого числа
int s21_truncate(s21_decimal value, s21_decimal *result_plus);
//  Возвращает целые цифры указанного Decimal числа; любые дробные цифры отбрасываются, включая конечные нули.
int s21_negate(s21_decimal value, s21_decimal *result_plus);
//  Возвращает результат умножения указанного Decimal на -1.

int find_scale (s21_decimal value);
// Определение степени.


int pow_int(int x, int y);
char* inside(s21_decimal dst);
int check_sign(s21_decimal dst);
int degree(s21_decimal dst);
int last_number(s21_decimal dst);

int main ( ) {
    char str[100] = {0};
    s21_decimal dst_y = {0};

    s21_decimal value_1 = {0};
    s21_decimal value_2 = {0};
    s21_decimal result_plus = {0};
    s21_decimal result_minus = {0};

    int x = 221329;
    int x2 = 1;
    //float y = 0.00000000000000000000000000000001;
    float y = -123.0;
    //float y = -0.00000000000000000000000001305961231313;

    s21_from_int_to_decimal(x, &value_1);
    s21_from_int_to_decimal(x2, &value_2);
    s21_add(value_1, value_2, &result_plus);
    s21_sub(value_1, value_2, &result_minus);
    


    printf("Число:   %d\n", value_1.bits[0]);
    printf("%s\n\n", inside(value_1));
    printf("Число:   %d\n", value_2.bits[0]);
    printf("%s\n\n", inside(value_2));


    printf("%d + %d = %d\n", value_1.bits[0], value_2.bits[0], result_plus.bits[0]);
    printf("Сложение\n%s\n\n", inside(result_plus));
    printf("%d - %d = %d\n", value_1.bits[0], value_2.bits[0], result_minus.bits[0]);
    printf("%s\n\n", inside(result_minus));

    sprintf(str, "%e\n", y);
    s21_from_float_to_decimal(y, &dst_y);

    printf("Число:   %de%+d\n",dst_y.bits[0], degree(dst_y));
    
    printf("%s\n\n", inside(dst_y));
    

    puts("Проверка степени:");
    printf("%e\n", y);
    printf("%de%+d\n\n",dst_y.bits[0], degree(dst_y));

    puts("Функции сравнения:");
    printf("%d %c %d\n\n", value_1.bits[0], (s21_is_less(value_1, value_2)) ? '>' : 0, value_2.bits[0]);

    puts("Функция определения последней цифры для округления:");
    printf(" Число: %d \n Последняя цифра: %d\n\n", value_1.bits[0], last_number(value_1));

    s21_negate(value_1, &value_1);
    s21_round(value_1, &value_1);

    printf("Степень чила: %d\n", find_scale(value_2));

    return 0;
}

int pow_int(int x, int y) {
    int result = 1;
    while (y > 0) {
        result *= x;
    y--;
    }
  return result;
}

/* Функция определения одной последней цифры - Эдуард */

// int last_number(s21_decimal dst) {
//     int x = 0;
//     for(int i = 95; i > 0; i--) {
//         if((dst.bits[i / 32] >> (i % 32)) & 1) {
//             x = (i % 4 == 0) ? (x + pow_int(2, 4)) % 10 : (x + pow_int(2, i % 4)) % 10;
//         }
//     }
//     return x += (dst.bits[0] >> 0) & 1;;
// }

/* Функция определения двух последних цифр - Андрей */

int last_number(s21_decimal dst) {
    int x = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 32; j++) {
            if ((dst.bits[i] & (1 << j)) != 0) {
                x += (1 << j) % 100;
            }
        }
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


int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    int flag = 0;
    for (int i = 2; i >= 0 && !flag; i--) {
        int x = (check_sign(value_1)) ? -value_1.bits[i] : value_1.bits[i];
        int y = (check_sign(value_2)) ? -value_2.bits[i] : value_2.bits[i];
        flag = (x > y) ? 1 : 0;
    }  
    return flag;
}


int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result_plus) {

    int prev_ch = 0;  //previous_char
    int cur_ch = 0;   //current_char
    for (int i = 0; i < 96; i++) {
        int x = ((value_1.bits[i / 32] >> (i % 32)) & 1);
        int y = ((value_2.bits[i / 32] >> (i % 32)) & 1);
        cur_ch = x ^ y ^ prev_ch;
        result_plus -> bits[i / 32] |= (cur_ch << (i % 32));
        prev_ch = (x + y + prev_ch > 1) ? 1 : 0;
    }  
    return 0;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result_plus) {
    if(s21_is_less(value_1, value_2)) {
        int prev_ch = 0;  //prev_char
        for (int i = 0; i < 96; i++) {
            int x = ((value_1.bits[i / 32] >> (i % 32)) & 1);
            int y = ((value_2.bits[i / 32] >> (i % 32)) & 1);
            x = (prev_ch == -1) ? abs(x - 1) : x;
            prev_ch = x - y;
            result_plus -> bits[i / 32] |= (prev_ch) ? (1 << (i % 32)) : (0 << (i % 32));
        }  
    }
    return 0;
}

// Побитовые операции И ( & ), ИЛИ ( | ), ИСКЛЮЧАЮЩЕЕ ИЛИ ( ^ ), НЕ ( ~ )

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    set_sign(&src, dst);
    dst -> bits[0] = src;
    return 0; 
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
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
    dst -> bits[3] |= (degree & 255) << 16;
    return 0;
}

// inside - Андрей

char* inside(s21_decimal dst) {
    
    char* str = (char*)malloc(140 * sizeof(char));
    int str_index = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 31; j >= 0; j--) {   

            str[str_index] = ((dst.bits[i] >> j) & 1) + '0';

            str_index++;

        }
        str[str_index++] = '\n';
    }
    
    str[str_index] = '\0';

    return str;
}


// /* Округляет указанное Decimal число до ближайшего целого числа в сторону отрицательной бесконечности. */

// int s21_floor(s21_decimal value, s21_decimal *result) {



//     return 0;
// }

/* Возвращает результат умножения указанного Decimal на -1. */

int s21_negate(s21_decimal value, s21_decimal *result) {

    printf("Возвращает результат умножения указанного Decimal на -1.\n");

    printf("До операции\n%s\n", inside(value));

    value.bits[3] ^= (1 << 31);

    printf("После операции\n%s\n", inside(value));

    *result = value;

    return 0;
}

/* Округляет Decimal до ближайшего целого числа */

int s21_round(s21_decimal value, s21_decimal *result) {

    int scale = find_scale(value); /* Извлекаем степень */

    s21_decimal support = value; /* Создаем копию value */

    support.bits[3] = 0; /* Очищаем bits 3 */

    // support = 

    // *result = 

    return 0;
}

/* Функция определения степени */

int find_scale (s21_decimal value) {

    int mask = 255; // 11111111 * xxxxxxx

    return ((value.bits[3] >> 16) & mask);

    /*

    11111111 11111111 11111111 11111111 >> 16
    00000000 00000000 11111111 11111111 & 00000000 00000000 00000000 11111111
    
    */

}

s21_big_decimal binary_div (s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal* OSTATOK) {
   
    s21_big_decimal result;

    s21_big_decimal part_remainder = {0};

    s21_big_decimal quotient = {0};

    if (s21_decimal_equal_zero(value_1.decimals[0]) && s21_decimal_equal_zero(value_1.decimals[1])) { /* Может быть получится заменить 
    s21_decimal_equal_zero на s21_big_decimal_binary_compare если не найдется ни одного бита то значит что все биты равны 0 */
        ;
    } else if (s21_big_decimal_binary_compare(value_1, value_2) == -1) {
        ;
    } else {
        int shift_1 = find_pos_most_major_bit(value_1.decimals[1]);
        
        if (shift_1 == -1) {
            shift_1 = find_pos_most_major_bit(value_1.decimals[0]);
        } else {
            shift_1 += 128;
        }

        int shift_2 = find_pos_most_major_bit(value_2.decimals[1]);
        if (shift_2 == -1) {
            shift_2 = find_pos_most_major_bit(value_2.decimals[0]);
        } else {
            shift_2 += 128;
        }

        int shift_general = shift_1 - shift_2;

    }

    return result;
}

/* Функция вычисляет равен ли биг децимал нулю */
int s21_decimal_equal_zero (s21_decimal value) {

    int result = value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0 && value.bits[3] == 0;

    return result;
}

/* Функция находит позицию самого старшего бита */
int find_pos_most_major_bit (s21_decimal value) {
    
    int result = -1;

    for (int i = 128 - 1; i >= 0; i--) { // Проходим с конца числа и находим первое вхождение бита | --> 010100 | 
        if (s21_decimal_is_set_bit(value, i)) {
            result = i;
            break;
        }
    }
    
    return result;
}

int s21_decimal_is_set_bit(s21_decimal decimal, int index) {
    return find_pos_bit(decimal.bits[index / 32], index % 32);
}

/* Проверка на то, что установлен ли бит на определённой позиции */
int find_pos_bit (int value, int pos) {
    
    int result = value & (1 << pos);
    
    if (result != 0) {
        result = 1;
    }

    return result;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (result == NULL) return puts("erorr");
    zero(result);
    if (checking_3_bytes(value_1) || checking_3_bytes(value_2)) return puts("erorr");
    if (checking_for_zero(value_2)) return 3;
    
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
        if (bit_pos <= 0 && used_bits(reduced) != 0 && (unsigned_comparison(reduced, deductible) >> 5 & 1) && used_bits(divisible) < 210) {
            mul_by_10(&divisible);
            bit_pos = used_bits(divisible);
            big_zero(&temp_res);
            big_zero(&reduced);
        }
    }
    //if (temp_res.bits[6] > 0) return 1;
    //inside3(temp_res);
    printf("%d\n", deg + big_degree(divisible));
    int z = 0;
    while(used_bits(temp_res) > 96 || abs(deg + big_degree(divisible)) > 28) {
        div_by_10(&temp_res);
        deg--;
        if (abs(deg + big_degree(divisible)) == 29) z = last_number(temp_res, 2);
    }
    s21_big_decimal temp_res1 = {{1, 0, 0, 0, 0, 0, 0, 0}};
    if ((z % 20 > 5 && z % 20 < 10) || (z % 20 >= 14 && z % 20 <= 19)) {
        add(temp_res, temp_res1, &temp_res);
    }
   //inside3(temp_res);
    printf("%d\n", deg + big_degree(divisible));

    s21_big_decimal temp_res_big = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

    if (deg + big_degree(divisible) < 0) return 1;

    *result = reducing_to_less(temp_res);
    result -> bits[3] |= abs(deg + big_degree(divisible)) << 16;             
    if (check_sign(value_1) ^ check_sign(value_2)) result -> bits[3] |= (1 << 31);
    
    return 0; 
}

/* 
 * int = 32
 * short = 16
 * char = 8
 * degree = 
*/
int checking_3_bytes(s21_decimal dst) {
    char c = dst.bits[3] >> 24;
    int degree_value = degree(dst);
    short z = dst.bits[3];
    int result = 0;

    if ((c != 0 && c != 128) || degree_value > 28 || degree_value < 0 || z != 0) {
        result = 1;
    }
    
    return result;
}
