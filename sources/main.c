#include <stdio.h>
#include <stdlib.h>
#include "../headers/global.h"
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

Vehicle *addNewVehicle(Vehicle *vehicles, int id){
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

    vehicles = addVehicles(vehicles, id, batteryCapacity, 100, autonomy, price, brand, model, "origem.rias.pontos");

    return vehicles;
}

int getId(char phrase[]){
    int id = 0;

    printf("%s", phrase);
	scanf("%d", &id);

    return id;
}

int main(){
    Vehicle *vehicles = NULL;
    int input = -1, vehicleId = 1;

    vehicles = getVehiclesFromDatabase();
    vehicleId = getLastIdFromDb("../databases/vehicles_database.txt");

    do{
        mainMenu();
        scanf("%d", &input);
        fflush(stdin);

        switch (input){
        case 0:
            clearConsole();
            printf("A sair!");
            break;

        case 1:
            clearConsole();
            vehicles = addNewVehicle(vehicles, vehicleId);
            saveVehiclesOnDatabase(vehicles);
            vehicleId++;
            break;

        case 2:
            clearConsole();
            listVehicles(vehicles);
            break;

        case 3:
            clearConsole();
	   		vehicles = deleteVehicle(vehicles, getId("Codigo do veiculo a remover: "));
            saveVehiclesOnDatabase(vehicles);
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (input != 0);

    return 0;
}