/*
Done by: Abir

What we will do in this file:
- find book by id
- add book to the list
- delete book from the list
- show all books
- search book by title or author
- check how many copies are left
- ask user and add a new book
- ask user and remove a book
- change how many copies a book has
*/

#include "library.h"

Book *bookHead = NULL;
int nextBookId = 1;

Book *findBook(int id)
{
    (void)id;
    return NULL;
}

Book *addBook(int id, const char *title, const char *author, int total, int available)
{
    (void)id;
    (void)title;
    (void)author;
    (void)total;
    (void)available;
    return NULL;
}

int deleteBookNode(int id)
{
    (void)id;
    return 0;
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
}

void searchBooks(void)
{
}

void checkStock(void)
{
}

void newBook(void)
{
}

void removeBook(void)
{
}

void updateCopies(void)
{
}


