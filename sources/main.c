#include <stdio.h>
#include <stdlib.h>
#include "../headers/vehicles.h"

void clearConsole(){
    system("cls||clear");
}

void mainMenu(){
    printf("Menu Fase 1");
    printf("\n\n1: Inserir transportes\n");
    printf("2: Listar transportes\n");
    printf("3: Remover transportes\n");
    printf("0: Sair");
    printf("\n\nOpcao: ");
}

Vehicle* addNewVehicle(Vehicle* vehicles, int id){
    float batteryCapacity, autonomy, price;
    char brand[20], model[20];

    printf("Id: %d", id);

    printf("\nMarca: ");
    scanf("%s", brand);
    fflush(stdin);

    printf("Modelo: ");
    scanf("%s", model);
    fflush(stdin);

    printf("Capacidade da bateria (Ah): ");
    scanf("%f", &batteryCapacity);

    printf("Bateria atual (%%): 100%%");

    printf("\nAutonomia (Km): ");
    scanf("%f", &autonomy);

    printf("Preco de aluguer (eur): ");
    scanf("%f", &price);

    printf("\n");

    vehicles = addVehicles(vehicles, id, batteryCapacity, autonomy, price, brand, model);

    return vehicles;
}

int main(){
    Vehicle* vehicles = NULL;
    int input = -1, vehicleId = 1;

    do{
        mainMenu();
        scanf("%d", &input);
        fflush(stdin);
        clearConsole();

        switch (input){
        case 0:
            printf("A sair!");
            break;

        case 1:
            vehicles = addNewVehicle(vehicles, vehicleId);
            vehicleId++;
            break;

        case 2:
            ListVehicles(vehicles);
            break;

        case 3:
            printf("Transporte a remover\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (input != 0);

    return 0;
}