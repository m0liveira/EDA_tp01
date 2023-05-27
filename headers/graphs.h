#include <stdio.h>

typedef struct AuxList {
    int id;
    float batteryCapacity;
    int currentBattery;
    float autonomy;
    float price;
    char brand[20];
    char model[20];
    char gpsTracker[50];
    struct AuxList* nextEntry;
} Aux;

typedef struct EdgeList {
    int id;
    int vertexA;
    int vertexB;
    float distance;
    struct EdgeList* nextEntry;
} Edge;

typedef struct GraphList {
    int vertex;
    Aux vehicle;
    Edge edge;
    struct GraphList* nextEntry;
} Graph;

int isGraphUnique(Graph *startEntry, int id);
Graph *addVertex(Graph *startEntry, int id, Aux vehicle);
float generateRandomDistance();
int doesVertexExist(Graph *graph, int vertex);
Edge *AddEdge(Graph *graph, Edge *startEntry, int startVertex, int endVertex);
int isEdgePresent(Graph *graph, Edge *edge, int vertexA, int vertexB);
Edge *generateRandomGraph(Graph *graph, Edge *edge, int numVertices, int numEdges);
void listGraph(Graph *startEntry, Edge *startEdge);