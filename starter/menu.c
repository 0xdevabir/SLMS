/*
Done by: Ardi

What we will do in this file:
- make student menu
- make staff menu
- make librarian menu
- connect each menu choice to the right function
- save data after changes
*/

#include "library.h"

void studentMenu(void)
{
    while (1) {
        printf("\n===== STUDENT MENU =====\n");
        printf("1. Show all books\n");
        printf("2. Search book\n");
        printf("3. Add book to cart\n");
        printf("4. Remove from cart\n");
        printf("5. Show my cart\n");
        printf("6. Submit cart (borrow requests)\n");
        printf("7. My requests\n");
        printf("8. Check out approved book\n");
        printf("9. Check in (return) book\n");
        printf("10. My loans\n");
        printf("11. My history\n");
        printf("0. Logout\n");

        switch (readInt("Choice: ")) {
            case 1:
                break;
            case 2:
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
                break;
            case 10:
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

void staffMenu(void)
{
    while (1) {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Show all books\n");
        printf("2. Search book\n");
        printf("3. Check stock\n");
        printf("4. View pending requests\n");
        printf("5. Approve / reject requests\n");
        printf("6. View history\n");
        printf("7. Books currently with students\n");
        printf("0. Logout\n");

        switch (readInt("Choice: ")) {
            case 1:
                break;
            case 2:
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
        printf("--- Staff features ---\n");
        printf(" 1. Show all books\n");
        printf(" 2. Search book\n");
        printf(" 3. Check stock\n");
        printf(" 4. View pending requests\n");
        printf(" 5. Approve / reject requests\n");
        printf(" 6. View history\n");
        printf(" 7. Books with students\n");
        printf("--- Librarian features ---\n");
        printf(" 8. Register user\n");
        printf(" 9. Delete user\n");
        printf("10. Show all users\n");
        printf("11. Add book\n");
        printf("12. Delete book\n");
        printf("13. Update copies\n");
        printf(" 0. Logout\n");

        switch (readInt("Choice: ")) {
            case 1:
                break;
            case 2:
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
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                break;
            case 0:
                return;
            default:
                printf("Invalid choice.\n");
        }
    }
}

