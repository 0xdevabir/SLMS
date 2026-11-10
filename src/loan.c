/*
 * loan.c - the LOAN LINKED LIST, check-out and check-in
 */
#include "library.h"

Loan *loanHead = NULL;   /* first node of the loan list */

void addLoan(int id, const char *username, int bookId, int status)
{
    Loan *node = newNode(sizeof(Loan));
    node->id = id;
    strcpy(node->username, username);
    node->bookId = bookId;
    node->status = status;
    node->next = NULL;

    if (loanHead == NULL) {
        loanHead = node;
    } else {
        Loan *temp = loanHead;
        while (temp->next != NULL) temp = temp->next;
        temp->next = node;
    }
    if (id >= nextRequestId) nextRequestId = id + 1;
}

Loan *findLoan(int id)
{
    Loan *temp = loanHead;
    while (temp != NULL) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return NULL;
}

/* Returns 1 if this user still has this book (approved or borrowed) */
int hasActiveLoan(const char *username, int bookId)
{
    Loan *temp = loanHead;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 && temp->bookId == bookId &&
            temp->status != STATUS_RETURNED) return 1;
        temp = temp->next;
    }
    return 0;
}

/* Returns 1 if this user still has ANY book (approved or borrowed) */
int userHasActiveLoans(const char *username)
{
    Loan *temp = loanHead;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 && temp->status != STATUS_RETURNED) return 1;
        temp = temp->next;
    }
    return 0;
}

/* Show loans. username == NULL means everyone. onlyActive == 1 hides returned ones. */
void showLoans(const char *username, int onlyActive)
{
    int count = 0;
    Loan *temp = loanHead;
    while (temp != NULL) {
        int userOk   = (username == NULL || strcmp(temp->username, username) == 0);
        int statusOk = (!onlyActive || temp->status != STATUS_RETURNED);
        if (userOk && statusOk) {
            if (count == 0) {
                printf("\n%-7s %-15s %-8s %-28s %-18s\n", "LoanID", "Student", "BookID", "Title", "Status");
                printf("-------------------------------------------------------------------------------\n");
            }
            Book *b = findBook(temp->bookId);
            printf("%-7d %-15s %-8d %-28.28s %-18s\n", temp->id, temp->username, temp->bookId,
                   b ? b->title : "(deleted book)", statusName(temp->status));
            count++;
        }
        temp = temp->next;
    }
    if (count == 0) printf("\nNo loans found.\n");
}

/* Student picks up an approved book */
void checkOutBook(void)
{
    showLoans(currentUser->username, 1);
    int id = readInt("Enter Loan ID to check out (pick up): ");
    Loan *loan = findLoan(id);
    if (loan == NULL || strcmp(loan->username, currentUser->username) != 0) {
        printf("No such loan for you.\n");
        return;
    }
    if (loan->status != STATUS_APPROVED) {
        printf("This loan is not waiting for pick up.\n");
        return;
    }
    char date[20];
    getDate(date, sizeof(date));
    loan->status = STATUS_BORROWED;
    pushHistory(currentUser->username, loan->bookId, "CHECKOUT", date);
    printf("Book checked out. Enjoy reading!\n");
}

/* Student returns a borrowed book */
void checkInBook(void)
{
    showLoans(currentUser->username, 1);
    int id = readInt("Enter Loan ID to check in (return): ");
    Loan *loan = findLoan(id);
    if (loan == NULL || strcmp(loan->username, currentUser->username) != 0) {
        printf("No such loan for you.\n");
        return;
    }
    if (loan->status != STATUS_BORROWED) {
        printf("This book is not checked out.\n");
        return;
    }
    char date[20];
    getDate(date, sizeof(date));
    loan->status = STATUS_RETURNED;
    Book *b = findBook(loan->bookId);
    if (b != NULL) b->available++;          /* copy goes back on the shelf */
    pushHistory(currentUser->username, loan->bookId, "CHECKIN", date);
    printf("Book checked in. Thank you!\n");
}
