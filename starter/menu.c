/*
Done by: Ardi

What we will do in this file:
- student menu
- staff menu
- librarian menu
- connect choices to functions
*/

#include "library.h"

void studentMenu(void)
{
    while (1) {
        printf("\n===== STUDENT MENU =====\n");
        printf("1. Show all books\n");
        printf("2. Search book\n");
        printf("3. Request a book\n");
        printf("4. My requests\n");
        printf("5. My loans\n");
        printf("6. Return a book\n");
        printf("7. My history\n");
        printf("0. Logout\n");

        switch (readInt("Choice: ")) {
            case 1:
                showAllBooks();
                break;
            case 2:
                searchBooks();
                break;
            case 3:
                requestBook();
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 0:
                return;
            default:
                printf("Invalid choice.\n");
        }
    }
}

void staffMenu(void)
{
    while (1) {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Show all books\n");
        printf("2. Search book\n");
        printf("3. View requests\n");
        printf("4. Approve / reject\n");
        printf("5. View loans\n");
        printf("6. View history\n");
        printf("0. Logout\n");

        switch (readInt("Choice: ")) {
            case 1:
                showAllBooks();
                break;
            case 2:
                searchBooks();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 0:
                return;
            default:
                printf("Invalid choice.\n");
        }
    }
}

void librarianMenu(void)
{
    while (1) {
        printf("\n===== LIBRARIAN MENU =====\n");
        printf("1. Show all books\n");
        printf("2. Search book\n");
        printf("3. View requests\n");
        printf("4. Approve / reject\n");
        printf("5. View loans\n");
        printf("6. View history\n");
        printf("7. Register user\n");
        printf("8. Delete user\n");
        printf("9. Show users\n");
        printf("10. Add book\n");
        printf("11. Delete book\n");
        printf("0. Logout\n");

        switch (readInt("Choice: ")) {
            case 1:
                showAllBooks();
                break;
            case 2:
                searchBooks();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                showAllUsers();
                break;
            case 10:
                newBook();
                saveAll();
                break;
            case 11:
                break;
            case 0:
                return;
            default:
                printf("Invalid choice.\n");
        }
    }
}
