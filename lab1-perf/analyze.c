#include "analyze.h"
#include "algorithm.h"
#include "ui.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

//
// Private
//

//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n)
{
    int strl = SIZE_START;

    int arr[16500];

    for (int i = 0; i < n; i++)
    {
        int start = strl;

        for (int j = 0; j < strl; j++)
        {
            arr[j] = start;
            start--;
        }
        struct timespec start_time, end_time;

        // clock_t t;
        // t = clock();

        switch (a)
        {
        case 0: // Bubble

            switch (c)
            {
            case 0:
                orderd_array(arr, strl);
                break;
            case 1:
                reverse_array(arr, strl);
                break;
            case 2:
                random_array(arr, strl);
                break;
            default:
                break;
            }
            //Bättra hantering för nanosekunder behövs, just nu hanteras endast nano.
            clock_gettime(CLOCK_REALTIME, &start_time);
            bubble_sort(arr, strl);
            clock_gettime(CLOCK_REALTIME, &end_time);
            // t = clock() - t;
            break;

        case 1: // Insertion
            switch (c)
            {
            case 0:
                orderd_array(arr, strl);
                break;
            case 1:
                reverse_array(arr, strl);
                break;
            case 2:
                random_array(arr, strl);
                break;
            default:
                break;
            }
            //t = clock();
            for (int k = 0; k < 10; k++)
            {
                insertion_sort(arr, strl);
            }
            //t = clock() - t;
            break;

        case 2: // Quick
            switch (c)
            {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            default:
                break;
            }
            break;

        case 3: // Linear
            printf("Linear\n");
            switch (c)
            {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            default:
                break;
            }
            break;

        case 4: // Binary
            printf("Binary\n");
            switch (c)
            {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            default:
                break;
            }
            break;

        default:
            break;
        }

        //double time_taken = ((double)t) / CLOCKS_PER_SEC;
        buf[i].size = strl;
        //buf[i].time = time_taken;
        buf[i].time = end_time.tv_nsec - start_time.tv_nsec;

        strl *= 2;
    }

    print_results(buf, n);
}

void orderd_array(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }
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
    {
        int random_value;
        int exists = 1;
        do
        {
            random_value = rand() % (n - 0 + 1) + 0;
            exists = 1;

            for (int j = 0; j < i; j++)
            {
                if (arr[j] == random_value)
                {
                    break;
                }
                exists = 0;
            }
        } while (exists);

        arr[i] = random_value;
        printf("%d ", random_value);
    }
}