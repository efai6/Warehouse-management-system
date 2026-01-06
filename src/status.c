#include <stdio.h>
#include <string.h>
#include "warehouse.h"

void print_status(char filename[],struct Warehouse *warehouses, int objectCount, int warehouseCount) {
    FILE *fvar;
    fvar = fopen(strcat(filename,".txt"), "w");
    for (int j = 0; j < warehouseCount; j++){
        fprintf(fvar, "%s\n", warehouses[j].code);

        for (int i = 0; i < objectCount; i++){
                fprintf(fvar, "%s %d %s\n",
                    warehouses[j].objects[i].code,
                    warehouses[j].objects[i].quantity,
                    warehouses[j].objects[i].name);
        }
    }
    fclose(fvar);
}
