#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10

int CircularQueue[MAXSIZE];
int front = -1;
int rear = -1;

void enqueue();
void dequeue();
void Display();
int isFull();
int isEmpty();

int main() {
    int choice;
    do {
        printf("\n1. Insert\n2. Delete\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                enqueue();
                break;
            case 2:
                dequeue();
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

// Function to check if the queue is full
int isFull() {
    // Queue is full when rear is just one position behind front in a circular fashion
    if ((rear + 1) % MAXSIZE == front) {
        return 1;
    }
    return 0;
}

// Function to check if the queue is empty
int isEmpty() {
    // Queue is empty when front is -1
    if (front == -1) {
        return 1;
    }
    return 0;
}

// Function to insert an element into the circular queue
void enqueue() {
    int value;
    if (isFull()) {
        printf("Queue is Full\n");
        return;
    }

    printf("Enter the value to insert: ");
    scanf("%d", &value);

    if (front == -1) {
        // If the queue is empty, initialize front and rear to 0
        front = 0;
    }
    rear = (rear + 1) % MAXSIZE;  // Increment rear circularly
    CircularQueue[rear] = value;
    printf("Inserted %d into the queue.\n", value);
}

// Function to delete an element from the circular queue
void dequeue() {
    if (isEmpty()) {
        printf("Queue is Empty\n");
        return;
    }

    printf("Deleted %d from the queue.\n", CircularQueue[front]);

    // If there's only one element, reset the queue by setting front and rear to -1
    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % MAXSIZE;  // Increment front circularly
    }
}

// Function to display the elements of the circular queue
void Display() {
    if (isEmpty()) {
        printf("Queue is Empty\n");
        return;
    }

    printf("Queue elements are: ");
    int i = front;
    while (i != rear) {
        printf("%d ", CircularQueue[i]);
        i = (i + 1) % MAXSIZE;
    }
    printf("%d\n", CircularQueue[rear]);  // Print the last element
}
