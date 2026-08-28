#include <stdio.h>
#include "file.h"
#include<stdlib.h>
#include<string.h>

void saveContactsToFile(AddressBook *addressBook){
    FILE *fp;
    fp = fopen("contacts.csv", "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(fp, "%d\n", addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(fp);
    printf("Contacts saved to file successfully.\n");
    printf("")
  
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp;
    char buffer[120];

    fp=fopen("contacts.csv","r");

    if(fp == NULL){
        printf("\nError opening file");
        return;
    }
    fscanf(fp, "%d\n", &addressBook->contactCount);
    printf("\nLoading %d contacts from file...\n", addressBook->contactCount);
    printf("____________________________________________________________________________________________________\n\n");
    //printf("Saved Contacts: \n");
    for (int i = 0; i < addressBook->contactCount; i++) {
        fgets(buffer, sizeof(buffer), fp);
        buffer[strcspn(buffer, "\r\n")] = 0;

        printf("%s\n", buffer);

        char *name  = strtok(buffer, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");

        if (name && phone && email) {
            strcpy(addressBook->contacts[i].name, name);
            strcpy(addressBook->contacts[i].phone, phone);
            strcpy(addressBook->contacts[i].email, email);
        }
    }

    fclose(fp);
    printf("____________________________________________________________________________________________________\n\n");
    printf("Contacts loaded from file successfully.\n");
}





