#include "snek.h"
#include <stdio.h>
#include <string.h>

int main(void) {
  long long i = 10;
  printf("&i: %p\n", &i);
  unsigned long long size_of_i = size_of_addr(i);
  printf("size_of_i: %llu\n", size_of_i);

  codefile_t f = {.lines = 10, .filetype = 0};
  printf("f: lines: %d, filetype: %d\n", f.lines, f.filetype);
  change_filetype_mutable(&f, 1);
  printf("f: lines: %d, filetype: %d\n", f.lines, f.filetype);

  int filedata[200] = {[1 ... 2] = 1, [3 ... 199] = 0};
  printf("filedata: lines: %d, filetype: %d\n", filedata[1], filedata[2]);
  update_file(filedata, 10, 10);
  printf("filedata: lines: %d, filetype: %d\n", filedata[1], filedata[2]);

  int numbers[5] = {1, 2, 3, 4, 5};
  int *numbers_ptr = numbers;

  printf("numbers[2]: %d\n", numbers[2]);
  printf("numbers[2]: %d\n", *(numbers + 2));
  int *p = numbers + 2;
  printf("numbers: %p\n", numbers);
  printf("p: %p\n", p);
  printf("*p: %d\n", *p); // value stored at the memory address p points to

  // Explanation:
  // In C, pointer arithmetic automatically scales by the size of the data type.
  // Because an integer (int) is typically 4 bytes in memory, incrementing an
  // int pointer by 2 actually advances the memory address by 2 * 4 = 8 bytes.
  // This is why the address jumps from 0x16d926810 to 0x16d926818.

  // multibyte array
  coordinate_t points[3] = {
      {.x = 1, .y = 2, .z = 3}, // 12 bytes
      {.x = 4, .y = 5, .z = 6}, // 12 bytes
      {.x = 7, .y = 8, .z = 9}, // 12 bytes
  };

  coordinate_t *ptr = points;

  printf("points[1].x = %d, points[1].y = %d, points[1].z = %d\n", (ptr + 1)->x,
         (ptr + 1)->y, (ptr + 1)->z);

  // Question:
  // A struct stores 8 integers in its ordered fields: A through H.
  // An array stores 10 of these structs.
  // What will be the offset in bytes from the start of the array to the 5th
  // element's C field?
  //
  // Answer: 136 bytes.
  // (The 5th element is at index 4, so 4 * 32 bytes = 128 bytes.
  // The C field is the 3rd integer, so 2 * 4 bytes = 8 bytes. 128 + 8 = 136).
  //
  // per index is 4 * 8. 4 -> sizeof(int), 8 is num of int fields
  // | [0] | [1] | [2] | [3] | [4]        |
  // | 32  | 32  | 32  | 32  | A + B -> 8 |
  // 4 * 8 * 4 + 4 * 2 = 136

  graphics_t graphics_array[10] = {
      {60, 1080, 1920},  {30, 720, 1280},  {144, 1440, 2560}, {75, 900, 1600},
      {120, 1080, 1920}, {60, 2160, 3840}, {240, 1080, 1920}, {60, 768, 1366},
      {165, 1440, 2560}, {90, 1200, 1920}};
  dump_graphics(graphics_array);

  int *int_ptr;
  char *char_ptr;
  double *double_ptr;
  printf("Size of int pointer %lu\n", sizeof(int_ptr));
  printf("Size of char pointer %lu\n", sizeof(char_ptr));
  printf("Size of double pointer %lu\n", sizeof(double_ptr));

  int int_arr[10];
  char char_arr[10];
  double double_arr[10];
  printf("Size of int array %lu\n", sizeof(int_arr));
  printf("Size of char array %lu\n", sizeof(char_arr));
  printf("Size of double array %lu\n", sizeof(double_arr));

  // Question:
  // Why int_ptr is 8 but int_arr is 40? Should it be 8 * 10?
  //
  // Answer:
  // int_ptr is a pointer, which stores a memory address. On a 64-bit system,
  // a memory address is 8 bytes, regardless of what data type it points to.
  // int_arr is an array of 10 ints. Because an int is typically 4 bytes, the
  // total size of the array is 10 * 4 = 40 bytes. It would only be 8 * 10 if
  // it were an array of pointers (int *int_arr[10]).
  //
  // // Array decay to pointer
  int core_utilization[] = {43, 67, 89, 92, 71, 43, 56, 12};
  int len = sizeof(core_utilization) / sizeof(core_utilization[0]);
  printf("sizeof core_utilization in main: %zu\n", sizeof(core_utilization));
  printf("len of core_utilization in main: %d\n", len);
  core_utils_func(core_utilization);

  char str1[] = "Hi!";
  char *str2 = "Snek";
  printf("%s %s\n", str1, str2);

  // Break down the memory of a C string
  char first[10] = "Snek";
  char *second = "lang!";

  strcat(first, second);
  printf("Hello, %s\n", first);

  char first_str[50] = "Hello";
  char *second_str = "World!";
  concat_strings(first_str, second_str);
  printf("first_str: %s\n", first_str);

  // sizeof and strlen
  printf("sizeof(second_str): %lu, strlen(second_str): %lu\n",
         sizeof(first_str), strlen(first_str));

  // smart_append
  TextBuffer buff = {0};
  printf("buff.buffer = %s, buff.length = %lu\n", buff.buffer, buff.length);

  char *src_1 = "HelloWorld";
  smart_append(&buff, src_1);
  printf("buff.buffer = %s, buff.length = %lu\n", buff.buffer, buff.length);
  char *src_2 = "HelloWorld";
  smart_append(&buff, src_2);
  printf("buff.buffer = %s, buff.length = %lu\n", buff.buffer, buff.length);
  char *src_3 = "HelloWorld";
  smart_append(&buff, src_3);
  printf("buff.buffer = %s, buff.length = %lu\n", buff.buffer, buff.length);
  char *src_4 = "HelloWorld";
  smart_append(&buff, src_4);
  printf("buff.buffer = %s, buff.length = %lu\n", buff.buffer, buff.length);
  char *src_5 = "HelloWorld";
  smart_append(&buff, src_5);
  printf("buff.buffer = %s, buff.length = %lu\n", buff.buffer, buff.length);
  char *src_6 = "HelloWorld";
  smart_append(&buff, src_6);
  printf("buff.buffer = %s, buff.length = %lu\n", buff.buffer, buff.length);
  char *src_7 = "HelloWorld";
  smart_append(&buff, src_7);
  printf("buff.buffer = %s, buff.length = %lu\n", buff.buffer, buff.length);
  char *src_8 = "HelloWorld";
  smart_append(&buff, src_8);
  printf("buff.buffer = %s, buff.length = %lu\n", buff.buffer, buff.length);

  return 0;
}
