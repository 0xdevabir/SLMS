/*
Done by: Abir

What we will do in this file:
- put role numbers (student, staff, librarian)
- put loan status numbers
- put the .txt file names
- make the structs (book, user, cart, request, loan, history)
- write the list heads used in other files
- write the function names so every .c file can use them
*/

#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define ROLE_STUDENT   1
#define ROLE_STAFF     2
#define ROLE_LIBRARIAN 3

#define STATUS_APPROVED 1
#define STATUS_BORROWED 2
#define STATUS_RETURNED 3

#define BOOK_FILE    "books.txt"
#define USER_FILE    "users.txt"
#define REQUEST_FILE "requests.txt"
#define LOAN_FILE    "loans.txt"
#define HISTORY_FILE "history.txt"

typedef struct Book {
    int  id;
    char title[100];
    char author[60];
    int  total;
    int  available;
    struct Book *next;
} Book;

typedef struct User {
    char username[30];
    char password[30];
    char name[60];
    int  role;
    struct User *next;
} User;

typedef struct CartItem {
    int bookId;
    struct CartItem *next;
} CartItem;

typedef struct Request {
    int  id;
    char username[30];
    int  bookId;
    struct Request *next;
} Request;

typedef struct Loan {
    int  id;
    char username[30];
    int  bookId;
    int  status;
    struct Loan *next;
} Loan;

typedef struct History {
    char username[30];
    int  bookId;
    char action[10];
    char date[20];
    struct History *next;
} History;

extern Book     *bookHead;
extern int       nextBookId;
extern User     *userHead;
extern User     *currentUser;
extern CartItem *cartHead;
extern Request  *queueFront;
extern Request  *queueRear;
extern int       nextRequestId;
extern Loan     *loanHead;
extern History  *historyTop;

void  readLine(const char *prompt, char *buf, int size);
int   readInt(const char *prompt);
int   containsIgnoreCase(const char *text, const char *word);
void  getDate(char *buf, int size);
void *newNode(int size);
const char *roleName(int role);
const char *statusName(int status);

Book *findBook(int id);
Book *addBook(int id, const char *title, const char *author, int total, int available);
int   deleteBookNode(int id);
void  printBookHeader(void);
void  printBook(Book *b);
void  showAllBooks(void);
void  searchBooks(void);
void  checkStock(void);
void  newBook(void);
void  removeBook(void);
void  updateCopies(void);

User *findUser(const char *username);
void  addUser(const char *username, const char *password, const char *name, int role);
int   deleteUserNode(const char *username);
void  showAllUsers(void);
void  registerUser(void);
void  removeUser(void);
void  login(void);

int   cartContains(int bookId);
void  addToCart(void);
void  removeFromCart(void);
void  showCart(void);
void  clearCart(void);
void  submitCart(void);

void     enqueue(int id, const char *username, int bookId);
Request *dequeue(void);
void     showRequests(const char *username);
int      hasPendingRequest(const char *username, int bookId);
void     processRequests(void);

void  addLoan(int id, const char *username, int bookId, int status);
Loan *findLoan(int id);
int   hasActiveLoan(const char *username, int bookId);
int   userHasActiveLoans(const char *username);
void  showLoans(const char *username, int onlyActive);
void  checkOutBook(void);
void  checkInBook(void);

void  pushHistory(const char *username, int bookId, const char *action, const char *date);
void  showHistory(const char *username);
void  viewStudentHistory(void);

void  saveAll(void);
int   loadAll(void);
void  createDefaultData(void);

void  studentMenu(void);
void  staffMenu(void);
void  librarianMenu(void);

#endif
