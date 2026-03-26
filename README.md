# Learning C and Memory Management

> **Note:** The `README.md` files throughout this repository were AI-generated to save time documenting my progress, but all the C code within the project was written entirely by me.

Welcome to my journey of learning the C programming language and mastering memory management! This repository serves as my personal playground, study guide, and archive of exercises as I delve deep into the low-level concepts of C.

## Contents

The repository is organized into chapters, each focusing on specific concepts.

### [Chapter 1: C Basics](./1_c_basics)
This directory establishes the foundational concepts of the C language. It covers compilation units, header files, primitive data types, functions, control flow, and an introduction to analyzing memory footprints using `sizeof()`.

### [Chapter 2: Structs and Memory Alignment](./2_struct)
This chapter covers data aggregation using structs. More importantly, it explores the critical concepts of memory padding and alignment, demonstrating how the order of variables inside a struct directly impacts its overall size in memory to optimize CPU access.

### [Chapter 3: Pointers and Memory Management](./3_pointer)
This chapter dives into the core of C: Pointers. It explores direct memory access, pointer arithmetic, array decay, C-style string manipulation (null-terminated character arrays), and safe buffer management strategies to prevent buffer overflows.

### [Chapter 4: Enums and Memory Sizing](./4_enum)
This chapter focuses on Enumerations (`enum`). It explores how enums are used to define sets of named integer constants, how they integrate with `switch` statements, and crucially, how the C compiler dynamically determines the underlying integer byte size of an enum based on the magnitude of its defined values.

### [Chapter 5: Unions and Memory Layout](./5_union)
This chapter explores Unions (`union`) and how they provide a way to store different data types in the same memory location. It covers creating algebraic data types by combining enums and unions, interpreting raw memory, and understanding endianness through memory layout examples.

### [Chapter 6.1: The Stack](./6_1_stack)
This chapter delves into the Call Stack. It explores how local variables and function call frames are managed in memory. Key concepts include understanding why the stack grows downwards, the strict memory limits imposed by the OS (`ulimit -s`) causing Segmentation Faults (Stack Overflow), and the danger of Dangling Pointers when returning addresses of local stack variables.

### [Chapter 6.2: The Heap](./6_2_heap)
This chapter explores dynamic memory allocation using the Heap. It covers using `malloc` to request memory that survives function returns, the absolute necessity of `free()` to prevent Memory Leaks, the critical dangers of "Use-After-Free" vulnerabilities, and a brief look at Big Endian vs. Little Endian byte ordering.

## How to Navigate

Feel free to explore the directories above. Each folder contains its own `README.md` with more detailed explanations of the key concepts covered, along with the source code (`.c` and `.h` files) demonstrating those concepts in action.