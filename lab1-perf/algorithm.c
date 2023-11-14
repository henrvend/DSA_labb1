#include "algorithm.h"

//
// Private
//

/*Quicksort starts here*/
void quickSort(int *a, int low, int high)
{
	if (low < high)
	{
		int p = partition(a, low, high);
		quickSort(a, low, p - 1);
		quickSort(a, p + 1, high);
	}
}

int partition(int a[], int low, int high)
{
	int index = low;
	int pivot = a[high];
	int i;
	for (i = low; i < high; i++)
	{
		if (a[i] < pivot)
		{
			swap(&a[i], &a[index]);
			index++;
		}
	}
	swap(&a[high], &a[index]);
	return index;
}

void swap(int *x, int *y)
{
	int t = *x;
	*x = *y;
	*y = t;
}
/*Quicksort ends here*/

//
// Public
//
void bubble_sort(int *a, int n)
{
	bool swapped = true;
	for (int i = 0; i < n - 1 && swapped; i++)
	{
		swapped = false;
		for (int j = 0; j < n - i - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				swapped = true;
			}
		}
	}
}

void insertion_sort(int *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		int key = a[i];
		int j = i - 1;

		while (j >= 0 && a[j] > key)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}

/* Quick sort starts here*/
void quick_sort(int *a, int n)
{
	quickSort(a, 0, n - 1);

	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

/*Quick sort ends here*/
bool linear_search(const int *a, int n, int v)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i] == v)
			return true;
	}
	return false; // TODO: linear search
}

bool binary_search(const int *a, int n, int v)
{
	int left = 0, right = (n - 1);

	while (left <= right)
	{
		int mid = left + (right - left) / 2;

		if (a[mid] == v)
		{
			return mid;
		}
		if (a[mid] < v)
		{
			left = mid + 1;
		}
		else
			right = mid - 1;
	}

	return false;
}
