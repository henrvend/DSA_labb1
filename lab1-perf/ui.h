#ifndef UI_H
#define UI_H

#define MENU_WIDTH 40
#define RESULT_ROWS 6
#define PRINT_WIDTH 80

#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

// ui_run starts a terminal-based user interface
void ui_run();
void print_results(result_t *buf, int n,  algorithm_t a, case_t c);

#endif
