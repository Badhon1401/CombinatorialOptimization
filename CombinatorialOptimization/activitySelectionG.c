#include <stdio.h>

// Structure to represent an activity
struct Activity {
    int start, finish;
};

// Function to swap two activities
void swap(struct Activity *a, struct Activity *b) {
    struct Activity temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform a bubble sort on activities based on finish time
void bubbleSort(struct Activity activities[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (activities[j].finish > activities[j + 1].finish) {
                swap(&activities[j], &activities[j + 1]);
            }
        }
    }
}

// Function to print selected activities
void printActivities(struct Activity activities[], int n) {
    printf("Selected activities:\n");

    // The first activity is always selected
    int i = 0;
    printf("(%d, %d) ", activities[i].start, activities[i].finish);

    // Consider the rest of the activities
    for (int j = 1; j < n; j++) {
        // If this activity has a start time greater than or equal to the finish
        // time of the previously selected activity, then select it
        if (activities[j].start >= activities[i].finish) {
            printf("(%d, %d) ", activities[j].start, activities[j].finish);
            i = j;
        }
    }
}

int main() {
    // Example activities
    struct Activity activities[] = {{1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}, {5, 9}};
    int n = sizeof(activities) / sizeof(activities[0]);

    // Sort activities based on finish time using bubble sort
    bubbleSort(activities, n);

    // Print the selected activities
    printActivities(activities, n);

    return 0;
}
