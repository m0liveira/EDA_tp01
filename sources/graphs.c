#include <stdio.h>
#include <stdlib.h>
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
        printf("\n\nVertice: %d\n", startEntry->vertex);
        printf("veiculo: %s %s\n", startEntry->vehicle.brand, startEntry->vehicle.model);
        
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