#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/global.h"
#include "../headers/vehicles.h"
#include "../headers/users.h"

void clearConsole(){
    system("cls||clear");
}

void mainMenu(){
    printf("Menu Fase 1");

    if (strcmp(session.role, "client") == 0) {
        printf("\n\n1: Alugar transporte\n");
        printf("2: Consultar saldo\n");
        printf("3: Carregar saldo\n");
        printf("4: Alterar palavra-passe\n");
        printf("5: Apagar conta\n");
        printf("0: Sair");
        printf("\n\nOpcao: "); 
        return;
    };
    
    printf("\n\n1: Inserir transportes\n");
    printf("2: Listar transportes\n");
    printf("3: Listar transportes por autonomia (decrescente)\n");
    printf("4: Remover transportes\n");
    printf("0: Sair");
    printf("\n\nOpcao: ");
}

void loginMenu(){
    printf("Login Menu");
    printf("\n\n1: Entrar\n");
    printf("2: Criar conta\n");
    printf("0: Sair");
    printf("\n\nOpcao: ");
}

Vehicle *newVehicle(Vehicle *vehicles, int id){
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

User *newUser(User *users, int id){
    int nif = 0;
    char name[30], password[30];

    printf("Id: %d", id);

    printf("\nNome: ");
    scanf("%s", name);
    fflush(stdin);

    printf("Password: ");
    scanf("%s", password);
    fflush(stdin);

    printf("Nif: ");
    scanf("%d", &nif);

    printf("Saldo: %.2f euros", 0);

    printf("\n");

    users = addUser(users, id, nif, 0, name, password, "client");

    return users;
}

int getId(char phrase[]){
    int id = 0;

    printf("%s", phrase);
	scanf("%d", &id);

    return id;
}

void depositBalance(){
    float balance = 0;
    printf("Quanto saldo quer depositar: ");
    scanf("%f", &balance);
    fflush(stdin);

    session.balance += balance;
}

int main(){
    Vehicle *vehicles = NULL;
    User *users = NULL;
    int input = -1, vehicleId = 1, userId = 1;
    
    users = getUsersFromDatabase();
    userId = getLastIdFromDb("../databases/users_database.txt");

    do{
        loginMenu();
        scanf("%d", &input);
        fflush(stdin);
        
        switch (input) {
            case 0:
                clearConsole();
                printf("A sair!");
            break;

            case 1:
                clearConsole();
                input = -1;

                printf("Nome: ");
                scanf("%s", session.name);
                fflush(stdin);

                printf("\nPassword: ");
                scanf("%s", session.password);
                fflush(stdin);

                if (!loginUser(users, session.name, session.password)){
                    printf("\nDados incorretos\n\n");
                    break;
                }

                clearConsole();
                vehicles = getVehiclesFromDatabase();
                vehicleId = getLastIdFromDb("../databases/vehicles_database.txt");

                do {
                    mainMenu();
                    scanf("%d", &input);
                    fflush(stdin);

                    if (strcmp(session.role, "client") == 0) {
                        switch (input){
                            case 0:
                                clearConsole();
                                printf("A sair!");
                            break;

                            case 1:
                                clearConsole();

                            break;

                            case 2:
                                clearConsole();
                                printf("Saldo: %.2f euros\n\n", session.balance);
                            break;

                            case 3:
                                clearConsole();
                                depositBalance();
                                users = editUser(users, session.id);
                                saveUsersOnDatabase(users);
                            break;

                            case 4:
                                clearConsole();
	   		                    printf("Nova palavra-passe: ");
                                scanf("%s", &session.password);
                                fflush(stdin);
                                users = editUser(users, session.id);
                                saveUsersOnDatabase(users);
                            break;

                            case 5:
                                clearConsole();
	   		                    users = deleteUser(users, session.id);
                                saveUsersOnDatabase(users);
                                printf("A encerrar programa...");
                                input = 0;
                            break;

                            default:
                                clearConsole();
                                printf("Opcao invalida!\n");
                            break;
                        }
                    } else {
                        switch (input){
                            case 0:
                                clearConsole();
                                printf("A sair!");
                            break;

                            case 1:
                                clearConsole();
                                vehicles = newVehicle(vehicles, vehicleId);
                                saveVehiclesOnDatabase(vehicles);
                                vehicleId = getLastIdFromDb("../databases/vehicles_database.txt");
                            break;

                            case 2:
                                clearConsole();
                                listVehicles(vehicles);
                            break;

                            case 3:
                                clearConsole();
	   		                    listVehiclesByAutnonomy(vehicles);
                            break;

                            case 4:
                                clearConsole();
	   		                    vehicles = deleteVehicle(vehicles, getId("Codigo do veiculo a remover: "));
                                saveVehiclesOnDatabase(vehicles);
                            break;

                            default:
                                clearConsole();
                                printf("Opcao invalida!\n");
                            break;
                        }
                    }
                } while (input != 0);
            break;

            case 2:
                clearConsole();
                users = newUser(users, userId);
                saveUsersOnDatabase(users);
                userId = getLastIdFromDb("../databases/users_database.txt");
            break;

            default:
                clearConsole();
                printf("Opcao invalida!\n\n");
            break;
        }
    } while (input != 0);

    return 0;
}