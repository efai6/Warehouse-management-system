#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "print.h"
#include "print_pdf.h"
#include "status.h"
#include "warehouse.h"
int apply_update_count(struct Object *obj, char zn, int num);
int init_objects(char filename[30]);
int update_objects(char filename[30]);
int Object_code_check(char* code);
int CreateWarehouse(char filename[30]);
struct Object objects[1000];
struct Warehouse warehouses[1000];
category categories[10];
int objectCount = 0;
int res;
int initvar;
int inpVar = 100;
int wq = 0;
int warehouseCount = 0;

int main(int argc, char** argv) {
    char inp[inpVar];
    char cmd[7];
    char filename[30];
    char filetype[4];
    int stat = 0;
    char status[10];

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
    while (fgets(inp, inpVar, fvar)){
        sscanf(inp, "%6s %29s", cmd,filename);
        if (strcmp(cmd,"init") == 0){ 
            stat++;
            sprintf(status,"Status%d",stat);
            if (initvar == 1){
                fprintf(stderr, "Two init commands in the instruction file %s were given", argv[1]);
                return 6;
            }
            int ResI = init_objects(filename);
            if (ResI == 4){
                fprintf(stderr, "Couldn't open file given for initialisation\n");
                return 4;
            }
            else if (ResI==8){
                fprintf(stderr, "The number of declarated objects in %s is smaller than number of objects given", filename);
                return 8;
            }
            else {
                print_status(status, objects,objectCount);
            }
        }

        else if (strcmp(cmd, "update") == 0) {
            stat++;
            sprintf(status,"Status%d",stat);
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
            print_status(status, objects,objectCount);
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
        else if (strcmp(cmd, "create") == 0){
            int CrVar = CreateWarehouse(filename);
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
       char inp[inpVar];
       char code [6];
       char name [32];
       initvar = 1;
            FILE *ifvar;
            ifvar = fopen(filename, "r");
            if (!ifvar){
                return 4;}
            fgets(inp, inpVar, ifvar);
            objectCount = atoi(inp);
            int validCount = 0;
            int actualCount = 0;
            while(fgets(inp, inpVar, ifvar)) {
                sscanf(inp, "%5s %31[^\n]", code, name);
                if(Object_code_check(code) == 1){
                    fprintf(stderr, "the %d object in the initialisation list (%s) has incorrect code given\n", actualCount+1, filename);
                    res++;
                    continue;
                }
                if (validCount<objectCount){
                strcpy(objects[validCount].code, code);
                strcpy(objects[validCount].name, name);
                objects[validCount].quantity = 0;
                validCount++;}
            }
            if (validCount > objectCount) {
                return 8;
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
    int i = 0;
    char inp[inpVar], code[6], zn[2], num[5], wcode[6];
    FILE *ufvar = fopen(filename, "r");
    if (!ufvar) return 1;
    fgets(inp, inpVar, ufvar);
    sscanf(inp, "%5s", wcode);
    for(i; i < warehouseCount; i++){
        if(strcmp(wcode,warehouses[i].code) == 0){printf("They are mathching\n");}
    }
    fgets(inp, inpVar, ufvar);
    while (fgets(inp, inpVar, ufvar)) {
        sscanf(inp, "%5s %1c %4s", code, zn, num);
        int k = 0;
        while (strcmp(code, warehouses[i-1].objects[k].code) != 0) 
        {k++; 
            if (k>objectCount){
                fprintf(stderr, "the code of the object (%s) was not innitialised\n", code);
                return 2;
            }
        }
        if (apply_update_count(&warehouses[i-1].objects[k], *zn, atoi(num)) != 0 ){
            fprintf(stderr, "Error in update function. The code of the error is %d\n", apply_update_count(&objects[k], *zn, atoi(num)));
            res++;
        }
    }
    fclose(ufvar);
    return 0;
}
int Object_code_check(char* code){
    int i;
    if (strlen(code)!=5){
        return 1;
    }
    for (i = 0;i<2;i++){
        if(code[i] >= 'A'&& code[i]<= 'Z'){
        }
        else{
            return 1;
        }
    }
    for (i=2; i<5; i++){
        int c_int = code[i] - '0';
        if (c_int >=0 && c_int<=9){
        }
        else{
            return 1;
        }
    }
    return 0;
}
int CreateWarehouse(char filename[30]){
    char inp[inpVar];
    int i = 0;
    FILE *fvar = fopen(filename, "r");
    if (!fvar) return 11;
    fgets(inp, inpVar, fvar);
    sscanf(inp,"%5s %4d %1d %31[^\n] %2d", warehouses[wq].code, &warehouses[wq].capacity, &warehouses[wq].flammability,
          warehouses[wq].name ,&warehouses[wq].quantity_of_categories);
    while (fgets(inp, inpVar, fvar)){
        sscanf(inp,"%3s %4d %4d", warehouses[wq].categories[i].info,&warehouses[wq].categories[i].amount, &warehouses[wq].categories[i].min);
        i++;
    }
    printf("The warehouse %s was created\n", warehouses[wq].code);
    warehouseCount++;
    for (int k = 0; k<objectCount; k++){
        warehouses[wq].objects[k] = objects[k];
    }
}
