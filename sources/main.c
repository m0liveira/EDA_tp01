#include <stdio.h>
#include <stdlib.h>
#include "../headers/vehicles.h"

void clearConsole(){
    system("cls||clear");
}

void mainMenu(){
    printf("\n1: Inserir transportes\n");
    printf("2: Listar transportes\n");
    printf("3: Remover transportes\n");
    printf("0: Sair\n");
    printf("Opcao: ");
}

int main(){
    Vehicle* vehicles = NULL;
    int input = -1, vehicleID = 1;
    float batteryCapacity, autonomy, pricePerKm;
    char brand[20], model[20];

    do{
        mainMenu();
        scanf("%d", &input);
        fflush(stdin);
        clearConsole();

        switch (input){
        case 0:
            printf("A sair\n");
            break;

        case 1:
            printf("Codigo: %d", vehicleID);
            printf("\nMarca: ");
            scanf("%s", brand);
            fflush(stdin);
            printf("\nModelo: ");
            scanf("%s", model);
            fflush(stdin);
            printf("\nCapacidade da bateria: ");
            scanf("%f", &batteryCapacity);
            printf("\nAutonomia: ");
            scanf("%f", &autonomy);
            printf("\nPreco por Km: ");
            scanf("%f", &pricePerKm);
            vehicles = addVehicles(vehicles, vehicleID, batteryCapacity, autonomy, pricePerKm, brand, model);
            vehicleID++;

            printf("\n carro: %s %s  bateria: %d%%", vehicles->brand, vehicles->model, vehicles->currentBattery);
            break;

        case 2:
            printf("Transporte a listar\n");
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