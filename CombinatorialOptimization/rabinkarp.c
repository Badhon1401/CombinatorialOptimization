#include <stdio.h>
#include <string.h>

#define PRIME 101

int rabinKarp(char text[], char pattern[]) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);
    int patternHash = 0, textHash = 0;
    int h = 1;

    // Calculate the hash value for the pattern and initial window in the text
    for (int i = 0; i < patternLength - 1; i++) {
        h = (h * 256) % PRIME;
    }
    for (int i = 0; i < patternLength; i++) {
        patternHash = (256 * patternHash + pattern[i]) % PRIME;
        textHash = (256 * textHash + text[i]) % PRIME;
    }

    // Slide the pattern over the text one by one
    for (int i = 0; i <= textLength - patternLength; i++) {
        // Check the hash values of the current window of text and pattern
        if (patternHash == textHash) {
            int j;
            // Check character by character
            for (j = 0; j < patternLength; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == patternLength) {
                return i; // Pattern found starting from index i in the text
            }
        }
        // Calculate hash value for next window in the text
        if (i < textLength - patternLength) {
            textHash = (256 * (textHash - text[i] * h) + text[i + patternLength]) % PRIME;
            if (textHash < 0) {
                textHash += PRIME;
            }
        }
    }
    return -1; // Pattern not found in the text
}

int main() {
    char text[] = "ABABCABABCD";
    char pattern[] = "ABAB";
    int result = rabinKarp(text, pattern);
    if (result != -1) {
        printf("Pattern found at index: %d\n", result);
    } else {
        printf("Pattern not found in the text.\n");
    }
    return 0;
}
