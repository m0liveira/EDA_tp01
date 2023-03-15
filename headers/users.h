#include <stdio.h>

typedef struct userList {
    int id;
    char name[30];
    char password[30];
    char role[10];
    struct userList *nextEntry;
} User;

int isUserUnique(User *startEntry, int id);
int isNameUnique(User *startEntry, char name[]);
User *addUser(User *startEntry, int id, char name[], char password[], char role[]);