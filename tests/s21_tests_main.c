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
    




  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow

  
    s21_decimal result;
    int z = s21_div(decimal1, decimal2, &result);
    inside2(decimal1);
    inside2(decimal2);
    inside2(result);
    //inside2(check);
    

    int number_failed;
    SRunner *sr;
    sr = srunner_create(NULL);



    srunner_add_suite(sr, div_suite0());
    //srunner_add_suite(sr, div_suite1());
    // srunner_add_suite(sr, div_suite2());
    // srunner_add_suite(sr, div_suite3());
    // srunner_add_suite(sr, div_suite4());
    // srunner_add_suite(sr, div_suite5());
    // srunner_add_suite(sr, div_suite6());
    // srunner_add_suite(sr, div_suite7());
    // srunner_add_suite(sr, div_suite8());
    // srunner_add_suite(sr, div_suite9());
    // srunner_add_suite(sr, div_suite10());
    // srunner_add_suite(sr, div_suite11());
    // srunner_add_suite(sr, div_suite12());
    // srunner_add_suite(sr, div_suite13());
    // srunner_add_suite(sr, div_suite14());
    // srunner_add_suite(sr, div_suite15());
    // srunner_add_suite(sr, div_suite16());
    // srunner_add_suite(sr, div_suite17());
    // srunner_add_suite(sr, div_suite18());

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




