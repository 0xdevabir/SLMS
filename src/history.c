/*
 * history.c - the HISTORY STACK (a linked list: push on top, newest first)
 */
#include "library.h"

History *historyTop = NULL;   /* top of the history stack */

void pushHistory(const char *username, int bookId, const char *action, const char *date)
{
    History *node = newNode(sizeof(History));
    strcpy(node->username, username);
    node->bookId = bookId;
    strcpy(node->action, action);
    strcpy(node->date, date);
    node->next = historyTop;   /* new node sits on top of old top */
    historyTop = node;
}

/* Show history from top of stack (newest) to bottom (oldest).
 * username == NULL means "show everyone's". */
void showHistory(const char *username)
{
    int count = 0;
    History *temp = historyTop;
    while (temp != NULL) {
        if (username == NULL || strcmp(temp->username, username) == 0) {
            if (count == 0) {
                printf("\n%-17s %-15s %-9s %-8s %-25s\n", "Date", "Student", "Action", "BookID", "Title");
                printf("-------------------------------------------------------------------------------\n");
            }
            Book *b = findBook(temp->bookId);
            printf("%-17s %-15s %-9s %-8d %-25.25s\n", temp->date, temp->username,
                   temp->action, temp->bookId, b ? b->title : "(deleted book)");
            count++;
        }
        temp = temp->next;
    }
    if (count == 0) printf("\nNo history found.\n");
}

/* Staff: see the history of one student, or of everyone */
void viewStudentHistory(void)
{
    char username[30];
    readLine("Enter student username (or ALL): ", username, sizeof(username));
    if (strcmp(username, "ALL") == 0 || strcmp(username, "all") == 0) {
        showHistory(NULL);
    } else {
        showHistory(username);
    }
}
