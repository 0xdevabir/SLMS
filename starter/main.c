/*
Done by: Touhid

What we will do in this file:
- start program
- load data or make default admin
- login / exit menu
- save when exit
*/

#include "library.h"

int main(void)
{
    if (loadAll() == 1) {
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
