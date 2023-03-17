#include <stdio.h>

typedef struct RentList {
    int id;
    int clientId;
    int vehicleId;
    char status[10];
    struct RentList *nextEntry;
} Rent;

int isRentUnique(Rent *startEntry, int id);
int isRented(Rent *startEntry, int vehicleId);
Rent *addRent(Rent *startEntry, int id, int clientId, int vehicleId, char status[]);
int saveRentOnDatabase(Rent *startEntry);
Rent *getRentsFromDatabase();
Rent *updateRent(Rent *startEntry, int id);
void listUserRents(Rent *startEntry);
void listUserActiveRents(Rent *startEntry);
int rentExists(Rent *startEntry, int id);