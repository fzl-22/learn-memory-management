# Chapter 1: C Basics

> *Note: While this README was AI-generated to save time, all the code within this directory is entirely my own work.*

Welcome to the first chapter of my C programming and memory management journey! This directory establishes the foundational concepts of the C language, covering everything from basic syntax to compilation units and primitive data types.

## What I Learned

Based on the exercises and code in this chapter, here are the key concepts I have explored and mastered:

### 1. Project Structure and Compilation Units
* **Source Files (`.c`) and Header Files (`.h`)**: I learned how to separate code into definitions (headers) and implementations (source files) to keep projects organized.
* **Include Guards**: I learned how to prevent redefinition errors when including header files multiple times. I explored both the modern `#pragma once` directive and the traditional macro guard pattern (`#ifndef`, `#define`, `#endif`).

### 2. Variables and Data Types
* **Primitive Types**: I worked with fundamental C data types including `int`, `float`, `double`, `char`, and boolean (`_Bool`).
* **Memory Footprint**: Using the `sizeof()` operator, I inspected the actual byte size of different data types in memory. This gave me an early look into how C allocates memory for basic variables, including platform-dependent types like `size_t`.

### 3. Functions and Type Casting
* **Function Prototypes**: I learned how to declare functions in a header file before defining them in a `.c` file.
* **Type Casting**: In functions like `get_average()` and `add()`, I learned how to explicitly cast integers to floats (e.g., `(float)(x + y + z)`) to ensure accurate floating-point arithmetic and prevent integer division truncation.
* **Returning Strings**: I learned how to return string literals using `char *` from functions.

### 4. Control Flow and Logic
* **Conditionals**: I implemented `if`, `else if`, and `else` branching logic to control program execution (e.g., in `get_temperature_status()`).
* **Iteration**: I practiced different types of loops:
  * `for` loops to iterate over a known range (`print_numbers()`).
  * `while` loops for continuous execution based on a condition (`print_numbers_reverse()`).

### 5. Formatting Output
* **`printf` Formatting**: I learned how to format console output using various format specifiers:
  * `%d` for integers
  * `%.2f` for floats (limiting to 2 decimal places)
  * `%s` for strings
  * `%zu` for `size_t` (vital for printing `sizeof()` results without warnings)

## Files in this Directory
* `exercise.h`: Contains function prototypes and demonstrates include guards.
* `exercise.c`: Implements the mathematical, logical, and looping functions.
* `main.c`: The entry point of the program that tests all the implemented functions and explores the sizes of various data types.