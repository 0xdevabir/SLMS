/*
 * user.c - the USER LINKED LIST (add, find, delete, show)
 *          plus register, remove and login
 */
#include "library.h"

User *userHead    = NULL;   /* first node of the user list */
User *currentUser = NULL;   /* who is logged in now        */

User *findUser(const char *username)
{
    User *temp = userHead;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

/* Insert a user at the END of the user list */
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
        while (temp->next != NULL) temp = temp->next;
        temp->next = node;
    }
}

int deleteUserNode(const char *username)
{
    User *temp = userHead, *prev = NULL;
    while (temp != NULL && strcmp(temp->username, username) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return 0;
    if (prev == NULL) userHead = temp->next;
    else prev->next = temp->next;
    free(temp);
    return 1;
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

/* Librarian: register a new student or staff member */
void registerUser(void)
{
    char username[30], password[30], name[60];
    int role;

    printf("\nRegister as:  1. Student   2. Staff\n");
    switch (readInt("Choice: ")) {
        case 1:  role = ROLE_STUDENT; break;
        case 2:  role = ROLE_STAFF;   break;
        default: printf("Invalid role.\n"); return;
    }

    readLine("Username (no spaces): ", username, sizeof(username));
    if (strchr(username, ' ') != NULL) {
        printf("Username cannot contain spaces.\n");
        return;
    }
    if (findUser(username) != NULL) {
        printf("This username is already taken.\n");
        return;
    }
    readLine("Password: ", password, sizeof(password));
    readLine("Full name: ", name, sizeof(name));
    addUser(username, password, name, role);
    printf("%s \"%s\" registered successfully.\n", roleName(role), username);
}

/* Librarian: delete a student or staff member */
void removeUser(void)
{
    char username[30];
    showAllUsers();
    readLine("Enter username to delete: ", username, sizeof(username));
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
        printf("A librarian account cannot be deleted.\n");
        return;
    }
    if (userHasActiveLoans(username)) {
        printf("This user still has books. They must return them first.\n");
        return;
    }
    deleteUserNode(username);
    printf("User deleted.\n");
}

/* Ask for username + password, then open the right menu */
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
        case ROLE_STUDENT: studentMenu();   break;
        case ROLE_STAFF:   staffMenu();     break;
        default:           librarianMenu(); break;
    }

    currentUser = NULL;
    printf("Logged out.\n");
}
