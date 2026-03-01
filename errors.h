#ifndef _ERRORS_H_
#define _ERRORS_H_

typedef enum {
    SUCCESS = 0,
    ERR_NULL_POINTER,
    ERR_INVALID_DIMENSION,
    ERR_INVALID_INDEX,
    ERR_TYPE_MISMATCH,
    ERR_DIMENSION_MISMATCH,
    ERR_ALLOCATION_FAILED,
    ERR_INVALID_INPUT,
    ERR_NOT_INITIALISED
} ErrorCode;

const char* errorMessage(ErrorCode);
void printError(ErrorCode, const char*);

#endif //_ERRORS_H_