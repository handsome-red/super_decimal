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
    
    
  // -0.0000000000000025
  s21_decimal decimal1 = {{0x19, 0x0, 0x0, 0x80100000}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // too small actually, no
  // 0.0000000000000000000000000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x1C0000}};
  
    s21_decimal result;
    s21_mul(decimal1, decimal2, &result);

    
    //printf("%d", s21_is_equal(result, decimal_check));
    inside2(decimal1);
    inside2(decimal2);
    inside2(result);
    inside2(decimal_check);






    int number_failed;
    SRunner *sr;
    sr = srunner_create(NULL);


    srunner_add_suite(sr, add_suite1());
    srunner_add_suite(sr, div_suite0());
    srunner_add_suite(sr, div_suite1());
    srunner_add_suite(sr, mul_suite0());
    srunner_add_suite(sr, mul_suite1());
    srunner_add_suite(sr, sub_suite1());


    // srunner_add_suite(sr, add_suite());
    // srunner_add_suite(sr, sub_suite());
    // srunner_add_suite(sr, mul_suite());
    // srunner_add_suite(sr, div_suite());
    
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




