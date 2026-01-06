#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "warehouse.h"
#include "print.h"
#include "print_pdf.h"
#include "status.h"
int apply_update_count(struct Object *obj, char zn, int num);
int init_objects(char filename[30]);
int update_objects(char filename[30]);
int Object_code_check(char* code);
int CreateWarehouse(char filename[30]);
int WarehouseCheck(struct Warehouse warehouse, int i);
int Categories_check(struct Warehouse warehouse, int i);
struct Object objects[1000];
struct Warehouse warehouses[100];
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
                print_status(status, warehouses,objectCount, warehouseCount);
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
            print_status(status, warehouses,objectCount, warehouseCount);
        }

        else if (strcmp(cmd, "print") == 0) {
            if (initvar != 1){
                fprintf(stderr, "The print was called before init in %s\n", argv[1]);
            return 3;
            }
            if (strcmp(filetype,"txt") == 0){
                print_txt(filename, warehouses,objectCount, warehouseCount);
            }
            else if (strcmp(filetype,"pdf") == 0){
                print_pdf(filename, warehouses,objectCount, warehouseCount);
            }
            else{
                fprintf(stderr, "Unpredicted type of output file\n");
                return 10;
            }
        }
        else if (strcmp(cmd, "create") == 0){
            int CrVar = CreateWarehouse(filename);
            if (CrVar!=0)
            {
            return CrVar;
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
       char inp[inpVar];
       char code [6];
       char name [32];
       char cat_info[4];
       int flammability = 0;
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
                sscanf(inp, "%3s %1d %5s %31[^\n]",cat_info,&flammability, code, name);
                if(Object_code_check(code) == 1){
                    fprintf(stderr, "the %d object in the initialisation list (%s) has incorrect code given\n", actualCount+1, filename);
                    res++;
                    continue;
                }
                if (validCount<objectCount){
                strcpy(objects[validCount].cat_info, cat_info);
                objects[validCount].flammability = flammability;
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
    int found = -1; 
    char inp[inpVar], code[6], zn[2], num[5], wcode[6];
    FILE *ufvar = fopen(filename, "r");
    if (!ufvar) return 1;
    fgets(inp, inpVar, ufvar);
    sscanf(inp, "%5s", wcode);
    for(int i = 0; i < warehouseCount; i++){
        if(strcmp(wcode,warehouses[i].code) == 0){
            //printf("They are mathching\n");
            found = i;}
    }
    fgets(inp, inpVar, ufvar);
    while (fgets(inp, inpVar, ufvar)) {
        sscanf(inp, "%5s %1c %4s", code, zn, num);
        int k = 0;
        while (strcmp(code, warehouses[found].objects[k].code) != 0) 
        {k++; 
            if (k>objectCount){
                fprintf(stderr, "the code of the object (%s) was not innitialised\n", code);
                return 2;
            }
        }
        if (apply_update_count(&warehouses[found].objects[k], *zn, atoi(num)) != 0 ){
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
        sscanf(inp,"%3s %4d %4d", warehouses[wq].categories[i].cat_info,&warehouses[wq].categories[i].amount, &warehouses[wq].categories[i].min);
        i++;
    }
    int check = WarehouseCheck(warehouses[wq], i);
    if(check != 0){return check;}
    check = Categories_check(warehouses[wq], i);
    warehouseCount++;
    for (int k = 0; k<objectCount; k++){
        warehouses[wq].objects[k] = objects[k];
    }
    wq++;
    return check;

}
int WarehouseCheck(struct Warehouse warehouse, int i){
    int sum_of_mins_capacities_for_categories = 0;
    for(int k = 0;k<i; k++){
        if (warehouse.capacity<warehouse.categories[k].amount){
            fprintf(stderr, "The capacity of warehouse %s was exceeded by reservation for category %s\n",warehouse.code, warehouse.categories[k].cat_info);
            return 16;}
            sum_of_mins_capacities_for_categories = sum_of_mins_capacities_for_categories + warehouse.categories[k].min;
        }
    if (sum_of_mins_capacities_for_categories > warehouse.capacity){
        fprintf(stderr, "The capacity of warehouse %s was exceeded by reservation too big minimum amounts for categories\n", warehouse.code);
        return 17;
    }

    printf("The warehouse %s was created\n", warehouse.code);
    return 0;
}
int Categories_check(struct Warehouse warehouse, int i){
    int main_index [10];
    int z = 0;
    int t = 0;
    for(int k = 0;k<i; k++){ 
        if(strlen(warehouse.categories[k].cat_info) == 1){
            warehouse.categories[k].main_cat = 1;
            main_index[z] = warehouse.categories[k].cat_info[0];
            z++;
        }
        else{warehouse.categories[k].main_cat = 0;}
        
    }
    for(int k = 0; k<i; k++){
        if(warehouse.categories[k].main_cat == 1 && warehouse.categories[k].cat_info[0] == main_index[t]){
            t++;
            for(int d = 0; d<i;d++){
                if(warehouse.categories[d].main_cat == 0 && warehouse.categories[d].cat_info[0] == warehouse.categories[k].cat_info[0] && warehouse.categories[k].amount < warehouse.categories[d].amount){
                    fprintf(stderr, "The subcategory %s has bigger reservation of items than its main category %s in warehouse %s\n", warehouse.categories[d].cat_info, warehouse.categories[k].cat_info, warehouse.code);
                    return 20;
                }
                if(warehouse.categories[d].main_cat == 0 && warehouse.categories[d].cat_info[0] == warehouse.categories[k].cat_info[0]){
                    int sum_of_min_amount = 0;
                    sum_of_min_amount = sum_of_min_amount + warehouse.categories[d].min;
                    if(sum_of_min_amount>warehouse.categories[k].amount){
                        fprintf(stderr, "The subcategories of category %s has bigger sum of minimal amount than overall amount of objects for category in warehouse %s", warehouse.categories[k].cat_info, warehouse.code);
                        return 22;}
                }
            }
        }
    }
    return 0;
}