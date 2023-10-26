#include <stdio.h>
#include <string.h>

// Function to find the length of Longest Common Subsequence and print the LCS
void longestCommonSubsequence(char X[], char Y[]) {
    int m = strlen(X);
    int n = strlen(Y);

    int dp[m + 1][n + 1];

    // Initialize the dp table
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
        }
    }

    // Length of LCS is dp[m][n]
    int length = dp[m][n];
    printf("Length of Longest Common Subsequence: %d\n", length);

    // Construct and print the Longest Common Subsequence
    char lcs[length + 1];
    lcs[length] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[length - 1] = X[i - 1];
            i--;
            j--;
            length--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("Longest Common Subsequence: %s\n", lcs);
}

int main() {
    char X[] = "AGGTA";
    char Y[] = "GXTXAYB";

    longestCommonSubsequence(X, Y);

    return 0;
}