#include <stdio.h>
#include "exercise.h"

float add(int x, int y) {
    return (float)(x + y);
}

int max_sneklang_memory(int max_threads, int memory_per_thread) {
    return (max_threads * memory_per_thread);
}

int main() {
    // printf("Program in C!\n");

    // printf("The sum is: %.2f", add(3, 4));
    printf("Max Sneklang memory: %d bytes\n", max_sneklang_memory(10, 10));

    printf("Average: %.2f\n", get_average(5, 4, 3));

    printf("Snek Score: %.2f\n", snek_score(10, 10, 10, 0.2));

    printf("Temperature status: %s\n", get_temperature_status(72));

    printf("SIZEOF()\n");
    printf("sizeof(char) = %zu bytes\n", sizeof(char));
    printf("sizeof(bool) = %zu bytes\n", sizeof(_Bool));
    printf("sizeof(int) = %zu bytes\n", sizeof(int));
    printf("sizeof(float) = %zu bytes\n", sizeof(float));
    printf("sizeof(double) = %zu bytes\n", sizeof(double));
    printf("sizeof(size_t) = %zu bytes\n", sizeof(size_t));

    print_numbers(1, 10);

    print_numbers_reverse(1, 10);
    return 0;
}
