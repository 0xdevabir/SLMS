# Smart Library Management System (C, Data Structure Lab)

Beginner console C program with three roles: **Student**, **Staff**, **Librarian**.

Uses linked lists, a queue, a stack, file I/O, and switch menus.

| Data structure | Used for |
|---|---|
| Singly linked list | books, users, loans |
| Queue (linked) | borrow requests |
| Stack (linked) | borrow / return history |

## Simple flow

1. Student requests a book → goes into the **queue**
2. Staff/librarian **approves** → book is borrowed (loan list)
3. Student **returns** the book
4. Each borrow/return is pushed on the **history stack**

No cart. No separate check-out step. Only two loan statuses: Borrowed / Returned.

## Files (`src/`)

| File | Contents |
|---|---|
| `library.h` | constants, structs, prototypes |
| `main.c` | start, login / exit |
| `menu.c` | student / staff / librarian menus |
| `utils.c` | input helpers, date, `newNode` |
| `book.c` | book linked list |
| `user.c` | user linked list, login |
| `request.c` | request queue, approve / reject |
| `loan.c` | loans, return book |
| `history.c` | history stack |
| `file.c` | save / load |

## Build and run

```bash
cd src
gcc *.c -o library
./library
```

First login: `admin` / `admin123` (created on first run with sample books).

Data files: `books.txt`, `users.txt`, `requests.txt`, `loans.txt`, `history.txt`.
Delete them to start fresh.

Team starter (partial work) is in `starter/`.
