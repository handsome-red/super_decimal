#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned int bits[4];
} s21_decimal;


//Арифметические операторы
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result_plus); //  +
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result_plus); //  -
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result_plus); //  *
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result_plus); //  :


//Операторы сравнения
int s21_is_less(s21_decimal value_1, s21_decimal value_2);                  //  <
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);         //  <=
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);               //  />
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


int main ( ) {
    char str[100] = {0};
    s21_decimal dst_y = {0};

    s21_decimal value_1 = {0};
    s21_decimal value_2 = {0};
    s21_decimal result_plus = {0};
    s21_decimal result_minus = {0};

    int x = 7;
    int x2 = 6;
    //float y = 0.00000000000000000000000000000001;
    float y = -123.0;
    //float y = -0.00000000000000000000000001305961231313;

    s21_from_int_to_decimal(x, &value_1);
    s21_from_int_to_decimal(x2, &value_2);
    // value_1.bits[1] = 4;
    // value_2.bits[1] = 4;
    s21_add(value_1, value_2, &result_plus);
    s21_sub(value_1, value_2, &result_minus);
    

    printf("Число:   %d\n", x);
    printf("%s\n\n", inside(value_1));
    printf("Число:   %d\n", x2);
    printf("%s\n\n", inside(value_2));


    printf("%d + %d = %d\n", value_1.bits[0], value_2.bits[0], result_plus.bits[0]);
    printf("%s\n\n", inside(result_plus));
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
    printf("%d %s %d\n\n", x, (s21_is_less(value_1, value_2)) ? "< " : "  ", x2);
    printf("%d %s %d\n\n", x, (s21_is_less_or_equal(value_1, value_2)) ? "<=" : "  ", x2);
    printf("%d %s %d\n\n", x, (s21_is_greater(value_1, value_2)) ? "> " : "  ", x2);
    printf("%d %s %d\n\n", x, (s21_is_greater_or_equal(value_1, value_2)) ? ">=" : "  ", x2);
    printf("%d %s %d\n\n", x, (s21_is_equal(value_1, value_2)) ? "==" : "  ", x2);
    printf("%d %s %d\n\n", x, (s21_is_not_equal(value_1, value_2)) ? "!=" : "  ", x2);
    
    puts("Функция определения последних двух цифр для округления:");
    printf(" Число: %d \n Последние две цифры: %d\n\n", value_1.bits[0], last_number(value_1));
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
    for (int i = 2; i >= 0 && !flag; i--) {
        int x = (check_sign(value_1)) ? -value_1.bits[i] : value_1.bits[i];
        int y = (check_sign(value_2)) ? -value_2.bits[i] : value_2.bits[i];
        flag |= (x < y) ? 3 << 0 : 0 << 0;
        flag |= (x > y) ? 3 << 2 : 0 << 2;
        flag |= (x != y) ? 1 << 5 : 0 << 5;
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

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result_plus) {
    int flag = 0;
    if(check_sign(value_1) && check_sign(value_2)) {
        result_plus -> bits[3] = (1 << 31);
        flag = 1;
    }
    if(!check_sign(value_1) && !check_sign(value_2)) {
        flag = 1;
    }
    if (flag) {
        int prev_ch = 0;  //previous_char
        int cur_ch = 0;   //current_char
        for (int i = 0; i < 96; i++) {
            int x = ((value_1.bits[i / 32] >> (i % 32)) & 1);
            int y = ((value_2.bits[i / 32] >> (i % 32)) & 1);
            cur_ch = x ^ y ^ prev_ch;
            result_plus -> bits[i / 32] |= (cur_ch << (i % 32));
            prev_ch = (x + y + prev_ch > 1) ? 1 : 0;
        }  
    } else s21_sub(value_1, value_2, result_plus);

    return 0;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result_plus) {
    //if(check_sign(value_2)) 
        int prev_ch = 0;  //prev_char
        for (int i = 0; i < 96; i++) {
            int x = ((value_1.bits[i / 32] >> (i % 32)) & 1);
            int y = ((value_2.bits[i / 32] >> (i % 32)) & 1);
            x = (prev_ch == -1) ? abs(x - 1) : x;
            prev_ch = x - y;
            result_plus -> bits[i / 32] |= (prev_ch) ? (1 << (i % 32)) : (0 << (i % 32));
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