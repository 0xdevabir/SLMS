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
    int count = 0;
    History *temp = historyTop;

    while (temp != NULL) {
        if (username == NULL || strcmp(temp->username, username) == 0) {
            Book *b = findBook(temp->bookId);
            if (count == 0) {
                printf("\n%-17s %-15s %-8s %-8s %-25s\n",
                       "Date", "Student", "Action", "BookID", "Title");
                printf("--------------------------------------------------------------------\n");
            }
            printf("%-17s %-15s %-8s %-8d %-25.25s\n",
                   temp->date, temp->username, temp->action, temp->bookId,
                   b ? b->title : "(gone)");
            count++;
        }
        temp = temp->next;
    }

    if (count == 0) {
        printf("\nNo history yet.\n");
    }
}
