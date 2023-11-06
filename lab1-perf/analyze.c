#include "analyze.h"
#include "algorithm.h"
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
    int start = 512;
    int arr[ARRAY_SIZE];
    for (int i = 0; i < 512; i++)
    {
        arr[i] = start;
        start--;
    }
    // Använd inte rakt av!

    // char *time_str = ctime(&mytime);
    // for(int i=0; i<n;i++){

    clock_t t;
    t = clock();

    bubble_sort(arr, strl);

    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("The program took %f seconds to execute", time_taken);

    // strl*=2;
    //}

    switch (a)
    {
    case 0:
        printf("Bubblesort\n");
        break;

    case 1:
        printf("Insertion\n");
        break;

    case 2:
        printf("Quick\n");
        break;

    case 3:
        printf("Linear\n");
        break;

    case 4:
        printf("Binary\n");
        break;

    default:
        break;
    }

    switch (a)
    {
    case 0:
        printf("Best\n");
        break;

    case 1:
        printf("Worst\n");
        break;

    case 2:
        printf("Average\n");
        break;

    default:
        break;
    }
}
