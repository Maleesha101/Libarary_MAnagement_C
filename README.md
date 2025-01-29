# Library Management System

## Overview

The **Library Management System** is a C-based application designed to manage library operations efficiently. It provides functionalities for both **admin** and **user** roles, allowing admins to manage books, members, and borrowing/returning processes, while users can search for books, view available books, and manage their borrowed books.

---

## Features

### 1. **User Management**
- **Registration:** Users can register as either an **admin** or a **user**.
- **Login:** Users can log in using their email and student number (for users) or email and admin keyword (for admins).
- **Update Member Information:** Admins can update member details such as email and student number.

### 2. **Book Management**
- **Add Books:** Admins can add new books to the library inventory.
- **Update Books:** Admins can update book details such as title, author, and published date.
- **View All Books:** Both admins and users can view all books in the library, including their availability status.

### 3. **Borrowing and Returning**
- **Borrow Books:** Users can borrow available books. The system automatically calculates the return date (14 days from the borrowing date).
- **Return Books:** Users can return borrowed books, and the system updates the book's availability status.
- **View Borrowed Books:** Users can view the list of books they have borrowed, along with the return date and days left to return.

### 4. **Search Functionality**
- **Search Books:** Users and admins can search for books by title or author.
- **Search Member Information:** Admins can search for member information using email or student number.

### 5. **Data Persistence**
- The system saves all data (users, books, borrow records, and return records) in text files (`users.txt`, `books.txt`, `borrows.txt`, `return.txt`, `info.txt`), ensuring data persistence across sessions.

---

## How to Use

### 1. **Main Menu**
Upon launching the application, you will see the **Main Menu** with the following options:
1. **Register as Admin**
2. **Register as User**
3. **Login as Admin**
4. **Login as User**
5. **Exit**

### 2. **Admin Features**
After logging in as an admin, you can access the following features:
- **Search Books:** Search for books by title or author.
- **Book Management:** Add, update, and view all books.
- **Member Management:** Register new members, update member information, and search for member details.
- **Borrowing and Returning:** Manage book borrowing and returning processes.

### 3. **User Features**
After logging in as a user, you can access the following features:
- **Search Books:** Search for books by title or author.
- **View All Books:** View a list of all available books.
- **View Borrowed Books:** View the list of books you have borrowed, along with the return date and days left to return.
- **Borrow and Return Books:** Borrow available books and return borrowed books.

---

## File Structure

The system uses the following text files to store data:
- **`users.txt`:** Stores user information (email, student number, role).
- **`books.txt`:** Stores book information (title, author, published date, availability status).
- **`borrows.txt`:** Stores borrowing records (email, student number, book title, borrow date, return date, returned status).
- **`return.txt`:** Stores return records (email, student number, book title, borrow date, return date, returned status).
- **`info.txt`:** Stores additional member information (email, student number, name, address, contact number).

---

## Code Structure

### Key Classes and Structures
- **`User`:** Represents a user (admin or user) with attributes like email, student number, and role.
- **`Book`:** Represents a book with attributes like title, author, published date, and availability status.
- **`BorrowRecord`:** Represents a borrowing record with attributes like email, student number, book title, borrow date, return date, and returned status.
- **`ReturnRecord`:** Represents a return record with attributes similar to `BorrowRecord`.
- **`Info`:** Represents additional member information like name, address, and contact number.

### Key Functions
- **`registerUser(const char* role)`:** Registers a new user (admin or user).
- **`loginUser(const char* role)`:** Logs in a user (admin or user).
- **`addBook()`:** Adds a new book to the library inventory.
- **`updateBook()`:** Updates book details.
- **`borrowBook()`:** Handles the borrowing process.
- **`returnBook()`:** Handles the returning process.
- **`viewBorrowedBooks(const char* email, const char* role)`:** Displays borrowed books for a user or all borrowed books for an admin.
- **`searchBooks()`:** Searches for books by title or author.
- **`searchinfo()`:** Searches for member information by email or student number.

---

## How to Run the Code

1. **Compile the Code:**
   - Use a C compiler (e.g., GCC) to compile the code:
     ```bash
     gcc -o library_management library_management.c
     ```

2. **Run the Executable:**
   - Run the compiled executable:
     ```bash
     ./library_management
     ```

3. **Follow the On-Screen Instructions:**
   - Use the menu options to register, log in, and perform various library management tasks.

---

## Conclusion

The **Library Management System** is a robust application that simplifies library operations for both admins and users. It ensures efficient management of books, members, and borrowing/returning processes while maintaining data persistence across sessions.

---

**Thank you for using the Library Management System!**
