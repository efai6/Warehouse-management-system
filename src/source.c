#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "print.h"
#include "print_pdf.h"

struct Object{
  char code [6];
  char name [32];
  int quantity;
};
struct Object objects[1000];
int objectCount = 0;
int main(int argc, char** argv) {
    char inp[100];
    char cmd[7];
    char filename[30];
    char filetype[4];

    if (argc < 3) {
        printf("argument expected\n");
        return 3;

    }
    FILE *fvar;
    fvar = fopen(argv[1], "r");
    strncpy(filetype, argv[2], 3);
    while (fgets(inp, 100, fvar)){
        sscanf(inp, "%6s %29s", cmd,filename);
        if (strcmp(cmd,"init") == 0){
            char inp[100];
            FILE *ifvar;
            ifvar = fopen(filename, "r");
            fgets(inp, 100, ifvar);
            objectCount = atoi(inp);
            for (int k = 0; k < objectCount; k++) {
                fgets(inp, 100, ifvar);
                sscanf(inp, "%5s %31[^\n]", objects[k].code, objects[k].name);
                objects[k].quantity = 0;
            }
        fclose(ifvar);}
        
        else if (strcmp(cmd, "update") == 0) {
            char code[6];
            char zn[2];
            char num[5];
            FILE *ufvar;
            ufvar = fopen(filename, "r");
            fgets(inp, 100, ufvar);
            while (fgets(inp, 100, ufvar)) {
                sscanf(inp, "%5s %1s %4s",code,zn,num);
                int k = 0;
                while (strcmp(code,objects[k].code) != 0 ){
                k++;
                }
                    if (strcmp(zn,"+")==0){
                        objects[k].quantity = objects[k].quantity + atoi(num);
                }
                    else if (strcmp(zn,"-") == 0){
                        objects[k].quantity = objects[k].quantity - atoi(num);
                }     
            }
            fclose(ufvar);
        }
        
        else if (strcmp(cmd, "print") == 0) {
            if (strcmp(filetype,"txt") == 0){
                print_txt(filename, objects,objectCount);
            }
            else if (strcmp(filetype,"pdf") == 0){
                print_pdf(filename, objects,objectCount);
            }
        }
    }
fclose(fvar);
return 0;
}
