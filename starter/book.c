/*
Done by: Abir

What we will do in this file:
- find / add / delete book in linked list
- show all books
- search books
- add new book (ask user)
- remove book (ask user)
*/

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
    (void)id;
    return 0;
}

void showAllBooks(void)
{
    if (bookHead == NULL) {
        printf("\nNo books yet.\n");
        return;
    }

    printf("\n%-5s %-30s %-20s %-6s %-6s\n", "ID", "Title", "Author", "Total", "Avail");
    printf("--------------------------------------------------------------------\n");

    Book *temp = bookHead;
    while (temp != NULL) {
        printf("%-5d %-30.30s %-20.20s %-6d %-6d\n",
               temp->id, temp->title, temp->author, temp->total, temp->available);
        temp = temp->next;
    }
}

void searchBooks(void)
{
    char key[100];
    int found = 0;

    readLine("Search title or author: ", key, sizeof(key));

    Book *temp = bookHead;
    while (temp != NULL) {
        if (containsIgnoreCase(temp->title, key) ||
            containsIgnoreCase(temp->author, key)) {
            if (found == 0) {
                printf("\n%-5s %-30s %-20s %-6s %-6s\n", "ID", "Title", "Author", "Total", "Avail");
                printf("--------------------------------------------------------------------\n");
            }
            printf("%-5d %-30.30s %-20.20s %-6d %-6d\n",
                   temp->id, temp->title, temp->author, temp->total, temp->available);
            found++;
        }
        temp = temp->next;
    }

    if (found == 0) {
        printf("No match found.\n");
    }
}

void newBook(void)
{
    char title[100];
    char author[60];
    int copies;

    readLine("Title: ", title, sizeof(title));
    readLine("Author: ", author, sizeof(author));
    copies = readInt("Copies: ");

    if (copies <= 0) {
        printf("Copies must be at least 1.\n");
        return;
    }

    Book *b = addBook(nextBookId, title, author, copies, copies);
    printf("Added. Book ID = %d\n", b->id);
}

void removeBook(void)
{
}
