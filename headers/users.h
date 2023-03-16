#include <stdio.h>

typedef struct UserList {
    int id;
    int nif;
    float balance;
    char name[30];
    char password[30];
    char role[10];
    struct UserList *nextEntry;
} User;

int isUserUnique(User *startEntry, int id);
int isNameUnique(User *startEntry, char name[]);
User *addUser(User *startEntry, int id, int nif, float balance, char name[], char password[], char role[]);
int loginUser(User *startEntry, char name[], char password[]);
int saveUsersOnDatabase(User *startEntry);
User *getUsersFromDatabase();