#include <stdlib.h>
#include <string.h>
#include "../headers/global.h"
#include "../headers/vehicles.h"

int isUnique(Vehicle *startEntry, int id){
    while (startEntry != NULL){
        if (startEntry->id == id) return (0);

        startEntry = startEntry->nextEntry;
    }

    return (1);
}

Vehicle *addVehicles(Vehicle *startEntry, int id, float batteryCapacity, int currentBattery, float autonomy, float price, char brand[], char model[], char gpsTracker[]){
    if (!isUnique(startEntry, id)){
        printf("\nErro: Este ID ja foi registado!\n");
        return (startEntry);
    }

    Vehicle *newEntry = malloc(sizeof(struct vehicleList));

    if (newEntry != NULL){
        newEntry->id = id;
        newEntry->batteryCapacity = batteryCapacity;
        newEntry->currentBattery = currentBattery;
        newEntry->autonomy = autonomy;
        newEntry->price = price;
        strcpy(newEntry->brand, brand);
        strcpy(newEntry->model, model);
        strcpy(newEntry->gpsTracker, gpsTracker);
        newEntry->nextEntry = startEntry;
        return (newEntry);
    }
}

void listVehicles(Vehicle *startEntry){
    if (startEntry == NULL){
        printf("Nao ha veiculos guardados\n\n");
        return;
    }

    printf("Lista de veiculos!\n\n");

    while (startEntry != NULL){
        printf("Id: %d", startEntry->id);
        printf("\nMarca: %s", startEntry->brand);
        printf("\nModelo: %s", startEntry->model);
        printf("\nCapacidade de bateria (Ah): %.2f", startEntry->batteryCapacity);
        printf("\nBateria atual (%%): %d%%", startEntry->currentBattery);
        printf("\nAutonomia (Km): %.2f", startEntry->autonomy);
        printf("\nPreco de aluguer (eur): %.2f euros", startEntry->price);
        printf("\nLocalizacao do veiculo: %s\n\n", startEntry->gpsTracker);

        startEntry = startEntry->nextEntry;
    }
}

Vehicle *deleteVehicle(Vehicle *startEntry, int id){
    Vehicle *previousEntry=startEntry, *currentEntry=startEntry, *aux;

    if (currentEntry==NULL) {
        printf("\nO veiculo indicado nao esta registado!\n\n");
        return(NULL);
    }
    
    if (currentEntry->id == id) {
        aux = currentEntry->nextEntry;
        free(currentEntry);
        return(aux);
    } 
   
    while ((currentEntry!=NULL)&&(currentEntry->id!=id)) {
        previousEntry = currentEntry;
        currentEntry = currentEntry->nextEntry;
    }
    
    if (currentEntry!=NULL) {
        previousEntry->nextEntry = currentEntry->nextEntry;
        free(currentEntry);
        return(startEntry);
    }

    printf("\nO veiculo indicado nao esta registado!\n\n");
    return(startEntry);
}

Vehicle *editVehicle(Vehicle *startEntry, int id, int currentBattery, char gpsTracker[]){
    Vehicle *previousEntry=startEntry, *currentEntry=startEntry;

    if (currentEntry==NULL) {
        printf("\nO veiculo indicado nao esta registado!\n\n");
        return(NULL);
    }

    while ((currentEntry!=NULL)&&(currentEntry->id!=id)) {
        previousEntry = currentEntry;
        currentEntry = currentEntry->nextEntry;
    }
    
    if (currentEntry!=NULL) {
        currentEntry->currentBattery = currentBattery;
        strcpy(currentEntry->gpsTracker, gpsTracker);
        return(startEntry);
    }

    printf("\nO veiculo indicado nao esta registado!\n\n");
    return(startEntry);
}

int saveVehiclesOnDatabase(Vehicle *startEntry){
    Vehicle* aux = startEntry;
    FILE* fp;

    fp = fopen("../databases/vehicles_database.txt","w");

    if (fp==NULL) return(0);

    while (aux != NULL) {
        fprintf(fp,"Id:%d;BatteryCap:%.2f;CurrBattery:%d;Autonomy:%.2f;Price:%.2f;Brand:%s;Model:%s;GPS:%s;\n", aux->id, aux->batteryCapacity, aux->currentBattery, aux->autonomy, aux->price, aux->brand, aux->model, aux->gpsTracker);

        aux = aux->nextEntry;
    }

    fclose(fp);

    return(1);
}

Vehicle *getVehiclesFromDatabase(){
    Vehicle *vehicles = NULL, *stack = NULL;;
    FILE *fp;
    int id, currentBattery;
    float batteryCapacity, autonomy, price;
    char brand[20], model[20], gpsTracker[50];

    fp = fopen("../databases/vehicles_database.txt","r");

    if (fp == NULL) return vehicles;

    if (isFileEmpty("../databases/vehicles_database.txt") == 1) return vehicles;

    while (!feof(fp)) {
        fscanf(fp,"Id:%d;BatteryCap:%f;CurrBattery:%d;Autonomy:%f;Price:%f;Brand:%[^;];Model:%[^;];GPS:%[^;\n];\n", &id, &batteryCapacity, &currentBattery, &autonomy, &price, brand, model, gpsTracker);
        stack = addVehicles(stack, id, batteryCapacity, currentBattery, autonomy, price, brand, model, gpsTracker);
    }

    fclose(fp);

    while (stack != NULL) {
        vehicles = addVehicles(vehicles, stack->id, stack->batteryCapacity, stack->currentBattery, stack->autonomy, stack->price, stack->brand, stack->model, stack->gpsTracker);
        stack = stack->nextEntry;
    }
    
    return(vehicles);
}