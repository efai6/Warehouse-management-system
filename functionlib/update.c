#include "update.h" 
#include "object.h"
int apply_update_count(struct Object *obj, char zn, int num) {
    if (zn == '+') {
        obj->quantity += num;
        return 0;
    } else if (zn == '-') {
        if (obj->quantity < num)
            return 2;
        obj->quantity -= num;
        return 0;
    }
    return 1;
}