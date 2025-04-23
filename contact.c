/*
 * Author       : Lekhan Goeda R
 * Project Name : Address Book
 * File Name    : contact.c
 * Description  : This file implements all core functionalities of 
 *                the address book, including adding, editing, deleting, 
 *                validating, and searching contacts.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Function declarations for internal validations
int ph_valid(char*, AddressBook*);
int em_valid(char*, AddressBook*);
int c_present(char*, AddressBook*);

// List all contacts in the address book
void listContacts(AddressBook *addressBook) {
    if (addressBook->contactCount == 0)
        printf("\nContact is empty!\n");
    else {
        printf("\n\t\t---- CONTACT LIST ----\n");
        printf("\nSL No.\tName\t\t\tPhone No.\t\tEmail ID\n");
        for (int i = 0; i < addressBook->contactCount; i++)
            printf("\n%d\t%s\t\t%s\t\t%s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}

// Initialize the address book and load data from file
void initialize(AddressBook *addressBook) {
    addressBook->contacts = malloc(MAX_CONTACTS * sizeof(Contact));
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

// Save all contacts to file and exit
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);
    free(addressBook->contacts);
    exit(EXIT_SUCCESS);
}

// Create a new contact with validation
void createContact(AddressBook *addressBook) {
    if (addressBook->contactCount == MAX_CONTACTS)
        printf("Maximum contacts reached! Cannot add more contacts.\n");
    else {
        getchar();
        printf("\n\t---- ENTER CONTACT DETAILS ----\nEnter the name : ");
        scanf("%[^\n]", addressBook->contacts[addressBook->contactCount].name);

        // Phone number input and validation
        printf("Enter the Phone Number : ");
        char ph_str[20];
        int success;
        do {
            scanf("%s", ph_str);
            success = ph_valid(ph_str, addressBook);
        } while (success == 0);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, ph_str);

        // Email input and validation
        printf("Enter the Email ID : ");
        char email_str[30];
        success = 0;
        do {
            scanf("%s", email_str);
            success = em_valid(email_str, addressBook);
        } while (success == 0);
        strcpy(addressBook->contacts[addressBook->contactCount].email, email_str);

        // Increment count if all inputs are valid
        if (success == 1) {
            addressBook->contactCount++;
            printf("\nCONTACT IS ADDED\n");
        }
    }
}

// Search for a contact using name, phone, or email
void searchContact(AddressBook *addressBook) {
    char toSearch[50];
    int index = -1;
    if (addressBook->contactCount == 0)
        printf("\nContact is empty!\n");
    else {
        do {
            getchar();
            printf("\nEnter the contact info (Name/Phone/Email) to search : ");
            scanf("%[^\n]", toSearch);
            index = c_present(toSearch, addressBook);
        } while (index == -1);

        // Display the found contact
        printf("\n\t---- CONTACT FOUND ----\n");
        printf("Name\t\t\tPhone No.\t\tEmail ID\n");
        printf("%s\t\t%s\t\t%s\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
    }
}

// Edit a contact by name, phone, or email
void editContact(AddressBook *addressBook) {
    char toEdit[50];
    int index = -1;
    if (addressBook->contactCount == 0)
        printf("\nCONTACT IS EMPTY!\n");
    else {
        do {
            getchar();
            printf("\nEnter the contact info (Name/Phone/Email) to edit : ");
            scanf("%[^\n]", toEdit);
            index = c_present(toEdit, addressBook);
        } while (index == -1);

        // Choose the field to edit
        printf("\n1. Name\n2. Phone Number\n3. Email ID\nEnter your choice to edit : ");
        int choice, valid;
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter the new name to edit : ");
                char new_name[20];
                scanf("%[^\n]", new_name);
                strcpy(addressBook->contacts[index].name, new_name);
                break;

            case 2:
                printf("Enter the new phone number to edit : ");
                char new_phone[20];
                do {
                    scanf("%[^\n]", new_phone);
                    getchar();
                    valid = ph_valid(new_phone, addressBook);
                } while (valid == 0);
                strcpy(addressBook->contacts[index].phone, new_phone);
                break;

            case 3:
                printf("Enter the new email to edit : ");
                char new_email[50];
                do {
                    scanf("%[^\n]", new_email);
                    getchar();
                    valid = em_valid(new_email, addressBook);
                } while (valid == 0);
                strcpy(addressBook->contacts[index].email, new_email);
                break;

            default:
                printf("Invalid choice\n");
        }
        printf("\nCONTACT IS UPDATED.\n");
    }
}

// Delete a contact by searching first
void deleteContact(AddressBook *addressBook) {
    char toDelete[50];
    int index = -1;
    if (addressBook->contactCount == 0)
        printf("\nContact is empty!\n");
    else {
        do {
            getchar();
            printf("Enter the contact info (Name/Phone/Email) to delete : ");
            scanf("%[^\n]", toDelete);
            index = c_present(toDelete, addressBook);
        } while (index == -1);

        // Shift contacts to remove the entry
        for (int i = index; i < addressBook->contactCount - 1; i++)
            addressBook->contacts[i] = addressBook->contacts[i + 1];

        addressBook->contactCount--;
        printf("\nTHE CONTACT IS DELETED.\n");
    }
}

// Check if string contains only digits
int only_num(char str[]) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i]))
            return 0;
    }
    return 1;
}

// Validate phone number
int ph_valid(char str[], AddressBook *addressBook) {
    if (only_num(str)) {
        if (strlen(str) == 10) {
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].phone, str) == 0) {
                    printf("\nPhone number already exists. Verify and enter again: ");
                    return 0;
                }
            }
        } else {
            printf("\nPhone number must be exactly 10 digits. Verify and enter again: ");
            return 0;
        }
    } else {
        printf("\nPhone number must contain only digits. Verify and enter again: ");
        return 0;
    }
    return 1;
}

// Validate email address
int em_valid(char em_str[], AddressBook *addressBook) {
    char *a = strstr(em_str, "@"), *b = strstr(em_str, ".com");
    int length = strlen(em_str);
    if (a && b) {
        if ((b - em_str == length - 4) && (a - em_str != 0) && (b - a > 1)) {
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcmp(addressBook->contacts[i].email, em_str) == 0) {
                    printf("Email ID already exists. Verify and enter again: ");
                    return 0;
                }
            }
        } else {
            printf("Invalid Email ID format. Verify and enter again: ");
            return 0;
        }
    } else {
        printf("Email must contain both '@' and '.com'. Verify and enter again: ");
        return 0;
    }
    return 1;
}

// Check if contact is present and return index
int c_present(char str[], AddressBook *addressBook) {
    int index = -1, count = 0, arr[addressBook->contactCount];

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strstr(addressBook->contacts[i].name, str) ||
            strstr(addressBook->contacts[i].phone, str) ||
            strstr(addressBook->contacts[i].email, str)) {
            if (count == 0)
                printf("\nSL No.\tName\t\t\tPhone No.\t\tEmail ID\n");

            printf("\n%d\t%s\t\t%s\t\t%s\n", count + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            arr[count++] = i;
        }
    }

    if (count == 0) {
        printf("\nCONTACT NOT FOUND!\n");
        return -1;
    } else if (count > 1) {
        int choice;
        printf("\nMultiple contacts found!\nEnter SL No. of the contact to select: ");
        scanf("%d", &choice);
        return arr[choice - 1];
    }

    return arr[0];
}
