#include "library.h"

Book *bookHead = NULL;
int nextBookId = 1;

Book *findBook(int id)
{
    Book *temp = bookHead;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Book *addBook(int id, const char *title, const char *author, int total, int available)
{
    Book *node = newNode(sizeof(Book));
    node->id = id;
    strcpy(node->title, title);
    strcpy(node->author, author);
    node->total = total;
    node->available = available;
    node->next = NULL;

    if (bookHead == NULL) {
        bookHead = node;
    } else {
        Book *temp = bookHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }

    if (id >= nextBookId) {
        nextBookId = id + 1;
    }
    return node;
}

int deleteBookNode(int id)
{
    Book *temp = bookHead;
    Book *prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return 0;
    }

    if (prev == NULL) {
        bookHead = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    return 1;
}

void printBookHeader(void)
{
    printf("\n%-5s %-32s %-22s %-6s %-6s\n", "ID", "Title", "Author", "Total", "Avail");
    printf("--------------------------------------------------------------------------\n");
}

void printBook(Book *b)
{
    printf("%-5d %-32.32s %-22.22s %-6d %-6d\n",
           b->id, b->title, b->author, b->total, b->available);
}

void showAllBooks(void)
{
    if (bookHead == NULL) {
        printf("\nNo books in the library.\n");
        return;
    }

    printBookHeader();
    Book *temp = bookHead;
    while (temp != NULL) {
        printBook(temp);
        temp = temp->next;
    }
}

void searchBooks(void)
{
    char key[100];
    int found = 0;

    readLine("Enter title or author to search: ", key, sizeof(key));

    Book *temp = bookHead;
    while (temp != NULL) {
        if (containsIgnoreCase(temp->title, key) ||
            containsIgnoreCase(temp->author, key)) {
            if (found == 0) {
                printBookHeader();
            }
            printBook(temp);
            found++;
        }
        temp = temp->next;
    }

    if (found == 0) {
        printf("No book matched \"%s\".\n", key);
    } else {
        printf("%d book(s) found.\n", found);
    }
}

void checkStock(void)
{
    int id = readInt("Enter book ID: ");
    Book *b = findBook(id);

    if (b == NULL) {
        printf("Book not found.\n");
        return;
    }

    printBookHeader();
    printBook(b);
    printf("Borrowed / reserved copies: %d\n", b->total - b->available);
}

void newBook(void)
{
    char title[100];
    char author[60];
    int copies;

    readLine("Book title: ", title, sizeof(title));
    readLine("Author: ", author, sizeof(author));
    copies = readInt("Number of copies: ");

    if (copies <= 0) {
        printf("Copies must be at least 1.\n");
        return;
    }

    Book *b = addBook(nextBookId, title, author, copies, copies);
    printf("Book added with ID %d.\n", b->id);
}

void removeBook(void)
{
    int id = readInt("Enter book ID to delete: ");
    Book *b = findBook(id);
    int choice;

    if (b == NULL) {
        printf("Book not found.\n");
        return;
    }

    if (b->available != b->total) {
        printf("Some copies are borrowed or reserved. Cannot delete now.\n");
        return;
    }

    printf("Delete \"%s\"? 1. Yes  0. No\n", b->title);
    choice = readInt("Choice: ");

    if (choice == 1) {
        deleteBookNode(id);
        printf("Book deleted.\n");
    } else {
        printf("Nothing deleted.\n");
    }
}

void updateCopies(void)
{
    int id = readInt("Enter book ID: ");
    Book *b = findBook(id);
    int out;
    int newTotal;

    if (b == NULL) {
        printf("Book not found.\n");
        return;
    }

    out = b->total - b->available;
    printf("Total now: %d  (out with students: %d)\n", b->total, out);
    newTotal = readInt("New total copies: ");

    if (newTotal < out) {
        printf("Total cannot be less than copies that are out (%d).\n", out);
        return;
    }

    b->total = newTotal;
    b->available = newTotal - out;
    printf("Updated. Available now: %d\n", b->available);
}
