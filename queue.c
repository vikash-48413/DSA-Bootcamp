#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10  // Corrected the definition of MAXSIZE

int Queue[MAXSIZE];
int front = 0;
int rear = -1;

// Function prototypes
void Insert();
void Delete();
void Display();

int main() { // Corrected the main function definition
    int choice; // Changed to an integer variable
    // clrscr(); // Removed clrscr() as it's not standard; use system("cls") if needed

    do {
        printf("\n1. Insert\n2. Delete\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); // Read user choice

        switch (choice) {
            case 1:
                Insert(); 
                break;
            case 2:
                Delete(); 
                break;
            case 3:
                Display(); 
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0; // Added return statement for main
}

void Insert() {
    int n;
    if (rear == MAXSIZE - 1) {
        printf("Queue overflow\n");
        // Checking if the queue is overflow
    } else {
        printf("Enter the element to insert: ");
        scanf("%d", &n);
        rear++; // Increment the rear index
        Queue[rear] = n; // Add the element to the queue
    }
}

void Delete() {
    if (front > rear) {
        printf("Queue underflow\n");
        // Checking if the queue is empty
    } else {
        printf("Deleted element: %d\n", Queue[front]); // Display the deleted element
        front++; // Increment the front index
    }
}

void Display() {
    if (front > rear) {
        printf("Queue is empty\n");
    } else {
        printf("Queue elements: ");
        for (int i = front; i <= rear; i++) {
            printf("%d ", Queue[i]); // Display elements from front to rear
        }
        printf("\n");
    }
}