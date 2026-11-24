# SLMS starter (beginner)

Team: Abir, Touhid, Anika, Amina, Ardi

Each person works on their own files.

Abir
- library.h
- utils.c
- book.c
- user.c

Touhid
- main.c
- file.c

Anika
- loan.c
- history.c

Amina
- request.c

Ardi
- menu.c

Finished beginner code is in `../src/`.

```bash
cd starter
gcc *.c -o library
./library
```

Flow (simple):
1. Student requests a book (queue)
2. Staff / librarian approve → loan starts
3. Student returns the book
4. History stack keeps borrow / return
