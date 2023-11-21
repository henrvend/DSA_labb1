#include "ui.h"
#include "io.h"
#include "analyze.h"
//
//  Private
//
static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0)
	{
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i = 0; i < num_options; i++)
	{
		printf("    %c) %s\n", 'a' + i, options[i]);
	}
}

static void ui_menu()
{
	const char *options[] = {
		"Menu",
		"Exit\n",
		"Bubble sort best case",
		"Bubble sort worst case",
		"Bubble sort average case\n",
		"Insertion sort best case",
		"Insertion sort worst case",
		"Insertion sort average case\n",
		"Quick sort best case",
		"Quick sort worst case",
		"Quick sort average case\n",
		"Linear search best case",
		"Linear search worst case",
		"Linear search average case\n",
		"Binary search best case",
		"Binary search worst case",
		"Binary search average case\n",
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

static char *getCaseTypeString(case_t c)
{
	switch (c)
	{
	case 0:
		return "Best";
	case 1:
		return "Worst";
	case 2:
		return "Average";
	default:
		return NULL;
	}
}

static char *getAlgorithmString(algorithm_t a)
{
	switch (a)
	{
	case 0:
		return "Bubble sort";
	case 1:
		return "Insertion sort";
	case 2:
		return "Quick sort";
	case 3:
		return "Linear search";
	case 4:
		return "Binary search";
	default:
		return NULL;
	}
}


//
// Public
//
void ui_run()
{
	bool running, show_menu;
	result_t result[RESULT_ROWS];

	show_menu = true;
	running = true;
	while (running)
	{
		if (show_menu)
		{
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice())
		{
		// House keeping
		case 'a':
			show_menu = true;
			break;
		case 'b':
			running = false;
			break;
		// Bubble sort
		case 'c':
			benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
			// printf("todo> implemenet BE + present results in FE\n");
			break;
		case 'd':
			benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
			break;
		case 'e':
			benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
			break;
		case 'f':
			benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
			break;
		case 'g':
			benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
			break;
		case 'h':
			benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
			break;
		case 'i':
			benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
			break;
		case 'j':
			benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
			break;
		case 'k':
			benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
			break;
		case 'l':
			benchmark(linear_search_t, best_t, result, RESULT_ROWS);
			break;
		case 'm':
			benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
			break;
		case 'n':
			benchmark(linear_search_t, average_t, result, RESULT_ROWS);
			break;
		case 'o':
			benchmark(binary_search_t, best_t, result, RESULT_ROWS);
			break;
		case 'p':
			benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
			break;
		case 'q':
			benchmark(binary_search_t, average_t, result, RESULT_ROWS);
			break;
		// Invalid input
		default:
			show_menu = false;
			ui_invalid_input();
			break;
		}
	}
	ui_exit();
}
void print_results(result_t *buf, int n, algorithm_t a, case_t c)
{
	switch (a)
	{
	case 0: // bubble
		switch (bubble_sort_t)
		{
		case best_t: printLines(a, c, buf, n, T_DIV_N_LOG_N_t, T_DIV_N_t, T_DIV_N_RAISED_2_t);		break;
		case worst_t:	printLines(a, c, buf, n, T_DIV_N_t, T_DIV_N_RAISED_2_t, T_DIV_N_RAISED_3_t);	break;
		case average_t:	printLines(a, c, buf, n, T_DIV_LOG_N_t, T_DIV_N_RAISED_2_t, T_DIV_TWO_N_t);		break;
		default: break;
		}
		break;
	case 1: // insertion
		switch (insertion_sort_t)
		{
		case best_t:	printLines(a, c, buf, n, T_DIV_N_LOG_N_t, T_DIV_N_t, T_DIV_LOG_N_t);			break;
		case worst_t:	printLines(a, c, buf, n, T_DIV_N_LOG_N_t, T_DIV_N_RAISED_2_t, T_DIV_LOG_N_t);	break;
		case average_t:	printLines(a, c, buf, n, T_DIV_LOG_N_t, T_DIV_N_RAISED_2_t, T_DIV_TWO_N_t);		break;
		default: break;
		}
		break;
	case 2: // quick
		switch (quick_sort_t)
		{
		case best_t:	printLines(a, c, buf, n, T_DIV_N_LOG_N_t, T_DIV_N_t, T_DIV_LOG_N_t);			break;
		case worst_t:	printLines(a, c, buf, n, T_DIV_N_LOG_N_t, T_DIV_N_RAISED_2_t, T_DIV_N_RAISED_3_t);break;
		case average_t:	printLines(a, c, buf, n, T_DIV_N_RAISED_2_t, T_DIV_N_LOG_N_t, T_DIV_TWO_N_t);	break;
		default: break;
		}
		break;
	case 3: // Linear
		switch (linear_search_t)
		{
		case best_t:	printLines(a, c, buf, n, T_DIV_ONE_t, T_DIV_N_t, T_DIV_N_DIV_2_t);		break;
		case worst_t:	printLines(a, c, buf, n, T_DIV_LOG_N_t, T_DIV_N_t, T_DIV_ONE_t);		break;
		case average_t:	printLines(a, c, buf, n, T_DIV_LOG_N_t, T_DIV_N_t, T_DIV_N_DIV_2_t); 	break;
		default: break;
		}
		break;
	case binary_search_t: // Binary
		switch (c)
		{
		case best_t:	printLines(a, c, buf, n, T_DIV_ONE_t, T_DIV_N_t, T_DIV_N_DIV_2_t);	break;
		case worst_t:	printLines(a, c, buf, n, T_DIV_LOG_N_t, T_DIV_N_t, T_DIV_ONE_t);	break;
		case average_t:	printLines(a, c, buf, n, T_DIV_LOG_N_t, T_DIV_N_t, T_DIV_N_DIV_2_t); break;
		default: break;
		}
		break;
	default:
		break;
	}
}


void printLines(algorithm_t a, case_t c, result_t *buf, int n, int x, int y, int z)
{
	ui_line('*', PRINT_WIDTH);
	printf("%40s: %s\n", getAlgorithmString(a), getCaseTypeString(c));
	ui_line('=', PRINT_WIDTH);

	const char *viewName[] = {"T/nlogn", "T/logn", "T/n^2", "T/n^3", "T/2n", "T/1", "T/n", "T/(n/2)"};

	printf("\n%-12s %12s %15s %15s %15s\n", "Size", "time T(s)", viewName[x], viewName[y], viewName[z]);
	ui_line('-', PRINT_WIDTH);

	for (int i = 0; i < n; i++)
	{
		double time = buf[i].time;
		int size = buf[i].size;
		const double calc[] = {	time / (size * log(size)), 
								time / log(size), 
								time / (size * size),
								time / (size * size * size), 
								time / (size * 2), 
								time / 1, 
								time / size, 
								time / (size / 2)};
		printf("%-12d %12.8f %15.7e %15.7e %15.7e\n", size, time, calc[x], calc[y], calc[z]);
	}
	ui_line('=', PRINT_WIDTH);
}
