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

Vehicle* addVehicles(Vehicle *startEntry, int id, float batteryCapacity, float autonomy, float pricePerKm, char brand[], char model[]){
    if (isUnique(startEntry, id)){
        Vehicle *newEntry = malloc(sizeof(struct vehicleList));

        if (newEntry != NULL){
            newEntry->id = id;
            newEntry->batteryCapacity = batteryCapacity;
            newEntry->currentBattery = 100;
            newEntry->autonomy = autonomy;
            newEntry->pricePerKm = pricePerKm;
            strcpy(newEntry->brand, brand);
            strcpy(newEntry->model, model);
            strcpy(newEntry->gpsTracker, "https://w3w.co/origem.rias.pontos");
            newEntry->nextEntry = startEntry;
            return (newEntry);
        }
    } else {
        printf("\nErro: ID já registado!\n");
        return (startEntry);
    }
}