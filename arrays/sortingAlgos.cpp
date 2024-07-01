#include <bits/stdc++.h>
using namespace std;

// Bubble Sort
// Bubble Sort repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order.
// Time Complexity: 𝑂 ( 𝑛^2 ) in the worst and average cases, 𝑂 ( 𝑛 ) in the best case (when the array is already sorted).
// Space Complexity: 𝑂 ( 1 ) [in place sorting]
void bubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// Selection Sort
// Divide the array into two parts: sorted and unsorted. Find the minimum element in the unsorted part and swap it with the first element of the unsorted part.
// Time Complexity: 𝑂 ( 𝑛^2 ) in all cases.
// Space Complexity: 𝑂 ( 1 ) [in place sorting]
void selectionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Insertion Sort
// Divide the array into two parts: sorted and unsorted. Pick an element from the unsorted part and insert it into its correct position in the sorted part.
// Time Complexity: 𝑂 ( 𝑛^2 ) in the worst and average cases, 𝑂 ( 𝑛 ) in the best case (when the array is already sorted).
// Space Complexity: 𝑂 ( 1 ) [in place sorting]
void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort
// Divide the array into two halves, sort the two halves, and merge them.
// Time Complexity: 𝑂 ( 𝑛 log 𝑛 ) in all cases.
// Space Complexity: 𝑂 ( 𝑛 ) [additional space required]
void merge(vector<int> &arr, int l, int m, int r)
{
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

// Binary search
// Time Complexity: 𝑂 ( log 𝑛 ) in worst and avg cases.
// Space Complexity: 𝑂 ( 1 ) [additional space required]
int binarySearch(vector<int> &arr, int x)
{
    int l = 0, r = arr.size() - 1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (arr[m] == x)
            return m;
        if (arr[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}