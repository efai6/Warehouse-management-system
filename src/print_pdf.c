#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "warehouse.h"

#define PROGRAM_VERSION "1.0.0"
#define EXECUTABLE_NAME "./magazyn"
#define HASH_CMD "sha256sum " EXECUTABLE_NAME " | cut -d ' ' -f1"
#ifndef COMPILER_NAME
#define COMPILER_NAME "Unknown"
#endif


int object_list_inf(int warehouseCount, struct Object *objects, struct Warehouse* warehouses, int objectCount){
    for(int i = 0; i < warehouseCount; i++){
       for (int j = 0; j < objectCount; j++){
        if(strcmp(objects[j].code, warehouses[i].objects[j].code) == 0){
            objects[j].quantity = objects[j].quantity + warehouses[i].objects[j].quantity;
        }
       }
    }
    return 0;
}

void get_current_date(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

void get_executable_hash(char *buffer, size_t size) {
    FILE *fp = popen(HASH_CMD, "r");
    if (!fp) {
        strncpy(buffer, "HASH_ERROR", size);
        return;
    }
    fgets(buffer, size, fp);
    buffer[strcspn(buffer, "\n")] = '\0';
    pclose(fp);
}
void print_environment(FILE *f) {
    fprintf(f,
        "\\section*{\\centering Środowisko uruchomieniowe}\n"
        "\\vspace{0.5cm}\n"
        "\\begin{tabular}{|l|l|}\n"
        "\\hline\n"
        "System operacyjny & Linux \\\\\n"
        "\\hline\n"
        "Architektura & x86\\_64 \\\\\n"
        "\\hline\n"
        "Kompilator & %s \\\\\n"
        "\\hline\n"
        "Standard języka C & %ld \\\\\n"
        "\\hline\n"
        "Data kompilacji & %s %s \\\\\n"
        "\\hline\n"
        "\\end{tabular}\n"
        "\\newpage\n",
        COMPILER_NAME,
        (long)__STDC_VERSION__,
        __DATE__,
        __TIME__
    );
}
void print_pdf(char filename[], struct Warehouse *warehouses,int objectCount, int warehouseCount, struct Object *objects){
    FILE *fvar = fopen(filename, "w");
    if (!fvar) return;
    char date[64];
    char hash[128];
    object_list_inf(warehouseCount, objects, warehouses, objectCount);
    get_current_date(date, sizeof(date));
    get_executable_hash(hash, sizeof(hash));
    fprintf(fvar,
        "\\documentclass{article}\n"
        "\\usepackage{geometry}\n"
        "\\usepackage{caption}"
        "\\captionsetup[longtable]{position=bottom}\n"
        "\\usepackage{array}\n"
        "\\usepackage{longtable}\n"
        "\\geometry{margin=1in}\n"
        "\\begin{document}\n"
    );
    fprintf(fvar,
        "\\begin{center}\n"
        "{\\LARGE\\textbf{Raport stanu magazynu}}\\\\[1cm]\n"
        "\\end{center}\n"
        "\\noindent\\textbf{Data utworzenia:} %s\\\\\n"
        "\\textbf{Wersja programu:} %s\\\\\n"
        "\\textbf{Kod programu (SHA256):}\\\\\n"
        "\\texttt{%s}\n",
        date,
        PROGRAM_VERSION,
        hash
    );
    print_environment(fvar);
    
    fprintf(fvar,
        "\\tableofcontents\n"
        "\\newpage\n");
    for (int j = 0; j < warehouseCount; j++) {
        fprintf(fvar,
            "\\section{%s}\n", warehouses[j].code
        );

fprintf(fvar,
            "\\small\n"
            "\\begin{longtable}{| m{3cm} | m{2cm} | m{7cm} |}\n"
            "\\hline\n"
            "Code & Quantity & Name \\\\ \\hline\n"
            "\\endfirsthead\n"
            "\\hline\n"
            "Code & Quantity & Name (cont.) \\\\ \\hline\n"
            "\\endhead\n"
            "\\hline\n"
            "\\caption{%s} \\\\\n"   
            "\\endlastfoot\n",       
            warehouses[j].name
        );

        for (int i = 0; i < objectCount; i++) {
            if (warehouses[j].objects[i].quantity > 0) {
                fprintf(fvar,
                    "%s & %d & %s \\\\ \\hline\n", warehouses[j].objects[i].code, warehouses[j].objects[i].quantity, warehouses[j].objects[i].name
                );
            }
        }

    fprintf(fvar, "\\end{longtable}\n");
    }
    fprintf(fvar, "\\newpage\n");

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
    );
    //table of products in revision 
    for (int j = 0; j < objectCount; j++) {
    fprintf(fvar,
        "\\subsection*{%s}\n", objects[j].cat_info
    );
    fprintf(fvar,
        "\\begin{tabular}{| m{3cm} | m{2cm} | m{7cm} |}\n"
        "\\hline\n"
        "Code & Quantity & Name \\\\ \\hline\n"
        );

        for (int i = 0; i < objectCount; i++) {
            if (objects[i].quantity > 0 && strcmp(objects[i].cat_info, objects[j].cat_info) == 0) {
                fprintf(fvar,
                    "%s & %d & %s \\\\ \\hline\n",objects[i].code, objects[i].quantity,objects[i].name
                );
            }
        }
        fprintf(fvar,
            "\\end{tabular}\n");
        }
        fprintf(fvar,
        "\\captionof{table}{List of all objects}\n"
        "\\end{document}\n"
        );
    fclose(fvar);
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "./makepdf.sh %s", filename);
    system(cmd);
}
