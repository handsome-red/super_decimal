#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned int bits[4];
} s21_decimal;

typedef struct {
    unsigned int bits[8];
} s21_big_decimal;


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

// Нормализация
int normalization (s21_decimal* num_1, s21_decimal* num_2);

int main ( ) {
    char str[100] = {0};
    s21_decimal dst_y = {0};

    s21_decimal value_1 = {0};//{{0xFFFFFFFF, 0, 0xFFFFFFFF, 0}};
    s21_decimal value_2 = {0};//{{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
    s21_decimal result_plus = {0};
    s21_decimal result_minus = {0};

    int x = 0;
    int x2 = 0;
    //float y = 0.00000000000000000000000000000001;
    float y = 0.00056500004;
    //float y = -0.00000000000000000000000001305961231313;

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

    puts("Нормализация:");
    printf("%d\n\n", (normalization(&value_1, &value_2)));
    return 0;
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

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int flag = 0;
    //if (!s21_sub(value_1, value_2, result)) flag = 1;
    
    if (flag) {
        int prev_ch = 0, cur_ch = 0;  //previous_char //current_char
        for (int i = 0; i < 96; i++) {
            int x = ((value_1.bits[i / 32] >> (i % 32)) & 1);
            int y = ((value_2.bits[i / 32] >> (i % 32)) & 1);
            cur_ch = x ^ y ^ prev_ch;
            result -> bits[i / 32] |= (cur_ch << (i % 32));
            prev_ch = (x + y + prev_ch > 1) ? 1 : 0;
        }  
    } 
    return 0;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
     int flag = 0;
    // if (check_sign(value_1) && (check_sign(value_2))) {

    //     //puts("101\n");
    //     result -> bits[3] |= (1 << 31);
    //     flag = 1;
    // }
    // if(!check_sign(value_1) && !check_sign(value_2)) {
    //     flag = 1;
    // }
    
    if (flag) {
        int prev_ch = 0;  //prev_char
        for (int i = 0; i < 96; i++) {
            int x = ((value_1.bits[i / 32] >> (i % 32)) & 1);
            int y = ((value_2.bits[i / 32] >> (i % 32)) & 1);
            x = (prev_ch == -1) ? abs(x - 1) : x;
            prev_ch = x - y;
            result -> bits[i / 32] |= (prev_ch) ? (1 << (i % 32)) : (0 << (i % 32));
        }
     } //else if (check_sign(value_1) && !check_sign(value_2)) {
    //     result -> bits[3] |= (1 << 31);
    //     s21_add(value_1, value_2, result);
    // } else if (!check_sign(value_1) && check_sign(value_2) ) {
    //     s21_add(value_1, value_2, result);
    // }
     
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
    strncat(ch_degree, ch_num + 11, 3);

    for(int i = 2; i < 8; i++) {
        ch_num[i] = ch_num[i + 1];
    }
    ch_num[8] = '\0';
    int num = atoi(ch_num);
    int degree = (atoi(ch_degree) - 6);
    set_sign(&num, dst);
    while(!(num % 10)) {
        num /= 10;
        degree += 1;
    }

    dst -> bits[0] = num;
    dst -> bits[3] |= degree << 16;
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

int normalization (s21_decimal* num_1, s21_decimal* num_2) {

//    num_1->bits[3] = 0x80000000;

    int common = 0;

    int exp_1 = (num_1->bits[3] << 1) >> 16; // степень первого числа
    int exp_2 = (num_2->bits[3] << 1) >> 16; // степень второго числа

    if (exp_1 > exp_2) {
        common = exp_1;
    } else {
        common = exp_2;
    }

    // УМНОЖЕНИЕ ЧИСЛА НА 10^(common - )int mantis * 10^common-()

    // printf("Степень первого числа: %d\nСтепень второго числа: %d\n", exp_1, exp_2);

    return 0;
}

// Побитовое сложение без учета знака

int bin_sum (s21_big_decimal num_1, s21_big_decimal num_2, s21_big_decimal* sum) {

    // s21_big_decimal sum = {0};

    int error = 0;

    int spectr = 0;
    int bit_1 = 0;
    int bit_2 = 0;

    for(int i = 0; i < 192; i++) { // 96        
        bit_1 = ((num_1.bits[i / 32] >> (i % 32)) & 1);
        bit_2 = ((num_2.bits[i / 32] >> (i % 32)) & 1); // 000000001

        spectr = spectr + bit_1 + bit_2;

        if (spectr == 0) {
            sum->bits[i / 32] &= ~(1 << (i % 32)); // 0
        } else if (spectr == 1) {
            sum->bits[i / 32] |= (1 << (i % 32)); // 1
            spectr = 0;
        } else if (spectr == 2) {
            sum->bits[i / 32] &= ~(1 << (i % 32)); // 0
            spectr = 1;
        } else if (spectr == 3) {
            sum->bits[i / 32] |= (1 << (i % 32)); // 0
            spectr = 1;
        }
    }
    
    if (spectr == 1) {
        error = 1;
    }

    return error;
}

int dec_to_big_dec (s21_decimal num) {
    
    ;

    return 0;
}

// 000 000 000
// bits 0 1 2

// 0000000001 = 1

// 00001010 = 10
// 00001010 = 10
// -------------
// 0000000

// 1100100 = 100

// -------------
// 1100100 = 100

// 0001010
// 0000000
// -------------
// 0000000

// 12
// 41
// ---
// 12,0
// 48


// 1111101000 = 1000

// 00000001 << 2
// 00000100
// 00010000

// 2 4 8 16

// 10

// 00000001 << 1
// 1 * 2
// 00000001 << 2
// 1 * 4
// 00000001 << x
// 1 * 10

// // 00000000 00000000 (15)0000000 70043210

// // 12345.678 3
// // 123.45678 5

// // =

// // 12345.67800 5
// // 123.45678 5


// // bits[2] 0000000
// // bits[2] 0010000

// // xxxxxxxxx 10
// // xxxxxxxxx 8