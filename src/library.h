/*
 * ============================================================
 *        SMART LIBRARY MANAGEMENT SYSTEM (SLMS)
 *        Data Structure Lab Project - written in C
 * ============================================================
 *
 * library.h  -  the shared "table of contents" of the project.
 *
 * Every .c file starts with  #include "library.h"  so that it
 * knows about all structures, global variables and functions,
 * even the ones written in other files.
 *
 * Project files:
 *   library.h  - structures, constants, function list (this file)
 *   main.c     - program starts here (main menu)
 *   menu.c     - student, staff and librarian menus
 *   utils.c    - input helpers and small tools
 *   book.c     - book linked list
 *   user.c     - user linked list, register, login
 *   cart.c     - cart linked list
 *   request.c  - borrow request queue (linked list)
 *   loan.c     - loan linked list, check-out, check-in
 *   history.c  - history stack (linked list)
 *   file.c     - save to files and load from files
 *
 * Compile : gcc *.c -o library
 * Run     : ./library        (Windows: library.exe)
 */

#ifndef LIBRARY_H      /* "include guard": stops this file from */
#define LIBRARY_H      /* being included twice in the same .c   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/* ---------- Roles of users ---------- */
#define ROLE_STUDENT   1
#define ROLE_STAFF     2
#define ROLE_LIBRARIAN 3

/* ---------- Status of a loan ---------- */
#define STATUS_APPROVED 1   /* staff approved, student has not picked it up yet */
#define STATUS_BORROWED 2   /* student checked the book out                     */
#define STATUS_RETURNED 3   /* student checked the book back in                 */

/* ---------- File names (data is saved here) ---------- */
#define BOOK_FILE    "books.txt"
#define USER_FILE    "users.txt"
#define REQUEST_FILE "requests.txt"
#define LOAN_FILE    "loans.txt"
#define HISTORY_FILE "history.txt"

/* ============================================================
 *                  STRUCTURES (NODES)
 * ============================================================ */

/* One book = one node of the BOOK LINKED LIST */
typedef struct Book {
    int  id;
    char title[100];
    char author[60];
    int  total;        /* how many copies the library owns  */
    int  available;    /* how many copies are on the shelf  */
    struct Book *next; /* pointer to the next book          */
} Book;

/* One user = one node of the USER LINKED LIST */
typedef struct User {
    char username[30];
    char password[30];
    char name[60];
    int  role;
    struct User *next;
} User;

/* One cart item = one node of the CART LINKED LIST */
typedef struct CartItem {
    int bookId;
    struct CartItem *next;
} CartItem;

/* One borrow request = one node of the REQUEST QUEUE */
typedef struct Request {
    int  id;
    char username[30];
    int  bookId;
    struct Request *next;
} Request;

/* One loan = one node of the LOAN LINKED LIST */
typedef struct Loan {
    int  id;
    char username[30];
    int  bookId;
    int  status;
    struct Loan *next;
} Loan;

/* One history record = one node of the HISTORY STACK */
typedef struct History {
    char username[30];
    int  bookId;
    char action[10];   /* "CHECKOUT" or "CHECKIN" */
    char date[20];
    struct History *next;
} History;

/* ============================================================
 *  GLOBAL VARIABLES
 *  "extern" means: this variable exists, but it is created
 *  (defined) in another .c file. Written next to each one.
 * ============================================================ */
extern Book     *bookHead;      /* book.c    - first node of book list   */
extern int       nextBookId;    /* book.c                                */
extern User     *userHead;      /* user.c    - first node of user list   */
extern User     *currentUser;   /* user.c    - who is logged in now      */
extern CartItem *cartHead;      /* cart.c    - cart of logged-in student */
extern Request  *queueFront;    /* request.c - remove from here          */
extern Request  *queueRear;     /* request.c - add here                  */
extern int       nextRequestId; /* request.c                             */
extern Loan     *loanHead;      /* loan.c    - first node of loan list   */
extern History  *historyTop;    /* history.c - top of history stack      */

/* ============================================================
 *  FUNCTION LIST (prototypes) - grouped by the file they live in
 * ============================================================ */

/* utils.c */
void  readLine(const char *prompt, char *buf, int size);
int   readInt(const char *prompt);
int   containsIgnoreCase(const char *text, const char *word);
void  getDate(char *buf, int size);
void *newNode(int size);
const char *roleName(int role);
const char *statusName(int status);

/* book.c */
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

/* user.c */
User *findUser(const char *username);
void  addUser(const char *username, const char *password, const char *name, int role);
int   deleteUserNode(const char *username);
void  showAllUsers(void);
void  registerUser(void);
void  removeUser(void);
void  login(void);

/* cart.c */
int   cartContains(int bookId);
void  addToCart(void);
void  removeFromCart(void);
void  showCart(void);
void  clearCart(void);
void  submitCart(void);

/* request.c */
void     enqueue(int id, const char *username, int bookId);
Request *dequeue(void);
void     showRequests(const char *username);
int      hasPendingRequest(const char *username, int bookId);
void     processRequests(void);

/* loan.c */
void  addLoan(int id, const char *username, int bookId, int status);
Loan *findLoan(int id);
int   hasActiveLoan(const char *username, int bookId);
int   userHasActiveLoans(const char *username);
void  showLoans(const char *username, int onlyActive);
void  checkOutBook(void);
void  checkInBook(void);

/* history.c */
void  pushHistory(const char *username, int bookId, const char *action, const char *date);
void  showHistory(const char *username);
void  viewStudentHistory(void);

/* file.c */
void  saveAll(void);
int   loadAll(void);
void  createDefaultData(void);

/* menu.c */
void  studentMenu(void);
void  staffMenu(void);
void  librarianMenu(void);

#endif
