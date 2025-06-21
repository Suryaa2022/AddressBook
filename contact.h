/*--------------------------------------------
Name : contact.h
Date : 17-06-2025
Description : Header file of contact.c
----------------------------------------------*/

#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

// Structure to store contact details
typedef struct {
	char name[50];
	char phone[20];
	char email[50];
} Contact;

// Structure to store all contacts and their count
typedef struct {
	Contact contacts[100];
	int contactCount;
} AddressBook;

//Function Declaration
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif
