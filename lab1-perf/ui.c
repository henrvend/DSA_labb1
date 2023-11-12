#include "ui.h"
#include "io.h"
#include "analyze.h"
//
// Private
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
	char str[25];

	switch (c)
	{
	case 0:
		strcpy(str, "Best");
		break;
	case 1:
		strcpy(str, "Worst");
		break;
	case 2:
		strcpy(str, "Average");
		break;

	default:
		break;
	}

	switch (a)
	{
	case 0: // bubble
		ui_line('*', PRINT_WIDTH);
		printf("%40s %s\n", "Bubble sort: ", str);
		ui_line('=', PRINT_WIDTH);

		switch (c)
		{
		case 0:
			printf("\n%-12s %12s %15s %15s %15s\n", "Size", "time T(s)", "T/nlogn", "T/n", "T/nlog");
			ui_line('-', PRINT_WIDTH);
			for (int i = 0; i < n; i++)
			{
				float time = buf[i].time / 1000000000L;
				printf("%-12d %12.8f %15.7e %15.7e %15.7e\n", buf[i].size, time, (time / (buf[i].size * log(buf[i].size))), time / buf[i].size, (time / (log(buf[i].size))));
			}
			break;
		case 1:
			printf("\n%-12s %12s %15s %15s %15s\n", "Size", "time T(s)", "T/nlogn", "T/n^2", "T/n^3");
			ui_line('-', PRINT_WIDTH);
			for (int i = 0; i < n; i++)
			{
				float time = buf[i].time / 1000000000L;
				printf("%-12d %12.8f %15.7e %15.7e %15.7e\n", buf[i].size, time, (time / (buf[i].size * log(buf[i].size))), time / (buf[i].size*buf[i].size), (time / (buf[i].size*buf[i].size*buf[i].size)));
			}
			break;
		case 2:
			printf("\n%-12s %12s %15s %15s %15s\n", "Size", "time T(s)", "T/nlogn", "T/n", "T/nlog");
			ui_line('-', PRINT_WIDTH);
			for (int i = 0; i < n; i++)
			{
				float time = buf[i].time / 1000000000L;
				printf("%-12d %12.8f %15.7e %15.7e %15.7e\n", buf[i].size, time, (time / (buf[i].size * log(buf[i].size))), time / buf[i].size, (time / (log(buf[i].size))));
			}
			break;

		default:
			break;
		}

		break;
	case 1: // Insertion
		for (int i = 0; i < n; i++)
		{
			float time = buf[i].time / 1000000000L;
			printf("%-12d %12.8f %15.7e %15.7e %15.7e\n", buf[i].size, time, (time / (buf[i].size * log(buf[i].size))), time / buf[i].size, (time / (log(buf[i].size))));
		}
		break;
	case 2: // quick
		for (int i = 0; i < n; i++)
		{
			float time = buf[i].time / 1000000000L;
			printf("Storlek: %d, Tid: %f, T/nlogn: %f\n", buf[i].size, time, (buf[i].time / (buf[i].size * log(buf[i].size))));
		}
		break;
	case 3: // Linear
		for (int i = 0; i < n; i++)
		{
			float time = buf[i].time / 1000000000L;
			printf("Storlek: %d, Tid: %f, T/nlogn: %f\n", buf[i].size, time, (buf[i].time / (buf[i].size * log(buf[i].size))));
		}
		break;
	case 4: // Binary
		for (int i = 0; i < n; i++)
		{
			float time = buf[i].time / 1000000000L;
			printf("Storlek: %d, Tid: %f, T/nlogn: %f\n", buf[i].size, time, (buf[i].time / (buf[i].size * log(buf[i].size))));
		}
		break;
	default:
		break;
	}
}
