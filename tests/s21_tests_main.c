#include "s21_tests_main.h"
#include "../s21_decimal.h"


int main() {
    // char str[100] = {0};
    // s21_decimal dst_y = {0};

    // s21_decimal value_1 = {0};//{{0xFFFFFFFF, 0, 0xFFFFFFFF, 0}};
    // s21_decimal value_2 = {0};//{{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

    // int x = 10;
    // int x2 = -10;
    // //float y = 0.00000000000000000000000000000001;
    // //float y = 10.00;
    // float y = -10;

    // s21_from_int_to_decimal(x, &value_1);
    // s21_from_int_to_decimal(x2, &value_2);
    
    // sprintf(str, "%e\n", y);
    // s21_from_float_to_decimal(y, &dst_y);
    
    // puts("Проверка степени:");
    // printf("%e = ", y);
    // printf("%c%de-%.2d\n\n", dst_y.bits[3] & 1 << 31 ? '-' : ' ', dst_y.bits[0], degree(dst_y));
    
    // inside2(dst_y);

    // puts("Функции сравнения:");
    // printf("%d %s %d\n", x, s21_is_less(value_1, value_2) ? "< " : "  ", x2);
    // printf("%d %s %d\n", x, s21_is_less_or_equal(value_1, value_2) ? "<=" : "  ", x2);
    // printf("%d %s %d\n", x, s21_is_greater(value_1, value_2) ? "> " : "  ", x2);
    // printf("%d %s %d\n", x, s21_is_greater_or_equal(value_1, value_2) ? ">=" : "  ", x2);
    // printf("%d %s %d\n", x, s21_is_equal(value_1, value_2) ? "==" : "  ", x2);
    // printf("%d %s %d\n", x, s21_is_not_equal(value_1, value_2) ? "!=" : "  ", x2);
    
    s21_decimal value_3 = {{150, 0, 0, 0x80000000}};     // 1 0 1 1 0 0
    s21_decimal value_4 = {{10, 0, 0, 0x00000000}};    // 
    s21_decimal res_div = {0};
    s21_decimal res_mul = {0};
    //printf("\n%d", last_number(value_3, 1, 1));
    
    inside2(value_3);
    inside2(value_4);
    s21_div(value_3, value_4, &res_div);
    s21_mul(value_3, value_4, &res_mul);
    inside2(res_div);
    inside2(res_mul);

    s21_big_decimal by_10 = {{225, 0, 0, 0, 0, 0, 0, 0x80020000}};
    div_by_10(&by_10);
    inside3(by_10);

    // mul_by_10(&res_div);
    // inside2(res_div);

    // div_by_10(&res_div);
    // inside2(res_div);

    // offse_by_one(&value_3);
    // inside2(value_3);
    // s21_decimal two = {{2, 0, 0, 0}};
    // s21_mul(value_3, two, &value_3);
    // inside2(value_3);

    // s21_big_decimal war = bringing_to_big(value_4);
    // inside3(war);

    // s21_decimal value_5 = {{10, 0, 0, 0}};
    // s21_decimal value_6 = {{8, 0, 0, 0x80000000}};
    // value_5.bits[3] |= 1 << 16;  
    // value_6.bits[3] |= 4 << 16;
    
    
    // s21_decimal result6 = {{0, 0, 0, 0}};

    // s21_add(value_5, value_6, &result6);
    
    // inside2(value_5);
    // inside2(value_6);
    // //div_by_10(&value_6);
    // //inside2(value_6);
    // inside2(result6);
    // s21_mul(value_5, value_6, &result6);
    // inside2(result6);



    // s21_decimal value_7 = {{50, 0, 0, 0}};
    // s21_decimal value_8 = {{1000, 0, 0, 0}};
    // s21_decimal result8 = {0};
    // value_7.bits[3] = 2 << 16;  
    // value_8.bits[3] = 4 << 16;
    // s21_sub(value_7, value_8, &result8);
    // inside2(value_7);
    // inside2(value_8);
    // inside2(result8);
    

    // s21_big_decimal war = bringing_to_big(result6); 
    // war.bits[7] |= 4 << 16;
    // war.bits[7] |= 1 << 31;

    // inside3(war);
    // big_mul_by_10(&war);
    // inside3(war);


    int number_failed;
    SRunner *sr;
    sr = srunner_create(NULL);


    srunner_add_suite(sr, add_suite());
    srunner_add_suite(sr, sub_suite());
    srunner_add_suite(sr, mul_suite());
    srunner_add_suite(sr, div_suite());
    
    // srunner_add_suite(sr, is_equal_suite1());
    // srunner_add_suite(sr, is_greater_suite1());
    // srunner_add_suite(sr, is_greater_or_equal_suite1());
    // srunner_add_suite(sr, is_less_suite1());
    // srunner_add_suite(sr, is_less_or_equal_suite1());
    // srunner_add_suite(sr, is_not_equal_suite1());

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}




