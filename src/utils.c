/*
 * utils.c - small helper functions used by every other file
 */
#include "library.h"

/* Read one line of text. Never empty, and never contains '|'
 * (because '|' is used to separate fields inside our files). */
void readLine(const char *prompt, char *buf, int size)
{
    while (1) {
        printf("%s", prompt);
        if (fgets(buf, size, stdin) == NULL) {   /* input ended (Ctrl+D) */
            printf("\nInput closed. Saving and exiting.\n");
            saveAll();
            exit(0);
        }
        char *nl = strchr(buf, '\n');
        if (nl != NULL) {
            *nl = '\0';                  /* remove the Enter key   */
        } else {
            int c;                        /* line too long: throw  */
            while ((c = getchar()) != '\n' && c != EOF) { } /* the rest away */
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

/* Read a whole number (int). Keeps asking until the user types one. */
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

/* Returns 1 if 'word' is found inside 'text' (ignoring capital letters) */
int containsIgnoreCase(const char *text, const char *word)
{
    char a[100], b[100];
    int i;
    for (i = 0; text[i] != '\0' && i < 99; i++) a[i] = tolower((unsigned char)text[i]);
    a[i] = '\0';
    for (i = 0; word[i] != '\0' && i < 99; i++) b[i] = tolower((unsigned char)word[i]);
    b[i] = '\0';
    return strstr(a, b) != NULL;
}

/* Puts today's date and time into buf, like "2026-11-10 14:30" */
void getDate(char *buf, int size)
{
    time_t now = time(NULL);
    strftime(buf, size, "%Y-%m-%d %H:%M", localtime(&now));
}

/* Makes a new node with malloc. Stops the program if memory is full. */
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
