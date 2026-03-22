#pragma once

typedef struct Coordinate {
    int x;
    int y;
    int z;
} coordinate_t;

coordinate_t new_coord(int x, int y, int z);
coordinate_t scale_coord(coordinate_t c, int factor);

typedef struct SneklangVar {
    char type;
    char *name;
    int value;
    char is_constant;
    int scope_level;
} sneklang_var_t;

typedef struct SneklangVarGood {
    char *name;
    int value;
    int scope_level;
    char is_constant;
    char type;
} sneklang_var_good_t;
