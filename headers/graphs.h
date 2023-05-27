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
    int vertex;
    float position;
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
void listVertices(Graph *startEntry);