/*------------------------------------------------------------
Name : contact.c
Date : 17-06-2025
Description : Implements functionalities of the Address Book
-------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<stdio_ext.h>
#include "contact.h"
#include "populate.h"

//Function to displays all the contacts stored in the address book
void listContacts(AddressBook *addressBook)
{
	//list all the contacts..
	printf("---------------------------------------------------------------\n");
	printf("Name	   Phone_number		email\n");
	printf("---------------------------------------------------------------\n");

	for(int i = 0; i < addressBook->contactCount; i++)
	{
		printf("%s\t %s\t %s\n", addressBook->contacts[i].name, 
				addressBook->contacts[i].phone, 
				addressBook->contacts[i].email);
	}
}


//Function to load contacts from a CSV file into the address book
void loadContactsFromFile(AddressBook *addressBook)
{
	//open file in read mode
	FILE *fptr = fopen("contacts.csv", "r");

	if (fptr == NULL)
	{
		printf("Failed to open file for reading");
		return;
	}

	//read contact count
	fscanf(fptr, "%d", &addressBook->contactCount);

	// Read each contacts
	for (int i = 0; i < addressBook->contactCount; i++)
	{
		fscanf(fptr, "%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,
				addressBook->contacts[i].phone,
				addressBook->contacts[i].email);
	}

	//close the file
	fclose(fptr);
}


//Functions to initializes the address book
void initialize(AddressBook *addressBook)
{
	addressBook->contactCount = 0;

	if (addressBook->contactCount == 0) 
	{
		populateAddressBook(addressBook);
	}

	// Load contacts from CSV file 
	loadContactsFromFile(addressBook);
}


//Function to saves all contacts to a CSV file
void saveContactsToFile(AddressBook *addressBook)
{
	//open file in write mode
	FILE *fptr = fopen("contacts.csv", "w");

	if (fptr == NULL)
	{
		printf("Failed to open file for writing");
		return;
	}

	// contact count
	fprintf(fptr, "%d", addressBook->contactCount);

	// Write contact in a contacts.CSV
	for (int i = 0; i < addressBook->contactCount; i++)
	{
		fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, 
				addressBook->contacts[i].phone, 
				addressBook->contacts[i].email);
	}

	//close the file
	fclose(fptr);
}

//Function to saves all contacts to file and exits the program.
void saveAndExit(AddressBook *addressBook)
{
	//save contacts to file
	saveContactsToFile(addressBook); 
	printf("Contacts saved successfully\n");
	exit(EXIT_SUCCESS);           
}




//check name is valid or not
int is_name_valid(char *name) 
{
	for (int i = 0; name[i] != '\0'; i++) 
	{
		//check any digits is found 
		if (isdigit(name[i])) 
		{
			return 0;
		}
	}
	return 1;
}

//check phone number is valid or not
int is_phone_valid( AddressBook *book, char *phone)
{
	int len = strlen(phone);

	//check the length of phone number is valid
	if (len != 10)
	{
		return 0;
	}

	//check phone number contains any not numeric value
	for (int i = 0; i < 10; i++)
	{
		//check any non digits are present
		if (!isdigit(phone[i])) 
		{
			return 0;
		}
	}

	//check for duplicate phone number
	for (int i = 0; i < book->contactCount; i++)
	{
		if (strcmp(book->contacts[i].phone, phone) == 0) 
		{
			return 0;
		}
	}
	return 1;
}

//check email is valid or not
int is_email_valid(AddressBook *book, const char *email) 
{
	int at_index = -1, dot_index = -1;

	//Find index of '.' and '@' character
	for (int i = 0; email[i] != '\0'; i++) 
	{
		if (email[i] == '@')
		{
			at_index = i;
		}
		if (email[i] == '.')
		{	
			dot_index = i;
		}
	}

	//check in between '.' and '@' atleast one character present or not
	if (at_index == -1 || dot_index == -1 || dot_index <= at_index + 1)
	{ 
		return 0;
	}

	//check for duplicate email
	for (int i = 0; i < book->contactCount; i++) 
	{
		if (strcmp(book->contacts[i].email, email) == 0)
		{
			return 0;
		}
	}
	return 1;
}


//Function to adds the contact to the address book
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

	//variable decalaration
	char name[50];
	int valid;


	do
	{
		//read name from the user
		printf("Enter the Name:\n");
		scanf("%49[^\n]", name);

		//clear the input buffer
		__fpurge(stdin);

		//check for name validation
		if (!is_name_valid(name)) 
		{
			printf("Invalid Name. It should not contain digits.\n");
		}
	} while (!is_name_valid(name));

	//save to addressBook
	strcpy(addressBook->contacts[addressBook->contactCount].name, name);



	//For Phone number	
	char phone_number[15];

	do
	{

		//read the phone number from user
		printf("Enter the phone number :\n");
		scanf("%14[^\n]", phone_number);

		//clear the input buffer
		__fpurge(stdin);

		//check the phone number is valid or not
		if (!is_phone_valid(addressBook, phone_number)) 
		{
			printf("Invalid or duplicate phone number.\n");
		}
	}while(!is_phone_valid(addressBook, phone_number));

	//store in addressBook
	strcpy(addressBook->contacts[addressBook->contactCount].phone, phone_number);


	//For email

	//variable declaration
	char email[50];

	do
	{
		printf("Enter the email:\n");
		scanf("%49[^\n]", email);

		//clear the input buffer
		__fpurge(stdin);

		// check for email validation
		if (!is_email_valid(addressBook, email)) 
		{
			printf("Invalid or duplicate email format.\n");
		}

	} while (!is_email_valid(addressBook, email));


	// Store the email 
	strcpy(addressBook->contacts[addressBook->contactCount].email, email);

	// Increment contact count
	addressBook->contactCount++;


}

//Function to search for a contact by name, phone number, or email
void searchContact(AddressBook *addressBook)
{
	/* Define the logic to search a Contacts */

	int choice;
	char keyword[50];
	int found = 0;

	printf("Search Contact By:\n");
	printf("1. Name\n");
	printf("2. Phone Number\n");
	printf("3. Email\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);
	__fpurge(stdin);

	switch (choice) {
		case 1: {
				//Read name from the user
				printf("Enter the name: ");
				scanf("%49[^\n]", keyword);
				__fpurge(stdin);

				//Array to store matching contacts
				int match_Contact[100];
				int matchCount = 0;

				for (int i = 0; i < addressBook->contactCount; i++)
				{
					if (strcmp(addressBook->contacts[i].name, keyword) == 0)
					{
						//Store matching contact and increment the count
						match_Contact[matchCount++] = i; 
					}
				}

				if(matchCount == 0)
				{
					printf("No contact found\n");
					return;
				}

				//Single match
				if (matchCount == 1) 
				{
					int idx = match_Contact[0];
					printf("\nContact Details:\n");
					printf("---------------------------------------------------------------\n");
					printf("Name\t\tPhone Number\tEmail\n");
					printf("---------------------------------------------------------------\n");
					printf("%s\t%s\t%s\n", addressBook->contacts[idx].name,
							addressBook->contacts[idx].phone,
							addressBook->contacts[idx].email);
					found = 1;
					break;
				}

				// Multiple matches
				printf("\nMatching contacts:\n");
				printf("---------------------------------------------------------------\n");
				printf("Index\tName\t\tPhone Number\tEmail\n");
				printf("---------------------------------------------------------------\n");

				for (int i = 0; i < matchCount; i++)
				{
					int idx = match_Contact[i];
					printf("%d.\t%s\t%s\t%s\n", i + 1,
							addressBook->contacts[idx].name,
							addressBook->contacts[idx].phone,
							addressBook->contacts[idx].email);
				}

				int choice;
				printf("\nEnter the index of the contact : ");
				scanf("%d", &choice);
				__fpurge(stdin);

				int choice_Idx = match_Contact[choice - 1];




				printf("\nContact Details:\n");
				printf("---------------------------------------------------------------\n");
				printf("Name\t\tPhone Number\tEmail\n");
				printf("---------------------------------------------------------------\n");
				printf("%s\t%s\t%s\n", addressBook->contacts[choice_Idx].name,
						addressBook->contacts[choice_Idx].phone,
						addressBook->contacts[choice_Idx].email);

				found = 1;
				break;

			}

		case 2: {
				//Read the phone number from user
				printf("Enter the phone number: ");
				scanf("%49[^\n]", keyword); 
				__fpurge(stdin);

				for (int i = 0; i < addressBook->contactCount; i++)
				{
					if (strcmp(addressBook->contacts[i].phone, keyword) == 0)
					{
						printf("Contact found:\n");


						printf("---------------------------------------------------------------\n");
						printf("Name       Phone_number         email\n");
						printf("---------------------------------------------------------------\n");
						printf("%s\t %s\t %s\n", addressBook->contacts[i].name, 
								addressBook->contacts[i].phone, 
								addressBook->contacts[i].email);

						found = 1;
						break;
					}
				}
				break;
			}

		case 3: 
			{
				//Read email from the user
				printf("Enter the email: ");
				scanf("%49[^\n]", keyword);
				__fpurge(stdin);

				for (int i = 0; i < addressBook->contactCount; i++)
				{
					if (strcmp(addressBook->contacts[i].email, keyword) == 0)
					{
						printf("Contact found:\n");

						printf("---------------------------------------------------------------\n");
						printf("Name       Phone_number         email\n");
						printf("---------------------------------------------------------------\n");
						printf("%s\t %s\t %s\n", addressBook->contacts[i].name, 
								addressBook->contacts[i].phone, 
								addressBook->contacts[i].email);

						found = 1;
						break;
					}
				}
				break;
			}
		default:
			printf("Invalid choice!\n");
			return;
	}

	if (!found)
	{
		printf("No contact matched.\n");
	}

}

//Function to edit a contact by name, phone number, or email
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */

	char keyword[50];
	int found = 0;

	printf("Edit Contact By:\n");
	printf("1. Name\n");
	printf("2. Phone Number\n");
	printf("3. Email\n");
	printf("Enter your choice:\n");

	int choice;
	//Read choice from the user
	scanf("%d", &choice);

	//Read search value from the user
	printf("Enter the search value: ");
	scanf(" %49[^\n]", keyword);

	for (int i = 0; i < addressBook->contactCount; i++) 
	{
		int match = 0;

		switch (choice) 
		{
			case 1:
				{
					//Array to store the matching contacts
					int match_Contacts[100];
					int matchCount = 0;

					for (int i = 0; i < addressBook->contactCount; i++) 
					{
						if (strcmp(addressBook->contacts[i].name, keyword) == 0)
						{
							//Store the matching conatcts and increment the count
							match_Contacts[matchCount++] = i;
						}
					}

					if (matchCount == 0)
					{
						printf("No contact matched\n");
						return;
					}

					int edit_Idx;
					if (matchCount == 1) 
					{
						edit_Idx = match_Contacts[0];
					} 

					else 
					{
						printf("\nMatching contacts:\n");
						printf("---------------------------------------------------------------\n");
						printf("Index\tName\t\tPhone Number\tEmail\n");
						printf("---------------------------------------------------------------\n");

						for (int i = 0; i < matchCount; i++) 
						{
							int idx = match_Contacts[i];
							printf("%d.\t%s\t%s\t%s\n", i + 1,
									addressBook->contacts[idx].name,
									addressBook->contacts[idx].phone,
									addressBook->contacts[idx].email);
						}

						int choice;

						//Read the choice
						printf("\nEnter the choice you want to edit: ");
						scanf("%d", &choice);
						__fpurge(stdin);


						edit_Idx = match_Contacts[choice - 1];
					}


					char newValue[50];

					//Read the new values from the user
					printf("Enter new name: ");
					scanf(" %49[^\n]", newValue);
					__fpurge(stdin);

					if (!is_name_valid(newValue)) 
					{
						printf("Invalid name.\n");
						return;
					}

					strcpy(addressBook->contacts[edit_Idx].name, newValue);
					printf("Contact updated successfully.\n");
					return;
				}
			case 2:
				if (strcmp(addressBook->contacts[i].phone, keyword) == 0)
				{
					match = 1;
				}
				break;
			case 3:
				if (strcmp(addressBook->contacts[i].email, keyword) == 0) 
				{
					match = 1;
				}
				break;
			default:
				printf("Invalid choice.\n");
				return;
		}

		if (match) {
			char newValue[50];

			printf("Contact Found:\n");

			printf("---------------------------------------------------------------\n");                                                                                printf("Name       Phone_number         email\n");                                                                                                          printf("---------------------------------------------------------------\n");                                                                                printf("%s\t %s\t %s\n", addressBook->contacts[i].name, 
					addressBook->contacts[i].phone, 
					addressBook->contacts[i].email);


			//Read the new value from the user
			printf("Enter new value: ");
			scanf(" %49[^\n]", newValue);

			switch (choice) 
			{
				case 2:
					if (!is_phone_valid(addressBook, newValue))
					{
						printf("Invalid or duplicate phone number.\n");
						return;
					}
					strcpy(addressBook->contacts[i].phone, newValue);
					break;
				case 3:
					if (!is_email_valid(addressBook, newValue)) 
					{
						printf("Invalid or duplicate email.\n");
						return;
					}
					strcpy(addressBook->contacts[i].email, newValue);
					break;
			}

			found = 1;
			break;

		}
	}

	if(!found)
	{
		printf("No contact matched.\n");
	}

}

//Function to Delete a contact by name, phone number, or email
void deleteContact(AddressBook *addressBook)

{


	char keyword[50];
	int found = 0;

	printf("Delete Contact By:\n");
	printf("1. Name\n");
	printf("2. Phone Number\n");
	printf("3. Email\n");
	printf("Enter the choice: ");

	int choice;
	scanf("%d", &choice);

	printf("Enter the search value: ");
	scanf(" %[^\n]", keyword);

	for (int i = 0; i < addressBook->contactCount; i++)
	{
		int match = 0;

		switch (choice)
		{
			case 1:
				{
					int match_Contacts[100];
					int matchCount = 0;
					for (int i = 0; i < addressBook->contactCount; i++)
					{
						if (strcmp(addressBook->contacts[i].name, keyword) == 0)
						{
							match_Contacts[matchCount++] = i;
						}
					}

					if (matchCount == 0)
					{
						printf("No contact matched\n");
						return;
					}

					int match_Idx;

					if (matchCount == 1) 
					{
						match_Idx = match_Contacts[0];
					} else 
					{
						printf("\nMatching contacts:\n");
						printf("---------------------------------------------------------------\n");
						printf("Index\tName\t\tPhone Number\tEmail\n");
						printf("---------------------------------------------------------------\n");

						for (int i = 0; i < matchCount; i++) 
						{
							int idx = match_Contacts[i];
							printf("%d.\t%s\t%s\t%s\n", i + 1,
									addressBook->contacts[idx].name,
									addressBook->contacts[idx].phone,
									addressBook->contacts[idx].email);
						}

						int choice;
						printf("\nEnter the choice of the contact to delete: ");
						scanf("%d", &choice);
						__fpurge(stdin);


						match_Idx = match_Contacts[choice - 1];
					}

					for (int i = match_Idx; i < addressBook->contactCount - 1; i++)
					{
						addressBook->contacts[i] = addressBook->contacts[i + 1];
					}

					addressBook->contactCount--;
					printf("Contact deleted successfully!\n");
					return;
				}
			case 2:
				if (strcmp(addressBook->contacts[i].phone, keyword) == 0)
				{
					match = 1;
				}
				break;
			case 3:
				if (strcmp(addressBook->contacts[i].email, keyword) == 0)
				{
					match = 1;
				}
				break;
			default:
				printf("Invalid choice.\n");
				return;
		}

		if (match)
		{
			//Replace the current index with next index
			for (int j = i; j < addressBook->contactCount - 1; j++)
			{
				addressBook->contacts[j] = addressBook->contacts[j + 1];
			}

			addressBook->contactCount--;
			found = 1;
			printf("Contact deleted successfully!\n");
			break;
		}
	}

	if (!found) 
	{
		printf("No contact matched.\n");
	}
}


