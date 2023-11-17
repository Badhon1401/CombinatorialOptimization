#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int weights[], int values[], int totalWeight, int n, int selected[]) {
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

    // Backtrack to find the selected items
    int i = n, w = totalWeight;
    while (i > 0 && w > 0) {
        if (dp[i][w] != dp[i - 1][w]) {
            // The item is included in the knapsack
            selected[i - 1] = 1;
            w -= weights[i - 1];
        }
        i--;
    }

    return dp[n][totalWeight];
}

int main() {
    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    int totalWeight = 5;
    int n = sizeof(weights) / sizeof(weights[0]);

    int selected[n];
    for (int i = 0; i < n; ++i) {
        selected[i] = 0;  // Initialize selected array
    }

    int maxValue = knapsack(weights, values, totalWeight, n, selected);

    printf("Maximum value in 0/1 Knapsack: %d\n", maxValue);
    printf("Objects to Pick: ");
    
    for (int i = 0; i < n; ++i) {
        if (selected[i]) {
            printf("Item %d ", i + 1);
        }
    }
    printf("\n");

    return 0;
}
