/***************************************************************
 * Name        : Lekhan Goeda R
 * Project     : Address Book
 * File Name   : file.c
 * Description : Handles file operations like saving to and loading
 *               from a CSV file. Supports persistence of contact data.
 ***************************************************************/

#include <stdio.h>
#include "file.h"
#include <string.h>

void saveContactsToFile(AddressBook *addressBook)
{
    // Open the file in write mode
    FILE *fptr = fopen("contact.csv", "w");

    // Write the contact count in the first line
    fprintf(fptr, "#%02d#\n", addressBook->contactCount);

    // Write each contact's data in CSV format
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    // Close the file
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    // Open the file in read mode
    FILE *fptr = fopen("contact.csv", "r");
    int i = 0;

    // Skip the first 5 bytes ("#nn#\n")
    fseek(fptr, 5, SEEK_SET);

    // Read the CSV data line by line
    while (fscanf(fptr, "%[^,],%[^,],%[^\n]",
                  addressBook->contacts[i].name,
                  addressBook->contacts[i].phone,
                  addressBook->contacts[i].email) == 3)
    {
        fseek(fptr, 1, SEEK_CUR); // Move past newline
        i++;
        addressBook->contactCount++; // Increase count as contact is loaded
    }

    // Close the file
    fclose(fptr);
}
