#include <stdio.h>
#include <string.h>
#include "object.h"

void print_status(char filename[],struct Object *objects, int objectCount) {
    FILE *fvar;
    fvar = fopen(strcat(filename,".txt"), "w");
    for (int i = 0; i < objectCount; i++) {
        fprintf(fvar, "%s %d %s\n",objects[i].code,objects[i].quantity,objects[i].name);
    }

    fclose(fvar);
}
