// - Stack is where local variables stored
// - When a function is called , a new stack frame is created in memory to store
// the function's parameters and local variables
// - When a function returns, its entire stack frame  is deallocated
// - Note: stack is used when the size is known ahead of time and can exist
// within one function. Heap is used when the size is unknown ahead of time or
// return value isn't limited to one fuction.
#include "exercise.h"
#include <stdio.h>

typedef struct {
  int x;
  int y;
} coord_t;

// PROBLEMATIC! `coord_t c;` is in the same location in memory each time, so we
// accidentally return the address to the same spot for each of these function.
// printf("c1: %d, %d\n", c1->x, c1->y);
// printf("c2: %d, %d\n", c2->x, c2->y);
// printf("c3: %d, %d\n", c3->x, c3->y);
// coord_t *new_coord(int x, int y) {
//   coord_t c; // 1. A local variable is created ON THE STACK
//   c.x = x;
//   c.y = y;
//   return &c; // 2. You return the memory address of that stack variable
// }

coord_t new_coord(int x, int y) {
  coord_t c; // 1. A local variable is created ON THE STACK
  c.x = x;
  c.y = y;
  return c; // 2. You return the memory address of that stack variable
}

int main(void) {
  // Stack
  printMessageOne();
  printMessageTwo();
  printMessageThree();

  printf("\n\n\n");

  // Stack Overflow
  // ❱ ulimit -s (user limit -stack size)
  // 8176 (in KB is the limit)
  // const int pool_size = 8170 * 1024; // segmentation fault
  // const int pool_size = 8169 * 1024; // not segmentation fault
  const int pool_size = 1024 * 10; // (10 kibibyte, safe as expected answer)
  char snek_pool[pool_size];
  snek_pool[0] = 's';
  snek_pool[1] = 'n';
  snek_pool[2] = 'e';
  snek_pool[3] = 'k';
  snek_pool[4] = '\0';

  printf("Size of pool: %d\n", pool_size);
  printf("Initial string: %s\n", snek_pool);

  printf("\n\n\n");

  // Pointers to the Stack
  coord_t c1 = new_coord(10, 20);
  coord_t c2 = new_coord(30, 40);
  coord_t c3 = new_coord(50, 60);

  printf("c1: %d, %d\n", c1.x, c1.y);
  printf("c2: %d, %d\n", c2.x, c2.y);
  printf("c3: %d, %d\n", c3.x, c3.y);

  return 0;
}

__attribute__((noinline)) void printMessageOne(void) {
  const char *message = "Dark mode?\n";
  printStackPointerDiff();
  printf("%s\n", message);
  // printMessageTwo();
}

__attribute__((noinline)) void printMessageTwo(void) {
  const char *message = "More like...\n";
  printStackPointerDiff();
  printf("%s\n", message);
  // printMessageThree();
}

__attribute__((noinline)) void printMessageThree(void) {
  const char *message = "dark roast.\n";
  printStackPointerDiff();
  printf("%s\n", message);
}

void printStackPointerDiff(void) {
  static void *last_sp = NULL;
  void *current_sp;
  current_sp = __builtin_frame_address(0);
  long diff;
  if (last_sp == NULL) {
    last_sp = current_sp;
    diff = 0;
  } else {
    diff = (char *)last_sp - (char *)current_sp;
  }
  printf("---------------------------------\n");
  printf("Stack pointer offset: %ld bytes\n", diff);
  printf("Current Stack Pointer   : %d\n", current_sp);
  printf("Last Stack Pointer      : %d\n", last_sp);
  printf("---------------------------------\n");
}

// Note: memory addrres printed below is printed as int (%d), not int* (%p)
// When nesting function call
// ---------------------------------
// Stack pointer offset: 0 bytes
// Current Stack Pointer   : 1828056336
// Last Stack Pointer      : 1828056336
// ---------------------------------
// Dark mode?

// ---------------------------------
// Stack pointer offset: 32 bytes
// Current Stack Pointer   : 1828056304
// Last Stack Pointer      : 1828056336
// ---------------------------------
// More like...

// ---------------------------------
// Stack pointer offset: 64 bytes
// Current Stack Pointer   : 1828056272
// Last Stack Pointer      : 1828056336
// ---------------------------------
// dark roast.
//
// When sequencing function call
// ---------------------------------
// Stack pointer offset: 0 bytes
// Current Stack Pointer   : 1809706256
// Last Stack Pointer      : 1809706256
// ---------------------------------
// Dark mode?

// ---------------------------------
// Stack pointer offset: 0 bytes
// Current Stack Pointer   : 1809706256
// Last Stack Pointer      : 1809706256
// ---------------------------------
// More like...

// ---------------------------------
// Stack pointer offset: 0 bytes
// Current Stack Pointer   : 1809706256
// Last Stack Pointer      : 1809706256
// ---------------------------------
// dark roast.
