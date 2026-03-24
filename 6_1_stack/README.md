# Chapter 6.1: The Call Stack

> **Note:** This README was AI-generated to summarize my learnings and save time. All the C code in this directory is entirely my own work.

This chapter explores **The Stack** (or Call Stack), one of the most critical areas of memory in a C program. By inspecting memory addresses directly using `__builtin_frame_address`, I was able to prove how the C compiler manages memory during function calls, why Stack Overflows happen, and the dangers of dangling pointers.

## Overview of Program Memory
When a C program runs, the Operating System assigns it a chunk of memory divided into segments. A crucial concept for Systems/Kernel programmers is understanding this layout:

```text
HIGH MEMORY ADDRESSES (e.g., 0xFFFFFFFF)
+------------------------+
|       The Stack        |  <-- Stack Pointer (SP) starts high
|           |            |
|           V            |  <-- Stack grows DOWNWARDS
|                        |
|                        |
|           ^            |  <-- Heap grows UPWARDS
|           |            |
|       The Heap         |  <-- Dynamic allocation (malloc)
+------------------------+
|     Data Segments      |  <-- Global & `static` variables
+------------------------+
|  Code (Text) Segment   |  <-- Compiled Machine Code
+------------------------+
LOW MEMORY ADDRESSES (e.g., 0x00000000)
```

## Key Concepts Explored

### 1. The Stack Grows Downwards
When a function is called, the CPU allocates a "Stack Frame" to store its local variables, arguments, and the return address. Because the Stack starts at the top of memory, it must **grow downwards** to allocate more space.
- In `main.c`, printing the stack pointer difference between nested function calls showed the `current_sp` continuously decreasing (e.g., moving from `...336` to `...304` to `...272`).

### 2. Stack Frames & The ARM64 ABI
Why did the stack pointer jump by exactly **32 bytes** with each nested function call?
This is dictated by the Application Binary Interface (ABI) for ARM64 (Apple Silicon):
- **8 bytes**: Return Address.
- **8 bytes**: Previous Frame Pointer.
- **8 bytes**: Local variable (`const char *message`).
- **8 bytes**: Alignment Padding (ARM64 strictly requires the stack to be 16-byte aligned).
- **Total = 32 bytes.** 
When functions run *sequentially* rather than nested, the Stack recycles this memory perfectly, moving down 32 bytes and back up 32 bytes over and over.

### 3. The `static` Keyword
In `printStackPointerDiff`, `last_sp` was declared as `static void *last_sp = NULL;`.
Unlike normal local variables, `static` variables are **not stored on the Stack**. They live in the Data Segment. This means they are only initialized once when the program starts, and their state persists across multiple function calls, which allowed the program to "remember" the original starting stack address.

### 4. Stack Overflows & `ulimit -s`
The Stack is incredibly fast, but it is **small**. On macOS, the Operating System imposes a strict hard limit of roughly **8 Megabytes** (visible by running `ulimit -s` in the terminal, which outputs `8176` KB).
- **The Crash:** Trying to allocate a 10MB array directly on the Stack (`char snek_pool[1024 * 1024 * 10];`) resulted in a `Segmentation Fault` because the OS instantly kills any program trying to exceed its 8MB boundary.
- **The Fix:** Massive data structures must be allocated on the **Heap** using `malloc()`, which can grow to consume almost all available RAM.

### 5. Dangling Pointers (The Golden Rule)
The most insidious bug explored was in the `new_coord()` function:
```c
coord_t *new_coord(int x, int y) {
  coord_t c;      // Created on the Stack
  // ...
  return &c;      // FATAL: Returning address of a local variable
}
```
**Never return a pointer to a local stack variable.**
When the function returns, its stack frame is instantly deallocated. The returned pointer becomes a "Dangling Pointer". In `main.c`, when we called `printf`, the `printf` function pushed its own massive stack frame right over the deallocated `coord_t c` memory space, corrupting the coordinates and printing garbage data (`1875094864, 1`).

## Files in this Directory
- `main.c`: Contains the code demonstrating stack pointer tracking, stack overflows, and dangling pointers.
- `exercise.h`: Header file containing function prototypes and the `coord_t` struct definition.