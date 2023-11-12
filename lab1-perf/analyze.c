#include "analyze.h"
#include "algorithm.h"
#include "ui.h"
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
    int v;
    for (int i = 0; i < n; i++)
    {
        struct timespec start_time, end_time;

        switch (a)
        {
        case 0: // Bubble
            getArray(arr, c, strl);
            // Bättra hantering för nanosekunder behövs, just nu hanteras endast nano.
            clock_gettime(CLOCK_REALTIME, &start_time);
            bubble_sort(arr, strl);
            clock_gettime(CLOCK_REALTIME, &end_time);
            break;

        case 1: // Insertion
            getArray(arr, c, strl);
            clock_gettime(CLOCK_REALTIME, &start_time);
            insertion_sort(arr, strl);
            clock_gettime(CLOCK_REALTIME, &end_time);
            break;

        case 2: // Quick
            getArray(arr, c, strl);
            clock_gettime(CLOCK_REALTIME, &start_time);
            quick_sort(arr, strl);
            clock_gettime(CLOCK_REALTIME, &end_time);
            break;

        case 3: // Linear
            v = 0;
            getArray(arr, c, strl);
            clock_gettime(CLOCK_REALTIME, &start_time);
            linear_search(arr, strl, v);
            clock_gettime(CLOCK_REALTIME, &end_time);
            break;

        case 4: // Binary
            v = 0;
            getArray(arr, c, strl);
            clock_gettime(CLOCK_REALTIME, &start_time);
            binary_search(arr, strl, v);
            clock_gettime(CLOCK_REALTIME, &end_time);
        default:
            break;
        }

        buf[i].size = strl;
        buf[i].time = end_time.tv_nsec - start_time.tv_nsec;
        strl *= 2;
    }


    /*Switch for printing right sort/search sequence*/
    print_results(buf, n, a, c);
    

}

/*--------------Array handling-----------------*/
/*---------------------------------------------*/

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
        arr[i] = i;
    }

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