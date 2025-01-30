CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wextra

LIB_NAME := s21_decimal.a
#TEST_NAME :=
#LDFLLAGS := -lm

all: s21_decimal

s21_decimal:
	tput reset
#	@$(CC) $(CFLAGS) s21_decimal.c -o s21_decimal
	@$(CC) s21_decimal.c -o s21_decimal
	@./s21_decimal
	@rm s21_decimal

clean:
	@rm s21_decimal