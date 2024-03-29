#include <stdlib.h>
#include <string.h>
#include "../headers/global.h"
#include "../headers/vehicles.h"

/*!
    * @brief Check vehicle ID
    *
    * Checks if the ID is dupped
    *
    * @param Vehicle *startEntry @param int id
    * @return 1 or 0 as true or false
*/

int isUnique(Vehicle *startEntry, int id){
    while (startEntry != NULL){
        if (startEntry->id == id) return (0);

        startEntry = startEntry->nextEntry;
    }

    return (1);
}

/*!
    * @brief Add vehicle
    *
    * Adds a new vehicle entry into a linked list
    *
    * @param Vehicle *startEntry @param int id @param float batteryCapacity @param int currentBattery @param float autonomy @param float price @param char brand[] @param char model[] @param char gpsTracker[]
    * @return Added vehicle
*/

Vehicle *addVehicles(Vehicle *startEntry, int id, float batteryCapacity, int currentBattery, float autonomy, float price, char brand[], char model[], char gpsTracker[]){
    if (!isUnique(startEntry, id)){
        printf("\nErro: Este ID ja foi registado!\n");
        return (startEntry);
    }

    Vehicle *newEntry = malloc(sizeof(struct VehicleList));

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

/*!
    * @brief List vehicles
    *
    * Outputs all vehicles
    *
    * @param Vehicle *startEntry
*/

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

/*!
    * @brief Delete vehicle
    *
    * Deletes a vehicle entry from the linked list
    *
    * @param Vehicle *startEntry @param int id
    * @return vehicles
*/

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

/*!
    * @brief Update vehicle
    *
    * Updates a specified vehicle entry from the linked list
    *
    * @param Vehicle *startEntry @param int id @param int currentBattery @param char gpsTracker[]
    * @return vehicles
*/

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

/*!
    * @brief Save vehicle on database
    *
    * Saves vehicles entrys into a database
    *
    * @param Vehicle *startEntry
    * @return 1 or 0 as true or false
*/

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

/*!
    * @brief Save vehicle on binary database
    *
    * Saves vehicles entrys into a binary database
    *
    * @param Vehicle *startEntry
    * @return 1 or 0 as true or false
*/

int saveVehiclesOnBinaryDatabase(Vehicle *startEntry) {
    Vehicle* aux = startEntry;
    FILE* fp;

    fp = fopen("../databases/vehicles_database.bin", "wb");

    if (fp == NULL) return 0;

    while (aux != NULL) {
        fwrite(&aux->id, sizeof(int), 1, fp);
        fwrite(&aux->batteryCapacity, sizeof(float), 1, fp);
        fwrite(&aux->currentBattery, sizeof(int), 1, fp);
        fwrite(&aux->autonomy, sizeof(float), 1, fp);
        fwrite(&aux->price, sizeof(float), 1, fp);
        fwrite(aux->brand, sizeof(char), strlen(aux->brand) + 1, fp);
        fwrite(aux->model, sizeof(char), strlen(aux->model) + 1, fp);
        fwrite(aux->gpsTracker, sizeof(char), strlen(aux->gpsTracker) + 1, fp);

        aux = aux->nextEntry;
    }

    fclose(fp);

    return 1;
}

/*!
    * @brief Get vehicles
    *
    * Gets all vehicles from a database
    *
    * @return vehicles
*/

Vehicle *getVehiclesFromDatabase(){
    Vehicle *vehicles = NULL, *stack = NULL;
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

/*!
    * @brief List vehicles by autonomy
    *
    * Outputs vehicles sorted by autonomy
    *
    * @param Vehicle *startEntry
*/

void listVehiclesByAutnonomy(Vehicle *startEntry) {
    if (startEntry == NULL) {
        printf("Nao ha veiculos guardados\n\n");
        return;
    }

    int count = 0;
    Vehicle **array = NULL;
    Vehicle *current = startEntry;
    while (current != NULL) {
        count++;
        array = realloc(array, count * sizeof(Vehicle *));
        array[count - 1] = current;
        current = current->nextEntry;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (array[i]->autonomy < array[j]->autonomy) {
                Vehicle *temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    printf("Lista de veiculos por autonomia!\n\n");

    for (int i = 0; i < count; i++) {
        Vehicle *vehicle = array[i];
        printf("Id: %d\n", vehicle->id);
        printf("Marca: %s\n", vehicle->brand);
        printf("Modelo: %s\n", vehicle->model);
        printf("Capacidade de bateria (Ah): %.2f\n", vehicle->batteryCapacity);
        printf("Bateria atual (%%): %d%%\n", vehicle->currentBattery);
        printf("Autonomia (Km): %.2f\n", vehicle->autonomy);
        printf("Preco de aluguer (eur): %.2f euros\n", vehicle->price);
        printf("Localizacao do veiculo: %s\n\n", vehicle->gpsTracker);
    }

    free(array);
}

/*!
    * @brief List vehicles by GPS
    *
    * Outputs vehicles in a specific GPS location
    *
    * @param Vehicle *startEntry @param char location[]
*/

void listVehiclesByGPS(Vehicle *startEntry, char location[]){
    if (startEntry == NULL){
        printf("Nao ha veiculos guardados\n\n");
        return;
    }

    printf("Lista de veiculos na area %s!\n\n", location);

    while (startEntry != NULL){
        if (strcmp(startEntry->gpsTracker, location) == 0) {
            printf("Id: %d", startEntry->id);
            printf("\nMarca: %s", startEntry->brand);
            printf("\nModelo: %s", startEntry->model);
            printf("\nCapacidade de bateria (Ah): %.2f", startEntry->batteryCapacity);
            printf("\nBateria atual (%%): %d%%", startEntry->currentBattery);
            printf("\nAutonomia (Km): %.2f", startEntry->autonomy);
            printf("\nPreco de aluguer (eur): %.2f euros", startEntry->price);
            printf("\nLocalizacao do veiculo: %s\n\n", startEntry->gpsTracker);
        }
        
        startEntry = startEntry->nextEntry;
    }
}

/*!
    * @brief Get vehicle by ID
    *
    * Stores a specific vehicle data in a struct
    *
    * @param Vehicle *startEntry @param int id
*/

void getVehicleByID(Vehicle *startEntry, int id){
    while (startEntry != NULL){
        if (startEntry->id == id) {
            car.id = startEntry->id;
            car.batteryCapacity = startEntry->batteryCapacity;
            car.currentBattery = startEntry->currentBattery;
            car.autonomy = startEntry->autonomy;
            car.price = startEntry->price;
            strcpy(car.brand, startEntry->brand);
            strcpy(car.model, startEntry->model);
            strcpy(car.gpsTracker, startEntry->gpsTracker);

            return;
        };

        startEntry = startEntry->nextEntry;
    }
}

/*!
    * @brief Vehicle exist
    *
    * Checks if a specified vehicle exists at the linked list
    *
    * @param Vehicle *startEntry @param int id
    * @return 1 or 0 as true or false
*/

int vehicleExists(Vehicle *startEntry, int id){
    while (startEntry != NULL){
        if (startEntry->id == id) return 1;

        startEntry = startEntry->nextEntry;
    }

    return 0;
}

/*!
    * @brief Recharge vehicles
    *
    * Recharges all vehicles stored in the linked list
    *
    * @param Vehicle *startEntry
    * @return vehicles
*/

Vehicle *rechargeVehicles(Vehicle *startEntry){
    Vehicle *currentEntry = startEntry;

    if (currentEntry == NULL) {
        printf("\nNao ha veiculos registados!\n\n");
        return NULL;
    }

    while (currentEntry != NULL) {
        if (currentEntry->currentBattery <= 50) currentEntry->currentBattery = 100;

        currentEntry = currentEntry->nextEntry;
    }
    
    printf("Todos os veiculos com bateria <= a 50/100 foram recarregados!\n\n");
    return startEntry;
}