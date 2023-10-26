#include <stdio.h>

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve rod cutting problem using dynamic programming
int rodCutting(int price[], int n) {
    int dp[n + 1]; // dp[i] stores the maximum value that can be obtained from rod of length i

    dp[0] = 0; // Base case

    // Build the dp table in a bottom-up manner
    for (int i = 1; i <= n; ++i) {
        int maxVal = -1;
        for (int j = 1; j <= i; ++j) {
            maxVal = max(maxVal, price[j] + dp[i - j]);
        }
        dp[i] = maxVal;
    }

    return dp[n];
}

int main() {
    int price[] = {0, 1, 5, 8, 9, 10, 17, 17, 20}; // Price array where price[i] is the price of rod of length i
    int n = sizeof(price) / sizeof(price[0]) - 1; // Length of the rod

    int maxRevenue = rodCutting(price, n);
    printf("Maximum revenue obtained: %d\n", maxRevenue);
    
    return 0;
}
