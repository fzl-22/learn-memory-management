#include "snek.h"
#include <stdio.h>
#include <string.h>

unsigned long size_of_addr(long long i) {
  unsigned long sizeof_snek_version = sizeof(&i);
  return sizeof_snek_version;
}

codefile_t change_filetype(codefile_t *f, int new_filetype) {
  codefile_t new_f = *f;
  new_f.filetype = new_filetype;
  return new_f;
}

void change_filetype_mutable(codefile_t *f, int new_filetype) {
  f->filetype = new_filetype;
}

void update_file(int filedata[200], int new_filetype, int new_num_lines) {
  filedata[1] = new_num_lines;
  filedata[2] = new_filetype;
  filedata[199] = 0;
}

void dump_graphics(graphics_t gsettings[10]) {
  int *ptr = (int *)gsettings;
  for (int i = 0; i < (10 * sizeof(graphics_t)) / sizeof(int); i++) {
    printf("settings[%d] = %d\n", i, ptr[i]);
  }
}

void core_utils_func(int core_utilization[]) {
  printf("sizeof core_utilization in core_utils_func: %ld\n",
         sizeof(core_utilization));
}

void concat_strings(char *str1, const char *str2) {
  int index_1 = 0;
  while (1) {
    if (str1[index_1] == '\0') {
      break;
    }
    index_1++;
  }

  int index_2 = 0;
  while (1) {
    if (str2[index_2] == '\0') {
      break;
    }
    str1[index_1 + index_2] = str2[index_2];
    index_2++;
  }

  str1[index_1 + index_2] = '\0';
}

int smart_append(TextBuffer *dest, const char *src) {
  // * Checks for available space before appending
  // * Appends as much as possible if there's not enough space
  // * Always ensure the buffer remains null-terminated
  // * Returns a status indicating whether the full append was possible
  if (dest == NULL || src == NULL) {
    return 1;
  }

  size_t capacity = sizeof(dest->buffer) - 1;

  if (dest->length >= capacity) {
    return 1;
  }

  size_t available_space = capacity - dest->length;
  size_t src_len = strlen(src);

  if (available_space >= src_len) {
    strcat(dest->buffer, src);
    dest->length += src_len;
    dest->buffer[dest->length] = '\0';
    return 1;
  } else {
    strncat(dest->buffer, src, available_space);
    dest->length += available_space;
    dest->buffer[dest->length] = '\0';
    return 0;
  }
}
