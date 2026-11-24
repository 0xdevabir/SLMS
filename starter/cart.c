/*
Done by: Amina

What we will do in this file:
- check if book is already in cart
- add book to cart
- remove book from cart
- show cart
- clear cart
- send cart as borrow requests
*/

#include "library.h"

CartItem *cartHead = NULL;

int cartContains(int bookId)
{
    CartItem *temp = cartHead;
    while (temp != NULL) {
        if (temp->bookId == bookId) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

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
    CartItem *node = newNode(sizeof(CartItem));
    node->bookId = id;
    node->next = cartHead;
    cartHead = node;
    printf("\"%s\" added to cart.\n", b->title);
}

void removeFromCart(void)
{
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
        if (b != NULL) {
            printBook(b);
        }
        temp = temp->next;
    }
}

void clearCart(void)
{
    while (cartHead != NULL) {
        CartItem *temp = cartHead;
        cartHead = cartHead->next;
        free(temp);
    }
}

void submitCart(void)
{
}
