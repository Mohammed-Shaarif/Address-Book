void populateName(AddressBook *addressBook,int f);
void populateMobile(AddressBook *addressBook,int f);
void populateEmail(AddressBook *addressBook,int f);

void sortContactsByName(AddressBook *addressBook);
void sortContactsByPhone(AddressBook *addressBook);
void sortContactsByEmail(AddressBook *addressBook);

int SearchContactsByName(AddressBook *addressBook, char *name, int flag,int foundIndex[]);
int SearchContactsByPhone(AddressBook *addressBook, char *phone, int flag,int foundIndex[]);
int SearchContactsByEmail(AddressBook *addressBook, char *email, int flag,int foundIndex[]);

void deleteContactByIndex(AddressBook *addressBook, int index);
