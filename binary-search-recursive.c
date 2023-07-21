#include <stdio.h>

int binSearch(int arr[], int left, int right, int key) 
{
    while (right >= left) 
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key)
            return mid;

        if (arr[mid] > key)
            return binarySearch(arr, left, mid - 1, key);
        
        return binarySearch(arr, mid + 1, right, key);
    }
    return -1;
}

int main() 
{
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &arr[i]);
    }

    int key;
    printf("Enter the key to search: ");
    scanf("%d", &key);

    int result = binarySearch(arr, 0, n - 1, key);

    if (result == -1) 
        printf("Element is not present in the array\n");
    else
        printf("Element is present at index %d\n", result);

    return 0;
}