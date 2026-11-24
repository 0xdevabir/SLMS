/*
Done by: Amina

What we will do in this file:
- enqueue / dequeue (queue)
- show waiting requests
- student requests a book
- staff approve or reject
*/

#include "library.h"

Request *queueFront = NULL;
Request *queueRear = NULL;
int nextRequestId = 1;

void enqueue(int id, const char *username, int bookId)
{
    Request *node = newNode(sizeof(Request));
    node->id = id;
    strcpy(node->username, username);
    node->bookId = bookId;
    node->next = NULL;

    if (queueRear == NULL) {
        queueFront = node;
        queueRear = node;
    } else {
        queueRear->next = node;
        queueRear = node;
    }

    if (id >= nextRequestId) {
        nextRequestId = id + 1;
    }
}

Request *dequeue(void)
{
    if (queueFront == NULL) {
        return NULL;
    }
    Request *node = queueFront;
    queueFront = queueFront->next;
    if (queueFront == NULL) {
        queueRear = NULL;
    }
    return node;
}

void showRequests(const char *username)
{
    (void)username;
}

void requestBook(void)
{
    int id = readInt("Book ID to request: ");
    Book *b = findBook(id);

    if (b == NULL) {
        printf("Book not found.\n");
        return;
    }

    enqueue(nextRequestId, currentUser->username, id);
    printf("Request sent for \"%s\".\n", b->title);
}

void processRequests(void)
{
}
