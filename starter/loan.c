/*
Done by: Anika

What we will do in this file:
- add loan to list
- find loan by id
- check if user has open loans
- show loans
- return book
*/

#include "library.h"

Loan *loanHead = NULL;
int nextLoanId = 1;

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

    if (id >= nextLoanId) {
        nextLoanId = id + 1;
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

int userHasActiveLoans(const char *username)
{
    (void)username;
    return 0;
}

void showLoans(const char *username)
{
    (void)username;
}

void returnBook(void)
{
}
