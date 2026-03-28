# Chapter 9: Objects and Polymorphism

> **Note:** This README was AI-generated to summarize my learnings and save time. All the C code in this directory is entirely my own work.

This chapter represents the culmination of all the previous memory management lessons. By combining `struct`s, `union`s, `enum`s, and dynamic Heap allocation, I built a dynamically typed object system (`snek_object_t`) from scratch. This mimics how high-level languages like Python or JavaScript handle variables under the hood!

## Key Concepts Explored

### 1. Tagged Unions (Polymorphism in C)
C is a statically typed language, but we can simulate dynamic typing (polymorphism) using a **Tagged Union**.
- **The Tag:** An `enum` (`snek_object_kind_t`) acts as the "tag" (e.g., `INTEGER`, `STRING`, `ARRAY`).
- **The Union:** A `union` (`snek_object_data_t`) reserves enough memory for the largest possible payload.
- **The Object:** By wrapping both in a `struct`, functions like `snek_add` can check the `kind` tag at runtime and safely route the logic to the correct union field.

### 2. Arrays of Pointers (Double Pointers `**`)
For the `ARRAY` type, the payload is a `snek_array_t` struct containing `snek_object_t **elements`.
- Instead of allocating a massive contiguous block of objects, `calloc` allocates an array of 8-byte **pointers**.
- This makes resizing instantaneous and allows the array to hold objects of drastically different sizes (since all pointers are 8 bytes).

#### Visualization: Nested Memory Layout of an Array Object
When creating an array `[11, "hi"]`, the Heap looks like a web of allocations:

| Memory Segment | Type | Contents | Points To |
| :--- | :--- | :--- | :--- |
| **Heap (Obj A)** | `snek_object_t` (Container) | `kind = ARRAY`, `data.v_array` struct | -> Heap (Array Ptrs) |
| **Heap (Array Ptrs)**| `snek_object_t **` | `[ Ptr 0 ] [ Ptr 1 ]` | `Ptr 0` -> Heap (Obj B)<br>`Ptr 1` -> Heap (Obj C) |
| **Heap (Obj B)** | `snek_object_t` (Integer) | `kind = INTEGER`, `data.v_int = 11` | *N/A (Raw value)* |
| **Heap (Obj C)** | `snek_object_t` (String) | `kind = STRING`, `data.v_string` | -> Heap (String Payload) |
| **Heap (String Payload)** | `char *` | `"hi\0"` | *N/A (Raw bytes)* |

*(Notice how a single Array requires at least **4 distinct malloc/calloc calls**! Freeing this structure requires a careful, bottom-up approach to avoid memory leaks.)*

### 3. The Local Stack Variable Bug (`&ptr_arr`)
When implementing `new_snek_array`, I accidentally introduced a severe Dangling Pointer bug:
```c
snek_object_t *ptr_arr = calloc(...);
snek_array_t arr = {.size = size, .elements = &ptr_arr}; // FATAL BUG
```
By taking the address of `ptr_arr` (`&ptr_arr`), I stored a pointer to a **temporary local Stack variable**. When the function returned, the Stack frame was destroyed, making `elements` a Dangling Pointer. The fix was to assign the double pointer returned by `calloc` directly.

### 4. Shallow Copies vs. Deep Copies
When passing objects into `new_snek_vector3(x, y, z)`, the vector stores the *exact memory addresses* of `x, y, z`. This is a **Shallow Copy**.
- **The Crash:** If `main.c` manually frees `x`, and then tries to free `vector->x`, the Operating System catches a **Double Free** and throws a `Trace Trap` (or `pointer being freed was not allocated` error).
- **The Lesson:** When structs share pointers to the same Heap memory, you must establish strict "Ownership" rules about who is responsible for calling `free()`.

### 5. The Hidden Flaw in `snek_add`
The `snek_add` function has a major architectural flaw when dealing with Vectors and Arrays: **It creates Shallow Copies.**
```c
// Inside snek_add for ARRAY:
snek_array_set(arr_obj, i, snek_array_get(a, i));
```
When `snek_add` concatenates two arrays, it doesn't duplicate the underlying objects (no `malloc`). It just copies the pointers. 
If `main.c` frees the original arrays, the new concatenated array is suddenly filled entirely with Dangling Pointers! A robust system requires implementing a "Deep Copy" (or `clone`) function to recursively duplicate all nested objects.

## Files in this Directory
- `snekobject.h`: Defines the Tagged Union architecture (`snek_object_t`).
- `snekobject.c`: Implements constructors (`new_snek_*`), array getters/setters, and the polymorphic `snek_add` function.
- `main.c`: A rigorous testing suite that exposes the extreme care required to traverse and `free()` deeply nested dynamic structures without triggering Trace Traps or Segfaults.