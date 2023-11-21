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
        double time_dif = 0;

        // getArray(arr, c, strl);
        v = get_v(arr, c, a, strl);
        //clock_gettime(CLOCK_MONOTONIC, &start_time);

        switch (a)
        {
        case bubble_sort_t: // Bubble
            loop_numbers = SORT_LOOP;
            for (int j = 0; j < loop_numbers; j++)
            {
                getArray(arr, c, strl);
                clock_gettime(CLOCK_MONOTONIC, &start_time);
                bubble_sort(arr, strl);
                clock_gettime(CLOCK_MONOTONIC, &end_time);
                time_dif += ((end_time.tv_sec * BILLION) + end_time.tv_nsec) - ((start_time.tv_sec * BILLION) + start_time.tv_nsec);
            }
            break;

        case insertion_sort_t: // Insertion
            loop_numbers = SORT_LOOP;
            for (int j = 0; j < loop_numbers; j++)
            {
                getArray(arr, c, strl);
                clock_gettime(CLOCK_MONOTONIC, &start_time);
                insertion_sort(arr, strl);
                clock_gettime(CLOCK_MONOTONIC, &end_time);
                time_dif += ((end_time.tv_sec * BILLION) + end_time.tv_nsec) - ((start_time.tv_sec * BILLION) + start_time.tv_nsec);
            }

            break;

        case quick_sort_t: // Quick
            loop_numbers = SORT_LOOP;
            for (int j = 0; j < loop_numbers; j++)
            {
                if (c == 1)
                {
                    zeroArray(arr, strl);
                }
                else
                {
                    getArray(arr, c, strl);
                }

                clock_gettime(CLOCK_MONOTONIC, &start_time);
                quick_sort(arr, strl);
                clock_gettime(CLOCK_MONOTONIC, &end_time);
                time_dif += ((end_time.tv_sec * BILLION) + end_time.tv_nsec) - ((start_time.tv_sec * BILLION) + start_time.tv_nsec);
            }
            break;

        case linear_search_t: // Linear
            loop_numbers = SEARCH_LOOP;
            for (int j = 0; j < loop_numbers; j++)
            {
                clock_gettime(CLOCK_MONOTONIC, &start_time);
                linear_search(arr, strl, v);
                clock_gettime(CLOCK_MONOTONIC, &end_time);
                time_dif += ((end_time.tv_sec * BILLION) + end_time.tv_nsec) - ((start_time.tv_sec * BILLION) + start_time.tv_nsec);
            }

            break;

        case binary_search_t: // Binary
            loop_numbers = SEARCH_LOOP;
            for (int j = 0; j < loop_numbers; j++)
            {
                clock_gettime(CLOCK_MONOTONIC, &start_time);
                binary_search(arr, strl, v);
                clock_gettime(CLOCK_MONOTONIC, &end_time);
                time_dif += ((end_time.tv_sec * BILLION) + end_time.tv_nsec) - ((start_time.tv_sec * BILLION) + start_time.tv_nsec);
            }
        default:
            break;
        }
        /*Lägger till värden i buf* för att skicka med till print-funktionen*/
        buf[i].size = strl;
        buf[i].time = (time_dif / loop_numbers) / BILLION;
        /*for (int q = 0; q < strl; q++)
        {
            printf("%d ", arr[q]);
        }*/
        printf("\n");
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
    case best_t: // best
        orderd_array(arr, strl);
        break;
    case worst_t: // worst
        reverse_array(arr, strl);
        break;
    case average_t: // average
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
    case best_t: // Best
        return (a == 3) ? arr[0] : arr[n / 2];
        break;
    case worst_t: // Worst
        return (a == 3) ? 1 : arr[0];
        break;
    case average_t: // Avarage
        return (a == 3) ? arr[n / 2] : arr[0];
        break;
    default:
        break;
    }
    return 0;
}

void zeroArray(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = 0;
}
