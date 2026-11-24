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
    int count = 0;
    Request *temp = queueFront;

    while (temp != NULL) {
        if (username == NULL || strcmp(temp->username, username) == 0) {
            Book *b = findBook(temp->bookId);
            if (count == 0) {
                printf("\n%-6s %-15s %-8s %-30s\n", "ReqID", "Student", "BookID", "Title");
                printf("------------------------------------------------------------\n");
            }
            printf("%-6d %-15s %-8d %-30.30s\n",
                   temp->id, temp->username, temp->bookId,
                   b ? b->title : "(gone)");
            count++;
        }
        temp = temp->next;
    }

    if (count == 0) {
        printf("\nNo pending requests.\n");
    }
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
    while (queueFront != NULL) {
        Request *r = queueFront;
        Book *b = findBook(r->bookId);

        printf("\nRequest #%d\n", r->id);
        printf("Student: %s\n", r->username);
        printf("Book: %d - %s\n", r->bookId, b ? b->title : "(gone)");
        printf("Available: %d\n", b ? b->available : 0);
        printf("1. Approve   2. Reject   0. Stop\n");

        switch (readInt("Choice: ")) {
            case 1:
                if (b == NULL || b->available == 0) {
                    printf("No copy available.\n");
                    break;
                }
                r = dequeue();
                b->available--;
                addLoan(nextLoanId, r->username, r->bookId, STATUS_BORROWED);
                {
                    char date[20];
                    getDate(date, sizeof(date));
                    pushHistory(r->username, r->bookId, "BORROW", date);
                }
                printf("Approved. Book is now borrowed.\n");
                free(r);
                break;
            case 2:
                r = dequeue();
                printf("Rejected.\n");
                free(r);
                break;
            case 0:
                return;
            default:
                printf("Invalid choice.\n");
        }
        saveAll();
    }
    printf("\nNo more requests.\n");
}
