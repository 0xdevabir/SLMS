# Smart Library Management System (C, Data Structure Lab)

C program with three roles: **Student**, **Staff**, **Librarian**.
Built with **linked lists**, **file handling** and **switch** menus, split into small files.

| Data structure | Used for |
|---|---|
| Singly linked list | books, users, cart, loans |
| Queue (linked) | borrow requests (first come, first served) |
| Stack (linked) | check-in / check-out history (newest first) |

## Files (`src/`)
| File | Contents |
|---|---|
| `library.h` | constants, structs, extern globals, all prototypes |
| `main.c` | program start, main menu |
| `menu.c` | student / staff / librarian menus |
| `utils.c` | input helpers, date, `newNode` |
| `book.c` | book linked list, add/delete/search books |
| `user.c` | user linked list, register, delete, login |
| `cart.c` | cart linked list |
| `request.c` | borrow request queue, approve/reject |
| `loan.c` | loans, check-out, check-in |
| `history.c` | history stack |
| `file.c` | save/load all data |

## Build and run
```
cd src
gcc *.c -o library
./library            # Windows: library.exe
```
In Code::Blocks, create a Console application project and add all files from `src/`.

First login: `admin` / `admin123` (created on first run along with 5 sample books).

Data is saved to `books.txt`, `users.txt`, `requests.txt`, `loans.txt`, `history.txt`
in the folder you run from. Delete them to start fresh.

## Guide
`SLMS_Guide.pdf` explains every part of the code and every data structure from zero.
