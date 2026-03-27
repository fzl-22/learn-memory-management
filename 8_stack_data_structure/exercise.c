#include "exercise.h"
#include <stdio.h>
#include <string.h>
#define stack_t system_stack_t
#include <stdlib.h>
#undef stack_t

stack_t *stack_new(size_t capacity) {
  stack_t *stack = malloc(sizeof(stack_t));
  if (stack == NULL) {
    return NULL;
  }

  stack->count = 0;
  stack->capacity = capacity;
  stack->data = (void *)malloc(capacity * sizeof(void *));
  if (stack->data == NULL) {
    free(stack);
    return NULL;
  }

  return stack;
}

void stack_push(stack_t *stack, void *obj) {
  if (stack->count == stack->capacity) {
    stack->capacity = 2 * stack->capacity;
    void *tmp = realloc(stack->data, stack->capacity * sizeof(void *));
    if (tmp == NULL) {
      stack->capacity = stack->capacity / 2;
      return;
    }
    stack->data = tmp;
  }

  stack->data[stack->count] = obj;
  stack->count++;
}

void *stack_pop(stack_t *stack) {
  if (stack->count == 0) {
    return NULL;
  }

  stack->count--;
  return stack->data[stack->count];
}

void stack_free(stack_t *stack) {
  if (stack == NULL) {
    return;
  }
  if (stack->data != NULL) {
    free(stack->data);
  }
  free(stack);
}

void stack_print(stack_t *stack) {
  printf("stack->capacity: %lu\n", stack->capacity);
  printf("stack->count: %lu\n", stack->count);
  for (int i = 0; i < stack->count; i++) {
    printf("%p ", stack->data[i]);
  }
  printf("\n");
}

void scary_double_push(stack_t *s) {
  // push both an int and an int*

  // lied to compiler that 1337 is an actual memory address (by casting it to
  // void*)
  stack_push(s, (void *)1337);

  // This is the right way
  int *ptr = malloc(sizeof(int));
  *ptr = 1024;
  stack_push(s, (void *)ptr);
}

void stack_push_multiple_types(stack_t *s) {
  float *ptr_float = malloc(sizeof(float));
  *ptr_float = 3.14;
  stack_push(s, (void *)ptr_float);

  // this is wrong, since it only allocates 1 byte for a single char
  // char *ptr_char = malloc(sizeof(char));
  // ptr_char = "Sneklang is blazingly slow!";
  char *value = "Sneklang is blazingly slow!";
  size_t len = strlen(value) + 1;

  char *ptr_char = malloc(len * sizeof(char));
  strcpy(ptr_char, value);
  stack_push(s, (void *)ptr_char);
}
