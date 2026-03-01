#include "errors.h"
#include <stdio.h>

const char* errorMessage( ErrorCode code ) {
    switch (code) {
        case SUCCESS:               return "Success";
        case ERR_NULL_POINTER:      return "Null pointer";
        case ERR_INVALID_DIMENSION: return "Invalid dimension";
        case ERR_INVALID_INDEX:     return "Index out of range";
        case ERR_TYPE_MISMATCH:     return "Incompatible types";
        case ERR_DIMENSION_MISMATCH:return "Dimensions do not match";
        case ERR_ALLOCATION_FAILED: return "Memory allocation failed";
        case ERR_INVALID_INPUT:     return "Invalid input";
        case ERR_NOT_INITIALISED:   return "Object not initialised";
        default:                    return "Unknown error";
    }
}

void printError( ErrorCode code, const char* context ) {
    if( code != SUCCESS ) {
        if( context ) {
            fprintf(stderr, "Error [%s]: %s\n", context, errorMessage(code));
        } else {
            fprintf(stderr, "Error: %s\n", errorMessage(code));
        }
    }
}
