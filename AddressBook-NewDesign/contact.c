#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
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

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{

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

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    __fpurge(stdin);
    int choice;
    printf("1. Search by Name\n2. Search by Phone Number\n3. Search by Email\n");
    scanf("%d", &choice);
    __fpurge(stdin);
    char input[50];


    switch (choice) {
        case 1:
            printf("Enter Name to search: ");
            scanf("%[^\n]", input);
            SearchContactsByName(addressBook, input, 0);
            break;
        case 2:
            printf("Enter Phone Number to search: ");
            scanf("%[^\n]", input);
            SearchContactsByPhone(addressBook, input, 0);
            break;
        case 3:
            printf("Enter Email to search: ");
            scanf("%[^\n]", input);
            SearchContactsByEmail(addressBook, input, 0);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
    printf("____________________________________________________________________________________________________\n\n");

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}
