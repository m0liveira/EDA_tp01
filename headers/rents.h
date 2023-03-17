#include <stdio.h>

typedef struct RentList {
    int id;
    int clientId;
    int vehicleId;
    char status[10];
    struct RentList *nextEntry;
} Rent;

int isRentUnique(Rent *startEntry, int id);
Rent *addRent(Rent *startEntry, int id, int clientId, int vehicleId, char status[]);
int saveRentOnDatabase(Rent *startEntry);
Rent *getRentsFromDatabase();