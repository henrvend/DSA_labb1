#include "analyze.h"
#include "algorithm.h"
#include "ui.h"
//
// Private
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n)
{
    int strl = ARRAY_SIZE;

    int arr[MAX_SIZE];
    int v;
    for (int i = 0; i < n; i++)
    {
        struct timespec start_time, end_time;
        int loop_numbers;

        getArray(arr, c, strl);
        v = get_v(arr, c, a, strl);
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        switch (a)
        {
        case 0: // Bubble
            loop_numbers = SORT_LOOP;
            for (int j = 0; j < loop_numbers; j++)
                bubble_sort(arr, strl);
            break;

        case 1: // Insertion
            loop_numbers = SORT_LOOP;
            for (int j = 0; j < loop_numbers; j++)
                insertion_sort(arr, strl);
            break;

        case 2: // Quick
            loop_numbers = SORT_LOOP;
            for (int j = 0; j < loop_numbers; j++)
                quick_sort(arr, strl);
            break;

        case 3: // Linear
            loop_numbers = SEARCH_LOOP;
            for (int j = 0; j < loop_numbers; j++)
                linear_search(arr, strl, v);
            break;

        case 4: // Binary
            loop_numbers = SEARCH_LOOP;
            for (int j = 0; j < loop_numbers; j++)
                binary_search(arr, strl, v);
        default:
            break;
        }
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        /*Calculate time*/
        double time_dif = ((end_time.tv_sec * BILLION) + end_time.tv_nsec) - ((start_time.tv_sec * BILLION) + start_time.tv_nsec);

        /*Lägger till värden i buf* för att skicka med till print-funktionen*/
        buf[i].size = strl;
        buf[i].time = (time_dif / loop_numbers) / BILLION;

        strl *= TIMES_TWO;
    }

    /*Switch for printing right sort/search sequence in ui.c*/
    print_results(buf, n, a, c);
}

/*--------------Array handling-----------------*/
/*---------------------------------------------*/

void orderd_array(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i;
}

void reverse_array(int *arr, int n)
{
    int j = 0;
    for (int i = n; i > 0; i--)
    {
        arr[j] = i;
        j++;
    }
}

void random_array(int *arr, int n)
{
    srand(time(NULL));

    for (int i = 0; i < n; i++)
        arr[i] = i;

    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

/*Get right array for the job*/
void getArray(int *arr, int c, int strl)
{
    switch (c)
    {
    case 0: // best
        orderd_array(arr, strl);
        break;
    case 1: // worst
        reverse_array(arr, strl);
        break;
    case 2: // average
        random_array(arr, strl);
        break;
    default:
        break;
    }
}

/*Get right variable for the case*/
int get_v(int *arr, case_t c, algorithm_t a, int n)
{
    switch (c)
    {
    case 0:
        return (a == 3) ? arr[0] : arr[n / 2];
        break;
    case 1:
        return (a == 3) ? arr[n - 1] : arr[0];
        break;
    case 2:
        return (a == 3) ? arr[n / 2] : arr[0];
        break;
    default:
        break;
    }
    return 0;
}