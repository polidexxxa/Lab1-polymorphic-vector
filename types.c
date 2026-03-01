#include <stdio.h>
#include "types.h"

static const int INT_ZERO = 0;
static const double DOUBLE_ZERO = 0.0;

static void addInt( const void* a1, const void* a2, void* res ) {
    *(int*)res = *(int*)a1 + *(int*)a2;
    return;
} 

static void subtrInt( const void* a1, const void* a2, void* res ) {
    *(int*)res = *(int*)a1 - *(int*)a2;
    return;
} 

static void multInt( const void* a1, const void* a2, void* res ) {
    *(int*)res = *(int*)a1 * *(int*)a2;
    return;
}

static void printInt( const void* value ) {
    if( value ) {
        printf("%d", *(const int*)value);
    } 
    else {
        printf("NULL");
    }
}

static int scanInt(void* value) {
    if (!value) return 0;
    return scanf("%d", (int*)value) == 1;
}


static void addDouble( const void* a1, const void* a2, void* res ) {
    *(double*)res = *(double*)a1 + *(double*)a2;
    return;
} 

static void subtrDouble( const void* a1, const void* a2, void* res ) {
    *(double*)res = *(double*)a1 - *(double*)a2;
    return;
} 

static void multDouble( const void* a1, const void* a2, void* res ) {
    *(double*)res = *(double*)a1 * *(double*)a2;
    return;
} 

static void printDouble( const void* value ) {
    if( value ) {
         printf("%.2f", *(const double*)value);
    } 
    else {
        printf("NULL");
    }
}

static int scanDouble(void* value) {
    if (!value) return 0;
    return scanf("%lf", (double*)value) == 1;
}


static FieldInfo* int_field_info = NULL;

FieldInfo* ofInt(void) {
    if(!int_field_info) {
        int_field_info = (FieldInfo*)malloc(sizeof(FieldInfo));

        int_field_info->size = sizeof(int);

        int_field_info->add = addInt;
        int_field_info->subtr = subtrInt;
        int_field_info->mult = multInt;
        int_field_info->print = printInt;
        int_field_info->scan = scanInt;

        int_field_info->zero_value = &INT_ZERO;
    }
    return int_field_info;
}

static FieldInfo* double_field_info = NULL;

FieldInfo* ofDouble(void) {
    if(!double_field_info) {
        double_field_info = (FieldInfo*)malloc(sizeof(FieldInfo));

        double_field_info->size = sizeof(double);

        double_field_info->add = addDouble;
        double_field_info->subtr = subtrDouble;
        double_field_info->mult = multDouble;
        double_field_info->print = printDouble;
        double_field_info->scan = scanDouble;

        double_field_info->zero_value = &DOUBLE_ZERO;
    }
    return double_field_info;
}


int AreTypesCompatible( FieldInfo* a, FieldInfo* b ) {
    return a == b;
}