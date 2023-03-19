#include <stdlib.h>
#include <string.h>
#include "../headers/global.h"
#include "../headers/users.h"

/*!
    * @brief Check user ID
    *
    * Checks if the ID is dupped
    *
    * @param User *startEntry @param int id
    * @return 1 or 0 as true or false
*/

int isUserUnique(User *startEntry, int id){
    while (startEntry != NULL){
        if (startEntry->id == id) return (0);

        startEntry = startEntry->nextEntry;
    }

    return (1);
}

/*!
    * @brief Check user name
    *
    * Checks if the user name is dupped
    *
    * @param User *startEntry @param char name[]
    * @return 1 or 0 as true or false
*/

int isNameUnique(User *startEntry, char name[]){
    while (startEntry != NULL){
        if (strcmp(startEntry->name, name) == 0) return (0);

        startEntry = startEntry->nextEntry;
    }

    return (1);
}

/*!
    * @brief Add user
    *
    * Adds a new user entry into a linked list
    *
    * @param User *startEntry @param int id @param int nif @param float balance @param char name[] @param char password[] @param char role[]
    * @return Added user
*/

User *addUser(User *startEntry, int id, int nif, float balance, char name[], char password[], char role[]){
    User *newEntry = malloc(sizeof(struct UserList));

    if (!isUserUnique(startEntry, id)){
        printf("Erro: Este ID ja foi registado!\n");
        return (startEntry);
    }

    if (!isNameUnique(startEntry, name)){
        printf("Erro: Este nome (%s) ja foi registado!\n", name);
        return (startEntry);
    }

    if (newEntry != NULL){
        newEntry->id = id;
        newEntry->nif = nif;
        newEntry->balance = balance;
        strcpy(newEntry->name, name);
        strcpy(newEntry->password, password);
        strcpy(newEntry->role, role);
        newEntry->nextEntry = startEntry;

        return (newEntry);
    }
}

/*!
    * @brief User login
    *
    * Logins a user into the program
    *
    * @param User *startEntry @param char name[] @param char password[]
    * @return 1 or 0 as true or false
*/

int loginUser(User *startEntry, char name[], char password[]){
    while (startEntry != NULL){
        if (strcmp(startEntry->name, name) == 0 && strcmp(startEntry->password, password) == 0) {
            session.id = startEntry->id;
            session.nif = startEntry->nif;
            session.balance = startEntry->balance;
            strcpy(session.name, startEntry->name);
            strcpy(session.password, startEntry->password);
            strcpy(session.role, startEntry->role);

            return (1);
        }

        startEntry = startEntry->nextEntry;
    }

    return 0;
}

/*!
    * @brief Save user on database
    *
    * Saves user entrys into a database
    *
    * @param User *startEntry
    * @return 1 or 0 as true or false
*/

int saveUsersOnDatabase(User *startEntry){
    User* aux = startEntry;
    FILE* fp;

    fp = fopen("../databases/users_database.txt","w");

    if (fp==NULL) return(0);

    while (aux != NULL) {
        fprintf(fp,"Id:%d;Name:%s;Password:%s;Nif:%d;Balance:%.2f;Role:%s;\n", aux->id, aux->name, aux->password, aux->nif, aux->balance, aux->role);

        aux = aux->nextEntry;
    }

    fclose(fp);

    return(1);
}

/*!
    * @brief Get Users
    *
    * Gets all users from a database
    *
    * @return users
*/

User *getUsersFromDatabase(){
    User *users = NULL, *stack = NULL;;
    FILE *fp;
    int id, nif;
    float balance;
    char name[30], password[30], role[10];

    fp = fopen("../databases/users_database.txt","r");

    if (fp == NULL) return users;

    if (isFileEmpty("../databases/users_database.txt") == 1) return users;

    while (fscanf(fp, "Id:%d;Name:%[^;];Password:%[^;];Nif:%d;Balance:%f;Role:%[^;\n];\n", &id, name, password, &nif, &balance, role) == 6) {
        stack = addUser(stack, id, nif, balance, name, password, role);
    }

    fclose(fp);

    while (stack != NULL) {
        users = addUser(users, stack->id, stack->nif, stack->balance, stack->name, stack->password, stack->role);
        stack = stack->nextEntry;
    }
    
    return(users);
}

/*!
    * @brief Delete user
    *
    * Deletes an user entry from the linked list
    *
    * @param User *startEntry @param int id
    * @return users
*/

User *deleteUser(User *startEntry, int id){
    User *previousEntry = startEntry, *currentEntry = startEntry, *aux;

    if (currentEntry == NULL) {
        printf("\nO utilizador indicado nao esta registado!\n\n");
        return(NULL);
    }
    
    if (currentEntry->id == id) {
        aux = currentEntry->nextEntry;
        free(currentEntry);
        return(aux);
    } 
   
    while ((currentEntry != NULL) && (currentEntry->id != id)) {
        previousEntry = currentEntry;
        currentEntry = currentEntry->nextEntry;
    }
    
    if (currentEntry != NULL) {
        previousEntry->nextEntry = currentEntry->nextEntry;
        free(currentEntry);
        return(startEntry);
    }

    printf("\nO utilizador indicado nao esta registado!\n\n");
    return(startEntry);
}

/*!
    * @brief Update user
    *
    * Updates a specified user entry from the linked list
    *
    * @param User *startEntry @param int id
    * @return users
*/

User *editUser(User *startEntry, int id){
    User *previousEntry = startEntry, *currentEntry = startEntry;

    if (currentEntry==NULL) {
        printf("\nO utilizador indicado nao esta registado!\n\n");
        return(NULL);
    }

    while ((currentEntry != NULL) && (currentEntry->id != id)) {
        previousEntry = currentEntry;
        currentEntry = currentEntry->nextEntry;
    }
    
    if (currentEntry != NULL) {
        currentEntry->balance = session.balance;
        strcpy(currentEntry->password, session.password);
        return(startEntry);
    }

    printf("\nO utilizador indicado nao esta registado!\n\n");
    return(startEntry);
}