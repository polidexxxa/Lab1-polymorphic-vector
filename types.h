#ifndef _TYPES_H_
#define _TYPES_H_

#include <stddef.h>
#include <stdlib.h>

typedef struct FieldInfo {
    size_t size;    //размер типа данных

    void (*add)(const void*, const void*, void*);   //сумма
    void (*subtr)(const void*, const void*, void*); //разность
    void (*mult)(const void*, const void*, void*);  //произведение
    void (*print)(const void*);
    int (*scan)(void*);

    const void* zero_value;

} FieldInfo;

FieldInfo* ofInt(void);
FieldInfo* ofDouble(void);

int AreTypesCompatible(FieldInfo*, FieldInfo*);

#endif //_TYPES_H_