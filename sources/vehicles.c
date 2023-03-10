#include <stdlib.h>
#include <string.h>
#include "../headers/vehicles.h"

int isUnique(Vehicle* startEntry, int id){
  while(startEntry != NULL){
    if (startEntry->id == id) return(1);

    startEntry = startEntry->nextEntry;
  }
  return(0);
}

Vehicle* addVehicles(Vehicle * startEntry, int id, float batteryCapacity, float currentBattery, float autonomy, float pricePerKm, char brand[], char model[], char gpsTracker[]) {}