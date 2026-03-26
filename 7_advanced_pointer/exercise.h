#pragma once

#include <stddef.h>
#include <stdint.h>
void allocate_int(int **pointer_pointer, int value);

typedef struct Token {
    char *literal;
    int line;
    int column;
} token_t;

token_t **create_token_pointer_array(token_t *tokens, size_t count);

typedef enum SnekObjectKind {
    INTEGER,
    FLOAT,
    BOOL,
} snek_object_kind_t;

typedef struct SnekInt {
    char *name;
    int value;
} snek_int_t;

typedef struct SnekFloat {
    char *name;
    long _pad;
    float value;
} snek_float_t;

typedef struct SnekBool {
    char *name;
    long _pad;
    unsigned int value;
} snek_bool_t;

void snek_zero_out(void *ptr, snek_object_kind_t kind);

void swap_ints(int *a, int *b);

void swap_strings(char **a, char **b);

typedef struct CoffeeShop {
  uint64_t quality;
  uint64_t taste;
  uint64_t branding;
} coffee_shop_t;

void swap(void *vp1, void *vp2, size_t size);
