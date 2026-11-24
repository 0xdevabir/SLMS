/*
Done by: Anika

What we will do in this file:
- add a loan
- find loan by id
- check if user already has that book
- check if user has any open loan
- show loans
- check out book (take book)
- check in book (return book)
*/

#include "library.h"

Loan *loanHead = NULL;

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
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
    if (id >= nextRequestId) {
        nextRequestId = id + 1;
    }
}

Loan *findLoan(int id)
{
    Loan *temp = loanHead;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int hasActiveLoan(const char *username, int bookId)
{
    Loan *temp = loanHead;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 &&
            temp->bookId == bookId &&
            temp->status != STATUS_RETURNED) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int userHasActiveLoans(const char *username)
{
    (void)username;
    return 0;
}

void showLoans(const char *username, int onlyActive)
{
    (void)username;
    (void)onlyActive;
}

void checkOutBook(void)
{
}

void checkInBook(void)
{
}
