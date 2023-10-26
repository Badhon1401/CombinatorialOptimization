#include <stdio.h>
#include <string.h>

void computeLPSArray(char pattern[], int patternLength, int lps[]) {
    int length = 0; // Length of the previous longest prefix suffix
    int i = 1;

    lps[0] = 0; // lps[0] is always 0

    while (i < patternLength) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(char text[], char pattern[]) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);
    int lps[patternLength]; // Longest prefix suffix values

    computeLPSArray(pattern, patternLength, lps);

    int i = 0; // Index for text[]
    int j = 0; // Index for pattern[]

    while (i < textLength) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == patternLength) {
            printf("Pattern found at index: %d\n", i - j);
            j = lps[j - 1];
        } else if (i < textLength && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";
    printf("Occurrences of the pattern:\n");
    KMPSearch(text, pattern);
    return 0;
}
