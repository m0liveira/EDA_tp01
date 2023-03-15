#include <stdlib.h>
#include <string.h>
#include "../headers/global.h"

int isFileEmpty(char dir[]){
    FILE *fp = fopen(dir, "r");

    if (fp == NULL) {
        printf("File does not exist or cannot be opened.\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END);

    
    if (ftell(fp) == 0) {
        fclose(fp);
        return 1;
    } else {
        fclose(fp);
        return 0;
    };
}

int getLastIdFromDb(char dir[]){
    FILE *fp;
    int id = 1, lastId = 0;

    fp = fopen(dir, "r");

    if (fp == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    if (isFileEmpty(dir) == 1) return 1;

    while (fscanf(fp, "Id:%d;", &id) == 1) {
        if (id > lastId) lastId = id;
    }

    fclose(fp);

    return lastId + 1;
}