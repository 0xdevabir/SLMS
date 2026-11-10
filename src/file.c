/*
 * file.c - FILE HANDLING (save and load everything)
 *          Each line of a file is one node. Fields are separated by '|'
 */
#include "library.h"

void saveAll(void)
{
    FILE *f;

    f = fopen(BOOK_FILE, "w");
    if (f != NULL) {
        for (Book *b = bookHead; b != NULL; b = b->next)
            fprintf(f, "%d|%s|%s|%d|%d\n", b->id, b->title, b->author, b->total, b->available);
        fclose(f);
    }

    f = fopen(USER_FILE, "w");
    if (f != NULL) {
        for (User *u = userHead; u != NULL; u = u->next)
            fprintf(f, "%s|%s|%s|%d\n", u->username, u->password, u->name, u->role);
        fclose(f);
    }

    f = fopen(REQUEST_FILE, "w");
    if (f != NULL) {
        for (Request *r = queueFront; r != NULL; r = r->next)
            fprintf(f, "%d|%s|%d\n", r->id, r->username, r->bookId);
        fclose(f);
    }

    f = fopen(LOAN_FILE, "w");
    if (f != NULL) {
        for (Loan *l = loanHead; l != NULL; l = l->next)
            fprintf(f, "%d|%s|%d|%d\n", l->id, l->username, l->bookId, l->status);
        fclose(f);
    }

    /* History is saved from top (newest) to bottom (oldest) */
    f = fopen(HISTORY_FILE, "w");
    if (f != NULL) {
        for (History *h = historyTop; h != NULL; h = h->next)
            fprintf(f, "%s|%d|%s|%s\n", h->username, h->bookId, h->action, h->date);
        fclose(f);
    }
}

/* Returns 1 if this is the very first run (no users file yet) */
int loadAll(void)
{
    FILE *f;
    char line[300];

    f = fopen(USER_FILE, "r");
    if (f == NULL) return 1;              /* first run */
    while (fgets(line, sizeof(line), f)) {
        char username[30], password[30], name[60];
        int role;
        if (sscanf(line, "%29[^|]|%29[^|]|%59[^|]|%d", username, password, name, &role) == 4)
            addUser(username, password, name, role);
    }
    fclose(f);

    f = fopen(BOOK_FILE, "r");
    if (f != NULL) {
        while (fgets(line, sizeof(line), f)) {
            int id, total, available;
            char title[100], author[60];
            if (sscanf(line, "%d|%99[^|]|%59[^|]|%d|%d", &id, title, author, &total, &available) == 5)
                addBook(id, title, author, total, available);
        }
        fclose(f);
    }

    f = fopen(REQUEST_FILE, "r");
    if (f != NULL) {
        while (fgets(line, sizeof(line), f)) {
            int id, bookId;
            char username[30];
            if (sscanf(line, "%d|%29[^|]|%d", &id, username, &bookId) == 3)
                enqueue(id, username, bookId);
        }
        fclose(f);
    }

    f = fopen(LOAN_FILE, "r");
    if (f != NULL) {
        while (fgets(line, sizeof(line), f)) {
            int id, bookId, status;
            char username[30];
            if (sscanf(line, "%d|%29[^|]|%d|%d", &id, username, &bookId, &status) == 4)
                addLoan(id, username, bookId, status);
        }
        fclose(f);
    }

    /* The file is newest-first. If we pushed each line, the oldest would end
     * up on top (wrong order). So we add each line at the BOTTOM instead. */
    f = fopen(HISTORY_FILE, "r");
    if (f != NULL) {
        History *bottom = NULL;
        while (fgets(line, sizeof(line), f)) {
            History *node = newNode(sizeof(History));
            if (sscanf(line, "%29[^|]|%d|%9[^|]|%19[^\n]", node->username, &node->bookId,
                       node->action, node->date) != 4) {
                free(node);
                continue;
            }
            node->next = NULL;
            if (bottom == NULL) historyTop = node;
            else bottom->next = node;
            bottom = node;
        }
        fclose(f);
    }
    return 0;
}

/* First run: create the main librarian and a few sample books */
void createDefaultData(void)
{
    addUser("admin", "admin123", "Head Librarian", ROLE_LIBRARIAN);
    addBook(nextBookId, "C Programming Language", "Kernighan & Ritchie", 3, 3);
    addBook(nextBookId, "Data Structures in C", "Reema Thareja", 2, 2);
    addBook(nextBookId, "Introduction to Algorithms", "Cormen", 2, 2);
    addBook(nextBookId, "Let Us C", "Yashavant Kanetkar", 4, 4);
    addBook(nextBookId, "Clean Code", "Robert C. Martin", 1, 1);
    saveAll();
    printf("First run: default librarian created (admin / admin123).\n");
}
