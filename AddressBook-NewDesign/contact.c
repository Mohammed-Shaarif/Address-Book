#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int foundIndex[100]={0};

void listContacts(AddressBook *addressBook){
    __fpurge(stdin);
    int choice;
    //printf("________________________________________________________________________________________________\n");
    printf("\n1. Sort by Name\n2. Sort by Phone Number\n3. Sort by Email\n");
    printf("________________________________________________________________________________________________\n\n");
    printf("Enter your choice for sorting (1-3): ");
    scanf("%d", &choice);
    __fpurge(stdin);

    switch (choice) {
        case 1:
            sortContactsByName(addressBook);
            break;
        case 2:
            sortContactsByPhone(addressBook);
            break;
        case 3:
            sortContactsByEmail(addressBook);
            break;
        default:
            printf("\nInvalid choice.\n");
            printf("________________________________________________________________________________________________\n\n");
            return;
    }

    // Sort contacts based on the chosen criteria
    printf("\nSaved Contacts: \n");
    printf("SR. NO\t%-20s\t%-15s\t%-30s\n", "Name", "Phone Number", "Email");
    printf("____________________________________________________________________________________________________\n\n");
    for(int i=0;i<addressBook->contactCount;i++){
        printf("%d\t%-20s\t%-15s\t%-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("____________________________________________________________________________________________________\n");
    printf("\n%d contacts found\n",addressBook->contactCount);
    printf("________________________________________________________________________________________________\n");
}

void initialize(AddressBook *addressBook){
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
    printf("Address Book initialized with %d contacts.\n", addressBook->contactCount);
}

void saveAndExit(AddressBook *addressBook) {
    int choice;
    printf("\nDo you want to save contacts before exiting? (1 for Yes, 0 for No): ");
    scanf("%d", &choice);
    printf("\n");
    if (choice == 1) {
        saveContactsToFile(addressBook); // Save contacts to file
        //printf("Contacts saved successfully. Exiting...\n");
    }
    else {
        printf("\nExiting without saving...\n");
    }
    printf("________________________________________________________________________________________________\n");
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook){

	/* Define the logic to create a Contacts */

    if (addressBook->contactCount < 100) {
        //Contact *newContact = &addressBook->contacts[addressBook->contactCount];
        printf("\n");
        printf("Enter contact details:\n");

        populateName(addressBook,-1);
        populateMobile(addressBook,-1);
        populateEmail(addressBook,-1);

        addressBook->contactCount++;
    }
    else{
        printf("Address book is full!\n");
    }
    printf("Contact Added Successfully\n");
    printf("____________________________________________________________________________________________________\n\n");
    
}

int searchContact(AddressBook *addressBook,int flag){
    /* Define the logic for search */
    __fpurge(stdin);
    int choice, size = 0;
    //printf("________________________________________________________________________________________________\n\n");
    printf("\nSearch options:\n1. Search by Name\n2. Search by Phone Number\n3. Search by Email\n");
    printf("________________________________________________________________________________________________\n\n");
    printf("Enter your choice for searching (1-3): ");
    scanf("%d", &choice);
    __fpurge(stdin);
    char input[50];
    //printf("_____________________________________________________________________________________________________\n\n");
    switch (choice) {
        case 1:
            printf("\nSearch Keyword: ");
            scanf("%[^\n]", input);
            __fpurge(stdin);
            size = SearchContactsByName(addressBook, input, flag,foundIndex);
            break;
        case 2:
            printf("\nSearch Keyword: ");
            scanf("%[^\n]", input);
            __fpurge(stdin);
            size = SearchContactsByPhone(addressBook, input, flag,foundIndex);
            break;
        case 3:
            printf("\nSearch Keyword: ");
            scanf("%[^\n]", input);
            __fpurge(stdin);
            size = SearchContactsByEmail(addressBook, input, flag,foundIndex);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
    //printf("____________________________________________________________________________________________________\n\n");
    return size;
    
}


void editContact(AddressBook *addressBook){
	/* Define the logic for Editcontact */
    printf("\nSearch for the contact to edit:");
    int size=searchContact(addressBook, 1);
    if (size == 0) {
        printf("________________________________________________________________________________________________\n\n");
        return;
    }
    for(int i = 0; i < size; i++) {
        printf("%d. Name: %s\tPhone: %s\tEmail: %s\n", i + 1, addressBook->contacts[foundIndex[i]].name, addressBook->contacts[foundIndex[i]].phone, addressBook->contacts[foundIndex[i]].email);
    }
    printf("\nEnter the index of the contact to edit (1 to %d): ", size);
    int index;
    scanf("%d", &index);
    if (index < 1 || index > size) {
        printf("Invalid index. Edit aborted.\n");
        return;
    }
    __fpurge(stdin);

    int choice;
    printf("\nEditing Contact: %s\n", addressBook->contacts[foundIndex[index - 1]].name);
    printf("\n1. Edit Name\n2. Edit Phone Number\n3. Edit Email\n\nChoice: ");
    scanf("%d", &choice);
    printf("\n");
    switch (choice) {
        case 1:
            populateName(addressBook,foundIndex[index - 1]);
            break;
        case 2:
            populateMobile(addressBook,foundIndex[index - 1]);
            break;
        case 3:
            populateEmail(addressBook,foundIndex[index - 1]);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    printf("\nContact updated successfully.\n");

    printf("____________________________________________________________________________________________________\n\n");

    
}

void deleteContact(AddressBook *addressBook){
	/* Define the logic for deletecontact */
    int size = searchContact(addressBook, 1);
    if (size == 0) {
        printf("Contact not found.\n");
        return;
    }
    printf("_____________________________________________________________________________________________________\n\n");

    printf("Enter the index of the contact to delete (1 to %d): ", size);
    printf("\nContacts matching the search criteria:\n");
    printf("sn. NO\t%-20s\t%-15s\t%-30s\n", "Name", "Phone Number", "Email");
    printf("____________________________________________________________________________________________________\n\n");
    for (int i = 0; i < size; i++) {
        printf("%d.%-20s\t%-15s\t%-30s\n", i + 1, addressBook->contacts[foundIndex[i]].name, addressBook->contacts[foundIndex[i]].phone, addressBook->contacts[foundIndex[i]].email);
    }
    printf("____________________________________________________________________________________________________\n\n");
    printf("Enter the index of the contact to delete (1 to %d): ", size);
    int index;
    scanf("%d", &index);
    if (index < 1 || index > size) {
        printf("Invalid index. Deletion aborted.\n");
        return;
    }
    else{
        printf("\nContact selected for deletion\n");
        printf("%-20s\t%-15s\t%-30s\n", "Name", "Phone Number", "Email");
        printf("%-20s\t%-15s\t%-30s\n\n",addressBook->contacts[foundIndex[index-1]].name, addressBook->contacts[foundIndex[index-1]].phone, addressBook->contacts[foundIndex[index-1]].email);
        deleteContactByIndex(addressBook, foundIndex[index - 1]);
    }

    printf("____________________________________________________________________________________________________\n\n");
   
}
