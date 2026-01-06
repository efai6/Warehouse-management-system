#ifndef OBJECT_H
#define OBJECT_H

struct Object {
    char code[6];
    char name[32];
    int quantity;
    char cat_info[4];
    int flammability;
};

#endif
