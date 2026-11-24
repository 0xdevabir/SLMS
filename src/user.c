#include "library.h"

User *userHead = NULL;
User *currentUser = NULL;

User *findUser(const char *username)
{
    User *temp = userHead;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void addUser(const char *username, const char *password, const char *name, int role)
{
    User *node = newNode(sizeof(User));
    strcpy(node->username, username);
    strcpy(node->password, password);
    strcpy(node->name, name);
    node->role = role;
    node->next = NULL;

    if (userHead == NULL) {
        userHead = node;
    } else {
        User *temp = userHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
}

int deleteUserNode(const char *username)
{
    User *temp = userHead;
    User *prev = NULL;

    while (temp != NULL && strcmp(temp->username, username) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return 0;
    }

    if (prev == NULL) {
        userHead = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    return 1;
}

void showAllUsers(void)
{
    printf("\n%-15s %-25s %-10s\n", "Username", "Name", "Role");
    printf("------------------------------------------------\n");

    User *temp = userHead;
    while (temp != NULL) {
        printf("%-15s %-25.25s %-10s\n",
               temp->username, temp->name, roleName(temp->role));
        temp = temp->next;
    }
}

void registerUser(void)
{
    char username[30], password[30], name[60];
    int role;

    printf("1. Student   2. Staff\n");
    role = readInt("Choice: ");
    if (role != ROLE_STUDENT && role != ROLE_STAFF) {
        printf("Invalid role.\n");
        return;
    }

    readLine("Username: ", username, sizeof(username));
    if (findUser(username) != NULL) {
        printf("Username already taken.\n");
        return;
    }
    readLine("Password: ", password, sizeof(password));
    readLine("Full name: ", name, sizeof(name));

    addUser(username, password, name, role);
    printf("User registered.\n");
}

void removeUser(void)
{
    char username[30];

    showAllUsers();
    readLine("Username to delete: ", username, sizeof(username));

    User *u = findUser(username);
    if (u == NULL) {
        printf("User not found.\n");
        return;
    }
    if (u == currentUser) {
        printf("You cannot delete yourself.\n");
        return;
    }
    if (u->role == ROLE_LIBRARIAN) {
        printf("Cannot delete librarian.\n");
        return;
    }
    if (userHasActiveLoans(username)) {
        printf("User still has books out.\n");
        return;
    }

    deleteUserNode(username);
    printf("User deleted.\n");
}

void login(void)
{
    char username[30], password[30];

    readLine("Username: ", username, sizeof(username));
    readLine("Password: ", password, sizeof(password));

    User *u = findUser(username);
    if (u == NULL || strcmp(u->password, password) != 0) {
        printf("Wrong username or password.\n");
        return;
    }

    currentUser = u;
    printf("\nWelcome, %s (%s)\n", u->name, roleName(u->role));

    if (u->role == ROLE_STUDENT) {
        studentMenu();
    } else if (u->role == ROLE_STAFF) {
        staffMenu();
    } else {
        librarianMenu();
    }

    currentUser = NULL;
    printf("Logged out.\n");
}
