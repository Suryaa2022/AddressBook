# Address Book Project in C

**My first project developed at Emertxe Information Technologies**

---

## Technologies Used

- C Programming
- File Handling (CSV)
- Structures
- String Manipulation
- Sorting Algorithms

---

## Project Overview

This is a command-line based Address Book Application written in C. It allows users to manage contacts efficiently. This project demonstrates practical knowledge of structures, input validation, file I/O, sorting, and modular programming.

---

## Features

### 1 Create Contact
- Takes Name, Phone, Email
- Validates input
- Prevents duplicates

### 2 Search Contact
- By Name / Phone / Email
- Supports partial search

### 3 Edit Contact
- Edit any field after searching
- Handles multiple matches

### 4 Delete Contact
- Delete after confirmation
- Updates file after deletion

### 5 List Contacts (Sorted)
- Displays all contacts
- Sort by Name / Phone / Email

### 6 File Persistence
- Stores data in CSV file (`Contacts.csv`)
- Loads data on program start

---

## How to Compile

```bash
gcc main.c contact.c populate.c -o addressbook
./addressbook

Author
Surya 
