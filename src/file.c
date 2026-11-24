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

    f = fopen(REQUEST_FILE, "w");
    if (f != NULL) {
        Request *r = queueFront;
        while (r != NULL) {
            fprintf(f, "%d|%s|%d\n", r->id, r->username, r->bookId);
            r = r->next;
        }
        fclose(f);
    }

    f = fopen(LOAN_FILE, "w");
    if (f != NULL) {
        Loan *l = loanHead;
        while (l != NULL) {
            fprintf(f, "%d|%s|%d|%d\n", l->id, l->username, l->bookId, l->status);
            l = l->next;
        }
        fclose(f);
    }

    f = fopen(HISTORY_FILE, "w");
    if (f != NULL) {
        History *h = historyTop;
        while (h != NULL) {
            fprintf(f, "%s|%d|%s|%s\n", h->username, h->bookId, h->action, h->date);
            h = h->next;
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

    f = fopen(REQUEST_FILE, "r");
    if (f != NULL) {
        while (fgets(line, sizeof(line), f)) {
            int id, bookId;
            char username[30];
            if (sscanf(line, "%d|%29[^|]|%d", &id, username, &bookId) == 3) {
                enqueue(id, username, bookId);
            }
        }
        fclose(f);
    }

    f = fopen(LOAN_FILE, "r");
    if (f != NULL) {
        while (fgets(line, sizeof(line), f)) {
            int id, bookId, status;
            char username[30];
            if (sscanf(line, "%d|%29[^|]|%d|%d", &id, username, &bookId, &status) == 4) {
                addLoan(id, username, bookId, status);
            }
        }
        fclose(f);
    }

    f = fopen(HISTORY_FILE, "r");
    if (f != NULL) {
        History *last = NULL;
        while (fgets(line, sizeof(line), f)) {
            History *node = newNode(sizeof(History));
            if (sscanf(line, "%29[^|]|%d|%9[^|]|%19[^\n]",
                       node->username, &node->bookId, node->action, node->date) != 4) {
                free(node);
                continue;
            }
            node->next = NULL;
            if (last == NULL) {
                historyTop = node;
            } else {
                last->next = node;
            }
            last = node;
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
