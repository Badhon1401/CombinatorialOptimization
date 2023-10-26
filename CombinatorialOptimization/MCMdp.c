#include <stdio.h>
#include <limits.h>

void printOptimalParens(int s[], int i, int j, int n) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParens(s, i, *((s + i * n) + j), n);
        printOptimalParens(s, *((s + i * n) + j) + 1, j, n);
        printf(")");
    }
}

void matrixChainMultiplication(int p[], int n) {
    int m[n][n]; // Minimum cost matrix
    int s[n][n]; // Parenthesis split index matrix

    // Initialize m[i][i] to 0 as single matrix has no multiplication cost
    for (int i = 1; i <= n; ++i) {
        m[i][i] = 0;
    }

    // Calculate minimum cost and optimal split indices
    for (int l = 2; l <= n; ++l) {
        for (int i = 1; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; ++k) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    // Print optimal parentheses and minimum cost
    printf("Optimal Parentheses: ");
    printOptimalParens((int *)s, 1, n, n);
    printf("\n");
    printf("Minimum Cost: %d\n", m[1][n]);
}

int main() {
    int p[] = {30, 35, 15, 5, 10, 20, 25}; // Matrix dimensions: [30x35, 35x15, 15x5, 5x10, 10x20, 20x25]
    int n = sizeof(p) / sizeof(p[0]) - 1; // Number of matrices

    matrixChainMultiplication(p, n);

    return 0;
}
