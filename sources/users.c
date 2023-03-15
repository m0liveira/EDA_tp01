#include <stdlib.h>
#include <string.h>
#include "../headers/global.h"
#include "../headers/users.h"

User *addUser(User *startEntry, int id, char name[], char password[], char role[]){
    User *newEntry = malloc(sizeof(struct userList));

    if (newEntry != NULL){
        newEntry->id = id;
        strcpy(newEntry->name, name);
        strcpy(newEntry->password, password);
        strcpy(newEntry->role, role);
        newEntry->nextEntry = startEntry;

        return (newEntry);
    }
}