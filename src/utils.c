#include "library.h"

void readLine(const char *prompt, char *buf, int size)
{
    while (1) {
        printf("%s", prompt);
        if (fgets(buf, size, stdin) == NULL) {
            printf("\n");
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
            printf("Cannot be empty.\n");
        } else if (strchr(buf, '|') != NULL) {
            printf("'|' is not allowed.\n");
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
        printf("Please enter a number.\n");
    }
}

int containsIgnoreCase(const char *text, const char *word)
{
    char a[100], b[100];
    int i;
    for (i = 0; text[i] != '\0' && i < 99; i++) {
        a[i] = tolower((unsigned char)text[i]);
    }
    a[i] = '\0';
    for (i = 0; word[i] != '\0' && i < 99; i++) {
        b[i] = tolower((unsigned char)word[i]);
    }
    b[i] = '\0';
    return strstr(a, b) != NULL;
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
    if (role == ROLE_STUDENT) return "Student";
    if (role == ROLE_STAFF) return "Staff";
    return "Librarian";
}
