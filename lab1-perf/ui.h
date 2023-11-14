#ifndef UI_H
#define UI_H

#define MENU_WIDTH 40
#define RESULT_ROWS 6
#define PRINT_WIDTH 80
#define BILLION 1000000000L
#define ARRAY_NAME 25
#define CASE_NAME 25
#define spacing "\n%-12s %12s %15s %15s %15s\n"

#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

const char *viewNames[] = {
    "T/nlogn",
    "T/logn",
    "T/n^2",
    "T/n^3",
    "T/2n",
    "T/1",
    "T/n",
    "T/(n/2)"};
const char *calculation[] = {
    "(time / (size * log(size)))",
    "T/logn",
    "time / (size * size)",
    "(time / (size * size * size))",
    "time / (size * 2)",
    "(time / 1)",
    "time / size",
    "(time / (size / 2))"
};

// ui_run starts a terminal-based user interface
void ui_run();
void print_results(result_t *buf, int n, algorithm_t a, case_t c);
void print_array_sort(result_t *buf, int n, case_t c, char *str, char *name);
void print_array_search(result_t *buf, int n, case_t c, char *str, char *name);
void printAdam(result_t *buf, case_t c, int one, int two, int three);

#endif
