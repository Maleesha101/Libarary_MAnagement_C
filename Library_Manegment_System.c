#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_USERS 1000
#define MAX_BOOKS 1000
#define MAX_BORROWS 1000
#define EMAIL_LENGTH 50
#define STUDENT_NUMBER_LENGTH 15
#define ROLE_LENGTH 15
#define TITLE_LENGTH 100
#define AUTHOR_LENGTH 50
#define DATE_LENGTH 11
#define ADMIN_KEYWORD "123456"
#define BORROW_PERIOD 14 // Borrow period in days

typedef struct {
    char email[EMAIL_LENGTH];
    char studentNumber[STUDENT_NUMBER_LENGTH];
    char name[EMAIL_LENGTH];
    char address[STUDENT_NUMBER_LENGTH];
    int contact;
} Info;

typedef struct {
    char email[EMAIL_LENGTH];
    char studentNumber[STUDENT_NUMBER_LENGTH];
    char role[ROLE_LENGTH]; // "admin" or "user"
} User;

typedef struct {
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    char publishedDate[DATE_LENGTH];
    int isBorrowed; // 0 if not borrowed, 1 if borrowed
} Book;

typedef struct {
    char email[EMAIL_LENGTH];
    char studentNumber[STUDENT_NUMBER_LENGTH];
    char bookTitle[TITLE_LENGTH];
    char borrowDate[DATE_LENGTH];
    char returnDate[DATE_LENGTH];
    int isReturned; // 0 if not returned, 1 if returned
} BorrowRecord;
typedef struct {
    char email[EMAIL_LENGTH];
    char studentNumber[STUDENT_NUMBER_LENGTH];
    char bookTitle[TITLE_LENGTH];
    char borrowDate[DATE_LENGTH];
    char returnDate[DATE_LENGTH];
    int isReturned; // 0 if not returned, 1 if returned
} ReturnRecord;
//Login
void registerUser(const char* role);
void loginUser(const char* role);
int isUserRegistered(const char* email, const char* studentNumber, const char* role);
int isEmailRegistered(const char* email);
int isStudentNumberRegistered(const char* studentNumber);
void saveUser(User user);
void loadUsers();
void adminPage(const char* email, const char* role );
void userPage(const char* email, const char* role );




//inventory management
void bookManagementPage(const char* email, const char* role );
void addBook();
void updateBook();
void saveBook(Book book);
void saveAllBooks();

//member management
void memberManagementPage();
void updateMemberInformations();
void otherInformations();
void searchinfo();
void saveInfo(Info info);
void loadinfo();


//borrowing and returing
void borrowAndReturnBooks(const char* email, const char* role );
void borrowBook();
void returnBook();
void viewBorrowedBooks(const char* email, const char* role );
void saveBorrowRecord(BorrowRecord record);
void saveReturnRecord(ReturnRecord record);
void loadBorrowRecords();
void loadReturnRecords();
int calculateDaysLeft(const char* date1, const char* date2);

//Search
void searchBooks();
void viewAllBooks();
void loadBooks();



User users[MAX_USERS];
Info infos[MAX_USERS];
Book books[MAX_BOOKS];
BorrowRecord borrows[MAX_BORROWS];
ReturnRecord returns[MAX_BORROWS];
int userCount = 0;
int infoCount = 0;
int bookCount = 0;
int borrowCount = 0;
int returnsCount = 0;



int main() {
    int choice;

    loadUsers();
    loadBooks();
    loadinfo();
    loadBorrowRecords();
    loadReturnRecords();
    while (1) {
        printf("----------------------------------\n");
        printf(">>> Library Management System <<< \n");
        printf("----------------------------------\n\n");
        printf("> 1. Register as Admin\n");
        printf("> 2. Register as User\n");
        printf("> 3. Login as Admin\n");
        printf("> 4. Login as User\n");
        printf("> 5. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser("admin");
                break;
            case 2:
                registerUser("user");
                break;
            case 3:
                loginUser("admin");
                break;
            case 4:
                loginUser("user");
                break;
            case 5:
                exit(0);
            default:
                printf("\n>>> Invalid choice. Please try again. <<<\n");
        }
    }
    return 0;
}

void registerUser(const char* role) {
    system("cls");
    fflush(stdin);

    User newUser;
    char keyword[20];

    printf("Enter your email: ");
    scanf("%s", newUser.email);

    if (isEmailRegistered(newUser.email)) {
        printf("\n>>> Email already registered. <<<\n\n");
        return;
    }

    if (strcmp(role, "admin") == 0) {
        printf("Enter the admin keyword: ");
        scanf("%s", keyword);
        if (strcmp(keyword, ADMIN_KEYWORD) != 0) {
            printf("\n>>> Invalid admin keyword. <<<\n\n");
            return;
        }
    } else {
        printf("Enter your student number (e.g., EC/2018/005): ");
        scanf("%s", newUser.studentNumber);
        if (isStudentNumberRegistered(newUser.studentNumber)) {
            printf("\n>>> Student number already registered. <<<\n\n");
            return;
        }
    }

    strcpy(newUser.role, role);
    saveUser(newUser);
    printf("\n>>> %s registration successful. <<<\n\n", role);
    return;
}

void loginUser(const char* role) {
    loadUsers();
    char email[EMAIL_LENGTH];
    char studentNumber[STUDENT_NUMBER_LENGTH] = "";
    char keyword[20];

    printf("Enter your email: ");
    scanf("%s", email);

    if (strcmp(role, "admin") == 0) {
        printf("Enter the admin keyword: ");
        scanf("%s", keyword);
        if (strcmp(keyword, ADMIN_KEYWORD) != 0) {
            printf("\n>>> Invalid admin keyword. <<<\n");
            return;
        }
    } else {
        printf("Enter your student number: ");
        scanf("%s", studentNumber);
    }

    if (isUserRegistered(email, studentNumber, role)) {
        
        if (strcmp(role, "admin") == 0) {
            adminPage(email, role);
        } else {
            userPage(email, role);
        }
    } else {
        printf("\n>>> Login failed. %s not found. <<<\n", role);
    }
}

int isUserRegistered(const char* email, const char* studentNumber, const char* role) {
    
    for (int i = 0; i < userCount; i++) {
        if (strlen(users[i].studentNumber) > 0) {
            if (strcmp(users[i].email, email) == 0 && strcmp(users[i].studentNumber, studentNumber) == 0 && strcmp(users[i].role, role)) {
                return 1;
            }
            
        } else {
            if (strcmp(users[i].email, email) == 0 && strcmp(users[i].role, role)) {
                return 1;
            }
        }
        
        }
    
    return 0;
}

int isEmailRegistered(const char* email) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}

int isStudentNumberRegistered(const char* studentNumber) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].studentNumber, studentNumber) == 0) {
            return 1;
        }
    }
    return 0;
}

void saveUser(User user) {
    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    if (strcmp(user.role, "admin") == 0) {
        fprintf(file, "%s;%s\n", user.email, user.role);
    } else {
        fprintf(file, "%s;%s;%s\n", user.email, user.studentNumber, user.role);
    }
    
    fclose(file);

    users[userCount++] = user;
}

void loadUsers() {
    User user;
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        return;  
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *email = strtok(line, ";");
        char *studentNo = strtok(NULL, ";");
        char *role = strtok(NULL, ";");

        if (email != NULL) {
            
            strcpy(user.email, email);
        }
        if (studentNo != NULL) {
            if (role != NULL) {
                
                strcpy(user.studentNumber, studentNo);
                strcpy(user.role, role);
            } else {
                
                strcpy(user.role, studentNo);
                user.studentNumber[0] = '\0';  
            }
        }

        users[userCount] = user;
        userCount++;
    }
    

    fclose(file);
    
}

void adminPage(const char* email, const char* role ) {
    system("cls");

    int choice;
    while (1) {
        printf("----------------------------------------------\n");
        printf(">>>       Login successful. Welcome!       <<<\n");
        printf(">>> Library Management System - Admin Page <<<\n");
        printf("----------------------------------------------\n\n");
        printf("> 1. Search Books\n");
        printf("> 2. Book Management\n");
        printf("> 3. Member Management\n");
        printf("> 4. Logout\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchBooks();
                break;
            case 2:
                bookManagementPage(email, role);
                break;
            case 3:
                memberManagementPage();
                break;
            case 4:
                system("cls");
                return;
            default:
                printf("\n>>> Invalid choice. Please try again. <<<\n");
        }
    }

}

void userPage(const char* email, const char* role ) {
    system("cls");

    int choice;
    

    while (1) {
        printf("---------------------------------------------\n");
        printf(">>>       Login successful. Welcome!      <<<\n");
        printf(">>> Library Management System - User Page <<<\n");
        printf("---------------------------------------------\n\n");
        printf("> 1. Search Books\n");
        printf("> 2. View All Books\n");
        printf("> 3. View Borrowed Books\n");
        printf("> 4. Logout\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchBooks();
                break;
            case 2:
                viewAllBooks();
                break;
            case 3:
                viewBorrowedBooks(email, role);
                break;
            case 4:
                system("cls");
                return;
            default:
                printf("\n>>> Invalid choice. Please try again. <<<\n");
        }
    }
}

void memberManagementPage(){
    system("cls");

    int choice;
    

    while (1) {
        printf("----------------------------------------------------------\n");
        printf(">>> Library Management System - Member Management Page <<<\n");
        printf("----------------------------------------------------------\n\n");
        printf("> 1. Register as Admin\n");
        printf("> 2. Register as User\n");
        printf("> 3. Update Member Informations\n");
        printf("> 4. Add other Member Informations\n");
        printf("> 5. Search Informations\n");
        printf("> 6. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser("admin");
                break;
            case 2:
                registerUser("user");
                break;
            case 3:
                updateMemberInformations();
                break;
            case 4:
                otherInformations();
                break;
            case 5:
                searchinfo();
                break;
            case 6:
                system("cls");
                return;
            default:
                printf("\n>>> Invalid choice! Please try again... <<<\n");
        }
    }

}

void updateMemberInformations(){
    system("cls");

    char email[EMAIL_LENGTH];
    int found = 0;

    printf("Enter the email of the user you want to update: ");
    getchar();
    fgets(email, EMAIL_LENGTH, stdin);
    email[strcspn(email, "\n")] = '\0'; 

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0) {
            printf("--------------------------------------\n");
            printf(">>> user found. Enter new details. <<<\n");
            printf("--------------------------------------\n\n");
            if(strcmp(users[i].role, "admin\n") == 0){

                printf("Enter the new email: ");
                fgets(users[i].email, sizeof(users[i].email), stdin);
                users[i].email[strcspn(users[i].email, "\n")] = '\0'; 

            }else if(strcmp(users[i].role, "user\n") == 0){
                printf("Enter the new email: ");
                fgets(users[i].email, sizeof(users[i].email), stdin);
                users[i].email[strcspn(users[i].email, "\n")] = '\0'; 

                printf("Enter the new Student number: ");
                fgets(users[i].studentNumber, sizeof(users[i].studentNumber), stdin);
                users[i].studentNumber[strcspn(users[i].studentNumber, "\n")] = '\0'; 
            }else{
                printf(">>> Role not recognized. No changes allowed. <<<\n");
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf(">>> User not found. <<<\n");
    }else{
        FILE *file; 
        file =fopen("users.txt", "w");
        for (int i = 0; i < userCount; i++) {
            if(strlen(users[i].studentNumber) > 0){
                fprintf(file, "%s;%s;%s", users[i].email, users[i].studentNumber, users[i].role);
            }else{
                fprintf(file, "%s;%s", users[i].email, users[i].role);
            }
        }
        fclose(file);
        printf(">>> user updated successfully! <<<\n");
    }
    
    printf("\nEnter any key to get back to Member Management Page.\n");
    getchar();
    system("cls");
    return;
}

void otherInformations(){
    system("cls");
    fflush(stdin);

    Info newinfo;
    char email[EMAIL_LENGTH];
    char studentNumber[STUDENT_NUMBER_LENGTH];
    char name[EMAIL_LENGTH];
    char add[EMAIL_LENGTH];
    int cont;
    int found = 0;
    char c;

    printf("Enter email: ");
    scanf("%s", email);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0) {
            printf("----------------------------------------\n");
            printf(">>> user found. Enter other details. <<<\n");
            printf("----------------------------------------\n\n");
            printf("Enter Name:\n"); 
            scanf("%s",name);
            printf("Enter Address:\n");
            scanf("%s",add);
            printf("Enter Contact number:\n");
            scanf("%d",&cont);
            strcpy(newinfo.studentNumber, users[i].studentNumber);
        }
    }
    strcpy(newinfo.email, email);
    strcpy(newinfo.name, name);
    strcpy(newinfo.address, add);
    newinfo.contact = cont;

    saveInfo(newinfo);
    printf("\n\n>>> Informes added successfully! <<<\n\n");

    printf("\nEnter any key to get back.\n");
    scanf("%s",&c);
    system("cls");
    return;

}

void searchBooks(){
    system("cls");
    char title_author[TITLE_LENGTH];
    int found = 0;

    printf("Enter Book Title or Author: ");
    getchar(); 
    fgets(title_author, TITLE_LENGTH, stdin);
    title_author[strcspn(title_author, "\n")] = '\0'; 

    for (int i = 0; i < bookCount; i++) {
        if(strcmp(books[i].title, title_author) == 0 || strcmp(books[i].author, title_author)==0 ){
                printf("\n-------------------\n");
                printf(">>> Book Found <<< \n");
                printf("-------------------\n\n");
                printf("Title: %s, Author: %s, Published Date: %s, Status: %s\n",
               books[i].title, books[i].author, books[i].publishedDate,
               books[i].isBorrowed ? "Borrowed" : "Available");
               found = 1;
               break;
        }
    }
    if(bookCount == 0){
            printf("------------------------------\n");
            printf("There is no books added yet...\n");
            printf("------------------------------\n\n");
        }else if(!found){
            printf("\n>>> Book Not Found <<< \n\n");
        }
    printf("\nEnter any key to get back.\n");
    getchar();
    system("cls");
    return;
}

void searchinfo(){
    system("cls");

    char email_no[EMAIL_LENGTH];
    int found = 0;

    printf("Enter user email or Student number: ");
    getchar(); 
    fgets(email_no, EMAIL_LENGTH, stdin);
    email_no[strcspn(email_no, "\n")] = '\0'; 

    for (int i = 0; i < infoCount; i++) {
        if(strcmp(infos[i].email, email_no) == 0 || strcmp(infos[i].studentNumber, email_no) == 0){
                printf("\n-----------------------\n");
                printf(">>> Informes Found <<< \n");
                printf("-----------------------\n\n");
                printf("Email: %s,Student number: %s, Name: %s, Address: %s, Contact Number: +94%d\n",
               infos[i].email, infos[i].studentNumber, infos[i].name, infos[i].address, infos[i].contact);
               found = 1;
               break;
        }
    }

    if(infoCount == 0){
            printf("------------------------------\n");
            printf("There is no Informes added yet...\n");
            printf("------------------------------\n\n");
        }else if(!found){
            printf("\n>>> Informes Not Found <<< \n\n");
        }
    
    printf("\nEnter any key to get back to Member Management Page.\n");
    getchar();
    system("cls");
    return;
}

void bookManagementPage(const char* email, const char* role ) {
    system("cls");

    int choice;
    while (1) {
        printf("--------------------------------------------------------\n");
        printf(">>> Library Management System - Book Management Page <<<\n");
        printf("--------------------------------------------------------\n\n");
        printf("> 1. Add Books\n");
        printf("> 2. Update Books\n");
        printf("> 3. View All Books\n");
        printf("> 4. Borrowing and Returning\n");
        printf("> 5. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                updateBook();
                break;
            case 3:
                viewAllBooks();
                break;
            case 4:
                borrowAndReturnBooks(email, role); 
                break;
            case 5:
                system("cls");
                return;
            default:
                printf(">>> Invalid choice. Please try again. <<<\n");
        }
    }
}

void addBook() {
    system("cls");

    Book newBook;

    printf("Enter the book title: ");
    getchar(); 
    fgets(newBook.title, TITLE_LENGTH, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; 

    printf("Enter the author name: ");
    fgets(newBook.author, AUTHOR_LENGTH, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0'; 

    printf("Enter the published Year: ");
    fgets(newBook.publishedDate, DATE_LENGTH, stdin);
    newBook.publishedDate[strcspn(newBook.publishedDate, "\n")] = '\0'; 

    newBook.isBorrowed = 0; 

    saveBook(newBook);
    printf("\n--------------------------------\n");
    printf(">>> Book added successfully! <<<\n", newBook.title, newBook.author);
    printf("--------------------------------\n");

    printf("\nEnter any key to get back to Book Management Page.\n");
    getchar();
    system("cls");
    return;
}

void updateBook() {
    system("cls");

    char title[TITLE_LENGTH];
    int found = 0;

    printf("Enter the title of the book you want to update: ");
    getchar(); 
    fgets(title, TITLE_LENGTH, stdin);
    title[strcspn(title, "\n")] = '\0'; 

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
            printf("\n--------------------------------------\n");
            printf(">>> Book found. Enter new details. <<<\n");
            printf("--------------------------------------\n\n");

            printf("Enter the new book title: ");
            fgets(books[i].title, TITLE_LENGTH, stdin);
            books[i].title[strcspn(books[i].title, "\n")] = '\0'; 
            printf("Enter the new author name: ");
            fgets(books[i].author, AUTHOR_LENGTH, stdin);
            books[i].author[strcspn(books[i].author, "\n")] = '\0'; 

            printf("Enter the new published Year: ");
            fgets(books[i].publishedDate, DATE_LENGTH, stdin);
            books[i].publishedDate[strcspn(books[i].publishedDate, "\n")] = '\0'; 

            saveAllBooks();
            printf("\n----------------------------------\n");
            printf(">>> Book updated successfully! <<<\n");
            printf("----------------------------------\n");
            found = 1;
            break;
        }
    }
    if(bookCount == 0){
        printf("------------------------------\n");
        printf("There is no Books added yet...\n");
        printf("------------------------------\n\n");
    }
    else if (!found) {
        printf(">>> Book not found. <<<\n", title);
    }

    printf("\nEnter any key to get back to Book Management Page.\n");
    getchar();
    system("cls");
    return;
}

void borrowAndReturnBooks(const char* email, const char* role ) {
    system("cls");

    int choice;
    while (1) {
        printf("--------------------------------------\n");
        printf(">>> Borrowing and Returning Page <<<\n");
        printf("--------------------------------------\n\n");
        printf("> 1. Borrow a Book\n");
        printf("> 2. Return a Book\n");
        printf("> 3. View Borrowed Books\n");
        printf("> 4. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                borrowBook();
                break;
            case 2:
                returnBook();
                break;
            case 3:
                viewBorrowedBooks(email, role);
                break;
            case 4:
                system("cls");
                return;
            default:
                printf(">>> Invalid choice. Please try again. <<<\n");
        }
    }
}

void borrowBook() {
    system("cls");

    char title[TITLE_LENGTH];
    int found = 0;
    BorrowRecord newBorrow;
    char email[EMAIL_LENGTH];
    char studentNumber[STUDENT_NUMBER_LENGTH];

    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your Student number: ");
    scanf("%s", studentNumber);
    printf("Enter the title of the book you want to borrow: ");
    getchar(); 
    fgets(title, TITLE_LENGTH, stdin);
    title[strcspn(title, "\n")] = '\0'; 

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, title) == 0 && books[i].isBorrowed == 0) {
            books[i].isBorrowed = 1;
            strcpy(newBorrow.email, email);
            strcpy(newBorrow.studentNumber, studentNumber);
            strcpy(newBorrow.bookTitle, books[i].title);

            // Get current date
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            snprintf(newBorrow.borrowDate, DATE_LENGTH, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

            // Calculate return date (2 weeks later)
            tm.tm_mday += BORROW_PERIOD;
            mktime(&tm);  // Normalize the tm structure
            snprintf(newBorrow.returnDate, DATE_LENGTH, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

            newBorrow.isReturned = 0;

            saveAllBooks();
            saveBorrowRecord(newBorrow);
            printf("\n----------------------------------------------------\n");
            printf("Book borrowed successfully! Return by %s.\n",newBorrow.returnDate);
            printf("----------------------------------------------------\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf(">>> Book with title '%s' is not available for borrowing. <<<\n", title);
    }

    printf("\nEnter any key to get back to Borrowing and Returning Page.\n");
    getchar();
    system("cls");
    return;
}

void returnBook() {
    system("cls");

    char title[TITLE_LENGTH];
    int found = 0;
    ReturnRecord newReturn;
    char email[EMAIL_LENGTH];
    char studentNumber[STUDENT_NUMBER_LENGTH];

    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your Student number: ");
    scanf("%s", studentNumber);

    printf("Enter the title of the book you want to return: ");
    getchar(); 
    fgets(title, TITLE_LENGTH, stdin);
    title[strcspn(title, "\n")] = '\0'; 

    for (int i = 0; i < borrowCount; i++) {
        if (strcmp(borrows[i].email, email) == 0 && strcmp(borrows[i].studentNumber, studentNumber) == 0 && strcmp(borrows[i].bookTitle, title) == 0 && borrows[i].isReturned == 0) {

            for (int j = 0; j < bookCount; j++) {
                if (strcmp(books[j].title, title) == 0) {
                    books[j].isBorrowed = 0;
                    break;
                }
            }
            strcpy(newReturn.email, email);
            strcpy(newReturn.studentNumber, studentNumber);
            strcpy(newReturn.bookTitle, title);
            strcpy(newReturn.borrowDate, borrows[i].borrowDate);

            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            snprintf(newReturn.returnDate, DATE_LENGTH, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
            newReturn.isReturned = 1;

            saveAllBooks();
            saveReturnRecord(newReturn);
            printf("\n---------------------------\n");
            printf("Book returned successfully!\n");
            printf("---------------------------\n");

            found = 1;
            break;
        }
    }

    if (!found) {
        printf(">>> No borrowed record found for book titled '%s'. <<<\n", title);
    }

    printf("\nEnter any key to get back to Borrowing and Returning Page.\n");
    getchar();
    system("cls");
    return;
}

void viewBorrowedBooks(const char* email, const char* role ) {
    system("cls");
    fflush(stdin);

    int found = 0;
    int find[1000];
    find[0] = 1;
    int x = 0;

    for (int i = 0; i < borrowCount; i++) {
            for(int j = 0; j < returnsCount; j++){
                    if(strcmp(borrows[i].email, returns[j].email) == 0 && strcmp(borrows[i].borrowDate, returns[j].borrowDate)==0 && strcmp(borrows[i].bookTitle, returns[j].bookTitle)==0){
                        find[i] = i;
                        break;
                }
            }
        } 

    if (strcmp(role, "admin") == 0)
    {
        printf("\n------------------------------\n");
        printf(">>> List of Borrowed Books <<<\n");
        printf("------------------------------\n\n");
        for(int i = 0;i<borrowCount;i++){
            if(i != find[i]){
                printf("Email: %s,StudentNumber: %s,Title: %s, Borrow Date: %s, Return Date: %s\n",borrows[i].email,borrows[i].studentNumber,
                    borrows[i].bookTitle, borrows[i].borrowDate, borrows[i].returnDate);

                // Calculate days left
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                char currentDate[DATE_LENGTH];
                snprintf(currentDate, DATE_LENGTH, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
                int daysLeft = calculateDaysLeft(currentDate, borrows[i].returnDate);

                printf("Days left to return: %d\n", daysLeft);

                found = 1;
                break;
            }
        }

    }else {
        printf("\n------------------------------\n");
        printf(">>> List of Borrowed Books <<<\n");
        printf("------------------------------\n\n");
        for (int i = 0; i < borrowCount; i++) {
                
                        if (strcmp(borrows[i].email, email) == 0 && i != find[i]) {
                    printf("Title: %s, Borrow Date: %s, Return Date: %s\n",
                        borrows[i].bookTitle, borrows[i].borrowDate, borrows[i].returnDate);

                    // Calculate days left
                    time_t t = time(NULL);
                    struct tm tm = *localtime(&t);
                    char currentDate[DATE_LENGTH];
                    snprintf(currentDate, DATE_LENGTH, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
                    int daysLeft = calculateDaysLeft(currentDate, borrows[i].returnDate);

                    printf("Days left to return: %d\n", daysLeft);

                    found = 1;
                    break;
                }

                
            
        }
    }
    
        
    if(borrowCount == 0){
        printf("---------------------------------------------\n");
        printf(">>> There is no borrow records added yet. <<<\n");
        printf("---------------------------------------------\n");
    }
    else if (!found) {
        printf(">>> No borrowed books found. <<<\n");
    }

    printf("\nEnter any key to get back.\n");
    getchar();
    system("cls");
    return;
}

void saveBook(Book book) {
    FILE *file = fopen("books.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fprintf(file, "%s;%s;%s;%d\n", book.title, book.author, book.publishedDate, book.isBorrowed);
    fclose(file);

    books[bookCount++] = book;
}

void saveAllBooks() {
    FILE *file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%s;%s;%s;%d\n", books[i].title, books[i].author, books[i].publishedDate, books[i].isBorrowed);
    }
    fclose(file);
}

void saveInfo(Info info){

    FILE *file = fopen("info.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fprintf(file, "%s;%s;%s;%s;%d\n",info.email,info.studentNumber, info.name, info.address, info.contact);
    fclose(file);

    infos[infoCount++] = info;
}


void loadBooks() {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        return;  
    }

    while (fscanf(file, "%[^;];%[^;];%[^;];%d\n", books[bookCount].title, books[bookCount].author, books[bookCount].publishedDate, &books[bookCount].isBorrowed) != EOF) {
        bookCount++;
    }
    fclose(file);
}

void loadinfo(){
    FILE *file = fopen("info.txt", "r");
    if (file == NULL) {
        return;  
    }

    while (fscanf(file, "%[^;];%[^;];%[^;];%[^;];%d\n", infos[infoCount].email, infos[infoCount].studentNumber, infos[infoCount].name, infos[infoCount].address, &infos[infoCount].contact) != EOF) {
        infoCount++;
    }
    fclose(file);

}

void saveBorrowRecord(BorrowRecord record) {
    FILE *file = fopen("borrows.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fprintf(file, "%s;%s;%s;%s;%s;%d\n", record.email, record.studentNumber, record.bookTitle, record.borrowDate, record.returnDate, record.isReturned);
    fclose(file);

    borrows[borrowCount++] = record;
}

void saveReturnRecord(ReturnRecord record) {
    FILE *file = fopen("return.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fprintf(file, "%s;%s;%s;%s;%s;%d\n", record.email, record.studentNumber, record.bookTitle, record.borrowDate, record.returnDate, record.isReturned);
    fclose(file);

    returns[returnsCount++] = record;
}

void loadBorrowRecords() {
    FILE *file = fopen("borrows.txt", "r");
    if (file == NULL) {
        return; 
    }

    while (fscanf(file, "%[^;];%[^;];%[^;];%[^;];%[^;];%d\n", borrows[borrowCount].email, borrows[borrowCount].studentNumber, borrows[borrowCount].bookTitle, borrows[borrowCount].borrowDate, borrows[borrowCount].returnDate, &borrows[borrowCount].isReturned) != EOF) {
        borrowCount++;
    }
    fclose(file);
}

void loadReturnRecords() {
    FILE *file = fopen("return.txt", "r");
    if (file == NULL) {
        return;  
    }

    while (fscanf(file, "%[^;];%[^;];%[^;];%[^;];%[^;];%d\n", returns[returnsCount].email, returns[returnsCount].studentNumber, returns[returnsCount].bookTitle, returns[returnsCount].borrowDate, returns[returnsCount].returnDate, &returns[returnsCount].isReturned) != EOF) {
        returnsCount++;
    }
    fclose(file);
}

int calculateDaysLeft(const char* date1, const char* date2) {
    struct tm tm1 = {0}, tm2 = {0};
    time_t time1, time2;

    sscanf(date1, "%d-%d-%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);
    sscanf(date2, "%d-%d-%d", &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday);

    tm1.tm_year -= 1900;
    tm1.tm_mon -= 1;
    tm2.tm_year -= 1900;
    tm2.tm_mon -= 1;

    time1 = mktime(&tm1);
    time2 = mktime(&tm2);

    double seconds = difftime(time2, time1);
    int days = (int)(seconds / (60 * 60 * 24));
    return days;
}

void viewAllBooks() {
    system("cls");
    fflush(stdin);

    printf("\n---------------------------\n");
    printf(">>> List of All Books <<<\n");
    printf("---------------------------\n\n");
    for (int i = 0; i < bookCount; i++) {
        printf("Title: %s, Author: %s, Published Date: %s, Status: %s\n",
               books[i].title, books[i].author, books[i].publishedDate,
               books[i].isBorrowed ? "Borrowed" : "Available");
    }

    printf("\nEnter any key to get back.\n");
    getchar();
    system("cls");
    return;
}
