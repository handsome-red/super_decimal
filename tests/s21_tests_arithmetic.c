#include "s21_tests_main.h"


START_TEST(test_add_plus_10_plus_3)
{
    s21_decimal value_1 = {{10, 0, 0, 0}};
    s21_decimal value_2 = {{3, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_add(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 13);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_add_plus_3_plus_10)
{
    s21_decimal value_1 = {{3, 0, 0, 0}};
    s21_decimal value_2 = {{10, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_add(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 13);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_add_plus_10_minus_3)
{
    s21_decimal value_1 = {{10, 0, 0, 0}};
    s21_decimal value_2 = {{3, 0, 0, 0x80000000}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_add(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 7);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_add_minus_3_plus_10)
{
    s21_decimal value_1 = {{3, 0, 0, 0x80000000}};
    s21_decimal value_2 = {{10, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_add(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 7);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_add_minus_10_plus_3)
{
    s21_decimal value_1 = {{10, 0, 0, 0x80000000}};
    s21_decimal value_2 = {{3, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_add(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 7);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_add_plus_3_minus_10)
{
    s21_decimal value_1 = {{3, 0, 0, 0}};
    s21_decimal value_2 = {{10, 0, 0, 0x80000000}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_add(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 7);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_add_minus_10_minus_3)
{
    s21_decimal value_1 = {{10, 0, 0, 0x80000000}};
    s21_decimal value_2 = {{3, 0, 0, 0x80000000}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_add(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 13);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_add_minus_3_minus_10)
{
    s21_decimal value_1 = {{3, 0, 0, 0x80000000}};
    s21_decimal value_2 = {{10, 0, 0, 0x80000000}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_add(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 13);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_s21_add_different_scales) {

    s21_decimal value_1 = {{1000, 0, 0, 0}};
    s21_decimal value_2 = {{50, 0, 0, 0}};
    value_1.bits[3] = 4 << 16;  
    value_2.bits[3] = 2 << 16;
    s21_decimal result;

    int return_code = s21_add(value_1, value_2, &result);
    ck_assert_int_eq(return_code, 0);
    ck_assert_uint_eq(result.bits[0], 6000);
    ck_assert_uint_eq(result.bits[3], 4 << 16);
    

} END_TEST

////////////////////////////////////////////


START_TEST(test_sub_plus_10_plus_3)
{
    s21_decimal value_1 = {{10, 0, 0, 0}};
    s21_decimal value_2 = {{3, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_sub(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 7);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_sub_plus_3_plus_10)
{
    s21_decimal value_1 = {{3, 0, 0, 0}};
    s21_decimal value_2 = {{10, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_sub(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 7);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_sub_plus_10_minus_3)
{
    s21_decimal value_1 = {{10, 0, 0, 0}};
    s21_decimal value_2 = {{3, 0, 0, 0x80000000}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_sub(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 13);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_sub_minus_3_plus_10)
{
    s21_decimal value_1 = {{3, 0, 0, 0x80000000}};
    s21_decimal value_2 = {{10, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_sub(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 13);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_sub_minus_10_plus_3)
{
    s21_decimal value_1 = {{10, 0, 0, 0x80000000}};
    s21_decimal value_2 = {{3, 0, 0, 0}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_sub(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 13);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_sub_plus_3_minus_10)
{
    s21_decimal value_1 = {{3, 0, 0, 0}};
    s21_decimal value_2 = {{10, 0, 0, 0x80000000}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_sub(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 13);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_sub_minus_10_minus_3)
{
    s21_decimal value_1 = {{10, 0, 0, 0x80000000}};
    s21_decimal value_2 = {{3, 0, 0, 0x80000000}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_sub(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 7);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_sub_minus_3_minus_10)
{
    s21_decimal value_1 = {{3, 0, 0, 0x80000000}};
    s21_decimal value_2 = {{10, 0, 0, 0x80000000}};
    s21_decimal result = {{0, 0, 0, 0}};
    int return_code = s21_sub(value_1, value_2, &result);
   
    ck_assert_int_eq(return_code, 0); 
    ck_assert_uint_eq(result.bits[0], 7);
    ck_assert_uint_eq(result.bits[1], 0);
    ck_assert_uint_eq(result.bits[2], 0);
    ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_sub_different_scales) {
    
    s21_decimal value_1 = {{50, 0, 0, 0}};
    s21_decimal value_2 = {{1000, 0, 0, 0}};
    value_1.bits[3] = 2 << 16;  
    value_2.bits[3] = 4 << 16;
    s21_decimal result = {{0, 0, 0, 0}};
    
    int return_code = s21_sub(value_1, value_2, &result);
    ck_assert_int_eq(return_code, 0);
    ck_assert_uint_eq(result.bits[0], 4000);
    ck_assert_uint_eq(result.bits[3], 4 << 16);
    

} END_TEST

////////////////////////////////////////////////////////////////

START_TEST(test_s21_mul_positiv) {
    
    s21_decimal value_1 = {{10, 0, 0, 0}};
    s21_decimal value_2 = {{5, 0, 0, 0}};
    value_1.bits[3] = 2 << 16;  
    value_2.bits[3] = 4 << 16;
    s21_decimal result = {{0, 0, 0, 0}};
    
    int return_code = s21_mul(value_1, value_2, &result);
    ck_assert_int_eq(return_code, 0);
    ck_assert_uint_eq(result.bits[0], 50);
    ck_assert_uint_eq(result.bits[3], 6 << 16);
    

} END_TEST

START_TEST(test_s21_div_positiv) {
    
    s21_decimal value_1 = {{10, 0, 0, 0}};
    s21_decimal value_2 = {{5, 0, 0, 0}};
    value_1.bits[3] = 2 << 16;  
    value_2.bits[3] = 4 << 16;
    s21_decimal result = {{0, 0, 0, 0}};
    inside2(value_1);
    inside2(value_2);
    
    int return_code = s21_div(value_1, value_2, &result);
    inside2(result);
    ck_assert_int_eq(return_code, 0);
    ck_assert_uint_eq(result.bits[0], 200);
    ck_assert_uint_eq(result.bits[3], 0 << 16);
    

} END_TEST

///////////////////////////////////////////////////////////////////

Suite *add_suite(void) {
    Suite *s;
    TCase *tc_add, *tc_sub;

    s = suite_create("Add");

    tc_add = tcase_create("Add");
    tcase_add_test(tc_add, test_add_plus_10_plus_3);
    tcase_add_test(tc_add, test_add_plus_3_plus_10);
    tcase_add_test(tc_add, test_add_plus_10_minus_3);
    tcase_add_test(tc_add, test_add_minus_3_plus_10);

    tcase_add_test(tc_add, test_add_minus_10_plus_3);
    tcase_add_test(tc_add, test_add_plus_3_minus_10);
    tcase_add_test(tc_add, test_add_minus_10_minus_3);
    tcase_add_test(tc_add, test_add_minus_3_minus_10);

    tcase_add_test(tc_add, test_s21_add_different_scales);


    suite_add_tcase(s, tc_add);
    return s;
}

Suite *sub_suite(void) {
    Suite *s;
    TCase *tc_sub;

    s = suite_create("Sub");
    tc_sub = tcase_create("Sub");

    tcase_add_test(tc_sub, test_sub_plus_10_plus_3);
    tcase_add_test(tc_sub, test_sub_plus_3_plus_10);
    tcase_add_test(tc_sub, test_sub_plus_10_minus_3);
    tcase_add_test(tc_sub, test_sub_minus_3_plus_10);

    tcase_add_test(tc_sub, test_sub_minus_10_plus_3);
    tcase_add_test(tc_sub, test_sub_plus_3_minus_10);
    tcase_add_test(tc_sub, test_sub_minus_10_minus_3);
    tcase_add_test(tc_sub, test_sub_minus_3_minus_10);

    tcase_add_test(tc_sub, test_s21_sub_different_scales);
    

    suite_add_tcase(s, tc_sub);

    return s;
}

Suite *mul_suite(void) {
    Suite *s;
    TCase *tc_mul;

    s = suite_create("Mul");
    tc_mul = tcase_create("Mul");

    tcase_add_test(tc_mul, test_s21_mul_positiv);
    
    

    suite_add_tcase(s, tc_mul);

    return s;
}

Suite *div_suite(void) {
    Suite *s;
    TCase *tc_div;

    s = suite_create("Div");
    tc_div = tcase_create("Div");

    tcase_add_test(tc_div, test_s21_div_positiv);
    
    

    suite_add_tcase(s, tc_div);

    return s;
}