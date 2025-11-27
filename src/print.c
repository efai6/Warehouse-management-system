#include <stdio.h>
#include <string.h>
#include "object.h"

void print_txt(char filename[],struct Object *objects, int objectCount) {
    FILE *fvar;
    fvar = fopen(strcat(filename,".txt"), "w");
    for (int i = 0; i < objectCount; i++) {
        if (objects[i].quantity > 0) {
            fprintf(fvar, "%s %d %s\n",objects[i].code,objects[i].quantity,objects[i].name);
        }
    }

    fclose(fvar);
}
