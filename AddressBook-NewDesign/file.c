#include <stdio.h>
#include "file.h"
#include<stdlib.h>
#include<string.h>

void saveContactsToFile(AddressBook *addressBook){
    FILE *fp;
    fp = fopen("contacts.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(fp);
    printf("Contacts saved to file successfully.\n");
  
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp;
    char buffer[120];

    fp=fopen("contacts.txt","r");

    if(fp == NULL){
        printf("Error opening file");
        return;
    }
    printf("Loading contacts from file...\n");
    printf("____________________________________________________________________________________________________\n\n");
    printf("Saved Contacts: \n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = 0;

        printf("%s\n", buffer);

        char *name  = strtok(buffer, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");

        if (name && phone && email) {
            strcpy(addressBook->contacts[addressBook->contactCount].name, name);
            strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
            strcpy(addressBook->contacts[addressBook->contactCount].email, email);
            addressBook->contactCount++;
        }
    }

    fclose(fp);
    printf("____________________________________________________________________________________________________\n\n");
    printf("Contacts loaded from file successfully.\n");
}





