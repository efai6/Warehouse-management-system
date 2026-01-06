#include "object.h"
#ifndef WAREHOUSE_H
#define WAREHOUSE_H
typedef struct{
    char cat_info[4];
    int amount;
    int min;
    int main_cat;
    char cat_class;
}category;
struct Warehouse {
    char code[6];
    char name[32];
    int capacity;
    int flammability;
    int quantity_of_categories;
    struct Object objects[1000];
    category categories[10];
};

#endif