#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "types.h"
#include "errors.h"

typedef struct Vector {
    int dim;            //dimensions 
    void* data;  
    FieldInfo* type;
} Vector;

Vector* createVector(int, FieldInfo*);
void deleteVector(Vector*);
int isVectorValid(const Vector*);

ErrorCode setVectorElement(Vector*, int, void*);
ErrorCode getVectorElement(Vector*, int, void*);

ErrorCode addVector(const Vector*, const Vector*, Vector*);
ErrorCode subtrVector(const Vector*, const Vector*, Vector*);
ErrorCode dotProduct(const Vector*, const Vector*, void*);

void printVector(const Vector*);
ErrorCode readVectorFromConsole(Vector*);

#endif //_VECTOR_H_