# Address Book Application

## Overview

The Address Book Application is a simple software tool that allows users to store, manage, and retrieve personal contact information in an organized manner. Users can add, update, delete, and search for contacts based on various criteria, such as name, phone number, and email address. The application allows for efficient contact management and ensures data persistence through file storage.

## Features

- **Add Contacts**: Allows users to add new contacts with information like name, phone number, email, and address.
- **Search Contacts**: Enables searching for contacts based on name, phone number, or email.
- **Update Contacts**: Provides the option to update existing contact details.
- **Delete Contacts**: Allows users to delete a contact from the address book.
- **Data Persistence**: Contacts are saved in a file, ensuring data is retained between sessions.
- **Display Contacts**: Displays all saved contacts in a user-friendly format.
- **Sort Contacts**: Users can sort contacts by name, phone number, or email.

## Project Structure

The project is organized into the following key files:

- `address_book.c`: Contains the main functionality for managing contacts (add, update, delete, search, etc.).
- `contact.h`: Header file defining the `Contact` structure and function prototypes for managing contacts.
- `file_operations.c`: Functions for saving and loading contacts to/from a file.
- `ui.c`: User interface functions for interacting with the user through the terminal.
- `Makefile`: Contains build instructions for compiling the application.
  
## Data Structures

The application uses the following structure to store contact information:

### `Contact` Structure

```c
typedef struct {
    char name[100];    // Contact's name
    char phone[15];    // Contact's phone number
    char email[100];   // Contact's email address
    char address[200]; // Contact's physical address
} Contact;
