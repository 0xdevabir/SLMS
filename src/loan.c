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
    Loan *temp = loanHead;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 &&
            temp->status == STATUS_BORROWED) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void showLoans(const char *username)
{
    int count = 0;
    Loan *temp = loanHead;

    while (temp != NULL) {
        if (username == NULL || strcmp(temp->username, username) == 0) {
            Book *b = findBook(temp->bookId);
            if (count == 0) {
                printf("\n%-7s %-15s %-8s %-25s %-10s\n",
                       "LoanID", "Student", "BookID", "Title", "Status");
                printf("--------------------------------------------------------------------\n");
            }
            printf("%-7d %-15s %-8d %-25.25s %-10s\n",
                   temp->id, temp->username, temp->bookId,
                   b ? b->title : "(gone)",
                   temp->status == STATUS_BORROWED ? "Borrowed" : "Returned");
            count++;
        }
        temp = temp->next;
    }

    if (count == 0) {
        printf("\nNo loans found.\n");
    }
}

void returnBook(void)
{
    showLoans(currentUser->username);

    int id = readInt("Loan ID to return: ");
    Loan *loan = findLoan(id);

    if (loan == NULL || strcmp(loan->username, currentUser->username) != 0) {
        printf("No such loan for you.\n");
        return;
    }
    if (loan->status != STATUS_BORROWED) {
        printf("Already returned.\n");
        return;
    }

    loan->status = STATUS_RETURNED;
    Book *b = findBook(loan->bookId);
    if (b != NULL) {
        b->available++;
    }

    {
        char date[20];
        getDate(date, sizeof(date));
        pushHistory(currentUser->username, loan->bookId, "RETURN", date);
    }
    printf("Book returned. Thank you!\n");
}
