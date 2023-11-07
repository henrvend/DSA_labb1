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
    
    int arr[20000];
   
    
    
    for(int i=0; i<n;i++){
        
        int start = strl;
        
        for (int i = 0; i < strl; i++)
        {
            arr[i] = start;
            start--;
        }
        clock_t t;
        t = clock();
        
        switch (a)
        {
            case 0:
                printf("\nBubblesort\n");
                bubble_sort(arr, strl);
            break;

            case 1:
                printf("\nInsertion\n");
                insertion_sort(arr, strl);
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
        

        t = clock() - t;
        
        double time_taken = ((double)t) / CLOCKS_PER_SEC;
        
        
        
        printf("The program took %f seconds to execute while %d long\n", time_taken, strl);

        strl*=2;
    }

    

    switch (c)
    {
    case 0:
        printf("\nBest\n");
        break;

    case 1:
        printf("\nWorst\n");
        break;

    case 2:
        printf("\nAverage\n");
        break;

    default:
        break;
    }
}
