# Chapter 8: Stack Data Structure

> **Note:** This README was AI-generated to summarize my learnings and save time. All the C code in this directory is entirely my own work.

This chapter focuses on building a generic Stack data structure (`stack_t`) from scratch using dynamic memory allocation. Implementing this structure surfaced several highly critical memory management bugs, including Bus Errors, Double Frees, and Null Pointer Dereferences.

## Key Concepts Explored

### 1. Generic Data Structures (`void **`)
To make the stack "generic" (capable of holding integers, strings, floats, etc.), its core storage is an array of void pointers: `void **data`.
- A `void *` can point to any data type on the Heap.
- A `void **` is a pointer to an array of these generic pointers.
- By casting data to `(void *)` on `push` and casting it back to its actual type on `pop`, the stack can hold heterogenous data types simultaneously.

### 2. Dynamic Resizing and The `realloc` Bus Error
When the stack reaches its capacity, it uses `realloc` to double its size.
- **The Bug:** Calling `realloc(stack->data, stack->capacity)` caused a **Bus Error / Heap Corruption**.
- **The Reason:** `realloc` expects the *total number of bytes*, not the number of array elements. Passing `4` instead of `4 * sizeof(void *)` (32 bytes) told the OS to shrink the memory block. Subsequent pushes wrote data past the boundary of the shrunk block, silently overwriting the **Heap Manager's hidden metadata** (which tracks free/used chunks).
- **The Crash:** The program didn't crash during the overwrite. It crashed with a Bus Error at the end of the program when `free()` tried to read the corrupted metadata to clean up the heap.

#### Visualization: Heap Corruption
```text
+-------------------+-------------------------------+
| Hidden Metadata   | Allocated Memory (Payload)    |
| (Size: 4 bytes)   | [ Ptr 1 ] [ Ptr 2 ] [ Ptr 3 ] | <- Wrote 24 bytes into a 4-byte space!
+-------------------+-------------------------------+
                    ^ OVERWRITES NEIGHBORING METADATA
```

### 3. Null Pointer Dereference (Segmentation Fault)
When popping items off the stack, if `stack->count` reaches `0`, the `stack_pop` function safely returns `NULL`.
- **The Bug:** Attempting to `printf` the dereferenced result (`*popped`) without checking if it was `NULL` caused an immediate **Segmentation Fault**.
- **The Lesson:** The OS actively prevents any program from reading or writing to memory address `0x0`. You must *always* check pointers returned by functions for `NULL` before dereferencing them.

### 4. Double Free (Trace Trap)
Calling `free()` on the same pointer multiple times triggers a **Trace Trap**.
- **The Bug:** Calling `stack_free(s)` three times.
- **The Reason:** `free()` returns memory to the OS, but it *does not* change the pointer variable. The pointer becomes a "Dangling Pointer". Calling `free()` on a Dangling Pointer causes the OS to halt the program to prevent malicious exploits (like a secondary system taking over that freed memory, only for your program to blindly free it again).
- **The Fix:** Always set a pointer to `NULL` immediately after freeing it. `free(NULL)` is safe and simply does nothing.

### 5. Type Punning (The "Scary" Push)
A pointer is fundamentally just an 8-byte integer (on a 64-bit system) that stores a memory address.
- In `scary_double_push`, we literally stored the integer `1337` *inside* the pointer itself by casting it: `stack_push(s, (void *)1337)`.
- To safely read it back without throwing compiler warnings, we cast it first to a `size_t` (an 8-byte integer), and then to an `int` (a 4-byte integer): `(int)(size_t)scary_stack->data[0]`.
- **Warning:** This is a common low-level optimization to save Heap allocations, but it makes the data structure incredibly dangerous to `free()`, because calling `free(1337)` will crash the program.

### 6. String Copying: `=` vs `strcpy`
When dealing with strings, pointer assignment is very different from string copying.

| Approach | Code Example | Memory Layout | Pros & Cons |
| :--- | :--- | :--- | :--- |
| **Pointer Assignment** | `ptr_char = "String";` | Both pointers point to the exact same memory address (often read-only memory). | **Fast**, but modifying one modifies both. Unsafe if returning from a local function scope. |
| **String Copy** | `malloc(len);`<br>`strcpy(ptr_char, val);` | Two separate memory addresses containing identical byte sequences. | **Safe**. You own the new Heap memory and can modify it independently. Requires manual `free()`. |

## Files in this Directory
- `exercise.h`: Defines the `stack_t` struct and function prototypes.
- `exercise.c`: Implements the stack creation, pushing (with dynamic `realloc`), popping, freeing, and multiple-type pushing logic.
- `main.c`: The testing ground demonstrating Heap corruption fixes, Null checks, Double Free protections, and Type Punning tricks.