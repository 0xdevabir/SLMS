/*
Done by: Abir

What we will do in this file:
- find user by username
- add user to the list
- delete user from the list
- show all users
- register student or staff
- remove a user safely
- login and open the right menu
*/

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
    (void)username;
    return 0;
}

void showAllUsers(void)
{
    printf("\n%-15s %-25s %-10s\n", "Username", "Name", "Role");
    printf("----------------------------------------------------\n");
    User *temp = userHead;
    while (temp != NULL) {
        printf("%-15s %-25.25s %-10s\n", temp->username, temp->name, roleName(temp->role));
        temp = temp->next;
    }
}

void registerUser(void)
{
}

void removeUser(void)
{
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
    printf("\nWelcome, %s! You are logged in as %s.\n", u->name, roleName(u->role));

    switch (u->role) {
        case ROLE_STUDENT:
            studentMenu();
            break;
        case ROLE_STAFF:
            staffMenu();
            break;
        default:
            librarianMenu();
            break;
    }

    currentUser = NULL;
    printf("Logged out.\n");
}
