#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int weights[], int values[], int totalWeight, int n) {
    int dp[n + 1][totalWeight + 1];

    // Initialize the dp table
    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= totalWeight; ++w) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][totalWeight];
}

int main() {
    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    int totalWeight = 5;
    int n = sizeof(weights) / sizeof(weights[0]);

    int maxValue = knapsack(weights, values, totalWeight, n);
    printf("Maximum value in 0/1 Knapsack: %d\n", maxValue);

    return 0;
}
