#include <stdio.h>

typedef struct VehicleList {
    int id;
    float batteryCapacity;
    int currentBattery;
    float autonomy;
    float price;
    char brand[20];
    char model[20];
    char gpsTracker[50];
    struct VehicleList* nextEntry;
} Vehicle;

int isUnique(Vehicle *startEntry, int id);
Vehicle *addVehicles(Vehicle *startEntry, int id, float batteryCapacity, int currentBattery, float autonomy, float price, char brand[], char model[], char gpsTracker[]);
void listVehicles(Vehicle *startEntry);
Vehicle *deleteVehicle(Vehicle *startEntry, int id);
Vehicle *editVehicle(Vehicle *startEntry, int id, int currentBattery, char gpsTracker[]);
int saveVehiclesOnDatabase(Vehicle *startEntry);
Vehicle *getVehiclesFromDatabase();
void listVehiclesByAutnonomy(Vehicle *startEntry);
void listVehiclesByGPS(Vehicle *startEntry, char location[]);
void getVehicleByID(Vehicle *startEntry, int id);
int vehicleExists(Vehicle *startEntry, int id);