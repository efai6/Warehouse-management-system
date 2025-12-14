#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "print.h"
#include "print_pdf.h"
#include "init.h"
int apply_update_count(struct Object *obj, char zn, int num);
int init_objects(char filename[30]);
int update_objects(char filename[30]);
struct Object objects[1000];
int objectCount = 0;
int res;
int main(int argc, char** argv) {
    char inp[100];
    char cmd[7];
    char filename[30];
    char filetype[4];

    if (argc < 3) {
        fprintf(stderr,"argument expected\n");
        return 3;

    }
    FILE *fvar;
    fvar = fopen(argv[1], "r");
    if(!fvar){
        fprintf(stderr, "The input file was not found");
        return 1;}
    strncpy(filetype, argv[2], 3);
    while (fgets(inp, 100, fvar)){
        sscanf(inp, "%6s %29s", cmd,filename);
        if (strcmp(cmd,"init") == 0){
            if (init_objects(filename) == 4){
                fprintf(stderr, "Couldn't open file given for initialisation");
                return init_objects(filename);
            }}
        else if (strcmp(cmd, "update") == 0) {
            if (update_objects(filename) == 1){
                fprintf(stderr, "Couldn't open file given for update");
                return update_objects(filename);
            }
        }

        else if (strcmp(cmd, "print") == 0) {
            if (strcmp(filetype,"txt") == 0){
                print_txt(filename, objects,objectCount);
            }
            else if (strcmp(filetype,"pdf") == 0){
                print_pdf(filename, objects,objectCount);
            }
            else{
                fprintf(stderr, "Unpredicted type of output file");
                return 10;
            }
        }
    }
fclose(fvar);
if (res != 0)
{
    return 15;
}
return 0;
}



int init_objects(char filename[30]){
       char inp[100];
            FILE *ifvar;
            ifvar = fopen(filename, "r");
            if (!ifvar){
                return 4;}
            fgets(inp, 100, ifvar);
            objectCount = atoi(inp);
            for (int k = 0; k < objectCount; k++) {
                fgets(inp, 100, ifvar);
                sscanf(inp, "%5s %31[^\n]", objects[k].code, objects[k].name);
                objects[k].quantity = 0;
            }
        fclose(ifvar);
        return 0;
        }
int apply_update_count(struct Object *obj, char zn, int num) {
    if (zn == '+') {
        obj->quantity += num;
        return 0;
    } 
    else if (zn == '-') {
        if (obj->quantity < num)
            return 2;
        obj->quantity -= num;
        return 0;
    }
    else {return 1;}
}
int update_objects(char filename[30]){
    char inp[100], code[6], zn[2], num[5];
    FILE *ufvar = fopen(filename, "r");
    if (!ufvar) return 1;
    fgets(inp, 100, ufvar);
    while (fgets(inp, 100, ufvar)) {
        sscanf(inp, "%5s %1c %4s", code, zn, num);
        int k = 0;
        while (k < objectCount && strcmp(code, objects[k].code) != 0) {k++;}
        apply_update_count(&objects[k], *zn, atoi(num));
        if (apply_update_count(&objects[k], *zn, atoi(num)) != 0 ){
            fprintf(stderr, "Error in update function. The code of the error is %d\n", apply_update_count(&objects[k], *zn, atoi(num)));
            res++;
        }
    }
    fclose(ufvar);
    return 0;
}
