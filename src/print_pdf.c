#include <stdio.h>
#include <stdlib.h>
#include "warehouse.h"

void print_pdf(char filename[],struct Warehouse *warehouses, int objectCount,int warehouseCount) {
    FILE *fvar;
    fvar = fopen(filename, "w");
    fprintf(fvar,
        "\\documentclass{article}\n"
        "\\usepackage{geometry}\n"
        "\\usepackage{array}\n"
        "\\geometry{margin=1in}\n"
        "\\begin{document}\n"
        "\\begin{center}\n");
    for (int j = 0; j < warehouseCount; j++){
        fprintf(fvar,
        "\\section{%s}"
        "\\begin{tabular}{| m{3cm} | m{2cm} | m{7cm} |}\n"
        "\\hline\n"
        "Code & Quantity & Name \\\\ \\hline\n",warehouses[j].code);
    for (int i = 0; i < objectCount; i++) {
        if (warehouses[j].objects[i].quantity > 0) {
            fprintf(fvar, "%s & %d & %s\\\\ \\hline\n",warehouses[j].objects[i].code,warehouses[j].objects[i].quantity,warehouses[j].objects[i].name);
        }
    }fprintf(fvar, "\\end{tabular}\n");}
    fprintf(fvar,
        "\\end{center}\n"
        "\\end{document}\n");
    
    fclose(fvar);
    char cmd[256];
    sprintf(cmd, "./makepdf.sh %s", filename);
    system(cmd);

}
