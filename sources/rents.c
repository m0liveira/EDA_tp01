#include <stdlib.h>
#include <string.h>
#include "../headers/global.h"
#include "../headers/rents.h"
#include "../headers/users.h"

int isRentUnique(Rent *startEntry, int id){
    while (startEntry != NULL){
        if (startEntry->id == id) return (0);

        startEntry = startEntry->nextEntry;
    }

    return (1);
}

int isRented(Rent *startEntry, int vehicleId){
    while (startEntry != NULL){
        if (startEntry->vehicleId == vehicleId && strcmp(startEntry->status, "active") == 0) return (0);

        startEntry = startEntry->nextEntry;
    }

    return (1);
}

Rent *addRent(Rent *startEntry, int id, int clientId, int vehicleId, char status[]){
    Rent *newEntry = malloc(sizeof(struct RentList));

    if (!isRentUnique(startEntry, id)){
        printf("Erro: Este ID ja foi registado!\n\n");
        return (startEntry);
    }

    if (!isRented(startEntry, vehicleId)){
        printf("Erro: Este veiculo ja foi alugado por outro cliente!\n\n");
        return (startEntry);
    }

    if (newEntry != NULL){
        newEntry->id = id;
        newEntry->clientId = clientId;
        newEntry->vehicleId = vehicleId;
        strcpy(newEntry->status, status);
        newEntry->nextEntry = startEntry;

        return (newEntry);
    }
}

int saveRentOnDatabase(Rent *startEntry){
    Rent* aux = startEntry;
    FILE* fp;

    fp = fopen("../databases/rents_database.txt","w");

    if (fp==NULL) return(0);

    while (aux != NULL) {
        fprintf(fp,"Id:%d;ClientID:%d;VehicleID:%d;Status:%s;\n", aux->id, aux->clientId, aux->vehicleId, aux->status);

        aux = aux->nextEntry;
    }

    fclose(fp);

    return(1);
}

Rent *getRentsFromDatabase(){
    Rent *rents = NULL, *stack = NULL;;
    FILE *fp;
    int id, clientId, vehicleId;
    char status[10];

    fp = fopen("../databases/rents_database.txt","r");

    if (fp == NULL) return rents;

    if (isFileEmpty("../databases/rents_database.txt") == 1) return rents;

    while (fscanf(fp, "Id:%d;ClientID:%d;VehicleID:%d;Status:%[^;\n];\n", &id, &clientId, &vehicleId, status) == 4) {
        stack = addRent(stack, id, clientId, vehicleId, status);
    }

    fclose(fp);

    while (stack != NULL) {
        rents = addRent(rents, stack->id, stack->clientId, stack->vehicleId, stack->status);
        stack = stack->nextEntry;
    }
    
    return(rents);
}

Rent *updateRent(Rent *startEntry, int id){
    Rent *previousEntry = startEntry, *currentEntry = startEntry;

    if (currentEntry==NULL) {
        printf("\nO aluguer indicado nao existe!\n\n");
        return(NULL);
    }

    while ((currentEntry != NULL) && (currentEntry->id != id)) {
        previousEntry = currentEntry;
        currentEntry = currentEntry->nextEntry;
    }
    
    if (currentEntry != NULL) {
        strcpy(currentEntry->status, "returned");
        return(startEntry);
    }

    printf("\nO aluguer indicado nao existe!\n\n");
    return(startEntry);
}

void listUserRents(Rent *startEntry){
    if (startEntry == NULL){
        printf("Nao ha veiculos guardados\n\n");
        return;
    }

    printf("Lista de alugueres!\n\n");

    while (startEntry != NULL){
        if (session.id == startEntry->clientId) {
            printf("Id: %d, id do veiculo: %d -> status: %s\n\n", startEntry->id, startEntry->vehicleId, startEntry->status);
        }
        
        startEntry = startEntry->nextEntry;
    }
}

void listUserActiveRents(Rent *startEntry){
    if (startEntry == NULL){
        printf("Nao ha veiculos guardados\n\n");
        return;
    }

    printf("Lista de alugueres ativos!\n\n");

    while (startEntry != NULL){
        if (session.id == startEntry->clientId && strcmp(startEntry->status, "active") == 0) {
            printf("Id: %d, id do veiculo: %d -> status: %s\n\n", startEntry->id, startEntry->vehicleId, startEntry->status);
        }
        
        startEntry = startEntry->nextEntry;
    }
}