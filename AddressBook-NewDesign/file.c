#include <stdio.h>
#include "file.h"
#include<stdlib.h>
#include<string.h>

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp;
    fp = fopen("contacts.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
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

    while(fgets(buffer,sizeof(buffer),fp) != NULL){
        printf("%s\n",buffer);

        strcpy(addressBook->contacts[addressBook->contactCount].name,strtok(buffer,","));
        strcpy(addressBook->contacts[addressBook->contactCount].phone,strtok(NULL,","));
        strcpy(addressBook->contacts[addressBook->contactCount].email,strtok(NULL,","));

        addressBook->contactCount++;

    }
}


