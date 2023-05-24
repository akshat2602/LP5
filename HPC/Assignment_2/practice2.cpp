#include <iostream>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;

void sequential_bubble_sort(int arr[], int size)
{
    int array[size];
    for (int i = 0; i < size; i++)
    {
        array[i] = arr[i];
    }
    double start = omp_get_wtime();
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                swap(array[j], array[j + 1]);
            }
        }
    }
    double end = omp_get_wtime();
    cout << "Sequential Bubble Sort: ";
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "Time required: " << end - start << endl;
}

void parallel_bubble_sort(int arr[], int size)
{
    int array[size];
    for (int i = 0; i < size; i++)
    {
        array[i] = arr[i];
    }
    double start = omp_get_wtime();

#pragma omp parallel for
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                swap(array[j], array[j + 1]);
            }
        }
    }
    double end = omp_get_wtime();
    cout << "Parallel Bubble Sort:\n";
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "Time Required: " << end - start << endl;
}

void merge(int array[], int low, int mid, int high, int size)
{
    int temp[size];
    int left = low;
    int right = mid + 1;
    int k = 0;

    while ((left < mid + 1) && (right < high + 1))
    {
        if (array[left] >= array[right])
        {
            temp[k] = array[right];
            right++;
            k++;
        }
        else
        {
            temp[k] = array[left];
            left++;
            k++;
        }
    }

    while (left < mid + 1)
    {
        temp[k] = array[left];
        left++;
        k++;
    }

    while (right < high + 1)
    {
        temp[k] = array[right];
        right++;
        k++;
    }

    k = 0;
    for (int i = low; i < high + 1; i++)
    {
        array[i] = temp[k];
        k++;
    }
}

void mergesort(int array[], int low, int high, int size)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergesort(array, low, mid, size);
        mergesort(array, mid + 1, high, size);
        merge(array, low, mid, high, size);
    }
}

void perform_merge_sort(int arr[], int size)
{
    int array[size];
    for (int i = 0; i < size; i++)
    {
        array[i] = arr[i];
    }
    double start = omp_get_wtime();
    mergesort(array, 0, size - 1, size);
    double end = omp_get_wtime();
    cout << "Merge Sort:\n";
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "Time Required: " << end - start << endl;
}

void p_mergesort(int array[], int low, int high, int size)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            p_mergesort(array, low, mid, size);
#pragma omp section
            p_mergesort(array, mid + 1, high, size);
        }
        merge(array, low, mid, high, size);
    }
}

void perform_p_merge_sort(int arr[], int size)
{
    int array[size];
    for (int i = 0; i < size; i++)
    {
        array[i] = arr[i];
    }
    double start = omp_get_wtime();
    p_mergesort(array, 0, size - 1, size);
    double end = omp_get_wtime();
    cout << "Parallel Merge Sort:\n";
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "Time Required: " << end - start << endl;
}

int main(int argc, char const *argv[])
{
    int SIZE;
    int MAX = 1000;
    cout << "Enter size of array: ";
    cin >> SIZE;
    int array[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % MAX;
    }
    cout << endl;
    sequential_bubble_sort(array, SIZE);
    parallel_bubble_sort(array, SIZE);
    perform_merge_sort(array, SIZE);
    perform_p_merge_sort(array, SIZE);
    return 0;
}