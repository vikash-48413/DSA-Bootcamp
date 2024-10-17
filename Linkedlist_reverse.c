#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct Node {
    int data;
    struct Node* next; // Pointer to the next node
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode; // If the list is empty, set head to the new node
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next; // Traverse to the end of the list
        }
        temp->next = newNode; // Link the new node at the end
    }
}

// Recursive function to print the linked list in reverse order
void printReverse(struct Node* head) {
    if (head == NULL) {
        return; // Base case: if the list is empty, return
    }
    printReverse(head->next); // Recursive call with the next node
    printf("%d ", head->data); // Print the data after returning from recursion
}

// Main function to demonstrate the linked list and reverse printing
int main() {
    struct Node* head = NULL; // Initialize the head of the linked list
    int choice, value;

    // Insert some elements into the linked list
    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);
    insertEnd(&head, 40);
    insertEnd(&head, 50);

    printf("Linked List in reverse order: ");
    printReverse(head); // Call the recursive function to print in reverse
    printf("\n");

    // Free the linked list memory
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp); // Free each node
    }

    return 0;
}