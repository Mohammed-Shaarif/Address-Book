#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include <stdio_ext.h>
#include "contact.h"
#include "populate.h"

/*Section 1 - Functions to populate the contact details. 
These functions are used to get the user input for name, mobile number and email address. 
The functions also validate the input and ensure that the input is in the correct format. 
The functions also check for duplicate entries and ensure that the input is unique. 
The functions also check for valid characters in the input and ensure that the input is in the correct format. 
The functions also check for valid length of the input and ensure that the input is in the correct format. 
The functions also check for valid starting character of the input and ensure that the input is in the correct format. 
The functions also check for valid domain extension of the input and ensure that the input is in the correct format. 
The functions also check for valid name before '@' in the email address and ensure that the input is in the correct format. 
The functions also check for valid domain name in the email address and ensure that the input is in the correct format. 
The functions also check for valid multiple '@' in the email address and ensure that the input is in the correct format. 
The functions also check for valid domain extension '.com' in the email address and ensure that the input is in the correct format. 
The functions also check for valid duplicate email address and ensure that the input is unique.
*/

// here f is the index of the contact to be populated. If f=-1, it means a new contact is being added, otherwise an existing contact is being edited.
void populateName(AddressBook *addressBook,int f){
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.
    int f: Index of the contact to be populated. -1 indicates a new contact is being added.

    Output:
    The function populates the name for the specified contact in the AddressBook structure.
    It ensures that the input is valid and unique, and it handles invalid input gracefully.
    */

    char input[50];
    char flag=1;
    if(f==-1){
        f=addressBook->contactCount;
    }
    while(flag==1){ //loop until valid name is entered
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
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.
    int f: Index of the contact to be populated. -1 indicates a new contact is being added.

    Output:
    The function populates the mobile number for the specified contact in the AddressBook structure.
    It ensures that the input is valid and unique, and it handles invalid input gracefully.
    */

    char input[20];
    char flag=1;
    if(f==-1){
        f=addressBook->contactCount;
    }
    //loop until valid mobile number is entered
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
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.
    int f: Index of the contact to be populated. -1 indicates a new contact is being added.

    Output:
    The function populates the email for the specified contact in the AddressBook structure.
    It ensures that the input is valid and unique, and it handles invalid input gracefully.
    */

    char input[50];
    char flag=1;
    char template1[]=".com";
    if(f==-1){
        f=addressBook->contactCount;
    }
    //loop until valid email is entered
    while(flag==1){
        //getchar();
        __fpurge(stdin);
        printf("Enter Email: ");
        scanf("%[^\n]",input);
        int count=0,n=strlen(input),index=0;

        if(strcmp(template1,input+n-4)){
            flag=5;
        }
        if(input[0]=='@' || !isalnum(input[0])){
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


/*
Section 2 - Functions to sort the contact details.
These functions are used to sort the contact details based on name, mobile number and email address.
The functions also ensure that the contact details are sorted in ascending order.
*/



void sortContactsByName(AddressBook *addressBook){
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.

    Output:
    The function sorts the contact details in ascending order based on the Name.
    */
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
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.

    Output:
    The function sorts the contact details in ascending order based on the Phone Number.
    */

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
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.

    Output:
    The function sorts the contact details in ascending order based on the Email.
    */
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


/*
Section 3 - Functions to search the contact details.
These functions are used to search the contact details based on name, mobile number and email address.
The functions also ensure that the contact details are searched in ascending order.
The functions also ensure that the contact details are searched in a case-insensitive manner.
There Search functions are used as helpers for editContact and deleteContact functions. They return the number of contacts found and populate the foundIndex array with the indices of the found contacts.
*/

char* convertToLower(const char *str,char *lowerStr){
    for(int i=0;str[i]!=0;i++){
        lowerStr[i]=tolower(str[i]);
    }
    lowerStr[strlen(str)]=0;
    return lowerStr;
}

int SearchContactsByName(AddressBook *addressBook, char *name, int flag, int foundIndex[]){
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.
    char *name: The name to search for in the contact details.
    int flag: A flag indicating whether to print the search results (0) or just return the number of contacts found (1).
    int foundIndex[]: An array to store the indices of the found contacts.

    return value:
    The function returns the number of contacts found that match the search criteria.

    Output:
    The function searches for contacts in the AddressBook structure based on the provided name.
    If flag is 0, it prints the search results. If flag is 1, it returns the number of contacts found and populates the foundIndex array with the indices of the found contacts.
    */

    sortContactsByName(addressBook);
    char temp1[50];
    char temp2[50];
    int k=0,f=0;
    if(flag==0){
        printf("_____________________________________________________________________________________________________\n\n");
        for(int i=0;i<addressBook->contactCount;i++){
            if(strstr(convertToLower(addressBook->contacts[i].name,temp1),convertToLower(name,temp2))){
                //printf("Name: %s\tPhone: %s\tEmail: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                f=1;
                foundIndex[k++] = i;
            }
        }
        if(f==1){
                printf("sn.NO\t%-20s\t%-15s\t%-30s\n", "Name", "Phone Number", "Email");
                for(int i=0;i<k;i++){
                    printf("%d.\t%-20s\t%-15s\t%-30s\n", i + 1, addressBook->contacts[foundIndex[i]].name, addressBook->contacts[foundIndex[i]].phone, addressBook->contacts[foundIndex[i]].email);
                }
        }
        if(f==0){
            printf("Name/match not found\n");
        }
        printf("_____________________________________________________________________________________________________\n\n");
    }
    else if(flag==1){
        for(int i=0;i<addressBook->contactCount;i++){
            if(strstr(convertToLower(addressBook->contacts[i].name,temp1),convertToLower(name,temp2))){
                //printf("%d. Name: %s\tPhone: %s\tEmail: %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                foundIndex[k++] = i;
                f=1;
            }
        }
        if(f==0){
            printf("Name/match not found\n");
            foundIndex[0] = -1;
        }
    }
    return k;
}

int SearchContactsByPhone(AddressBook *addressBook, char *phone, int flag,int foundIndex[]){
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.
    char *phone: The phone number to search for in the contact details.
    int flag: A flag indicating whether to print the search results (0) or just return the number of contacts found (1).
    int foundIndex[]: An array to store the indices of the found contacts.

    return value:
    The function returns the number of contacts found that match the search criteria.

    Output:
    The function searches for contacts in the AddressBook structure based on the provided phone number.
    If flag is 0, it prints the search results. If flag is 1, it returns the number of contacts found and populates the foundIndex array with the indices of the found contacts.
    */

    sortContactsByPhone(addressBook);
    int k=0,f=0;
    if(flag==0){
        printf("_____________________________________________________________________________________________________\n\n");
        for(int i=0;i<addressBook->contactCount;i++){
            if(strstr(addressBook->contacts[i].phone,phone)){
                //printf("Name: %s\tPhone: %s\tEmail: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                f=1;
                foundIndex[k++] = i;
                
            }
        }
        if(f==1){
            printf("sn.NO\t%-20s\t%-15s\t%-30s\n", "Name", "Phone Number", "Email");
            for(int i=0;i<k;i++){
                    printf("%d.\t%-20s\t%-15s\t%-30s\n", i + 1, addressBook->contacts[foundIndex[i]].name, addressBook->contacts[foundIndex[i]].phone, addressBook->contacts[foundIndex[i]].email);
            }
        }
        
        if(f==0){
            printf("Phone number not found\n");
        }
        printf("_____________________________________________________________________________________________________\n\n");
    }
    else if(flag==1){
        for(int i=0;i<addressBook->contactCount;i++){
            if(strstr(addressBook->contacts[i].phone,phone)){
                //printf("contact found name: %s\tPhone: %s\tEmail: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                foundIndex[k++] = i;
                f=1;
            }
        }
        if(f==0){
            printf("Phone number not found\n");
            foundIndex[0] = -1;
        }
    }
    return k;
}

int SearchContactsByEmail(AddressBook *addressBook, char *email,int flag,int foundIndex[]){
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.
    char *email: The email to search for in the contact details.
    int flag: A flag indicating whether to print the search results (0) or just return the number of contacts found (1).
    int foundIndex[]: An array to store the indices of the found contacts.

    return value:
    The function returns the number of contacts found that match the search criteria.

    Output:
    The function searches for contacts in the AddressBook structure based on the provided email.
    If flag is 0, it prints the search results. If flag is 1, it returns the number of contacts found and populates the foundIndex array with the indices of the found contacts.
    */

    sortContactsByEmail(addressBook);
    char temp1[50];
    char temp2[50];
    int k=0,f=0;
    if(flag==0){
        printf("_____________________________________________________________________________________________________\n\n");
        for(int i=0;i<addressBook->contactCount;i++){
            if(strstr(convertToLower(addressBook->contacts[i].email,temp1),convertToLower(email,temp2))){
                //printf("%d. Name: %s\tPhone: %s\tEmail: %s\n",k+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                f=1;
                foundIndex[k++] = i;
            }
        }
        if(f==1){
                printf("sn.NO\t%-20s\t%-15s\t%-30s\n", "Name", "Phone Number", "Email");
                for(int i=0;i<k;i++){
                    printf("%d.\t%-20s\t%-15s\t%-30s\n", i + 1, addressBook->contacts[foundIndex[i]].name, addressBook->contacts[foundIndex[i]].phone, addressBook->contacts[foundIndex[i]].email);
                }
        }
        if(f==0){
            printf("Email not found\n");
        }
        printf("_____________________________________________________________________________________________________\n\n");
    }
    else if(flag==1){
        for(int i=0;i<addressBook->contactCount;i++){
            if(strstr(convertToLower(addressBook->contacts[i].email,temp1),convertToLower(email,temp2))){
                //printf("contact found name: %s\tPhone: %s\tEmail: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                foundIndex[k++] = i;
                f=1;
            }
        }
        if(f==0){
        printf("Email not found\n");
            foundIndex[0] = -1;
            return -1;
        }
    }
    return k;
}



/*
Section 4 - Functions to delete the contact details.
*/

void deleteContactByIndex(AddressBook *addressBook, int index){
    /*
    Input parameters:
    AddressBook *addressBook: Pointer to the AddressBook structure that contains the contacts.
    int index: The index of the contact to be deleted.

    Output:
    The function deletes the contact at the specified index from the AddressBook structure.
    */
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

