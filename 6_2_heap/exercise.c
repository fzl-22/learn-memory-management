#include <stdio.h>
#include <stdlib.h>

// full_greeting[100] is allocated on the stack, therefore it returns the memory
// address that is deallocated after the function returned
// char *get_full_greeting(char *greeting, char *name, int size) {
//   char full_greeting[100];
//   snprintf(full_greeting, 100, "%s %s", greeting, name);
//   return full_greeting;
// }

// full_greeting is allocated on the heap
char *get_full_greeting(char *greeting, char *name, int size) {
  char *full_greeting = malloc(size * sizeof(char));
  snprintf(full_greeting, size, "%s %s", greeting, name);
  return full_greeting;
}

int *allocate_scalar_array(int size, int multiplier) {
  int *scalar_array = malloc(size * sizeof(int));
  if (scalar_array == NULL) {
    return NULL;
  }

  for (int i = 0; i < size; i++) {
    *(scalar_array + i) = i * multiplier;
  }

  return scalar_array;
}

int *allocate_scalar_list(int size, int multiplier) {
  int *lst = malloc(size * sizeof(int));
  if (lst == NULL) {
    return NULL;
  }
  for (int i = 0; i < size; i++) {
    lst[i] = i * multiplier;
  }
  return lst;
}
