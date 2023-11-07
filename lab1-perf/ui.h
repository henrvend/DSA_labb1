#ifndef UI_H
#define UI_H

#define MENU_WIDTH 40
#define RESULT_ROWS 6

#include "analyze.h"

// ui_run starts a terminal-based user interface
void ui_run();
void print_results(result_t *buf, int n);

#endif
