/*
 * main.c - the program starts here
 *
 * Compile : gcc *.c -o library
 * Run     : ./library        (Windows: library.exe)
 * First login: username = admin   password = admin123
 */
#include "library.h"

int main(void)
{
    if (loadAll() == 1) {          /* 1 means: first run, no saved data */
        createDefaultData();
    }

    while (1) {
        printf("\n==========================================\n");
        printf("    SMART LIBRARY MANAGEMENT SYSTEM\n");
        printf("==========================================\n");
        printf("1. Login\n");
        printf("0. Exit\n");

        switch (readInt("Choice: ")) {
            case 1:
                login();
                break;
            case 0:
                saveAll();
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}
