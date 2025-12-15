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
int initvar;

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
        fprintf(stderr, "The input file was not found\n");
        return 1;}
    strncpy(filetype, argv[2], 3);
    while (fgets(inp, 100, fvar)){
        sscanf(inp, "%6s %29s", cmd,filename);
        if (strcmp(cmd,"init") == 0){   
            if (initvar == 1){
                fprintf(stderr, "Two init commands in the instruction file %s were given", argv[1]);
                return 6;
            }
            if (init_objects(filename) == 4){
                fprintf(stderr, "Couldn't open file given for initialisation\n");
                return init_objects(filename);
            }}
        else if (strcmp(cmd, "update") == 0) {
            if (initvar != 1){
                fprintf(stderr, "The update was called before init in %s\n", argv[1]);
                return 3;
            }
            int resU = update_objects(filename);
            if (resU == 1){
                fprintf(stderr, "Couldn't open file given for update\n");
                return resU;
            }
            else if (resU == 2){
                return resU;
            }
        }

        else if (strcmp(cmd, "print") == 0) {
            if (initvar != 1){
                fprintf(stderr, "The print was called before init in %s\n", argv[1]);
            return 3;
            }
            if (strcmp(filetype,"txt") == 0){
                print_txt(filename, objects,objectCount);
            }
            else if (strcmp(filetype,"pdf") == 0){
                print_pdf(filename, objects,objectCount);
            }
            else{
                fprintf(stderr, "Unpredicted type of output file\n");
                return 10;
            }
        }
        else{fprintf(stderr, "The command %s was not found\n", cmd); }
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
       char code [6];
       char name [32];
       initvar = 1;
            FILE *ifvar;
            ifvar = fopen(filename, "r");
            if (!ifvar){
                return 4;}
            fgets(inp, 100, ifvar);
            objectCount = atoi(inp);
            int validCount = 0;
            for (int k = 0; k < objectCount; k++) {
                fgets(inp, 100, ifvar);
                sscanf(inp, "%5s %31[^\n]", code, name);
                if(strlen(code) != 5){
                    fprintf(stderr, "the %d object in the initialisation list (%s) has incorrect code given\n", k+1, filename);
                    res++;
                    continue;
                }
                strcpy(objects[validCount].code, code);
                strcpy(objects[validCount].name, name);
                objects[validCount].quantity = 0;
                validCount++;
            }
        objectCount = validCount;
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
        while (strcmp(code, objects[k].code) != 0) 
        {k++; 
            if (k>objectCount){
                fprintf(stderr, "the code of the object (%s) was not innitialised\n", code);
                return 2;
            }
        }
        if (apply_update_count(&objects[k], *zn, atoi(num)) != 0 ){
            fprintf(stderr, "Error in update function. The code of the error is %d\n", apply_update_count(&objects[k], *zn, atoi(num)));
            res++;
        }
    }
    fclose(ufvar);
    return 0;
}
