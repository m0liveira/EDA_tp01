#include <stdio.h>

typedef struct vehicleList {
    int id;
    float batteryCapacity;
    int currentBattery;
    float autonomy;
    float price;
    char brand[20];
    char model[20];
    char gpsTracker[50];
    struct vehicleList* nextEntry;
} Vehicle;

int isUnique(Vehicle* startEntry, int id);
Vehicle* addVehicles(Vehicle* startEntry, int id, float currentBattery, float autonomy, float price, char brand[], char model[]);
