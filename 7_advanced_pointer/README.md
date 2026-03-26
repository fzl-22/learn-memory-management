# Chapter 7: Advanced Pointers

> **Note:** This README was AI-generated to summarize my learnings and save time. All the C code in this directory is entirely my own work.

This chapter ventures beyond basic memory addresses and explores the advanced pointer concepts required to build complex data structures, dynamic arrays, and generic functions in C.

## Key Concepts Explored

### 1. Pointers to Pointers (Double Pointers `**`)
A double pointer stores the memory address of *another pointer*. 
- **Why it's needed:** In C, everything is passed by value. If you pass a pointer (`int *p`) into a function and try to `malloc` it inside the function, the original pointer in the caller won't change; only the local copy changes. To modify where a pointer points from inside a function, you must pass a pointer to that pointer (`int **p`).
- **Example (`allocate_int`)**: The function takes `int **pointer_pointer`, allocates heap memory, and modifies the caller's pointer to point to this new memory by dereferencing it: `*pointer_pointer = malloc(...)`.

### 2. Arrays of Pointers
Instead of an array of heavy structs, it is often much more efficient to create an array of *pointers* to structs. 
- **Example (`create_token_pointer_array`)**: This function allocates an array of pointers (`token_t **`). It then individually allocates heap memory for each `token_t` and assigns the resulting pointers to the array. This prevents dangling pointers by ensuring the tokens live on the Heap rather than relying on Stack-allocated inputs.

### 3. Void Pointers (`void *`)
A `void *` is a "generic" pointer. It represents a raw memory address with no associated data type.
- **Bypassing the Type System**: You can pass any pointer type (e.g., `int *`, `char *`, `struct *`) into a function expecting a `void *` without compiler warnings.
- **The Catch (Casting)**: Because the compiler doesn't know the underlying type, you *cannot* directly dereference a `void *`. You must explicitly cast it back to a known type first (e.g., `*(int *)void_ptr`).
- **Example (`snek_zero_out`)**: This function accepts a `void *` and an `enum` tag. It uses a `switch` statement on the tag to safely cast the `void *` into the correct struct type (`snek_int_t *`, `snek_float_t *`, etc.) before modifying its fields.

### 4. Generic Memory Manipulation (`memcpy` and `swap`)
By combining `void *`, the `sizeof` operator, and the `memcpy` (memory copy) function, you can write truly generic C functions.
- **The Generic Swap**: Instead of writing separate `swap_ints` and `swap_strings` functions, `exercise.c` implements a universal `swap(void *vp1, void *vp2, size_t size)` function.
- **How it works**:
  1. It allocates a temporary buffer on the heap using `malloc(size)`.
  2. It copies the raw bytes from `vp1` into the `tmp` buffer using `memcpy`.
  3. It copies the raw bytes from `vp2` into `vp1`.
  4. It copies the raw bytes from `tmp` into `vp2`.
  5. It frees the temporary buffer.
- This allows the program to swap *anything*—integers, string pointers, or even entire massive `coffee_shop_t` structs—using the exact same function!

## Files in this Directory
- `exercise.h`: Defines the structs (`token_t`, `snek_float_t`, `coffee_shop_t`) and function prototypes.
- `exercise.c`: Implements the double pointer allocations, void pointer casting, and generic memory swapping.
- `main.c`: The entry point that tests double pointers, array of pointers, and proves that the generic `swap` function works on varying data types.
