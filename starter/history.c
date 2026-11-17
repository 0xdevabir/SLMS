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
    (void)username;
    (void)bookId;
    (void)action;
    (void)date;
}

void showHistory(const char *username)
{
    (void)username;
}

void viewStudentHistory(void)
{
}

