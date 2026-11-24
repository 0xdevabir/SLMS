/*
Done by: Anika

What we will do in this file:
- push borrow / return on stack
- show history (newest first)
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
