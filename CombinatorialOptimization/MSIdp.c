#include <stdio.h>

int maxSumInterval(int arr[], int size) {
    int maxEndingHere = arr[0];
    int maxSoFar = arr[0];

    for (int i = 1; i < size; ++i) {
        maxEndingHere = (maxEndingHere + arr[i] > arr[i]) ? maxEndingHere + arr[i] : arr[i];
        maxSoFar = (maxEndingHere > maxSoFar) ? maxEndingHere : maxSoFar;
    }

    return maxSoFar;
}

int main() {
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    int maxSum = maxSumInterval(arr, size);
    printf("Maximum sum of subarray: %d\n", maxSum);

    return 0;
}
