#include <stdio.h>

// Structure to represent an item
struct Item {
    int weight, value;
};

// Function to swap two items
void swap(struct Item *a, struct Item *b) {
    struct Item temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the items based on value per unit weight using quicksort algorithm
int partition(struct Item items[], int low, int high) {
    double pivot = (double)items[high].value / items[high].weight;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        double ratio = (double)items[j].value / items[j].weight;
        if (ratio >= pivot) {
            i++;
            swap(&items[i], &items[j]);
        }
    }
    swap(&items[i + 1], &items[high]);
    return i + 1;
}

// Function to perform quicksort on items based on value per unit weight
void quicksort(struct Item items[], int low, int high) {
    if (low < high) {
        int pi = partition(items, low, high);
        quicksort(items, low, pi - 1);
        quicksort(items, pi + 1, high);
    }
}

// Function to solve fractional knapsack problem
void fractionalKnapsack(struct Item items[], int n, int capacity) {
    // Sort items based on value per unit weight using quicksort
    quicksort(items, 0, n - 1);

    int currentWeight = 0; // Current weight in knapsack
    double totalValue = 0.0; // Total value in knapsack

    // Fill the knapsack greedily
    for (int i = 0; i < n; i++) {
        // If adding the next item doesn't exceed the capacity, add it completely
        if (currentWeight + items[i].weight <= capacity) {
            currentWeight += items[i].weight;
            totalValue += items[i].value;
        } else {
            // If adding the next item exceeds the capacity, add a fraction of it
            int remainingCapacity = capacity - currentWeight;
            totalValue += items[i].value * ((double)remainingCapacity / items[i].weight);
            break; // Knapsack is full, so exit the loop
        }
    }

    printf("Maximum value in knapsack = %.2lf\n", totalValue);
}

int main() {
    // Example items
    struct Item items[] = {{10, 60}, {20, 100}, {30, 120}};
    int n = sizeof(items) / sizeof(items[0]);
    int capacity = 50; // Capacity of the knapsack

    // Solve fractional knapsack problem
    fractionalKnapsack(items, n, capacity);

    return 0;
}
