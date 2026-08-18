#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include <stdio_ext.h>
#include "contact.h"
#include "populate.h"

void populateName(AddressBook *addressBook){
    char input[50];
    char flag=1;
    while(flag==1){
        __fpurge(stdin);
        printf("Enter Name: ");
        scanf("%[^\n]",input);


        for(int i=0;input[i]!=0;i++){
            if(!isalnum(input[i]) || input[i]==' '){
                flag=2;
                break;
            }
                
        }
        if(flag==1){
            strcpy(addressBook->contacts[addressBook->contactCount].name,input);
            flag=0;
            }
        else if(flag==2){
            printf("Name should include only Alphabets, Numbers and Spaces\n");
            flag=1;
        }
    }
    printf("Test-> populateName Success\n");
}



void populateMobile(AddressBook *addressBook){
    char input[20];
    char flag=1;
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
        if(input[0]<='6')
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
            strcpy(addressBook->contacts[addressBook->contactCount].phone,input);
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
    printf("Test-> populateMobile Success\n");
}



void populateEmail(AddressBook *addressBook){
    char input[50];
    char flag=1;
    char template1[]=".com";
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
            if(!isalnum(input[i])|| input[i]!='@' || input[i]!='.'){
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
            strcpy(addressBook->contacts[addressBook->contactCount].email,input);
            flag=0;
        }
        else if(flag==2){
            printf("Please Enter Valid Characters\n");
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
    printf("Test-> populateEmail Success\n");
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
    printf("Test-> sortContactsByName Success\n");
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
    printf("Test-> sortContactsByPhone Success\n");
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
    printf("Test-> sortContactsByEmail Success\n");
}   

