#include <stdio.h>
#include<stdlib.h>

// Structure to represent a node in Huffman tree
struct Node {
    char data;
    int frequency;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(char data, int frequency) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node) {
        node->data = data;
        node->frequency = frequency;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

// Function to build Huffman tree using a greedy approach
struct Node* buildHuffmanTree(char data[], int frequency[], int size) {
    // Array to store nodes
    struct Node* nodes[size];
    
    // Create initial nodes for characters
    for (int i = 0; i < size; ++i) {
        nodes[i] = newNode(data[i], frequency[i]);
    }

    while (size > 1) {
        int min1 = 0, min2 = 1;
        if (nodes[min1]->frequency > nodes[min2]->frequency) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for (int i = 2; i < size; ++i) {
            if (nodes[i]->frequency < nodes[min1]->frequency) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->frequency < nodes[min2]->frequency) {
                min2 = i;
            }
        }

        // Create a new internal node with merged frequencies
        struct Node* internalNode = newNode('$', nodes[min1]->frequency + nodes[min2]->frequency);
        internalNode->left = nodes[min1];
        internalNode->right = nodes[min2];

        // Remove the used nodes and add the internal node
        nodes[min1] = internalNode;
        // Swap nodes[min2] with the last node and decrease size
        struct Node* temp = nodes[min2];
        nodes[min2] = nodes[size - 1];
        nodes[size - 1] = temp;

        // Decrease the size of nodes array
        size--;
    }

    return nodes[0];
}

// Function to print Huffman codes from the Huffman tree
void printCodes(struct Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (root->left == NULL && root->right == NULL) {
        printf("'%c': ", root->data);
        for (int i = 0; i < top; ++i) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

int main() {
    char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int frequency[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(data) / sizeof(data[0]);

    struct Node* root = buildHuffmanTree(data, frequency, size);

    int arr[100], top = 0;
    printf("Huffman Codes:\n");
    printCodes(root, arr, top);
    return 0;
}
