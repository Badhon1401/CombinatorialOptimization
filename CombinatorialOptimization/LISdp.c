#include <stdio.h>

int longestIncreasingSubsequence(int arr[], int size) {
    int lis[size]; // Array to store the length of LIS ending at each index
    int maxLIS = 1; // Initialize the maximum length of LIS as 1

    // Initialize LIS values for all indexes as 1
    for (int i = 0; i < size; ++i) {
        lis[i] = 1;
    }

    // Compute LIS values in bottom-up manner
    for (int i = 1; i < size; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
        // Update the maximum LIS length
        if (lis[i] > maxLIS) {
            maxLIS = lis[i];
        }
    }

    return maxLIS;
}

int main() {
    int arr[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    int size = sizeof(arr) / sizeof(arr[0]);

    int length = longestIncreasingSubsequence(arr, size);
    printf("Length of Longest Increasing Subsequence: %d\n", length);

    return 0;
}
