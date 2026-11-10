/*
 * menu.c - the three menus. Each one: print options, read a number,
 *          and a switch calls the right function.
 */
#include "library.h"

void studentMenu(void)
{
    while (1) {
        printf("\n===== STUDENT MENU (%s) =====\n", currentUser->name);
        printf(" 1. Show all books\n");
        printf(" 2. Search book\n");
        printf(" 3. Add book to cart\n");
        printf(" 4. Remove book from cart\n");
        printf(" 5. View cart\n");
        printf(" 6. Send borrow request (submit cart)\n");
        printf(" 7. My pending requests\n");
        printf(" 8. My books (loans)\n");
        printf(" 9. Check out (pick up approved book)\n");
        printf("10. Check in (return book)\n");
        printf("11. My history\n");
        printf(" 0. Logout\n");

        switch (readInt("Choice: ")) {
            case 1:  showAllBooks(); break;
            case 2:  searchBooks(); break;
            case 3:  addToCart(); break;
            case 4:  removeFromCart(); break;
            case 5:  showCart(); break;
            case 6:  submitCart(); break;
            case 7:  showRequests(currentUser->username); break;
            case 8:  showLoans(currentUser->username, 0); break;
            case 9:  checkOutBook(); break;
            case 10: checkInBook(); break;
            case 11: showHistory(currentUser->username); break;
            case 0:  clearCart(); return;
            default: printf("Invalid choice.\n");
        }
        saveAll();
    }
}

void staffMenu(void)
{
    while (1) {
        printf("\n===== STAFF MENU (%s) =====\n", currentUser->name);
        printf(" 1. Show all books\n");
        printf(" 2. Search book\n");
        printf(" 3. Check stock of a book\n");
        printf(" 4. View pending borrow requests\n");
        printf(" 5. Approve / reject requests\n");
        printf(" 6. View check-in / check-out history\n");
        printf(" 7. View books currently with students\n");
        printf(" 0. Logout\n");

        switch (readInt("Choice: ")) {
            case 1: showAllBooks(); break;
            case 2: searchBooks(); break;
            case 3: checkStock(); break;
            case 4: showRequests(NULL); break;
            case 5: processRequests(); break;
            case 6: viewStudentHistory(); break;
            case 7: showLoans(NULL, 1); break;
            case 0: return;
            default: printf("Invalid choice.\n");
        }
        saveAll();
    }
}

void librarianMenu(void)
{
    while (1) {
        printf("\n===== LIBRARIAN MENU (%s) =====\n", currentUser->name);
        printf("--- Staff features ---\n");
        printf(" 1. Show all books\n");
        printf(" 2. Search book\n");
        printf(" 3. Check stock of a book\n");
        printf(" 4. View pending borrow requests\n");
        printf(" 5. Approve / reject requests\n");
        printf(" 6. View check-in / check-out history\n");
        printf(" 7. View books currently with students\n");
        printf("--- Librarian features ---\n");
        printf(" 8. Register new student / staff\n");
        printf(" 9. Delete a user\n");
        printf("10. Show all users\n");
        printf("11. Add new book\n");
        printf("12. Delete book\n");
        printf("13. Update number of copies\n");
        printf(" 0. Logout\n");

        switch (readInt("Choice: ")) {
            case 1:  showAllBooks(); break;
            case 2:  searchBooks(); break;
            case 3:  checkStock(); break;
            case 4:  showRequests(NULL); break;
            case 5:  processRequests(); break;
            case 6:  viewStudentHistory(); break;
            case 7:  showLoans(NULL, 1); break;
            case 8:  registerUser(); break;
            case 9:  removeUser(); break;
            case 10: showAllUsers(); break;
            case 11: newBook(); break;
            case 12: removeBook(); break;
            case 13: updateCopies(); break;
            case 0:  return;
            default: printf("Invalid choice.\n");
        }
        saveAll();
    }
}
