/*----------------------------------------------------------------------------
Name : main.c
Date : 17-06-2025
Description : Main function for the Address Book project. Displays a menu and   
	      performs operations like create, search, edit, delete, list, 
              and save contacts.
----------------------------------------------------------------------------*/


#include <stdio.h>
#include "contact.h"

int main() {

	int choice;
	AddressBook addressBook;
	initialize(&addressBook); // Initialize the address book

	do {
		//Display menu
		printf("\nAddress Book Menu:\n");
		printf("1. Create contact\n");
		printf("2. Search contact\n");
		printf("3. Edit contact\n");
		printf("4. Delete contact\n");
		printf("5. List all contacts\n");
		printf("6. Save and Exit\n");

		//Read choice from user
		printf("Enter your choice: ");
		scanf("%d", &choice);
		getchar();

		// Perform operation based on user choice
		switch (choice) {
			case 1:
				createContact(&addressBook);
				break;
			case 2:
				searchContact(&addressBook);
				break;
			case 3:
				editContact(&addressBook);
				break;
			case 4:
				deleteContact(&addressBook);
				break;
			case 5:          
				listContacts(&addressBook);
				break;
			case 6:
				saveContactsToFile(&addressBook);
				printf(" Exiting...\n");
				break;
			default:
				printf("Invalid choice. Please try again.\n");
		}
	} while (choice != 6); // Repeat until user chooses to exit

	return 0;
}
