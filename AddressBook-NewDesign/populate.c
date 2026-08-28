#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include <stdio_ext.h>
#include "contact.h"
#include "populate.h"

void populateName(AddressBook *addressBook,int f){
    char input[50];
    char flag=1;
    if(f==-1){
        f=addressBook->contactCount;
    }
    while(flag==1){
        __fpurge(stdin);
        printf("Enter Name: ");
        scanf("%[^\n]",input);


        for(int i=0;input[i]!=0;i++){
            if(!(isalnum(input[i]) || input[i]==' ')){
                flag=2;
                break;
            }
                
        }
        if(flag==1){
            strcpy(addressBook->contacts[f].name,input);
            flag=0;
            }
        else if(flag==2){
            printf("Name should include only Alphabets, Numbers and Spaces\n");
            flag=1;
        }
    }
    //printf("Test-> populateName Success\n");
}



void populateMobile(AddressBook *addressBook,int f){
    char input[20];
    char flag=1;
    if(f==-1){
        f=addressBook->contactCount;
    }
    while(flag==1){
        //getchar();
        __fpurge(stdin);
        printf("Enter Mobile Number: ");
        scanf("%[0-9]",input);



        for(int i=0;input[i]!=0;i++){
            if(!isdigit(input[i])){
                flag=3;
                break;
            }
        }
        if(input[0]<'6')
            flag=4;

        if(strlen(input)!=10){
            flag=2;
        }

        for(int i=0;i<addressBook->contactCount;i++){
            if(!strcmp(addressBook->contacts[i].phone,input)){
                flag=5;
                break;
                       
            }
        }

        if(flag==1){
            strcpy(addressBook->contacts[f].phone,input);
            flag=0;
        }
        else if(flag==2){
            printf("Length of phone number should be 10 digits\n");
            flag=1;
        }
        else if(flag==3){
            printf("Phone number should contain only digits\n");
            flag=1;
        }
        else if(flag==4){
            printf("Phone number should start with digits 6,7,8 or 9\n");
            flag=1;
        }
        else if(flag==5){
            printf("Phone number already exists\n");
            flag=1;
        }
    }
    //printf("Test-> populateMobile Success\n");
}



void populateEmail(AddressBook *addressBook,int f){
    char input[50];
    char flag=1;
    char template1[]=".com";
    if(f==-1){
        f=addressBook->contactCount;
    }
    while(flag==1){
        //getchar();
        __fpurge(stdin);
        printf("Enter Email: ");
        scanf("%[^\n]",input);
        int count=0,n=strlen(input),index=0;

        if(strcmp(template1,input+n-4)){
            flag=5;
        }
        if(input[0]=='@'){
            flag=4;
        }
        for(int i=0;i<n;i++){
            if(!(isalnum(input[i])|| input[i]=='@' || input[i]=='.')){
                flag=2;
                break;
            }
            if(input[i]=='@'){
                count++;
                if(count>1){
                    flag=3;
                    break;
                }
                index=i;
            }
        }
        if(index>n-5){
            flag=3;
        }

        for(int i=0;i<addressBook->contactCount;i++){
            if(!strcmp(addressBook->contacts[i].email,input)){
                flag=6;
                break;
            }
        }

        if(flag==1){
            strcpy(addressBook->contacts[f].email,input);
            //printf("Email: %s\n",addressBook->contacts[addressBook->contactCount].email);
            flag=0;
        }
        else if(flag==2){
            printf("Please Enter Valid Characters\n");
            flag=1;
        }
        else if(flag==3){
            printf("No domain name or multiple '@' present in email\n");
            flag=1;
        }
        else if(flag==4){
            printf("name before '@' is missing\n");
            flag=1;
        }
        else if(flag==5){
            printf("missing domain extension '.com'\n");
            flag=1;
        }
        else if(flag==6){
            printf("Email already exists\n");
            flag=1;
        }
    }
    //printf("Test-> populateEmail Success\n");
}








void sortContactsByName(AddressBook *addressBook){
    for(int i=0;i<addressBook->contactCount-1;i++){
        for(int j=i+1;j<addressBook->contactCount;j++){
            if(strcmp(addressBook->contacts[i].name,addressBook->contacts[j].name)>0){
                Contact temp=addressBook->contacts[i];
                addressBook->contacts[i]=addressBook->contacts[j];
                addressBook->contacts[j]=temp;
            }
        }
    }
    //printf("Test-> sortContactsByName Success\n");
}



void sortContactsByPhone(AddressBook *addressBook){
    for(int i=0;i<addressBook->contactCount-1;i++){
        for(int j=i+1;j<addressBook->contactCount;j++){
            if(strcmp(addressBook->contacts[i].phone,addressBook->contacts[j].phone)>0){
                Contact temp=addressBook->contacts[i];
                addressBook->contacts[i]=addressBook->contacts[j];
                addressBook->contacts[j]=temp;
            }
        }
    }
    //printf("Test-> sortContactsByPhone Success\n");
}



void sortContactsByEmail(AddressBook *addressBook){
    for(int i=0;i<addressBook->contactCount-1;i++){
        for(int j=i+1;j<addressBook->contactCount;j++){
            if(strcmp(addressBook->contacts[i].email,addressBook->contacts[j].email)>0){
                Contact temp=addressBook->contacts[i];
                addressBook->contacts[i]=addressBook->contacts[j];
                addressBook->contacts[j]=temp;
            }
        }
    }
    //printf("Test-> sortContactsByEmail Success\n");
}   

char* convertToLower(const char *str,char *lowerStr){
    for(int i=0;str[i]!=0;i++){
        lowerStr[i]=tolower(str[i]);
    }
    lowerStr[strlen(str)]=0;
    return lowerStr;
}

int SearchContactsByName(AddressBook *addressBook, char *name, int flag){
    char temp1[50];
    char temp2[50];
    if(flag==0){
        char f=0;
        for(int i=0;i<addressBook->contactCount;i++){
            if(strstr(convertToLower(addressBook->contacts[i].name,temp1),convertToLower(name,temp2))){
                printf("Name: %s\tPhone: %s\tEmail: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                f=1;
            }
        }
        if(f==0){
            printf("Name/match not found\n");
        }
    }
    else if(flag==1){
        for(int i=0;i<addressBook->contactCount;i++){
            if(strstr(convertToLower(addressBook->contacts[i].name,temp1),convertToLower(name,temp2))){
                printf("contact found name: %s\tPhone: %s\tEmail: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                return i;
            }
        }
        printf("Name/match not found\n");
        return -1;
    }
}



int SearchContactsByPhone(AddressBook *addressBook, char *phone, int flag){
    char temp1[50];
    char temp2[50];
    if(flag==0){
        char f=0;
        for(int i=0;i<addressBook->contactCount;i++){
            if(!strcmp(convertToLower(addressBook->contacts[i].phone,temp1),convertToLower(phone,temp2))){
                printf("Name: %s\tPhone: %s\tEmail: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                f=1;
                break;
            }
        }
        if(f==0){
            printf("Phone number not found\n");
        }
    }
    else if(flag==1){
        for(int i=0;i<addressBook->contactCount;i++){
            if(!strcmp(convertToLower(addressBook->contacts[i].phone,temp1),convertToLower(phone,temp2))){
                printf("contact found name: %s\tPhone: %s\tEmail: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                return i;
            }
        }
        printf("Phone number not found\n");
        return -1;
    }
}

int SearchContactsByEmail(AddressBook *addressBook, char *email,int flag){
    char temp1[50];
    char temp2[50];
    if(flag==0){
        char f=0;
        for(int i=0;i<addressBook->contactCount;i++){
            if(!strcmp(convertToLower(addressBook->contacts[i].email,temp1),convertToLower(email,temp2))){
                printf("Name: %s\tPhone: %s\tEmail: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                f=1;
                break;
            }
        }
        if(f==0){
            printf("Email not found\n");
        }
    }
    else if(flag==1){
        for(int i=0;i<addressBook->contactCount;i++){
            if(!strcmp(convertToLower(addressBook->contacts[i].email,temp1),convertToLower(email,temp2))){
                printf("contact found name: %s\tPhone: %s\tEmail: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                return i;
            }
        }
        printf("Email not found\n");
        return -1;
    }
}


void deleteContactByIndex(AddressBook *addressBook, int index){
    int choice;
    printf("Are you sure you want to delete the contact: %s? (1 for Yes, 0 for No): ", addressBook->contacts[index].name);
    scanf("%d", &choice);
    if (choice == 1){
        for(int i=index;i<addressBook->contactCount-1;i++){
            addressBook->contacts[i]=addressBook->contacts[i+1];
        }
        addressBook->contactCount--;
        printf("\nContact deleted successfully.\n");
    }else{
        printf("\nDeletion cancelled.\n");
    }
    //printf("Test-> deleteContactByIndex Success\n");
}

