#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Vector* createVector( int dim, FieldInfo* field_info ) {
    if( dim <= 0 ) {
        printError(ERR_INVALID_DIMENSION, "createVector");
        return NULL;
    }
    if( !field_info ){
        printError(ERR_NULL_POINTER, "createVector");
        return NULL;
    }

    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if( !vec ) {
        printError(ERR_ALLOCATION_FAILED, "createVector");
        return NULL;
    }

    vec->dim = dim;
    vec->type = field_info;
    vec->data = malloc( dim * field_info->size );
    if ( !vec->data ) {
        printError(ERR_ALLOCATION_FAILED, "createVector");
        free(vec);
        return NULL;
    }

    char* element = (char*)vec->data;
    int i;
    for ( i = 0; i < dim; i++ ) {
        memcpy(element, field_info->zero_value, field_info->size);
        element += field_info->size;
    }

    return vec;
}

void deleteVector( Vector* delVec ) {
    if( !delVec ) {
        return;
    }
    if ( delVec->data ) {
        free(delVec->data);
    }

    free(delVec);
    return;
}

int isVectorValid( const Vector* vec ) {
    if( !vec ) return 0;
    if( !vec->data ) return 0;
    if( !vec->type ) return 0;
    if( vec->dim <= 0) return 0;
    return 1;
}

ErrorCode setVectorElement( Vector* vec, int index, void* value ) {
    if ( !value || !vec ) {
        printError(ERR_NULL_POINTER, "setVectorElement");
        return ERR_NULL_POINTER;
    }
    if( !isVectorValid(vec) ) {
        printError(ERR_NOT_INITIALISED, "setVectorElement");
        return ERR_NOT_INITIALISED;
    }
    if( index < 0 || index >= vec->dim ) {
        printError(ERR_INVALID_INDEX, "setVectorElement");
        return ERR_INVALID_INDEX;
    }

    void *element = (char*)vec->data + index * vec->type->size;
    memcpy(element, value, vec->type->size);

    return SUCCESS;
}

ErrorCode getVectorElement( Vector* vec, int index, void* result ) {
    if ( !result || !vec ) {
        printError(ERR_NULL_POINTER, "getVectorElement");
        return ERR_NULL_POINTER;
    }
    if( !isVectorValid(vec) ) {
        printError(ERR_NOT_INITIALISED, "getVectorElement");
        return ERR_NOT_INITIALISED;
    }
    if( index < 0 || index >= vec->dim ) {
        printError(ERR_INVALID_INDEX, "getVectorElement");
        return ERR_INVALID_INDEX;
    }

    void* element = (char*)vec->data + index * vec->type->size;
    memcpy(result, element, vec->type->size);

    return SUCCESS;
}

static ErrorCode areVectorsCompatible( const Vector* v1, const Vector* v2, const Vector* v3 ) {
    if( !v1 || !v2 || !v3 ) {
        return ERR_NULL_POINTER;
    }
    if( !isVectorValid(v1) || !isVectorValid(v2) || !isVectorValid(v3) ) {
        return ERR_NOT_INITIALISED;
    }
    if( !AreTypesCompatible(v1->type, v2->type) || !AreTypesCompatible(v1->type, v3->type) ) {
        return ERR_TYPE_MISMATCH;
    }
    if( v1->dim != v2->dim || v1->dim != v3->dim ) {
        return ERR_DIMENSION_MISMATCH;
    }

    return SUCCESS;
}

ErrorCode addVector( const Vector* v1, const Vector* v2, Vector* res ) {
    ErrorCode err = areVectorsCompatible(v1, v2, res);
    if (err != SUCCESS) {
        printError(err, "addVector");
        return err;
    }

    FieldInfo* type = v1->type;
    size_t size = type->size;
    
    int i;
    for (i = 0; i < v1->dim; i++) {
        void* elem_v1 = (char*)v1->data + i * size;
        void* elem_v2 = (char*)v2->data + i * size;
        void* elem_res = (char*)res->data + i * size;
        
        void* sum = (void*)malloc(size);
        if ( !sum ) {    
            printError(ERR_ALLOCATION_FAILED, "addVector");            
            return ERR_ALLOCATION_FAILED;
        }

        type->add(elem_v1, elem_v2, sum);
        memcpy(elem_res, sum, size);
        free(sum);
    }

    return SUCCESS;
}

ErrorCode subtrVector( const Vector* v1, const Vector* v2, Vector* res ) {
    ErrorCode err = areVectorsCompatible(v1, v2, res);
    if (err != SUCCESS) {
        printError(err, "subtrVector");
        return err;
    }

    FieldInfo* type = v1->type;
    size_t size = type->size;
    
    int i;
    for (i = 0; i < v1->dim; i++) {
        void* elem_v1 = (char*)v1->data + i * size;
        void* elem_v2 = (char*)v2->data + i * size;
        void* elem_res = (char*)res->data + i * size;
        
        void* dif = (void*)malloc(size);
        if ( !dif ) {                
            printError(ERR_ALLOCATION_FAILED, "subtrVector");            
            return ERR_ALLOCATION_FAILED;
        }

        type->subtr(elem_v1, elem_v2, dif);
        memcpy(elem_res, dif, size);
        free(dif);
    }

    return SUCCESS;
}

ErrorCode dotProduct( const Vector* v1, const Vector* v2, void* dot_product ) {
    ErrorCode err = areVectorsCompatible(v1, v2, v2);
    if (err != SUCCESS) {
        printError(err, "dotProduct");
        return err;
    }

    FieldInfo* type = v1->type;
    size_t size = type->size;

    void* sum = (void*)malloc(size);
    void* new_sum = (void*)malloc(size);
    void* product = (void*)malloc(size);
    if ( !sum || !product || !new_sum ) {                
        printError(ERR_ALLOCATION_FAILED, "dotProduct");            
        return ERR_ALLOCATION_FAILED;
    }
    memcpy(sum, type->zero_value, size);

    int i;
    for( i = 0; i < v1->dim; i++ ) {
        void* elem_v1 = (char*)v1->data + i * size;
        void* elem_v2 = (char*)v2->data + i * size;

        type->mult(elem_v1, elem_v2, product);
        type->add(sum, product, new_sum);
        memcpy(sum, new_sum, size);
    }

    memcpy(dot_product, sum, size);
    
    free(sum);
    free(new_sum);
    free(product);

    return SUCCESS;
}

void printVector( const Vector* vec ) {
    if( !isVectorValid(vec) ) {
        printError(ERR_NOT_INITIALISED, "printVector");
        return;
    }

    printf("(");
    int i;
    for( i = 0; i < vec->dim; i++ ) {
        void* element = (char*)vec->data + i * vec->type->size;
        
        vec->type->print(element);
        
        if (i < vec->dim - 1) {
            printf(", ");
        }
    }
    printf(")");
}

ErrorCode readVectorFromConsole( Vector* vec ) {
    if( !vec || !vec->type ) {
        printError(ERR_NULL_POINTER, "readVectorFromConsole");
        return ERR_NULL_POINTER;
    }
    if( !isVectorValid(vec) ) {
        printError(ERR_NOT_INITIALISED, "readVectorFromConsole");
        return ERR_NOT_INITIALISED;
    }
    
    printf("Enter %d vector elements:\n", vec->dim);
    
    void *value = malloc(vec->type->size);
    int i;
    for( i = 0; i < vec->dim; i++ ) {
        printf("  element[%d]: ", i);
        
        if( vec->type->scan(value) != 1 ) {
            while (getchar() != '\n');
            printError(ERR_INVALID_INPUT, "readVectorFromConsole");
            return ERR_INVALID_INPUT;
        }
        setVectorElement(vec, i, value);
    }
    
    free(value);
    return SUCCESS;

}

