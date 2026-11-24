/*
Done by: Abir

What we will do in this file:
- role numbers and loan status
- file names
- structs for book, user, request, loan, history
- list heads and function names
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

#define STATUS_BORROWED 1
#define STATUS_RETURNED 2

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

extern Book    *bookHead;
extern int      nextBookId;
extern User    *userHead;
extern User    *currentUser;
extern Request *queueFront;
extern Request *queueRear;
extern int      nextRequestId;
extern Loan    *loanHead;
extern int      nextLoanId;
extern History *historyTop;

void  readLine(const char *prompt, char *buf, int size);
int   readInt(const char *prompt);
int   containsIgnoreCase(const char *text, const char *word);
void  getDate(char *buf, int size);
void *newNode(int size);
const char *roleName(int role);

Book *findBook(int id);
Book *addBook(int id, const char *title, const char *author, int total, int available);
int   deleteBookNode(int id);
void  showAllBooks(void);
void  searchBooks(void);
void  newBook(void);
void  removeBook(void);

User *findUser(const char *username);
void  addUser(const char *username, const char *password, const char *name, int role);
int   deleteUserNode(const char *username);
void  showAllUsers(void);
void  registerUser(void);
void  removeUser(void);
void  login(void);

void     enqueue(int id, const char *username, int bookId);
Request *dequeue(void);
void     showRequests(const char *username);
void     requestBook(void);
void     processRequests(void);

void  addLoan(int id, const char *username, int bookId, int status);
Loan *findLoan(int id);
int   userHasActiveLoans(const char *username);
void  showLoans(const char *username);
void  returnBook(void);

void  pushHistory(const char *username, int bookId, const char *action, const char *date);
void  showHistory(const char *username);

void  saveAll(void);
int   loadAll(void);
void  createDefaultData(void);

void  studentMenu(void);
void  staffMenu(void);
void  librarianMenu(void);

#endif
