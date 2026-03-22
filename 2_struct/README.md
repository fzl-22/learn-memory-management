# Chapter 2: Structs and Memory Alignment

> *Note: This README was AI-generated to summarize my learnings and save time. All the C code in this directory is entirely my own work.*

This directory covers the fundamentals of defining, manipulating, and understanding the memory layout of structures (`struct`) in C. 

## Key Concepts Covered

### 1. Defining and Using Structs
A `struct` is a composite data type that groups variables of different types under a single name. 
- We use the `typedef struct { ... } name_t;` pattern to create a new type alias, avoiding the need to write the `struct` keyword every time we use it. 
- Example: `coordinate_t` groups `x`, `y`, and `z` integers.

### 2. Designated Initializers
When creating a new struct instance, we use designated initializers (e.g., `.x = x, .y = y`). This is a modern C99 feature that makes code much more readable and robust, as you explicitly define which member is receiving which value, regardless of their declared order.

### 3. Pass by Value
In `coord.c`, functions like `scale_coord(coordinate_t c, int factor)` take a struct as an argument and return a `coordinate_t`. 
- **Important Note:** When a struct is passed this way, the entire struct is copied into the function's local scope. Returning it copies it back out. While this is fine for small structs (like 3 integers), it can be inefficient for large structs, which is where pointers come in later.

### 4. Memory Padding and Alignment (Crucial for Memory Management)
This is the most critical memory management concept in this chapter, demonstrated in `main.c` comparing `sneklang_var_t` ("bad" packing) and `sneklang_var_good_t` ("good" packing).

CPUs read memory in word-sized chunks (e.g., 4 or 8 bytes at a time). To optimize CPU access speed, C compilers automatically insert empty "padding" bytes so that structural members align to these boundaries.

- **Bad Packing (`sneklang_var_t`)**: 
  Types are mixed (`char`, then `char*`, then `int`, then `char`, then `int`). Because a pointer (`char*`) needs 8-byte alignment and an `int` needs 4-byte alignment, the compiler must insert multiple padding bytes between the smaller `char` fields to align the larger ones. This bloats the overall `sizeof()` the struct.
  
- **Good Packing (`sneklang_var_good_t`)**: 
  Fields are ordered largest to smallest (or grouped by similar alignment requirements): pointer (`char*`), then `int`s, then `char`s. This minimizes wasted space because the smaller fields neatly pack together at the end without requiring padding between them.

## Files
* `coord.h`: Contains struct definitions and function prototypes. Highlights the contrast between unoptimized and memory-optimized struct definitions.
* `coord.c`: Contains the implementation of struct initialization and manipulation using designated initializers.
* `main.c`: The entry point that executes the functions and proves the theory of memory alignment by printing the `sizeof()` both the optimized and unoptimized structs.