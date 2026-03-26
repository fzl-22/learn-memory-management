#include "exercise.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void allocate_int(int **pointer_pointer, int value) {
  int *pointer = malloc(sizeof(int));
  *pointer_pointer = pointer;
  **pointer_pointer = value;
}

token_t **create_token_pointer_array(token_t *tokens, size_t count) {
  token_t **token_pointers = malloc(count * sizeof(token_t *));
  if (token_pointers == NULL) {
    exit(1);
  }
  for (size_t i = 0; i < count; ++i) {
    // ! addresses stored in token_pointers[i] are from stack-allocated inputs
    // ! token_pointers[i] = &tokens[i];
    //
    token_t *pointer = malloc(sizeof(token_t));
    token_pointers[i] = pointer;
    *token_pointers[i] = tokens[i];
  }
  return token_pointers;
}

void snek_zero_out(void *ptr, snek_object_kind_t kind) {
  switch (kind) {
  case INTEGER:
    ((snek_int_t *)ptr)->value = 0;
    break;
  case FLOAT:
    ((snek_float_t *)ptr)->value = 0.0;
    break;
  case BOOL:
    ((snek_float_t *)ptr)->value = false;
    break;
  }
}

void swap_ints(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void swap_strings(char **a, char **b) {
  char *tmp = *a;
  *a = *b;
  *b = tmp;
}

void swap(void *vp1, void *vp2, size_t size) {
  void *tmp = malloc(size);
  if (tmp == NULL) {
    return;
  }

  memcpy(tmp, vp1, size);
  memcpy(vp1, vp2, size);
  memcpy(vp2, tmp, size);

  free(tmp);
}
