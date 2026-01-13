#include <stdio.h>
#include <stdlib.h>
#include "warehouse.h"

void print_pdf(char filename[], struct Warehouse *warehouses,int objectCount, int warehouseCount){
    FILE *fvar = fopen(filename, "w");
    if (!fvar) return;
    fprintf(fvar,
        "\\documentclass{article}\n"
        "\\usepackage{geometry}\n"
        "\\usepackage{caption}"
        "\\usepackage{array}\n"
        "\\geometry{margin=1in}\n"
        "\\begin{document}\n"
        "\\tableofcontents\n"
        "\\newpage\n"
    );

    for (int j = 0; j < warehouseCount; j++) {
        fprintf(fvar,
            "\\section{%s}\n", warehouses[j].code
        );

        fprintf(fvar,
            "\\begin{table}[h]\n"
            "\\small\n"
            "\\begin{tabular}{| m{3cm} | m{2cm} | m{7cm} |}\n"
            "\\hline\n"
            "Code & Quantity & Name \\\\ \\hline\n"
        );

        for (int i = 0; i < objectCount; i++) {
            if (warehouses[j].objects[i].quantity > 0) {
                fprintf(fvar,
                    "%s & %d & %s \\\\ \\hline\n", warehouses[j].objects[i].code, warehouses[j].objects[i].quantity, warehouses[j].objects[i].name
                );
            }
        }

        fprintf(fvar,
            "\\end{tabular}\n"
            "\\caption{%s}\n"
            "\\end{table}\n",warehouses[j].name
        );
    }

    /* === SUMMARY === */
    fprintf(fvar,
        "\\section{Podsumowanie}\n"
        "Liczba magazynow: %d\\\\", warehouseCount
    );

    fprintf(fvar,
        "\\small\n"
        "\\begin{tabular}{| m{2cm} | m{2cm} | m{2cm} | m{4cm} |}\n"
        "\\hline\n"
        "Code & Capacity & Flammability & Name \\\\ \\hline\n"
    );

    for (int j = 0; j < warehouseCount; j++) {
        fprintf(fvar,
            "%s & %d & %d & %s \\\\ \\hline\n",warehouses[j].code,warehouses[j].capacity,warehouses[j].flammability, warehouses[j].name
        );
    }

    fprintf(fvar,
        "\\end{tabular}\n"
        "\\par\n"
        "\\captionof{table}{Summary of warehouses}\n"
        "\\end{document}\n"
    );
    fclose(fvar);
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "./makepdf.sh %s", filename);
    system(cmd);
}
