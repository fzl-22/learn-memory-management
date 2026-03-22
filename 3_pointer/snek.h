#pragma once

#include <stddef.h>

unsigned long size_of_addr(long long i);

typedef struct CodeFile {
    int lines;
    int filetype;
} codefile_t;

codefile_t change_filetype(codefile_t *f, int new_filetype);

void change_filetype_mutable(codefile_t *f, int new_filetype);

void update_file(int filedata[200], int new_filetype, int new_num_lines);

typedef struct Coordinate {
    int x;
    int y;
    int z;
} coordinate_t;

typedef struct Graphics {
    int fps;
    int height;
    int width;
} graphics_t;

void dump_graphics(graphics_t gsettings[10]);

void core_utils_func(int *arr);

void concat_strings(char *str1, const char *str2);

typedef struct {
    size_t length;
    char buffer[64];
} TextBuffer;

int smart_append(TextBuffer* dest, const char* src);

// Forward declaration
typedef struct Node node_t;
typedef struct Node {
    int value;
    node_t *next;
} node_t;

// Mutual Struct
typedef struct Employee employee_t;
typedef struct Department department_t;

typedef struct Employee {
    int id;
    char *name;
    department_t *department;
} employee_t;

typedef struct Department {
    char *name;
    employee_t *manager;
} department_t;
