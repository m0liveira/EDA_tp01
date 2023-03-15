#include <stdio.h>

struct Session {
    int id;
    char name[30];
    char password[30];
    char role[10];
} session;

int isFileEmpty(char dir[]);
int getLastIdFromDb(char dir[]);