/*
Done by: Amina

What we will do in this file:
- add request to the queue
- take request from the front
- show waiting requests
- check if user already asked for that book
- approve or reject requests
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

int hasPendingRequest(const char *username, int bookId)
{
    Request *temp = queueFront;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 && temp->bookId == bookId) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void processRequests(void)
{
}
