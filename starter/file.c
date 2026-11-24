/*
Done by: Touhid

What we will do in this file:
- save books and users to txt
- load them back
- later also requests, loans, history
- create admin + sample books on first run
*/

#include "library.h"

void saveAll(void)
{
    FILE *f;

    f = fopen(BOOK_FILE, "w");
    if (f != NULL) {
        Book *b = bookHead;
        while (b != NULL) {
            fprintf(f, "%d|%s|%s|%d|%d\n", b->id, b->title, b->author, b->total, b->available);
            b = b->next;
        }
        fclose(f);
    }

    f = fopen(USER_FILE, "w");
    if (f != NULL) {
        User *u = userHead;
        while (u != NULL) {
            fprintf(f, "%s|%s|%s|%d\n", u->username, u->password, u->name, u->role);
            u = u->next;
        }
        fclose(f);
    }
}

int loadAll(void)
{
    FILE *f;
    char line[300];

    f = fopen(USER_FILE, "r");
    if (f == NULL) {
        return 1;
    }
    while (fgets(line, sizeof(line), f)) {
        char username[30], password[30], name[60];
        int role;
        if (sscanf(line, "%29[^|]|%29[^|]|%59[^|]|%d", username, password, name, &role) == 4) {
            addUser(username, password, name, role);
        }
    }
    fclose(f);

    f = fopen(BOOK_FILE, "r");
    if (f != NULL) {
        while (fgets(line, sizeof(line), f)) {
            int id, total, available;
            char title[100], author[60];
            if (sscanf(line, "%d|%99[^|]|%59[^|]|%d|%d", &id, title, author, &total, &available) == 5) {
                addBook(id, title, author, total, available);
            }
        }
        fclose(f);
    }

    return 0;
}

void createDefaultData(void)
{
    addUser("admin", "admin123", "Head Librarian", ROLE_LIBRARIAN);
    addBook(nextBookId, "C Programming Language", "Kernighan & Ritchie", 3, 3);
    addBook(nextBookId, "Data Structures in C", "Reema Thareja", 2, 2);
    addBook(nextBookId, "Let Us C", "Yashavant Kanetkar", 4, 4);
    saveAll();
    printf("First run: admin / admin123 created.\n");
}
