/*
 * Author       : Lekhan Goeda R
 * Project Name : Address Book
 * File Name    : main.c
 * Description  : Entry point of the Address Book application. 
 *                Displays menu and handles user interaction.
 */

#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;

    initialize(&addressBook); // Initialize the address book (load from file or set up empty structure)

    do {
        // Display menu options
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save And Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Handle user choice
        switch (choice) {
            case 1:
                createContact(&addressBook); // Add a new contact
                break;
            case 2:
                searchContact(&addressBook); // Search contact by name or number
                break;
            case 3:
                editContact(&addressBook); // Modify an existing contact
                break;
            case 4:
                deleteContact(&addressBook); // Remove a contact
                break;
            case 5:
                listContacts(&addressBook); // Display all saved contacts
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook); // Save contacts before exit
                break;
            default:
                printf("Invalid choice. Please try again.\n"); // Handle invalid input
        }
    } while (choice != 6); // Repeat until user chooses to exit

    return 0;
}
