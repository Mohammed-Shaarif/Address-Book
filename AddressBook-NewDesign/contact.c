#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Global array to store the indices of found contacts during search operations
int foundIndex[100]={0}; 

void listContacts(AddressBook *addressBook){
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.

    Output:
    The function sorts the contact details in ascending order based on selected criteria (Name, Phone Number, or Email) and displays the sorted list of contacts.
    */

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
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that will be initialized.

    Output:
    The function initializes the AddressBook structure by setting the contact count to 0 and loading contacts from a file (if available).
    */
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
    printf("Address Book initialized with %d contacts.\n", addressBook->contactCount);
    printf("________________________________________________________________________________________________\n\n");
}

void saveAndExit(AddressBook *addressBook){
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.

    Output:
    The function prompts the user to save contacts before exiting the program. If the user chooses to save, it saves the contacts to a file and exits the program. If the user chooses not to save, it exits without saving.
    */
    __fpurge(stdin);
    int choice;
    printf("\nDo you want to save contacts before exiting? (1 for Yes, 0 for No): ");
    scanf("%d", &choice);
    printf("\n");
    if(choice == 1){
        saveContactsToFile(addressBook); // Save contacts to file
        //printf("Contacts saved successfully. Exiting...\n");
    }
    else{
        printf("\nExiting without saving...\n");
        printf("________________________________________________________________________________________________\n");
    }

    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook){
    /* 
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.

    Output:
    The function prompts the user to enter contact details (Name, Phone Number, and Email) and adds the new contact to the AddressBook structure. It also checks for duplicate phone numbers and validates the input.
    */

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
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.
    int flag: A flag indicating the search mode (0 for display, 1 for edit or delete).

    return:
    The function returns the number of contacts found based on the search criteria.

    Output:
    The function prompts the user to enter a search keyword and searches for contacts based on the selected criteria (Name, Phone Number, or Email).
    It displays the search results and returns the number of contacts found. 
    If flag is 1, it also populates the foundIndex array with the indices of the found contacts.
    */
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
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.

    Output:
    The function allows the user to edit the details of an existing contact in the AddressBook structure.
    It prompts the user to search for a contact, select the contact to edit, and choose which field (Name, Phone Number, or Email) to modify.
    The function ensures that the input is valid and updates the contact details accordingly.
    */

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
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.

    Output:
    The function allows the user to delete an existing contact from the AddressBook structure.
    It prompts the user to search for a contact, select the contact to delete, and confirms the deletion before removing the contact from the address book.
    The function ensures that the input is valid and updates the contact list accordingly.
    */

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
