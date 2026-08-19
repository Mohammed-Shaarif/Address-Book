void populateName(AddressBook *addressBook);
void populateMobile(AddressBook *addressBook);
void populateEmail(AddressBook *addressBook);

void sortContactsByName(AddressBook *addressBook);
void sortContactsByPhone(AddressBook *addressBook);
void sortContactsByEmail(AddressBook *addressBook);

int SearchContactsByName(AddressBook *addressBook, char *name, int flag);
int SearchContactsByPhone(AddressBook *addressBook, char *phone, int flag);
int SearchContactsByEmail(AddressBook *addressBook, char *email, int flag);

void deleteContactByIndex(AddressBook *addressBook, int index);
