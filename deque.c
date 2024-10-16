#include <stdio.h>
#define MAXSIZE 10  // Fixed size for the deque
int Deque[MAXSIZE];  // Array to hold deque elements
int front = -1;      // Front pointer
int rear = -1;       // Rear pointer
void insertFront();
void deleteRear();
void Display();
int isFull();
int isEmpty();
int main() {
    int choice;
    do {
        printf("\n1. Insert Front\n2. Delete Rear\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                insertFront();
                break;
            case 2:
                deleteRear();
                break;
            case 3:
                Display();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);
    return 0;
}
// Function to check if the deque is full
int isFull() {
    if ((front == 0 && rear == MAXSIZE - 1) || (front == rear + 1)) {
        return 1;
    }
    return 0;
}
// Function to check if the deque is empty
int isEmpty() {
    if (front == -1) {
        return 1;
    }
    return 0;
}
// Function to insert an element at the front of the deque
void insertFront() {
    int value;
    printf("Enter the value to insert at front: ");
    scanf("%d", &value);
    if (isFull()) {
        printf("Deque is full!\n");
        return;
    }
    // If deque is empty, initialize front and rear to 0
    if (front == -1) {
        front = 0;
        rear = 0;
    }
    else if (front == 0) {
        front = MAXSIZE - 1;  // Wrap around to the last index
    }
    else {
        front--;  // Decrement front
    }
    Deque[front] = value;  // Insert value at the front
    printf("Inserted %d at front.\n", value);
}
// Function to delete an element from the rear of the deque
void deleteRear() {
    if (isEmpty()) {
        printf("Deque is empty!\n");
        return;
    }
    printf("Deleted %d from rear.\n", Deque[rear]);
    // If the deque has only one element, reset it
    if (front == rear) {
        front = -1;
        rear = -1;
    }
    else if (rear == 0) {
        rear = MAXSIZE - 1;  // Wrap around to the last index
    }
    else {
        rear--;  // Decrement rear
    }
}
// Function to display the elements of the deque
void Display() {
    if (isEmpty()) {
        printf("Deque is empty!\n");
        return;
    }
    printf("Deque elements are: ");
    if (rear >= front) {
        // Print from front to rear if rear is ahead of front
        for (int i = front; i <= rear; i++) {
            printf("%d ", Deque[i]);
        }
    }
    else {
        // Print in two parts if front has wrapped around
        for (int i = front; i < MAXSIZE; i++) {
            printf("%d ", Deque[i]);
        }
        for (int i = 0; i <= rear; i++) {
            printf("%d ", Deque[i]);
        }
    }
    printf("\n");
}