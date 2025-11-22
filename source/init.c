#include <stdio.h>

void initialize(char filename[]) {
    char inp[100];
    FILE *fvar;
    fvar = fopen(filename, "r");
    fgets(inp, 100, fvar);
    while (fgets(inp, 100, fvar)) {
        printf("%s", inp);
        
    }

    fclose(fvar);
}
