#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

void swap(int arr[], int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void Sort2Way(int arr[], int left, int right)
{
	int pivot, i, j;
	int temp;
	if(left < right)
	{
		i = left;
		j = right + 1;
		pivot = arr[left];
		do
		{
			do{ i++; }while(arr[i] < pivot);
			do{ j--; }while(arr[j] > pivot);
			if(i < j) swap(arr, i, j);
		}while(i < j);
		swap(arr ,left, j);
		Sort2Way(arr, left, j - 1);
		Sort2Way(arr, j + 1, right);
	}
}

void Sort3Way(int arr[], int l, int r)
{
	if (r <= l) return;
	int i = l - 1, j = r;
	int p = l - 1, q = r;
	while (1)
	{
		while (arr[++i] < arr[r]);
		while (arr[r] < arr[--j]) if (j == l) break;
		if (i >= j) break;
		swap(arr, i, j);
		if (arr[i] == arr[r]) swap(arr, ++p, i);
		if (arr[j] == arr[r]) swap(arr, --q, j);
	}
	swap(arr, i, r);
	j = i - 1;
	i = i + 1;
	for (int k = l; k <= p; k++) swap(arr, k, j--);
	for (int k = r - 1; k >= q; k--) swap(arr, k, i++);
	Sort3Way(arr, l, j);
	Sort3Way(arr, i, r);
}

void CreateArray(int *array, int n, int a, int b)
{
	for (int i = 0; i < n; i++)
	{
		array[i] = a + rand() % (b - 1 + a);
	}
}

void main()
{
	int *array;
	array = (int*) malloc (1000 * sizeof(int));
	memset(array, 0, 1000);
	
	int *array2;
	array2 = (int*) malloc (1000 * sizeof(int));
	memset(array2, 0, 1000);
	
	CreateArray(array, 20, 1, 10);
    printf("array1: ");
	for (int i = 0; i < 20; i++)
	{
		printf(" %d ", array[i]);
	}
	memcpy(array2,array, 20*sizeof(int));
    
    Sort3Way(array, 0, 19);
	printf("\nAfter 3-way partitioning sort:\n");
	for (int i = 0; i < 20; i++)
	{
		printf(" %d ", array[i]);
	}
	
	Sort2Way(array2, 0, 19);
	printf("\nAfter 2-way partitioning sort:\n");
	for (int i = 0; i < 20; i++)
	{
		printf(" %d ", array2[i]);
	}

	
	printf("\n");

	free(array);
	free(array2);
}
