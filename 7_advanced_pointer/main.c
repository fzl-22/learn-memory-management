#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Pointer-Pointer
  int value = 5;
  int *pointer = &value;

  printf("value: %d\n", value);
  printf("*pointer: %d\n", *pointer);

  allocate_int(&pointer, 20);

  printf("value: %d\n", value);
  printf("*pointer: %d\n", *pointer);

  // Array of Pointers
  token_t token = {"hello", 1, 2};
  token_t **result = create_token_pointer_array(&token, 1);

  printf("result[0]->literal: %s\n", result[0]->literal);
  printf("result[0]->line: %d\n", result[0]->line);
  printf("result[0]->column: %d\n", result[0]->column);
  printf("token pointer should not point to original token:\n");
  printf("result[0]: %p, .&token: %p\n", result[0], &token);

  free(result[0]);
  free(result);

  // Void Pointer
  int val = 10;
  void *void_ptr = &val;
  printf("*(int *)void_ptr: %d\n", *(int *)void_ptr);

  snek_int_t integer;
  snek_float_t float_num;
  snek_bool_t boolean;

  integer.value = -100;
  float_num.value = -99.99;
  boolean.value = 255;

  snek_zero_out(&integer, INTEGER);
  snek_zero_out(&float_num, FLOAT);
  snek_zero_out(&boolean, BOOL);

  printf("integer.value: %d\n", integer.value);
  printf("float_num.value: %f\n", float_num.value);
  printf("boolean.value: %d\n", boolean.value);

  // Swapping Integers
  int a = 10;
  int b = 20;
  printf("a,b=%d,%d\n", a, b);
  swap_ints(&a, &b);
  printf("a,b=%d,%d\n", a, b);

  // Swap Strings
  char *x = "Hello";
  char *y = "World";
  printf("x,y=%s,%s\n", x, y);
  swap_strings(&x, &y);
  printf("x,y=%s,%s\n", x, y);

  // Generic Swaps
  swap(&a, &b, sizeof(int));
  swap(&x, &y, sizeof(char *));
  printf("a,b=%d,%d\n", a, b);
  printf("x,y=%s,%s\n", x, y);

  coffee_shop_t sbucks = {2, 3, 4};
  coffee_shop_t terminalshop = {10, 10, 10};
  swap(&sbucks, &terminalshop, sizeof(coffee_shop_t));
  printf("sbucks,terminalshops: %llu,%llu", sbucks.quality,
         terminalshop.quality);
}
