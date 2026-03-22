# Chapter 3: Pointers and Memory Management

> **Note:** This README was AI-generated to save time documenting my progress, but all the C code in this directory was written entirely by me.

This chapter delves into one of the most powerful and core features of C: **Pointers**. By exploring the code in this directory, I have learned how C manages memory, how to interact with memory addresses directly, and how arrays and strings work under the hood.

## Key Concepts Explored

### 1. Pointers Basics & Memory Addresses
- **The Address-Of Operator (`&`)**: Used to get the exact memory address of a variable (e.g., `&i`).
- **Pointer Sizes**: A pointer stores a memory address. On a 64-bit system, a memory address is typically 8 bytes long. Therefore, `sizeof(int *)`, `sizeof(char *)`, and `sizeof(double *)` will all evaluate to 8 bytes, regardless of the size of the underlying data type they point to.

### 2. Pointers to Structs and Mutability
- By default, passing a struct to a function passes it by value (a copy). To modify a struct's state inside a function, we must pass a pointer to the struct.
- The `change_filetype_mutable` function demonstrates using the `->` operator to dereference a pointer to a struct and update its fields directly in memory.

### 3. Pointer Arithmetic & Arrays
- **Arrays are Memory Blocks**: An array is a contiguous block of memory. The array's name acts as a pointer to its first element.
- **Pointer Arithmetic**: In C, adding an integer to a pointer automatically scales the memory address by the size of the data type it points to. For example, if `numbers` is an `int *`, `numbers + 2` skips exactly 8 bytes forward (2 * 4 bytes for an integer).
- **Equivalence**: `numbers[2]` is exactly equivalent to `*(numbers + 2)`.
- **Struct Offsets**: Calculating the exact byte offset for specific fields inside arrays of structs, demonstrating how structs are laid out linearly in memory.

### 4. Array Decay
- When an array is passed as an argument to a function, it "decays" into a pointer to its first element.
- Inside the scope where the array is declared, `sizeof(arr)` returns the total size in bytes (e.g., an array of 10 `int`s is 40 bytes).
- However, when passed to a function like `core_utils_func(int *arr)`, `sizeof(arr)` only returns the size of the pointer itself (8 bytes), making it impossible to calculate the array's length inside the function using `sizeof` without passing the length explicitly.

### 5. Strings in C
- C does not have a native string type. Instead, strings are simply arrays of `char` that are terminated by a null character (`'\0'`).
- **String Manipulation**: Investigating built-in string functions like `strlen`, `strcat`, and `strncat`.
- **Manual Concatenation**: Built a custom `concat_strings` function using loops and pointer indexing to manually copy characters and append the crucial null terminator.
- **`sizeof` vs `strlen`**: Learned the distinction between `strlen` (which counts characters until it hits `\0`) and `sizeof` (which measures the size of the array or pointer storing the string).

### 6. Buffer Management & Safety
- **TextBuffer**: Defined a struct that holds a fixed-size `buffer` and its current `length`.
- **Smart Append**: Created a `smart_append` function that checks for available capacity before appending new characters to the buffer. It prevents buffer overflows by only appending what fits and safely maintaining the null terminator.

### 7. Forward Declarations and Mutual Dependencies
- **Self-Referential Structs**: Demonstrated in `snek.h` with `node_t` for a linked list, using a forward declaration so the struct can contain a pointer to its own type.
- **Mutual Dependencies**: Used forward declarations to allow two structs to reference each other (e.g., an `Employee` has a pointer to a `Department`, and a `Department` has a pointer to a Manager `Employee`).

## Files in this Directory

- `main.c`: Contains hands-on test cases demonstrating array decay, pointer arithmetic, string manipulation, and buffer management.
- `snek.c`: Implements the various pointer and struct utility functions.
- `snek.h`: Contains struct definitions (`coordinate_t`, `graphics_t`, `TextBuffer`), function prototypes, and examples of forward declarations.