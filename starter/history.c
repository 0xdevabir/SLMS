/*
Done by: Anika

What we will do in this file:
- push check-out / check-in on the stack
- show history (new ones first)
- let staff see one student’s history
*/

#include "library.h"

History *historyTop = NULL;

void pushHistory(const char *username, int bookId, const char *action, const char *date)
{
    History *node = newNode(sizeof(History));
    strcpy(node->username, username);
    node->bookId = bookId;
    strcpy(node->action, action);
    strcpy(node->date, date);
    node->next = historyTop;
    historyTop = node;
}

void showHistory(const char *username)
{
    (void)username;
}

void viewStudentHistory(void)
{
}
