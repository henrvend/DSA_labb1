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
	char case_type[CASE_NAME];
	char array_type[ARRAY_NAME];

	switch (c)
	{
	case 0:
		strcpy(case_type, "Best");
		break;
	case 1:
		strcpy(case_type, "Worst");
		break;
	case 2:
		strcpy(case_type, "Average");
		break;

	default:
		break;
	}

	switch (a)
	{
	case 0: // bubble
		strcpy(array_type, "Bubble sort: ");
		print_array_sort(buf, n, c, case_type, array_type);
		break;

	case 1: // Insertion
		strcpy(array_type, "Insertion: ");
		print_array_sort(buf, n, c, case_type, array_type);
		break;
	case 2: // quick
		for (int i = 0; i < n; i++)
		{
			double time = buf[i].time / BILLION;
			printf("Storlek: %d, Tid: %f, T/nlogn: %f\n", buf[i].size, time, (buf[i].time / (buf[i].size * log(buf[i].size))));
		}
		break;
	case 3: // Linear
		strcpy(array_type, "Linear: ");
		print_array_search(buf, n, c, case_type, array_type);
		break;
	case 4: // Binary
		strcpy(array_type, "Binary: ");
		print_array_search(buf, n, c, case_type, array_type);
		break;
	default:
		break;
	}
}

void print_array_sort(result_t *buf, int n, case_t c, char *str, char *name)
{
	ui_line('*', PRINT_WIDTH);
	printf("%40s %s\n", name, str);
	ui_line('=', PRINT_WIDTH);

	switch (c)
	{
	case 0:
		printf("\n%-12s %12s %15s %15s %15s\n", "Size", "time T(s)", "T/nlogn", "T/n", "T/nlog");
		ui_line('-', PRINT_WIDTH);
		for (int i = 0; i < n; i++)
		{
			double time = buf[i].time / BILLION;
			int size = buf[i].size;
			printf("%-12d %12.8f %15.7e %15.7e %15.7e\n", size, time, (time / (size * log(size))), time / size, (time / (log(size))));
		}
		break;
	case 1:
		printf("\n%-12s %12s %15s %15s %15s\n", "Size", "time T(s)", "T/nlogn", "T/n^2", "T/n^3");
		ui_line('-', PRINT_WIDTH);
		for (int i = 0; i < n; i++)
		{
			double time = buf[i].time / BILLION;
			int size = buf[i].size;
			printf("%-12d %12.8f %15.7e %15.7e %15.7e\n", size, time, (time / (size * log(size))), time / (size * size), (time / (size * size * size)));
		}
		break;
	case 2:
		printf("\n%-12s %12s %15s %15s %15s\n", "Size", "time T(s)", "T/nlogn", "T/n^2", "T/2n");
		ui_line('-', PRINT_WIDTH);
		for (int i = 0; i < n; i++)
		{
			double time = buf[i].time / BILLION;
			int size = buf[i].size;
			printf("%-12d %12.8f %15.7e %15.7e %15.7e\n", size, time, (time / (size * log(size))), time / (size * size), time / (size * 2));
		}
		break;

	default:
		break;
	}
	ui_line('=', PRINT_WIDTH);
}

void print_array_search(result_t *buf, int n, case_t c, char *str, char *name)
{
	ui_line('*', PRINT_WIDTH);
	printf("%40s %s\n", name, str);
	ui_line('=', PRINT_WIDTH);

	switch (c)
	{
	case 0:
		printf("\n%-12s %12s %15s %15s %15s\n", "Size", "time T(s)", "T/1", "T/n", "T/(n/2)");
		ui_line('-', PRINT_WIDTH);
		for (int i = 0; i < n; i++)
		{
			double time = buf[i].time / BILLION;
			int size = buf[i].size;
			printf("%-12d %12.8f %15.7e %15.7e %15.7e\n", size, time, time / 1, time / size, (time / (size / 2)));
		}
		break;
	case 1:
		printf("\n%-12s %12s %15s %15s %15s\n", "Size", "time T(s)", "T/logn", "T/n", "T/1");
		ui_line('-', PRINT_WIDTH);
		for (int i = 0; i < n; i++)
		{
			double time = buf[i].time / BILLION;
			int size = buf[i].size;
			printf("%-12d %12.8f %15.7e %15.7e %15.7e\n", size, time, (time / (log(size))), time / size, (time / 1));
		}
		break;
	case 2:
		printf("\n%-12s %12s %15s %15s %15s\n", "Size", "time T(s)", "T/logn", "T/n", "T/(n/2)");
		ui_line('-', PRINT_WIDTH);
		for (int i = 0; i < n; i++)
		{
			double time = buf[i].time / BILLION;
			int size = buf[i].size;
			printf("%-12d %12.8f %15.7e %15.7e %15.7e\n", size, time, (time / (log(size))), time / size, time / (size / 2));
		}
		break;

	default:
		break;
	}
	ui_line('=', PRINT_WIDTH);
}

/*void print(result_t *buf, case_t c, int one, int two, int three)
{

	ui_line('*', PRINT_WIDTH);
	printf("%40s %s\n", c, str);
	ui_line('=', PRINT_WIDTH);

	char arr[3][7];
	arr[0][one];
	char text1[7];
	strcpy(text1, arr[0][one]);

	printf("spacing", "Size", "time T(s)", text1, text2, text3);


	printf("\n%-12s %12s %15s %15s %15s\n", "Size", "time T(s)", "T/nlogn = 1 ", "T/logn = 2", "T/n^2 = 3 ", "T/n^3 = 4 ", "T/2n = 5 ", "T/1 = 6", "T/n = 7 ", "T/(n/2) = 8 ");
}*/