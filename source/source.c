#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"

int main(int argc, char** argv) {
    char inp[100];
    char cmd[7];
    char file[30];
    if (argc<2) {
        printf("argument expected\n");
        return 3;

    }
    FILE *fvar;
    fvar = fopen(argv[1], "r");
    fgets(inp, 100, fvar);
    fclose(fvar);
    sscanf(inp, "%6s %29s", cmd,file);

    if(strcmp(cmd, "init") == 0){
        initialize(file);
        
    }
    else if(strcmp(cmd, "update") == 0){

    }
    else if(strcmp(cmd, "print") == 0){

    }
}

