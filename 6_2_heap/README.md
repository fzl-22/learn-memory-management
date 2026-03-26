# Chapter 6.2: The Heap and Dynamic Memory

> **Note:** This README was AI-generated to summarize my learnings and save time. All the C code in this directory is entirely my own work.

This chapter shifts focus from the automated, size-restricted Stack to the vast, manually managed territory of the **Heap**. By using `malloc()` and `free()`, I learned how to safely create variables that outlive their host functions, manage large data allocations, and avoid critical memory bugs.

## Key Concepts Explored

### 1. Dynamic Allocation (`malloc`)
Unlike Stack variables that are destroyed the moment a function returns, memory allocated on the Heap persists until it is explicitly freed.
- In `exercise.c`, the initial (commented out) version of `get_full_greeting` tried to return a `char full_greeting[100]` allocated on the Stack, which creates a dangerous Dangling Pointer.
- The fixed version uses `malloc(size * sizeof(char))`. This asks the Operating System for memory on the Heap. The function safely returns a pointer to this Heap memory, allowing the greeting string to survive after the function finishes.

### 2. Proving Memory Location (`is_on_stack`)
To physically prove that `malloc` places data far away from the Stack, `main.c` implements an `is_on_stack` helper function. 
- It uses `__builtin_frame_address(0)` to find the current top of the Stack.
- It calculates if a given pointer is within a `1024` byte threshold of that active stack frame.
- When passing the pointers returned by `get_full_greeting`, the function returns `0` (`false`), definitively proving that `malloc` allocates memory in an entirely different segment of RAM (the Heap).

### 3. Memory Leaks and `free()`
With great power comes great responsibility. Because the Heap is manually managed, the compiler will *never* clean it up for you.
- If you call `malloc()` but forget to call `free()`, that memory remains locked and unusable. This is a **Memory Leak**.
- In the `allocate_scalar_list` loop, the program allocates 50,000 integers 500 times. By correctly calling `free(lst)` at the end of each iteration, the program safely recycles the Heap memory. Without `free()`, this loop would rapidly consume Megabytes of RAM and potentially crash the system.

### 4. The "Use-After-Free" Vulnerability
A critical security flaw occurs if you try to read or write to a pointer *after* you have called `free()` on it.
- **Why it prints garbage:** When `free()` is called, the memory allocator reclaims the chunk and often overwrites the data with its own internal metadata (like linked-list pointers to track available memory). 
- If you dereference a freed pointer (e.g., in a `for` loop), you aren't reading your old data; you are reading the memory allocator's secret internal bookkeeping, which looks like garbage numbers (e.g., `6 0 6 0 0`).
- **Best Practice:** After calling `free(result);`, immediately set the pointer to `NULL` (`result = NULL;`) so you cannot accidentally use it again.

### 5. Endianness (Byte Ordering)
The end of `main.c` introduces **Endianness**, which dictates how a CPU reads and writes multi-byte data types (like integers) into memory byte-by-byte. 
- Most modern systems (including Apple Silicon and Intel/x86) are **Little-Endian**. 
- Network protocols generally use **Big-Endian** (Network Byte Order).

#### Endianness Memory Layout Example
If we store the 32-bit hex integer `0x12345678` starting at memory address `0x1000`, here is how the two architectures arrange the bytes:

| Memory Address | Big Endian (Network Order) | Little Endian (Modern CPUs) |
| :--- | :--- | :--- |
| `0x1000` (Lowest) | `0x12` *(Most Significant Byte)* | `0x78` *(Least Significant Byte)* |
| `0x1001` | `0x34` | `0x56` |
| `0x1002` | `0x56` | `0x34` |
| `0x1003` (Highest) | `0x78` *(Least Significant Byte)* | `0x12` *(Most Significant Byte)* |

*Understanding Endianness is mandatory for systems programming, as failing to swap bytes when reading from a network packet or a file will result in completely corrupted values!*

## Files in this Directory
- `main.c`: Demonstrates `malloc`, `free`, checking memory segments, and Use-After-Free protections.
- `exercise.c`: Implements functions that safely allocate strings and arrays on the Heap.
- `exercise.h`: Function prototypes.