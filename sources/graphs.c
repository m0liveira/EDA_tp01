#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/global.h"
#include "../headers/graphs.h"

/*!
    * @brief Check vertices uniqueness
    *
    * Checks if the vertice is dupped
    *
    * @param Graph *startEntry @param int id
    * @return 1 or 0 as true or false
*/

int isGraphUnique(Graph *startEntry, int id){
    while (startEntry != NULL){
        if (startEntry->vertex == id) return 0;

        startEntry = startEntry->nextEntry;
    }

    return 1;
}

/*!
    * @brief Adds vertices
    *
    * Adds a new vertex entry into a linked list that represents a graph
    *
    * @param Graph *graph @param int id @param Vehicle *vehicle
    * @return vertices
*/

Graph *addVertex(Graph *startEntry, int id, Aux vehicle) {
    if (!isGraphUnique(startEntry, id)){
        printf("\nErro: Este vertice ja foi registado!\n");
        return (startEntry);
    }

    Graph *newEntry = malloc(sizeof(struct GraphList));

    if (newEntry != NULL) {
        newEntry->vertex = id;
        newEntry->vehicle = vehicle;
        newEntry->nextEntry = NULL;

        if (startEntry == NULL) {
            return newEntry;
        } else {
            Graph *currentEntry = startEntry;

            while (currentEntry->nextEntry != NULL) {
                currentEntry = currentEntry->nextEntry;
            }

            currentEntry->nextEntry = newEntry;
        }
    }

    return startEntry;
}

/*!
    * @brief Generator random distance
    *
    * Generates a random distance that is going to be used as the length of the graph edges
    *
    * @return distance
*/

float generateRandomDistance() {
    // Generate a random distance between 1.0 and 10.0 (you can adjust the range as needed)
    float distance = (float)(rand() % 1000) / 100.0 + 1.0;

    return distance;
}

/*!
    * @brief Check vertices existence
    *
    * Checks if the given vertex exists
    *
    * @param Graph *graph @param int vertex
    * @return 1 or 0 as true or false
*/

int doesVertexExist(Graph *graph, int vertex) {
    while (graph != NULL) {
        if (graph->vertex == vertex) return 1;
    
        graph = graph->nextEntry;
    }

    return 0;
}

/*!
    * @brief Adds edges
    *
    * Adds a new edge entry into a linked list to complete a graph
    *
    * @param Graph *graph @param Edge *startEntry @param int startVertex @param Vehicle *vehicle
    * @return edges
*/

Edge *AddEdge(Graph *graph, Edge *startEntry, int startVertex, int endVertex) {
    if (doesVertexExist(graph, startVertex) && doesVertexExist(graph, endVertex)) {
        Edge *newEntry = malloc(sizeof(struct EdgeList));

        if (newEntry != NULL) {
            newEntry->vertexA = startVertex;
            newEntry->vertexB= endVertex;
            newEntry->distance = generateRandomDistance();
            newEntry->nextEntry = NULL;

            if (startEntry == NULL) {
                return newEntry;
            } else {
                Edge *currentEntry = startEntry;

                while (currentEntry->nextEntry != NULL) {
                    currentEntry = currentEntry->nextEntry;
                }

                currentEntry->nextEntry = newEntry;
            }
        }

        return startEntry;
    } else {
        printf("Um dos vertices indicados nao existe %d - %d\n", startVertex, endVertex);
        return startEntry;
    }
}

/*!
    * @brief Checks edges
    *
    * Checks if an edge exists
    *
    * @param Graph *graph @param Edge *edge @param int vertexA @param int vertexB
    * @return 1 or 0 as true or false
*/

int isEdgePresent(Graph *graph, Edge *edge, int vertexA, int vertexB) {
    while (edge != NULL) {
        if ((edge->vertexA == vertexA && edge->vertexB == vertexB) ||
            (edge->vertexA == vertexB && edge->vertexB == vertexA)) {
            return 1;
        }

        edge = edge->nextEntry;
    }

    return 0;
}

/*!
    * @brief Generates Graphs
    *
    * Generates a random graph dynamically from the number of existent vertices
    *
    * @param Graph *graph @param Edge *edge @param int numVertices @param int numEdges
    * @return edges
*/

Edge *generateRandomGraph(Graph *graph, Edge *edge, int numVertices, int numEdges) {
    if (numVertices <= 0 || numEdges <= 0) return edge;

    if (numEdges > numVertices * (numVertices - 1) / 2) return edge;

    int *vertices = malloc(numVertices * sizeof(int));

    if (vertices == NULL) return edge;

    for (int i = 0; i < numVertices; i++) {
        vertices[i] = i + 1;
    }

    for (int i = numVertices - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = vertices[i];
        vertices[i] = vertices[j];
        vertices[j] = temp;
    }

    int remainingEdges = numEdges;

    for (int i = 0; i < numVertices - 1 && numEdges > 0; i++) {
        int j = (i + 1) % numVertices;
        edge = AddEdge(graph, edge, vertices[i], vertices[j]);
        remainingEdges--;
    }

    while (remainingEdges != 0) {
        int randomVertexA = vertices[rand() % numVertices];
        int randomVertexB = vertices[rand() % numVertices];

        if (randomVertexA != randomVertexB && !isEdgePresent(graph, edge, randomVertexA, randomVertexB)) {
            edge = AddEdge(graph, edge, randomVertexA, randomVertexB);
            remainingEdges--;
        }
    }

    free(vertices);
    return edge;
}

/*!
    * @brief List graph
    *
    * Outputs graph vertices and edges
    *
    * @param Graph *startEntry
*/

void listGraph(Graph *startEntry, Edge *startEdge) {    
    if (startEntry == NULL) {
        printf("Nao ha vertices guardados\n\n");
        return;
    }

    printf("Grafo!");

    while (startEntry != NULL) {
        printf("\n\nZona: %d\n", startEntry->vertex);
        printf("Veiculo: %s %s\n", startEntry->vehicle.brand, startEntry->vehicle.model);
        
        Edge *newEdge = startEdge;

        int hasEdges = 0;

        while (newEdge != NULL) {
            if (startEntry->vertex == newEdge->vertexA || startEntry->vertex == newEdge->vertexB){
                printf("Arestas conectadas: %d - %d, Distancia: %.2fkm\n", newEdge->vertexA, newEdge->vertexB, newEdge->distance);
                hasEdges = 1;
            }
            
            newEdge = newEdge->nextEntry;
        }

        if (hasEdges == 0) printf("Nao esta conectado a outro vertice!\n");

        startEntry = startEntry->nextEntry;
    }
}

/*!
    * @brief List zones
    *
    * Outputs graph vertices
    *
    * @param Graph *startEntry
*/

void listZones(Graph *startEntry) {    
    if (startEntry == NULL) {
        printf("Nao ha vertices guardados\n\n");
        return;
    }

    printf("Mapa!\n\n");

    while (startEntry != NULL) {
        printf("Zona: %d\n", startEntry->vertex);

        startEntry = startEntry->nextEntry;
    }
}

/*!
    * @brief List cars by zones
    *
    * Outputs graph vertices
    *
    * @param Graph *startEntry
*/

void listVehiclesByZone(Graph *startEntry, int zone) {    
    if (startEntry == NULL) {
        printf("Nao ha vertices guardados\n\n");
        return;
    }

    printf("Veiculos num raio de %d zonas!\n\n", zone);

    while (startEntry != NULL) {
        if (startEntry->vertex <= zone) {
            printf("Id: %d\n", startEntry->vehicle.id);
            printf("Veiculo: %s %s\n", startEntry->vehicle.brand, startEntry->vehicle.model);
            printf("Preco: %.2f euros\n", startEntry->vehicle.price);
            printf("Bateria: %d%%\n\n", startEntry->vehicle.currentBattery);
        }

        startEntry = startEntry->nextEntry;
    }
}

/*!
    * @brief Save vertices on database
    *
    * Saves vertices entrys into a database
    *
    * @param Graph *startEntry
    * @return 1 or 0 as true or false
*/

int saveVerticesOnDatabase(Graph *startEntry){
    Graph *aux = startEntry;
    FILE *fp;

    fp = fopen("../databases/vertices_database.txt","w");

    if (fp==NULL) return 0;

    while (aux != NULL) {
        printf("vertex:%d", startEntry->vertex);

        fprintf(fp,"Vertex:%d;Id:%d;BatteryCap:%.2f;CurrBattery:%d;Autonomy:%.2f;Price:%.2f;Brand:%s;Model:%s;GPS:%s;\n", aux->vertex, aux->vehicle.id, aux->vehicle.batteryCapacity, aux->vehicle.currentBattery, aux->vehicle.autonomy, aux->vehicle.price, aux->vehicle.brand, aux->vehicle.model, aux->vehicle.gpsTracker);

        aux = aux->nextEntry;
    }

    fclose(fp);

    return 1;
}

/*!
    * @brief Get vertices
    *
    * Gets all vertices from a database
    *
    * @return vertices
*/

Graph *getVerticesFromDatabase() {
    Graph *vertices = NULL, *stack = NULL;
    Aux *car = NULL;
    FILE *fp;
    int vertex, id, currentBattery;
    float batteryCapacity, autonomy, price;
    char brand[20], model[20], gpsTracker[50];

    fp = fopen("../databases/vertices_database.txt", "r");

    if (fp == NULL) return vertices;

    if (isFileEmpty("../databases/vertices_database.txt") == 1) return vertices;

    while (!feof(fp)) {
        car = malloc(sizeof(Aux));

        if (car == NULL) {
            while (stack != NULL) {
                Graph *next = stack->nextEntry;
                free(stack);
                stack = next;
            }

            fclose(fp);

            return vertices;
        }

        if (fscanf(fp, "Vertex:%d;Id:%d;BatteryCap:%f;CurrBattery:%d;Autonomy:%f;Price:%f;Brand:%[^;];Model:%[^;];GPS:%[^;\n];\n", &vertex, &id, &batteryCapacity, &currentBattery, &autonomy, &price, brand, model, gpsTracker) == 9) {
            car->id = id;
            car->batteryCapacity = batteryCapacity;
            car->currentBattery = currentBattery;
            car->autonomy = autonomy;
            car->price = price;
            strcpy(car->brand, brand);
            strcpy(car->model, model);
            strcpy(car->gpsTracker, gpsTracker);

            stack = addVertex(stack, vertex, *car);
        } else {
            free(car);
            break;
        }
    }

    fclose(fp);

    while (stack != NULL) {
        vertices = addVertex(vertices, stack->vertex, stack->vehicle);
        stack = stack->nextEntry;
    }

    return vertices;
}