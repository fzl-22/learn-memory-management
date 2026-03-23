# Chapter 5: Unions and Memory Layout

> **Note:** This README was AI-generated to summarize my learnings and save time. All the C code in this directory is entirely my own work.

This chapter explores **Unions** (`union`) in C and how they allow different data types to be stored in the exact same memory location. It also dives deep into raw memory layout, type punning, and the concept of Endianness.

## Key Concepts Explored

### 1. The Basics of Unions
Unlike a `struct` where every member has its own distinct memory space, all members of a `union` share the *exact same memory location*. 
- The `sizeof` a union is simply the size of its largest member.
- You can only safely store a value in *one* of the union's members at a time. If you write to one member and read from another, you are interpreting the raw bytes of the first data type as if they were the second data type.

### 2. Tagged Unions (Algebraic Data Types)
Because a union doesn't inherently know which of its fields is currently "active," it is standard practice to pair a `union` with an `enum` "tag" inside a `struct`.
- **Example (`snek_object_t`)**: This acts like a dynamically typed variable (similar to Python). The `kind` field (an enum) tells the program whether the active payload in the `data` union is a `v_int` (integer) or a `v_string` (pointer). The `format_object` function safely uses a `switch` statement on the tag to read the correct field.

### 3. Type Punning
Type punning is the practice of writing to one union member and reading from a different one to perform raw byte translation.
- **Example (`val_or_err_t`)**: By setting `lanes_score.value = -420` and reading `lanes_score.err`, we are forcing the CPU to read the two's complement binary representation of `-420` as if it were an `unsigned int`.

### 4. Memory Layout and Endianness (Crucial for Networking & Kernels)
This is the most critical concept in this chapter. The `packet_header_t` union allows us to write structured data using the `tcp_header` struct and read the raw underlying memory byte-by-byte using the `raw[8]` array.

**Endianness** refers to the order in which a computer stores multi-byte data types in memory. Your Mac uses an architecture that is **Little-Endian**. This means the "little end" (the least significant byte) is stored at the lowest memory address.

When we set the fields in `main.c`:
- `header.tcp_header.src_port = 0x1234;` (2 bytes)
- `header.tcp_header.dest_port = 0x5678;` (2 bytes)
- `header.tcp_header.seq_num = 0x9ABCDEF0;` (4 bytes)

Because of Little-Endianness, the bytes are flipped in memory. 

#### Memory Layout Table for `packet_header_t`

| Byte Offset | `raw` array | `tcp_header` struct mapping | Value Stored (Hex) | Why this value? (Little-Endian) |
| :--- | :--- | :--- | :--- | :--- |
| `0` | `raw[0]` | `src_port` (byte 0) | `0x34` | Least significant byte of `0x1234` |
| `1` | `raw[1]` | `src_port` (byte 1) | `0x12` | Most significant byte of `0x1234` |
| `2` | `raw[2]` | `dest_port` (byte 0) | `0x78` | Least significant byte of `0x5678` |
| `3` | `raw[3]` | `dest_port` (byte 1) | `0x56` | Most significant byte of `0x5678` |
| `4` | `raw[4]` | `seq_num` (byte 0) | `0xF0` | Least significant byte of `0x9ABCDEF0` |
| `5` | `raw[5]` | `seq_num` (byte 1) | `0xDE` | ... |
| `6` | `raw[6]` | `seq_num` (byte 2) | `0xBC` | ... |
| `7` | `raw[7]` | `seq_num` (byte 3) | `0x9A` | Most significant byte of `0x9ABCDEF0` |

*This concept is vital for kernel developers and network programmers, as network protocols typically require data to be sent in Big-Endian (Network Byte Order). You must constantly be aware of how the CPU lays out memory!*

## Files
- `exercise.h`: Defines the various unions and structs (`snek_object_t`, `val_or_err_t`, `color_t`, `packet_header_t`).
- `exercise.c`: Implements the constructor and formatting functions for the tagged union.
- `main.c`: The entry point that demonstrates tagged unions, type punning, and proves the Little-Endian memory layout by inspecting the byte array of a simulated TCP header.