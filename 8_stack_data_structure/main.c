#include "exercise.h"
#include <stdio.h>
#define stack_t system_stack_t
#include <stdlib.h>
#undef stack_t

int main(void) {
  // Low Level Stack
  stack_t *s = stack_new(2);
  stack_print(s);

  // Stack Push
  int a = 10;
  stack_print(s);
  stack_push(s, &a);
  stack_print(s);
  stack_push(s, &a);
  stack_print(s);
  stack_push(s, &a);
  stack_print(s);

  // Stack Pop
  int *popped = stack_pop(s);
  if (popped != NULL) {
    printf("*popped: %d\n", *popped);
  } else {
    printf("Stack is empty!\n");
  }
  stack_print(s);
  popped = stack_pop(s);
  if (popped != NULL) {
    printf("*popped: %d\n", *popped);
  } else {
    printf("Stack is empty!\n");
  }
  stack_print(s);
  popped = stack_pop(s);
  if (popped != NULL) {
    printf("*popped: %d\n", *popped);
  } else {
    printf("Stack is empty!\n");
  }
  stack_print(s);
  popped = stack_pop(s);
  if (popped != NULL) {
    printf("*popped: %d\n", *popped);
  } else {
    printf("Stack is empty!\n");
  }
  stack_print(s);
  popped = stack_pop(s);
  if (popped != NULL) {
    printf("*popped: %d\n", *popped);
  } else {
    printf("Stack is empty!\n");
  }
  stack_print(s);

  // Stack Free
  stack_free(s);
  s = NULL;
  stack_free(s);
  stack_free(s);

  // Dangerous Push
  stack_t *scary_stack = stack_new(2);
  scary_double_push(scary_stack);

  printf("scary_stack->data[0]: %d\n", (int)(size_t)scary_stack->data[0]);
  printf("scary_stack->data[0]: %d\n", *(int *)scary_stack->data[1]);

  stack_free(scary_stack);
  scary_stack = NULL;

  // Multiple Types
  stack_t *heterogenous_stack = stack_new(2);
  stack_push_multiple_types(heterogenous_stack);

  printf("heterogenous_stack->data[0]: %f\n",
         *(float *)heterogenous_stack->data[0]);
  printf("heterogenous_stack->data[1]: %s\n",
         (char *)heterogenous_stack->data[1]);

  stack_free(heterogenous_stack);
  heterogenous_stack = NULL;

  return 0;
}
