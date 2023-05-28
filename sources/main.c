#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/global.h"
#include "../headers/vehicles.h"
#include "../headers/users.h"
#include "../headers/rents.h"
#include "../headers/graphs.h"

/*!
    * @brief Clear console
    *
    * Clears the console outputs.
*/

void clearConsole(){
    system("cls||clear");
}

/*!
    * @brief Main menu
    *
    * Outputs a different menu for each user role.
*/

void mainMenu(){
    printf("Menu Fase 1");

    if (strcmp(session.role, "client") == 0) {
        printf("\n\n1: Alugar veiculo\n");
        printf("2: Entregar veiculo\n");
        printf("3: Consultar alugueres\n");
        printf("4: Consultar veiculos numa area\n");
        printf("5: Consultar saldo\n");
        printf("6: Carregar saldo\n");
        printf("7: Alterar palavra-passe\n");
        printf("8: Apagar conta\n");
        printf("0: Sair");
        printf("\n\nOpcao: "); 
        return;
    };
    
    printf("\n\n1: Inserir veiculos\n");
    printf("2: Listar veiculos\n");
    printf("3: Listar veiculos por autonomia (decrescente)\n");
    printf("4: Listar veiculos numa area\n");
    printf("5: Recarregar veiculos\n");
    printf("6: Remover veiculos\n");
    printf("7: Listar alugueres\n");
    printf("8: Listar ganhos\n");
    printf("9: calcular percurso mais rapido para recolha de veiculos\n");
    printf("0: Sair");
    printf("\n\nOpcao: ");
}

/*!
    * @brief Login menu
    *
    * Outputs a menu so the user can login into the app and create an account.
*/

void loginMenu(){
    printf("Login Menu");
    printf("\n\n1: Entrar\n");
    printf("2: Criar conta\n");
    printf("0: Sair");
    printf("\n\nOpcao: ");
}

/*!
    * @brief New vehicle.
    *
    * Outputs and ask for input for the admin to add a new vehicle
    *
    * @param Vehicle *vehicles @param int id
    * @return Added vehicle
*/

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

/*!
    * @brief New user.
    *
    * Outputs and ask for input for the user to create an account
    *
    * @param User *users @param int id
    * @return Added user
*/

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

/*!
    * @brief New rent.
    *
    * Outputs and ask for input for the user to rent a vehicle
    * Deducts the cost of the vehicle from the user balance
    * 
    * @param Vehicle *vehicles @param int id
    * @return Added vehicle
*/

Rent *newRent(Rent *rents, Vehicle *vehicles, User *users, int id){
    int vehicleId = 0;

    printf("\n\nId: %d", id);
    printf("\nId do cliente: %d", session.id);
    printf("\nNome do cliente: %s", session.name);
    printf("\nId do veiculo a alugar: ");
    scanf("%d", &vehicleId);
    fflush(stdin);

    clearConsole();

    if (!vehicleExists(vehicles, vehicleId)){
        printf("Erro: Este veiculo nao existe!\n\n");
        return (rents);
    }

    getVehicleByID(vehicles, vehicleId);

    if (car.price > session.balance) {
        printf("saldo insuficiente! Necessita de %.2f euros para alugar este veiculo\n\n", car.price - session.balance);
        return rents;
    }

    rents = addRent(rents, id, session.id, vehicleId, "active");

    session.balance -= car.price;
    users = editUser(users, session.id);
    saveUsersOnDatabase(users);
    saveUsersOnBinaryDatabase(users);

    return rents;
}

/*!
    * @brief Get ID.
    *
    * Gets an ID
    *
    * @param char phrase[]
    * @return ID
*/

int getId(char phrase[]){
    int id = 0;

    printf("%s", phrase);
	scanf("%d", &id);

    return id;
}

/*!
    * @brief Deposit balance.
    *
    * Ask for input for the user to add balance
*/

void depositBalance(){
    float balance = 0;
    printf("Quanto saldo quer depositar: ");
    scanf("%f", &balance);
    fflush(stdin);

    session.balance += balance;
}

/*!
    * @brief Get profit
    *
    * Outputs the income made from the vehicles renting
    *
    * @param Rent *startEntry @param Vehicle *entrys
*/

void getProfits(Rent *startEntry, Vehicle *entrys){
    float income = 0.00;

    if (startEntry == NULL){
        printf("Nao ha veiculos guardados\n\n");
        return;
    }

    while (startEntry != NULL){
        getVehicleByID(entrys, startEntry->vehicleId);
        income += car.price;
        startEntry = startEntry->nextEntry;
    }

    printf("Ganhos de aluguer: %.2f euros\n\n", income);
}

/*!
    * @brief Get linked lists length.
    *
    * Gets the lenght of a linked list
    *
    * @param Graph *graph
    * @return length
*/

int getLinkedListLength(Graph *graph) {
    int length = 0;

    while (graph != NULL) {
        length++;
        graph = graph->nextEntry;
    }

    return length;
}

/*!
    * @brief Generate random number.
    *
    * Generates a random number betwwen two values
    *
    * @param int min @param int max
    * @return number
*/

int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

/*!
    * @brief Build graph.
    *
    * Builds the graph by using other functions throughout the code
    *
    * @param Graph *graphs @param Edge *edges
*/

Edge *buildGraph(Graph *graphs, Edge *edges){
    srand(time(NULL));

    int numVertices = getLinkedListLength(graphs);
    int maxPossibleEdges = numVertices * (numVertices - 1) / 2;
    int rnd = generateRandomNumber(numVertices - 1, maxPossibleEdges);

    return edges = generateRandomGraph(graphs, edges, numVertices, rnd);
}

int main(){
    Vehicle *vehicles = NULL;
    User *users = NULL;
    Rent *rents = NULL;
    Graph *graphs = NULL;
    Edge *edges = NULL;
    Aux *aux = NULL;
    int input = -1, verticesId = 1, vehicleId = 1, userId = 1, rentId = 1, updateRentId = 0, vehicleBattery = 0, zone = 0;
    char location[50];

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

                rents = getRentsFromDatabase();
                rentId = getLastIdFromDb("../databases/rents_database.txt");

                graphs = getVerticesFromDatabase();
                verticesId = getLastVerticeFromDb("../databases/vertices_database.txt");
                edges = buildGraph(graphs, edges);

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
                                listVehicles(vehicles);

                                rents = newRent(rents, vehicles, users, rentId);
                                saveRentOnDatabase(rents);
                                saveRentOnBinaryDatabase(rents);
                                rentId = getLastIdFromDb("../databases/rents_database.txt");
                            break;

                            case 2:
                                clearConsole();
                                listUserActiveRents(rents);

                                printf("\nId do aluguer a concluir: ");
                                scanf("%d", &updateRentId);
                                fflush(stdin);

                                printf("\nBateria do veiculo: ");
                                scanf("%d", &vehicleBattery);
                                fflush(stdin);

                                printf("Stand onde o veiculo foi deixado: ");
                                scanf("%s", location);
                                fflush(stdin);

                                if (rentExists(rents, updateRentId)){
                                    updateRent(rents, updateRentId);
                                    saveRentOnDatabase(rents);
                                    saveRentOnBinaryDatabase(rents);
                                    rentId = getLastIdFromDb("../databases/rents_database.txt");

                                    vehicles = editVehicle(vehicles, car.id, vehicleBattery, location);
                                    saveVehiclesOnDatabase(vehicles);
                                    saveVehiclesOnBinaryDatabase(vehicles);
                                    vehicleId = getLastIdFromDb("../databases/vehicles_database.txt");
                                }else{
                                    printf("Erro: Este aluguer nao existe!\n\n");
                                }
                            break;

                            case 3:
                                clearConsole();
                                listUserRents(rents);
                            break;

                            case 4:
                                clearConsole();
                                listZones(graphs);

                                printf("\nPesquisar num raio de (zonas): ");
                                scanf("%d", &zone);
                                fflush(stdin);

                                clearConsole();
                                listVehiclesByZone(graphs, zone);
                            break;

                            case 5:
                                clearConsole();
                                printf("Saldo: %.2f euros\n\n", session.balance);
                            break;

                            case 6:
                                clearConsole();
                                depositBalance();
                                users = editUser(users, session.id);
                                saveUsersOnDatabase(users);
                                saveUsersOnBinaryDatabase(users);
                            break;

                            case 7:
                                clearConsole();
	   		                    printf("Nova palavra-passe: ");
                                scanf("%s", &session.password);
                                fflush(stdin);
                                users = editUser(users, session.id);
                                saveUsersOnDatabase(users);
                                saveUsersOnBinaryDatabase(users);
                            break;

                            case 8:
                                clearConsole();
	   		                    users = deleteUser(users, session.id);
                                saveUsersOnDatabase(users);
                                saveUsersOnBinaryDatabase(users);
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
                                saveVehiclesOnBinaryDatabase(vehicles);
                                vehicleId = getLastIdFromDb("../databases/vehicles_database.txt");

                                aux = malloc(sizeof(Aux));

                                aux->id = vehicles->id;
                                aux->batteryCapacity = vehicles->batteryCapacity;
                                aux->currentBattery = vehicles->currentBattery;
                                aux->autonomy = vehicles->autonomy;
                                aux->price = vehicles->price;
                                strcpy(aux->brand, vehicles->brand);
                                strcpy(aux->model, vehicles->model);
                                strcpy(aux->gpsTracker, vehicles->gpsTracker);

                                graphs = addVertex(graphs, verticesId, *aux);
                                saveVerticesOnDatabase(graphs);
                                saveVerticesOnBinaryDatabase(graphs);
                                verticesId = getLastVerticeFromDb("../databases/vertices_database.txt");
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
                                printf("Area: ");
                                scanf("%s", location);
                                fflush(stdin);
                                clearConsole();
	   		                    listVehiclesByGPS(vehicles, location);
                            break;

                            case 5:
                                clearConsole();
	   		                    vehicles = rechargeVehicles(vehicles);
                                saveVehiclesOnDatabase(vehicles);
                                saveVehiclesOnBinaryDatabase(vehicles);
                                vehicleId = getLastIdFromDb("../databases/vehicles_database.txt");

                                graphs = addVertex(graphs, verticesId, *aux);
                                saveVerticesOnDatabase(graphs);
                                saveVerticesOnBinaryDatabase(graphs);
                                verticesId = getLastVerticeFromDb("../databases/vertices_database.txt");
                            break;

                            case 6:
                                clearConsole();
	   		                    vehicles = deleteVehicle(vehicles, getId("Codigo do veiculo a remover: "));
                                saveVehiclesOnDatabase(vehicles);
                                saveVehiclesOnBinaryDatabase(vehicles);
                            break;

                            case 7:
                                clearConsole();
                                listRents(rents);
                            break;

                            case 8:
                                clearConsole();
                                getProfits(rents, vehicles);
                            break;

                            case 9:
                                clearConsole();
                                listGraph(graphs, edges);
                                getShortestPath(graphs, edges, graphs->vertex, getLinkedListLength(graphs));
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
                saveUsersOnBinaryDatabase(users);
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