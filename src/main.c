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
