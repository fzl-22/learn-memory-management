#include "exercise.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool is_on_stack(void *ptr) {
  void *stack_top = __builtin_frame_address(0);
  uintptr_t stack_top_addr = (uintptr_t)stack_top;
  uintptr_t ptr_addr = (uintptr_t)ptr;

  uintptr_t threshold = 1024;

  return ptr_addr >= (stack_top_addr - threshold) &&
         ptr_addr <= (stack_top_addr + threshold);
}

int main(void) {
  // Heap
  char *result1 = get_full_greeting("Hello", "Alice", 20);
  char *result2 = get_full_greeting("Hello", "Andy", 20);
  char *result3 = get_full_greeting("Hello", "Lucy", 20);

  printf("result: %s\n", result1);
  printf("is on stack: %d\n", is_on_stack(result1));
  printf("result: %s\n", result2);
  printf("is on stack: %d\n", is_on_stack(result2));
  printf("result: %s\n", result3);
  printf("is on stack: %d\n", is_on_stack(result3));

  // Malloc
  int size = 5;
  int multiplier = 2;
  int *result = allocate_scalar_array(size, multiplier);
  for (int i = 0; i < size; i++) {
    printf("%d ", *(result + i));
  }
  printf("\n");
  free(result);
  result = NULL;

  // Free
  const int num_lists = 500;
  for (int i = 0; i < num_lists; i++) {
    int *lst = allocate_scalar_list(50000, 2);
    if (lst == NULL) {
      printf("Failed to allocate list\n");
      return 1;
    } else {
      printf("Allocated list %d\n", i);
      free(lst);
    }
  }

  // Big Endian & Little Endian
  //
  // Big Endian
  // Most significant byte is stored first, at the lowest memory address
  // Example: 0x12345678
  // <- Lower Addr.   Higher Addr. ->
  // | 0x12 | 0x34 | 0x56 | 0x78 |
  // <- Most signif. Least signif. ->
  //
  // Little Endian
  // Least significant byte is stored first, at the lowest memory address
  // <- Lower Addr.   Higher Addr. ->
  // | 0x78 | 0x56 | 0x34 | 0x12 |
  // <- Least signif. Most signif. ->
  //
  // For now, just know that most modern system use little-endian, and the
  // compiler takes care of how data is stored and accessed.
  return 0;
}
