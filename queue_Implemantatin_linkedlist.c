#include <stdio.h>
#include <stdlib.h>

// Define the structure for a queue node
struct Node {
    int data;
    struct Node* next; // Pointer to the next node
};

// Define the structure for the queue
struct Queue {
    struct Node* front; // Pointer to the front node
    struct Node* rear;  // Pointer to the rear node
};

// Function to create a new queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL; // Initialize front to NULL
    queue->rear = NULL;  // Initialize rear to NULL
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to enqueue an element into the queue
void enqueue(struct Queue* queue, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL; // New node will be the last node

    if (isEmpty(queue)) {
        queue->front = newNode; // If the queue is empty, set front to the new node
    } else {
        queue->rear->next = newNode; // Link the new node at the end
    }
    queue->rear = newNode; // Update rear to the new node
    printf("Enqueued %d into the queue.\n", value);
}

// Function to dequeue an element from the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1; // Return -1 if the queue is empty
    }
    struct Node* temp = queue->front; // Get the front node
    int dequeuedValue = temp->data; // Store the value to return
    queue->front = queue->front->next; // Update front to the next node

    if (queue->front == NULL) {
        queue->rear = NULL; // If the queue is now empty, update rear to NULL
    }
    free(temp); // Free the memory of the dequeued node
    printf("Dequeued %d from the queue.\n", dequeuedValue);
    return dequeuedValue;
}

// Function to display the elements in the queue
void display(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    struct Node* temp = queue->front;
    printf("Queue elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next; // Move to the next node
    }
    printf("\n");
}

// Main function to demonstrate queue operations
int main() {
    struct Queue* queue = createQueue();
    int choice, value;

    do {
        printf("\nQueue Operations Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to enqueue: ");
                scanf("%d", &value);
                enqueue(queue, value);
                break;
            case 2:
                dequeue(queue);
                break;
            case 3:
                display(queue);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    // Free the queue memory
    while (!isEmpty(queue)) {
        dequeue(queue); // Dequeue all elements to free memory
    }
    free(queue); // Free the queue structure

    return 0;
}