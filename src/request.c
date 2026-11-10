/*
 * request.c - the BORROW REQUEST QUEUE
 *             (a linked list: enqueue at rear, dequeue at front)
 */
#include "library.h"

Request *queueFront    = NULL;   /* remove from here */
Request *queueRear     = NULL;   /* add here         */
int      nextRequestId = 1;      /* id for the next new request */

void enqueue(int id, const char *username, int bookId)
{
    Request *node = newNode(sizeof(Request));
    node->id = id;
    strcpy(node->username, username);
    node->bookId = bookId;
    node->next = NULL;

    if (queueRear == NULL) {         /* queue is empty */
        queueFront = node;
        queueRear = node;
    } else {
        queueRear->next = node;      /* join at the back of the line */
        queueRear = node;
    }
    if (id >= nextRequestId) nextRequestId = id + 1;
}

/* Remove and return the request at the front. Caller must free() it. */
Request *dequeue(void)
{
    if (queueFront == NULL) return NULL;
    Request *node = queueFront;
    queueFront = queueFront->next;
    if (queueFront == NULL) queueRear = NULL;   /* queue became empty */
    return node;
}

/* Show pending requests. username == NULL means "show everyone's". */
void showRequests(const char *username)
{
    int count = 0;
    Request *temp = queueFront;
    while (temp != NULL) {
        if (username == NULL || strcmp(temp->username, username) == 0) {
            if (count == 0) {
                printf("\n%-6s %-15s %-8s %-32s\n", "ReqID", "Student", "BookID", "Title");
                printf("----------------------------------------------------------------\n");
            }
            Book *b = findBook(temp->bookId);
            printf("%-6d %-15s %-8d %-32.32s\n", temp->id, temp->username,
                   temp->bookId, b ? b->title : "(deleted book)");
            count++;
        }
        temp = temp->next;
    }
    if (count == 0) printf("\nNo pending requests.\n");
}

int hasPendingRequest(const char *username, int bookId)
{
    Request *temp = queueFront;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 && temp->bookId == bookId) return 1;
        temp = temp->next;
    }
    return 0;
}

/* Staff: take requests from the FRONT of the queue one by one */
void processRequests(void)
{
    while (queueFront != NULL) {
        Request *r = queueFront;
        Book *b = findBook(r->bookId);

        printf("\nNext request  #%d\n", r->id);
        printf("  Student : %s\n", r->username);
        printf("  Book    : %d - %s\n", r->bookId, b ? b->title : "(deleted book)");
        printf("  Copies available: %d\n", b ? b->available : 0);
        printf("1. Approve   2. Reject   0. Stop\n");

        switch (readInt("Choice: ")) {
            case 1:                                   /* approve */
                if (b == NULL || b->available == 0) {
                    printf("Cannot approve: no copy available. Reject it or try later.\n");
                    break;
                }
                r = dequeue();
                b->available--;                       /* reserve one copy */
                addLoan(r->id, r->username, r->bookId, STATUS_APPROVED);
                printf("Approved. Student can now check out the book.\n");
                free(r);
                break;
            case 2:                                   /* reject */
                r = dequeue();
                printf("Request rejected.\n");
                free(r);
                break;
            case 0:                                   /* stop */
                return;
            default:
                printf("Invalid choice.\n");
        }
        saveAll();
    }
    printf("\nNo more pending requests.\n");
}
