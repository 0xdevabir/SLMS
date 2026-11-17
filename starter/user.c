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
    (void)username;
    (void)password;
    (void)name;
    (void)role;
}

int deleteUserNode(const char *username)
{
    (void)username;
    return 0;
}

void showAllUsers(void)
{
}

void registerUser(void)
{
}

void removeUser(void)
{
}

void login(void)
{
}


