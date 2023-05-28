#include <stdio.h>

struct Session {
    int id;
    int nif;
    float balance;
    char name[30];
    char password[30];
    char role[10];
} session;

struct Car {
    int id;
    float batteryCapacity;
    int currentBattery;
    float autonomy;
    float price;
    char brand[20];
    char model[20];
    char gpsTracker[50];
} car;

int isFileEmpty(char dir[]);
int getLastIdFromDb(char dir[]);
int getLastVerticeFromDb(char dir[]);
