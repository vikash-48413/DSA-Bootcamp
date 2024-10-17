#include <stdio.h>
#include <stdlib.h>

// Define the structure for a deque node
struct Node {
    int data;
    struct Node* next; // Pointer to the next node
    struct Node* prev; // Pointer to the previous node
};

// Define the structure for the deque
struct Deque {
    struct Node* front; // Pointer to the front node
    struct Node* rear;  // Pointer to the rear node
};

// Function to create a new deque
struct Deque* createDeque() {
    struct Deque* deque = (struct Deque*)malloc(sizeof(struct Deque));
    deque->front = NULL; // Initialize front to NULL
    deque->rear = NULL;  // Initialize rear to NULL
    return deque;
}

// Function to check if the deque is empty
int isEmpty(struct Deque* deque) {
    return deque->front == NULL;
}

// Function to add an element at the front of the deque
void addFront(struct Deque* deque, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = deque->front; // Link the new node to the current front
    newNode->prev = NULL; // New node will be the first node

    if (isEmpty(deque)) {
        deque->rear = newNode; // If the deque is empty, set rear to the new node
    } else {
        deque->front->prev = newNode; // Link the current front's previous to the new node
    }
    deque->front = newNode; // Update front to the new node
    printf("Added %d to the front of the deque.\n", value);
}

// Function to add an element at the rear of the deque
void addRear(struct Deque* deque, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL; // New node will be the last node
    newNode->prev = deque->rear; // Link the new node to the current rear

    if (isEmpty(deque)) {
        deque->front = newNode; // If the deque is empty, set front to the new node
    } else {
        deque->rear->next = newNode; // Link the current rear to the new node
    }
    deque->rear = newNode; // Update rear to the new node
    printf("Added %d to the rear of the deque.\n", value);
}

// Function to remove an element from the front of the deque
int removeFront(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty! Cannot remove from front.\n");
        return -1; // Return -1 if the deque is empty
    }
    struct Node* temp = deque->front; // Get the front node
    int removedValue = temp->data; // Store the value to return

    deque->front = deque->front->next; // Update front to the next node
    if (deque->front != NULL) {
        deque->front->prev = NULL; // Update the previous pointer of the new front
    } else {
        deque->rear = NULL; // If the deque is now empty, update rear to NULL
    }
    free(temp); // Free the memory of the removed node
    printf("Removed %d from the front of the deque.\n", removedValue);
    return removedValue;
}

// Function to remove an element from the rear of the deque
int removeRear(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty! Cannot remove from rear.\n");
        return -1; // Return -1 if the deque is empty
    }
    struct Node* temp = deque->rear; // Get the rear node
    int removedValue = temp->data; // Store the value to return

    deque->rear = deque->rear->prev; // Update rear to the previous node
    if (deque->rear != NULL) {
        deque->rear->next = NULL; // Update the next pointer of the new rear
    } else {
        deque->front = NULL; // If the deque is now empty, update front to NULL
    }
    free(temp); // Free the memory of the removed node
    printf("Removed %d from the rear of the deque.\n", removedValue);
    return removedValue;
}

// Function to display the elements in the deque
void display(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty.\n");
        return;
    }
    struct Node* temp = deque->front;
    printf("Deque elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next; // Move to the next node
    }
    printf("\n");
}

// Main function to demonstrate deque operations
int main() {
    struct Deque* deque = createDeque();
    int choice, value;

    do {
        printf("\nDeque Operations Menu:\n");
        printf("1. Add to Front\n");
        printf("2. Add to Rear\n");
        printf("3. Remove from Front\n");
        printf("4. Remove from Rear\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to add to the front: ");
                scanf("%d", &value);
                addFront(deque, value);
                break;
            case 2:
                printf("Enter the element to add to the rear: ");
                scanf("%d", &value);
                addRear(deque, value);
                break;
            case 3:
                removeFront(deque);
                break;
            case 4:
                removeRear(deque);
                break;
            case 5:
                display(deque);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    // Free the deque memory
    while (!isEmpty(deque)) {
        removeFront(deque); // Remove all elements to free memory
    }
    free(deque); // Free the deque structure

    return 0;
}