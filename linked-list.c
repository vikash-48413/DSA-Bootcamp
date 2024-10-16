#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct node {
    int data;
    struct node *next; // Pointer to the next node
};

// Global pointer to the start of the linked list
struct node *start = NULL;

// Function prototypes
void create();
void insertAtBeginning(int data);
void display();

int main() {
    int choice, data;

    do {
        printf("\nLinked List Operations Menu:\n");
        printf("1. Create List\n");
        printf("2. Insert at Beginning\n");
        printf("3. Display List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                printf("Enter the element to insert at the beginning: ");
                scanf("%d", &data);
                insertAtBeginning(data);
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Function to create the linked list
void create() {
    int n;
    char ch;

    do {
        printf("Enter the element: ");
        scanf("%d", &n);
        
        // Create a new node
        struct node *newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = n;
        newNode->next = NULL;

        // If the list is empty, set start to the new node
        if (start == NULL) {
            start = newNode;
        } else {
            // Traverse to the end of the list and add the new node
            struct node *temp = start;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode; // Link the new node
        }

        printf("Want to continue adding elements? (Press 'Y' or 'y'): ");
        scanf(" %c", &ch); // Space before %c to consume any newline character
    } while (ch == 'Y' || ch == 'y');
}

// Function to insert a node at the beginning of the list
void insertAtBeginning(int data) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = start; // Link the new node to the current start
    start = newNode; // Update start to the new node
    printf("Inserted %d at the beginning of the list.\n", data);
}

// Function to display the linked list
void display() {
    if (start == NULL) {
        printf("The list is empty.\n");
        return;
    }
    struct node *temp = start;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n"); // Indicate the end of the list
}