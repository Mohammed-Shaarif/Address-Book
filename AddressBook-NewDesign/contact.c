#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook){
    __fpurge(stdin);
    int choice;
    printf("1. Sort by Name\n2. Sort by Phone Number\n3. Sort by Email\n");
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
            printf("Invalid choice. Listing contacts without sorting.\n");
            break;
    }

    // Sort contacts based on the chosen criteria
    printf("\nSaved Contacts: \n");
    printf("SR. NO\t%-20s\t%-15s\t%-30s\n", "Name", "Phone Number", "Email");
    printf("____________________________________________________________________________________________________\n");
    for(int i=0;i<addressBook->contactCount;i++){
        printf("%d\t%-20s\t%-15s\t%-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    printf("____________________________________________________________________________________________________\n\n");
    
}

void initialize(AddressBook *addressBook){
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook){

	/* Define the logic to create a Contacts */

    if (addressBook->contactCount < 100) {
        Contact *newContact = &addressBook->contacts[addressBook->contactCount];

        populateName(addressBook);
        populateMobile(addressBook);
        populateEmail(addressBook);

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
    int choice, index = -1;
    printf("1. Search by Name\n2. Search by Phone Number\n3. Search by Email\n");
    scanf("%d", &choice);
    __fpurge(stdin);
    char input[50];
    printf("\nsearch: ");
    scanf("%[^\n]", input);
    __fpurge(stdin);


    switch (choice) {
        case 1:
            index = SearchContactsByName(addressBook, input, flag);
            break;
        case 2:
            index = SearchContactsByPhone(addressBook, input, flag);
            break;
        case 3:
            index = SearchContactsByEmail(addressBook, input, flag);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
    printf("____________________________________________________________________________________________________\n\n");
    return index;
    
}


void editContact(AddressBook *addressBook){
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook){
	/* Define the logic for deletecontact */
    int index = searchContact(addressBook, 1);
    printf("name: %s\nPhone: %s\nEmail: %s\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
    if (index == -1) {
        printf("Contact not found.\n");
        return;
    }
    deleteContactByIndex(addressBook, index);
    printf("Contact deleted successfully.\n");

    printf("____________________________________________________________________________________________________\n\n");
   
}
