#include "algorithm.h"

//
// Private
//

//
// Public
//
void bubble_sort(int *a, int n)
{
	bool swapped=true;
	for(int i=0; i<n-1 && swapped; i++){
		swapped=false;
		for(int j=0; j<n-i-1; j++){
			if(a[j]>a[j+1]){
				int temp=a[j];
				a[j] = a[j+1];
				a[j+1]=temp;
				swapped=true;
			}
		}
	}

}

void insertion_sort(int *a, int n)
{
    for(int i=0; i<n; i++){
        int key=a[i];
        int j= i-1;
        
        while (j >= 0 && a[j]>key) {
            a[j+1]= a[j];
            j=j-1;
        }
        a[j+1]=key;
    }
}

void quick_sort(int *a, int n)
{
	// TODO: quick sort
}

bool linear_search(const int *a, int n, int v)
{
	return false; // TODO: linear search
}

bool binary_search(const int *a, int n, int v)
{
	return false; // TODO: binary search
}
