# Chapter 4: Enums and Memory Sizing

> **Note:** This README was AI-generated to summarize my learnings and save time. All the C code in this directory is entirely my own work.

This chapter explores Enumerations (`enum`) in C, which provide a way to define a set of named integer constants, improving code readability and maintainability.

## Key Concepts Explored

### 1. Basic Enum Definitions
- By default, an `enum` starts at value `0` and increments by `1` for each subsequent member. 
- Example: `days_of_week_t` demonstrates standard implicit numbering where `MONDAY` is `0`, `TUESDAY` is `1`, and so on.

### 2. Custom Enum Values
- You can explicitly assign integer values to enum members to match external specifications or specific needs.
- Examples include `color_t` where colors are assigned arbitrary RGB-like values, and `HttpErrorCode` where standard HTTP status codes like `404` and `500` are explicitly defined.
- If you assign a value to one member, subsequent unassigned members will simply increment from the last explicitly assigned value.

### 3. Enums and Switch Statements
- Enums pair perfectly with `switch` statements to map integer codes to behavior or human-readable strings.
- In `exercise.c`, the `http_to_str` function efficiently converts an `HttpErrorCode` integer back into a descriptive string literal.

### 4. Dynamic Enum Sizing (Memory Management)
This is the critical memory management takeaway from this chapter, demonstrated in `main.c` using the `sizeof` operator.

**An `enum` is not an array; it is a single integer.** 
When you declare a variable of an enum type (like `HttpErrorCode code`), the compiler allocates exactly enough memory for **one** integer value. 

However, the size of that integer depends on the largest value defined within the enum:

- **`HttpErrorCode` (4 bytes)**: The largest value is `500`. The C compiler determines that a standard 4-byte `int` is more than sufficient to store numbers up to 500, so `sizeof(HttpErrorCode)` evaluates to 4.
- **`BigNumbers` (8 bytes)**: This enum defines massive values (e.g., `123412341234123`) that exceed the maximum capacity of a standard 32-bit integer (roughly 2.1 billion). To accommodate this, the C compiler automatically promotes the underlying type to an 8-byte integer (like a `long long`), meaning `sizeof(BigNumbers)` evaluates to 8.

## Files
- `exercise.h`: Defines the various `enum` types (`DaysOfWeek`, `Color`, `HttpErrorCode`, `BigNumbers`) and struct combinations.
- `exercise.c`: Implements the `switch`-based mapping function `http_to_str`.
- `main.c`: The entry point that demonstrates working with enums and proves the dynamic sizing behavior using `printf` and `sizeof()`.