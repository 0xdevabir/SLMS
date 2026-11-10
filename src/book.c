/*
 * book.c - the BOOK LINKED LIST
 *          (add, find, delete, show, search, stock, update)
 */
#include "library.h"

Book *bookHead   = NULL;   /* first node of the book list */
int   nextBookId = 1;      /* id given to the next new book */

/* Linear search: walk the list one by one until the id matches */
Book *findBook(int id)
{
    Book *temp = bookHead;
    while (temp != NULL) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return NULL;
}

/* Insert a new book at the END of the linked list */
Book *addBook(int id, const char *title, const char *author, int total, int available)
{
    Book *node = newNode(sizeof(Book));
    node->id = id;
    strcpy(node->title, title);
    strcpy(node->author, author);
    node->total = total;
    node->available = available;
    node->next = NULL;

    if (bookHead == NULL) {          /* list is empty */
        bookHead = node;
    } else {                         /* go to the last node */
        Book *temp = bookHead;
        while (temp->next != NULL) temp = temp->next;
        temp->next = node;
    }
    if (id >= nextBookId) nextBookId = id + 1;
    return node;
}

/* Delete the node with this id from the linked list */
int deleteBookNode(int id)
{
    Book *temp = bookHead, *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return 0;            /* not found */

    if (prev == NULL) bookHead = temp->next;  /* deleting the first node */
    else prev->next = temp->next;             /* skip over the node      */
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
    printf("%-5d %-32.32s %-22.22s %-6d %-6d\n", b->id, b->title, b->author, b->total, b->available);
}

/* Traverse (walk through) the whole list and print every book */
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

/* Search by title or author (part of the word is enough) */
void searchBooks(void)
{
    char key[100];
    int found = 0;
    readLine("Enter title or author to search: ", key, sizeof(key));

    Book *temp = bookHead;
    while (temp != NULL) {
        if (containsIgnoreCase(temp->title, key) || containsIgnoreCase(temp->author, key)) {
            if (found == 0) printBookHeader();
            printBook(temp);
            found++;
        }
        temp = temp->next;
    }
    if (found == 0) printf("No book matched \"%s\".\n", key);
    else printf("%d book(s) found.\n", found);
}

/* Staff: check how many copies of one book are in stock */
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

/* Librarian: add a brand new book */
void newBook(void)
{
    char title[100], author[60];
    readLine("Book title: ", title, sizeof(title));
    readLine("Author: ", author, sizeof(author));
    int copies = readInt("Number of copies: ");
    if (copies <= 0) {
        printf("Copies must be at least 1.\n");
        return;
    }
    Book *b = addBook(nextBookId, title, author, copies, copies);
    printf("Book added with ID %d.\n", b->id);
}

/* Librarian: delete a book (only when no copy is out) */
void removeBook(void)
{
    int id = readInt("Enter book ID to delete: ");
    Book *b = findBook(id);
    if (b == NULL) {
        printf("Book not found.\n");
        return;
    }
    if (b->available != b->total) {
        printf("Some copies are borrowed or reserved. Cannot delete now.\n");
        return;
    }
    printf("Delete \"%s\"? 1. Yes  0. No\n", b->title);
    switch (readInt("Choice: ")) {
        case 1:
            deleteBookNode(id);
            printf("Book deleted.\n");
            break;
        default:
            printf("Nothing deleted.\n");
    }
}

/* Librarian: change how many copies the library owns */
void updateCopies(void)
{
    int id = readInt("Enter book ID: ");
    Book *b = findBook(id);
    if (b == NULL) {
        printf("Book not found.\n");
        return;
    }
    int out = b->total - b->available;    /* copies currently out */
    printf("Total now: %d  (out with students: %d)\n", b->total, out);
    int newTotal = readInt("New total copies: ");
    if (newTotal < out) {
        printf("Total cannot be less than copies that are out (%d).\n", out);
        return;
    }
    b->total = newTotal;
    b->available = newTotal - out;
    printf("Updated. Available now: %d\n", b->available);
}
