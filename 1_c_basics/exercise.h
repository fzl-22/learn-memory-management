#pragma once
// avoid redefinition errors
// older method is to use:
// #ifndef EXERCISE_H
// #define EXERCISE_H
// ...some cool code...
// #endif

float get_average(int x, int y, int z);

float snek_score(
    int num_files,
    int num_contributors,
    int num_commits,
    float avg_bug_criticality
);

char *get_temperature_status(int temp);

void print_numbers(int start, int end);

void print_numbers_reverse(int start, int end);
