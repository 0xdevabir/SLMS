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
    (void)id;
    (void)username;
    (void)bookId;
}

Request *dequeue(void)
{
    return NULL;
}

void showRequests(const char *username)
{
    (void)username;
}

int hasPendingRequest(const char *username, int bookId)
{
    (void)username;
    (void)bookId;
    return 0;
}

void processRequests(void)
{
}

