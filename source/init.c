#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void initialize(const char *file) {
    char inp[100];
    FILE *fvar;
    fvar = fopen(file, "r");
    while (fgets(inp, 100, fvar)) {
        printf("%s", inp);
    }

    fclose(fvar);
}