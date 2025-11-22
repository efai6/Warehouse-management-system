#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"
struct Object{
  char code [6];
  char name [32];
  int quantity;
};
int main(int argc, char** argv) {
    char inp[100];
    char cmd[7];
    char filename[30];
    if (argc < 2) {
        printf("argument expected\n");
        return 3;

    }
    FILE *fvar;
    fvar = fopen(argv[1], "r");
    fgets(inp, 100, fvar);
    fclose(fvar);
    sscanf(inp, "%6s %29s", cmd,filename);

    if (strcmp(cmd, "init") == 0) {
        int k = 0;
        char inp[100];
        FILE *fvar;
        fvar = fopen(filename, "r");
        fgets(inp, 100, fvar);
        int i = atoi(inp);
        struct Object objects[i];
        while (fgets(inp, 100, fvar)) {
            sscanf(inp, "%5s %31s",objects[k].code,objects[k].name);
            k++;

        }
        printf("%s", objects[0].code);
        fclose(fvar);
    } else if (strcmp(cmd, "update") == 0) {

    } else if (strcmp(cmd, "print") == 0) {

    }
}
