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

typedef enum
{
	T_DIV_N_LOG_N_t,
	T_DIV_LOG_N_t,
	T_DIV_N_RAISED_2_t,
    T_DIV_N_RAISED_3_t,
    T_DIV_TWO_N_t,
    T_DIV_ONE_t,
    T_DIV_N_t,
    T_DIV_N_DIV_2_t
} viewName_t;

// ui_run starts a terminal-based user interface
void ui_run();
void print_results(result_t *buf, int n, algorithm_t a, case_t c);
void print_array_sort(result_t *buf, int n, case_t c, algorithm_t a);
void print_array_search(result_t *buf, int n, case_t c, algorithm_t a);
void printAdam(result_t *buf, case_t c, int one, int two, int three);
void printLines(algorithm_t a, case_t c, result_t *buf, int size, int x, int y, int z);

#endif
