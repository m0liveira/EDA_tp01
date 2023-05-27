#include <stdlib.h>
#include <string.h>
#include "../headers/global.h"
#include "../headers/graphs.h"

/*!
    * @brief Check vertexes ID
    *
    * Checks if the ID is dupped
    *
    * @param Graph *startEntry @param int id
    * @return 1 or 0 as true or false
*/

int isGraphUnique(Graph *startEntry, int id){
    while (startEntry != NULL){
        if (startEntry->vertex == id) return (0);

        startEntry = startEntry->nextEntry;
    }

    return (1);
}

/*!
    * @brief Add vertex
    *
    * Adds a new vertex entry into a linked list that represents a graph
    *
    * @param Graph *graph @param int id @param Vehicle *vehicle
    * @return 1 or 0 as true or false
*/

Graph *addVertex(Graph *startEntry, int id, Aux vehicle) {
    if (!isGraphUnique(startEntry, id)){
        printf("\nErro: Este ID ja foi registado!\n");
        return (startEntry);
    }

    Graph *newEntry = malloc(sizeof(struct GraphList));

    if (newEntry != NULL) {
        newEntry->vertex = id;
        newEntry->vehicle = vehicle;
        newEntry->nextEntry = startEntry;

        return (newEntry);
    }
}

/*!
    * @brief List vertices
    *
    * Outputs all existent vertices
    *
    * @param Graph *startEntry
*/

void listVertices(Graph *startEntry){
    if (startEntry == NULL){
        printf("Nao ha vertices guardados\n\n");
        return;
    }

    printf("Lista de vertices!\n\n");

    while (startEntry != NULL){
        printf("Id: %d\n", startEntry->vertex);
        printf("vehicle: %s %s\n\n", startEntry->vehicle.brand, startEntry->vehicle.model);
        startEntry = startEntry->nextEntry;
    }
}
