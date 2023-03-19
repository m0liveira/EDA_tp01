#include <stdlib.h>
#include <string.h>
#include "../headers/global.h"

/*!
    * @brief Check File
    *
    * Checks if a specified file is empty.
    * 
    * @param char dir[]
    * @return 1 or 0 as true or false
*/

int isFileEmpty(char dir[]){
    FILE *fp = fopen(dir, "r");

    if (fp == NULL) return 1;

    fseek(fp, 0, SEEK_END);

    
    if (ftell(fp) == 0) {
        fclose(fp);
        return 1;
    } else {
        fclose(fp);
        return 0;
    };
}

/*!
    * @brief Get last ID from database
    *
    * Gets the last ID saved in a specified database.
    *
    * @param char dir[]
    * @return Next ID counting from the last ID at the database
*/

int getLastIdFromDb(char dir[]){
    FILE *fp;
    int id = 1, lastId = 0;

    fp = fopen(dir, "r");

    if (fp == NULL) return 1;

    if (isFileEmpty(dir) == 1) return 1;

    while (fscanf(fp, "Id:%d;", &id) == 1) {
        if (id > lastId) lastId = id;
    }

    fclose(fp);

    return lastId + 1;
}