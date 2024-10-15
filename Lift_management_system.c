#include <stdio.h>

#define MAX_FLOORS 10  // Maximum number of floors

// Define the Queue structure
typedef struct {
    int floors[MAX_FLOORS];
    int front, rear;
} Queue;

// Initialize the queue
void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

// Check if the queue is empty
int isEmpty(Queue q) {
    return (q.front == -1);
}

// Enqueue function to add floor requests to the queue
void enqueue(Queue* q, int floor) {
    if (q->rear == MAX_FLOORS - 1) {
        printf("Queue overflow, can't add more requests.\n");
        return;
    }
    if (q->front == -1) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }
    q->floors[q->rear] = floor;
    printf("Added floor %d to the queue.\n", floor);
}

// Dequeue function to remove the next floor request
int dequeue(Queue* q) {
    if (isEmpty(*q)) {
        printf("Queue underflow, no more requests.\n");
        return -1;
    }
    int floor = q->floors[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return floor;
}

// Display the current queue status
void displayQueue(Queue q) {
    if (isEmpty(q)) {
        printf("No floors in the queue.\n");
    } else {
        printf("Current floor requests in the queue: ");
        for (int i = q.front; i <= q.rear; i++) {
            printf("%d ", q.floors[i]);
        }
        printf("\n");
    }
}

// Main function to handle user requests using switch case
int main() {
    Queue liftQueue;
    initQueue(&liftQueue);  // Initialize the queue

    int choice, floor;
    int currentFloor = 0;  // Track the current floor

    while (1) {
        printf("\n--- Lift Management System ---\n");
        printf("Current floor: %d\n", currentFloor);
        displayQueue(liftQueue);
        printf("1. Add Floor Request (Enqueue)\n");
        printf("2. Serve Next Request (Dequeue)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the floor number (0-%d): ", MAX_FLOORS - 1);
                scanf("%d", &floor);
                if (floor < 0 || floor >= MAX_FLOORS) {
                    printf("Invalid floor number!\n");
                } else {
                    enqueue(&liftQueue, floor);
                }
                break;

            case 2:
                floor = dequeue(&liftQueue);
                if (floor != -1) {
                    printf("Moving from floor %d to floor %d...\n", currentFloor, floor);
                    currentFloor = floor;  // Update the current floor to the dequeued floor
                }
                break;

            case 3:
                printf("Exiting the system.\n");
                return 0;

            default:
                printf("Invalid choice! Please enter again.\n");
        }
    }

    return 0;
}
