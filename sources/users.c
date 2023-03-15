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
    User *newEntry = malloc(sizeof(struct UserList));

    if (!isUserUnique(startEntry, id)){
        printf("Erro: Este ID ja foi registado!\n\n");
        return (startEntry);
    }

    if (!isNameUnique(startEntry, name)){
        printf("Erro: Este nome (%s) ja foi registado!\n\n", name);
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

int loginUser(User *startEntry, char name[], char password[]){
    while (startEntry != NULL){
        if (strcmp(startEntry->name, name) == 0 && strcmp(startEntry->password, password) == 0) {
            session.id = startEntry->id;
            strcpy(session.name, startEntry->name);
            strcpy(session.password, startEntry->password);
            strcpy(session.role, startEntry->role);

            return (1);
        }

        startEntry = startEntry->nextEntry;
    }

    return 0;
}

int saveUsersOnDatabase(User *startEntry){
    User* aux = startEntry;
    FILE* fp;

    fp = fopen("../databases/users_database.txt","w");

    if (fp==NULL) return(0);

    while (aux != NULL) {
        fprintf(fp,"Id:%d;Name:%s;Password:%s;Role:%s;\n", aux->id, aux->name, aux->password, aux->role);

        aux = aux->nextEntry;
    }

    fclose(fp);

    return(1);
}