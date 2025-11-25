#include <stdio.h>
#include <stdlib.h>
#include "object.h"

void print_pdf(char filename[],struct Object *objects, int objectCount) {
    FILE *fvar;
    fvar = fopen(filename, "w");
    fprintf(fvar,
        "\\documentclass{article}\n"
        "\\usepackage{geometry}\n"
        "\\usepackage{array}\n"
        "\\geometry{margin=1in}\n"
        "\\begin{document}\n"
        "\\begin{center}\n"
        "\\begin{tabular}{| m{3cm} | m{2cm} | m{7cm} |}\n"
        "\\hline\n"
        "Code & Quantity & Name \\\\ \\hline\n");
    for (int i = 0; i < objectCount; i++) {
        if (objects[i].quantity > 0) {
            fprintf(fvar, "%s & %d & %s\\\\ \\hline\n",objects[i].code,objects[i].quantity,objects[i].name);
        }
    }
    fprintf(fvar,
        "\\end{tabular}\n"
        "\\end{center}\n"
        "\\end{document}\n");

    fclose(fvar);
    char cmd[256];
    sprintf(cmd, "./makepdf.sh %s", filename);
    system(cmd);

}
