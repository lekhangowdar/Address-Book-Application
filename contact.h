/*
 * Author       : Lekhan Goeda R
 * Project Name : Address Book
 * File Name    : contact.h
 * Description  : Header file that contains structure definitions 
 *                and function declarations for managing contacts.
 */

#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100  // Maximum number of contacts allowed

// Structure to store a single contact's details
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

// Structure to store the address book
typedef struct {
    Contact *contacts;     // Dynamic array of contacts
    int contactCount;      // Total number of contacts stored
} AddressBook;

// Function declarations for contact operations
void createContact(AddressBook *addressBook);         // Add new contact
void searchContact(AddressBook *addressBook);         // Search for a contact
void editContact(AddressBook *addressBook);           // Edit an existing contact
void deleteContact(AddressBook *addressBook);         // Delete a contact
void listContacts(AddressBook *addressBook);          // List all contacts
void initialize(AddressBook *addressBook);            // Initialize the address book
void saveContactsToFile(AddressBook *addressBook);    // Save contacts to file

#endif
