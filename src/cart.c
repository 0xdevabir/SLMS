/*
 * cart.c - the CART LINKED LIST (only for the logged-in student)
 */
#include "library.h"

CartItem *cartHead = NULL;   /* first node of the cart */

int cartContains(int bookId)
{
    CartItem *temp = cartHead;
    while (temp != NULL) {
        if (temp->bookId == bookId) return 1;
        temp = temp->next;
    }
    return 0;
}

/* Insert at the BEGINNING of the cart list (fastest insert) */
void addToCart(void)
{
    int id = readInt("Enter book ID to add to cart: ");
    Book *b = findBook(id);
    if (b == NULL) {
        printf("Book not found.\n");
        return;
    }
    if (cartContains(id)) {
        printf("This book is already in your cart.\n");
        return;
    }
    if (b->available == 0) {
        printf("Note: no copy is free right now, but you can still request it.\n");
    }
    CartItem *node = newNode(sizeof(CartItem));
    node->bookId = id;
    node->next = cartHead;   /* new node points to old first node */
    cartHead = node;         /* new node becomes the first node   */
    printf("\"%s\" added to cart.\n", b->title);
}

void removeFromCart(void)
{
    int id = readInt("Enter book ID to remove from cart: ");
    CartItem *temp = cartHead, *prev = NULL;
    while (temp != NULL && temp->bookId != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("That book is not in your cart.\n");
        return;
    }
    if (prev == NULL) cartHead = temp->next;
    else prev->next = temp->next;
    free(temp);
    printf("Removed from cart.\n");
}

void showCart(void)
{
    if (cartHead == NULL) {
        printf("\nYour cart is empty.\n");
        return;
    }
    printBookHeader();
    CartItem *temp = cartHead;
    while (temp != NULL) {
        Book *b = findBook(temp->bookId);
        if (b != NULL) printBook(b);
        temp = temp->next;
    }
}

/* Free every node of the cart (used after submit and on logout) */
void clearCart(void)
{
    while (cartHead != NULL) {
        CartItem *temp = cartHead;
        cartHead = cartHead->next;
        free(temp);
    }
}

/* Every book in the cart becomes a request in the queue */
void submitCart(void)
{
    if (cartHead == NULL) {
        printf("Your cart is empty. Add books first.\n");
        return;
    }
    CartItem *temp = cartHead;
    while (temp != NULL) {
        Book *b = findBook(temp->bookId);
        if (b == NULL) {
            printf("Book %d no longer exists - skipped.\n", temp->bookId);
        } else if (hasPendingRequest(currentUser->username, temp->bookId)) {
            printf("You already requested \"%s\" - skipped.\n", b->title);
        } else if (hasActiveLoan(currentUser->username, temp->bookId)) {
            printf("You already have \"%s\" - skipped.\n", b->title);
        } else {
            enqueue(nextRequestId, currentUser->username, temp->bookId);
            printf("Request sent for \"%s\".\n", b->title);
        }
        temp = temp->next;
    }
    clearCart();
}
