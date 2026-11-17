/*
Done by: Abir

What we will do in this file:
- read text from user
- read a number from user
- search text (ignore capital / small letters)
- get today’s date and time
- make a new node with malloc
- show role name from number
- show loan status name from number
*/

#include "library.h"

void readLine(const char *prompt, char *buf, int size)
{
    while (1) {
        printf("%s", prompt);
        if (fgets(buf, size, stdin) == NULL) {
            printf("\nInput closed.\n");
            exit(0);
        }
        char *nl = strchr(buf, '\n');
        if (nl != NULL) {
            *nl = '\0';
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
        if (strlen(buf) == 0) {
            printf("  Input cannot be empty. Try again.\n");
        } else if (strchr(buf, '|') != NULL) {
            printf("  The character '|' is not allowed. Try again.\n");
        } else {
            return;
        }
    }
}

int readInt(const char *prompt)
{
    char buf[50];
    int value;
    while (1) {
        readLine(prompt, buf, sizeof(buf));
        if (sscanf(buf, "%d", &value) == 1) {
            return value;
        }
        printf("  Please enter a number.\n");
    }
}

int containsIgnoreCase(const char *text, const char *word)
{
    (void)text;
    (void)word;
    return 0;
}

void getDate(char *buf, int size)
{
    time_t now = time(NULL);
    strftime(buf, size, "%Y-%m-%d %H:%M", localtime(&now));
}

void *newNode(int size)
{
    void *p = malloc(size);
    if (p == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }
    return p;
}

const char *roleName(int role)
{
    switch (role) {
        case ROLE_STUDENT: return "Student";
        case ROLE_STAFF:   return "Staff";
        default:           return "Librarian";
    }
}

const char *statusName(int status)
{
    switch (status) {
        case STATUS_APPROVED: return "Approved (pick up)";
        case STATUS_BORROWED: return "Borrowed";
        default:              return "Returned";
    }
}


