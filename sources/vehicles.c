#include <stdlib.h>
#include <string.h>
#include "../headers/vehicles.h"

int isUnique(Vehicle *startEntry, int id){
    while (startEntry != NULL){
        if (startEntry->id == id) return (0);

        startEntry = startEntry->nextEntry;
    }

    return (1);
}

Vehicle *addVehicles(Vehicle *startEntry, int id, float batteryCapacity, float autonomy, float price, char brand[], char model[]){
    if (!isUnique(startEntry, id)){
        printf("\nErro: Este ID ja foi registado!\n");
        return (startEntry);
    }

    Vehicle *newEntry = malloc(sizeof(struct vehicleList));

    if (newEntry != NULL){
        newEntry->id = id;
        newEntry->batteryCapacity = batteryCapacity;
        newEntry->currentBattery = 100;
        newEntry->autonomy = autonomy;
        newEntry->price = price;
        strcpy(newEntry->brand, brand);
        strcpy(newEntry->model, model);
        strcpy(newEntry->gpsTracker, "https://w3w.co/origem.rias.pontos");
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