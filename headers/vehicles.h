#include <stdio.h>

typedef struct vehicleList {
    int id;
    float batteryCapacity;
    float currentBattery;
    float autonomy;
    float pricePerKm;
    char brand[20];
    char model[20];
    char gpsTracker[50];
    struct entry* nextEntry;
} vehicle;