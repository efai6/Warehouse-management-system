#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    char inp[100];
    char cmd[7];
    char file[30];
    if (argc<2) {
        printf("argument expected\n");
        return 3;

    }
    FILE *fptr;
    fptr = fopen(argv[1], "r");
    fgets(inp, 100, fptr);
    fclose(fptr);
    sscanf(inp, "%7s %30s", cmd,file);

    if(strcmp(cmd, "init") == 0){
        

    }
    else if(strcmp(cmd, "update") == 0){

    }
    else if(strcmp(cmd, "print") == 0){

    }
}
