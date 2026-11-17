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
    (void)id;
    (void)username;
    (void)bookId;
    (void)status;
}

Loan *findLoan(int id)
{
    (void)id;
    return NULL;
}

int hasActiveLoan(const char *username, int bookId)
{
    (void)username;
    (void)bookId;
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

