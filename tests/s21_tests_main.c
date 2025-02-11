#include "s21_tests_main.h"
#include "../s21_decimal.h"



int main() {
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
    float y = -10;

    s21_from_int_to_decimal(x, &value_1);
    s21_from_int_to_decimal(x2, &value_2);
    //value_1.bits[1] = 2;
    // value_2.bits[1] = 3;
    s21_add(value_1, value_2, &result_plus);
    s21_sub(value_1, value_2, &result_minus);
    


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


    s21_decimal result_mul = {0};
    for(int i = 1; i < 11; i++) {
        for(int j = -1; j > -11; j--) {
            zero(&value_1);
            zero(&value_2);
            s21_from_int_to_decimal(i, &value_1);
            s21_from_int_to_decimal(j, &value_2);
            s21_mul(value_1, value_2, &result_mul);
            printf(" %c%d ", (check_sign(result_minus)) ? '-' : '+', result_mul.bits[0]);
        }
        puts("\n");
    }
    

    s21_decimal result_div = {0};
    
    zero(&value_1);
    zero(&value_2);
    zero(&result_div);

            s21_from_float_to_decimal(-100, &value_1); 
            inside2(value_1);
            s21_from_float_to_decimal(-7, &value_2);
            s21_div(value_1, value_2, &result_div);
    
    inside2(result_div);



    int number_failed;
    SRunner *sr;
    sr = srunner_create(NULL);


    srunner_add_suite(sr, add_suite());
    srunner_add_suite(sr, sub_suite());
    srunner_add_suite(sr, mul_suite());
    srunner_add_suite(sr, div_suite());




    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}