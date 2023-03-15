#include <stdlib.h>
#include <string.h>
#include "../headers/global.h"
#include "../headers/users.h"

int isUserUnique(User *startEntry, int id){
    while (startEntry != NULL){
        if (startEntry->id == id) return (0);

        startEntry = startEntry->nextEntry;
    }

    return (1);
}

int isNameUnique(User *startEntry, char name[]){
    while (startEntry != NULL){
        if (strcmp(startEntry->name, name) == 0) return (0);

        startEntry = startEntry->nextEntry;
    }

    return (1);
}

User *addUser(User *startEntry, int id, char name[], char password[], char role[]){
    User *newEntry = malloc(sizeof(struct userList));

    if (!isUserUnique(startEntry, id)){
        printf("\nErro: Este ID ja foi registado!\n");
        return (startEntry);
    }

    if (!isNameUnique(startEntry, name)){
        printf("\nErro: Este nome (%s) ja foi registado!\n", name);
        return (startEntry);
    }

    if (newEntry != NULL){
        newEntry->id = id;
        strcpy(newEntry->name, name);
        strcpy(newEntry->password, password);
        strcpy(newEntry->role, role);
        newEntry->nextEntry = startEntry;

        return (newEntry);
    }
}