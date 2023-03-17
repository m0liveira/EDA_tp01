#include <stdlib.h>
#include <string.h>
#include "../headers/global.h"
#include "../headers/rents.h"

int isRentUnique(Rent *startEntry, int id){
    while (startEntry != NULL){
        if (startEntry->id == id) return (0);

        startEntry = startEntry->nextEntry;
    }

    return (1);
}

int isRented(Rent *startEntry, int id){
    while (startEntry != NULL){
        if (startEntry->id == id) return (0);

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

        printf("Veiculo alugado!\n\n");

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