#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "vector.h"
#include "errors.h"

void test_int_vector_creation() {
    printf("Test 1: Creating int vector... ");
    
    Vector* vec = createVector(5, ofInt());
    assert(vec != NULL);
    assert(vec->dim == 5);
    assert(vec->type == ofInt());
    assert(vec->data != NULL);
    
    for( int i = 0; i < 5; i++ ) {
        int val;
        getVectorElement(vec, i, &val);
        assert(val == 0);
    }
    
    deleteVector(vec);
    printf("OK\n");
}

void test_int_vector_set_get() {
    printf("Test 2: Setting/getting elements (int)... ");
    
    Vector* vec = createVector(3, ofInt());
    assert(vec != NULL);
    
    int values[] = {10, -5, 42};

    int i;
    for( i = 0; i < 3; i++ ) {
        ErrorCode err = setVectorElement(vec, i, &values[i]);
        assert(err == SUCCESS);
    }
    
    for( i = 0; i < 3; i++ ) {
        int result;
        ErrorCode err = getVectorElement(vec, i, &result);
        assert(err == SUCCESS);
        assert(result == values[i]);
    }
    
    deleteVector(vec);
    printf("OK\n");
}

void test_int_vector_add() {
    printf("Test 3: Vector addition (int)... ");
    
    Vector* v1 = createVector(3, ofInt());
    Vector* v2 = createVector(3, ofInt());
    Vector* v3 = createVector(3, ofInt());
    
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    int expected[] = {5, 7, 9};
    
    int i;
    for( i = 0; i < 3; i++ ) {
        setVectorElement(v1, i, &a[i]);
        setVectorElement(v2, i, &b[i]);
    }
    
    ErrorCode err = addVector(v1, v2, v3);
    assert(err == SUCCESS);
    
    for( i = 0; i < 3; i++) {
        int result;
        getVectorElement(v3, i, &result);
        assert(result == expected[i]);
    }
    
    deleteVector(v1);
    deleteVector(v2);
    deleteVector(v3);
    printf("OK\n");
}

void test_int_vector_subtr() {
    printf("Test 4: Vector subtraction (int)... ");
    
    Vector* v1 = createVector(3, ofInt());
    Vector* v2 = createVector(3, ofInt());
    Vector* v3 = createVector(3, ofInt());
    
    int a[] = {10, 20, 30};
    int b[] = {4, 5, 6};
    int expected[] = {6, 15, 24};
    
    int i;
    for( i = 0; i < 3; i++ ) {
        setVectorElement(v1, i, &a[i]);
        setVectorElement(v2, i, &b[i]);
    }
    
    ErrorCode err = subtrVector(v1, v2, v3);
    assert(err == SUCCESS);
    
    for( i = 0; i < 3; i++ ) {
        int result;
        getVectorElement(v3, i, &result);
        assert(result == expected[i]);
    }
    
    deleteVector(v1);
    deleteVector(v2);
    deleteVector(v3);
    printf("OK\n");
}

void test_int_dot_product() {
    printf("Test 5: Dot product (int)... ");
    
    Vector* v1 = createVector(3, ofInt());
    Vector* v2 = createVector(3, ofInt());
    
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    int expected = 1*4 + 2*5 + 3*6;
    
    for( int i = 0; i < 3; i++ ) {
        setVectorElement(v1, i, &a[i]);
        setVectorElement(v2, i, &b[i]);
    }
    
    int result;
    ErrorCode err = dotProduct(v1, v2, &result);
    assert(err == SUCCESS);
    assert(result == expected);
    
    deleteVector(v1);
    deleteVector(v2);
    printf("OK\n");
}

void test_double_vector_creation() {
    printf("Test 6: Creating double vector... ");
    
    Vector* vec = createVector(5, ofDouble());
    assert(vec != NULL);
    assert(vec->dim == 5);
    assert(vec->type == ofDouble());
    assert(vec->data != NULL);
    
    for( int i = 0; i < 5; i++ ) {
        double val;
        getVectorElement(vec, i, &val);
        assert(val == 0.0);
    }
    
    deleteVector(vec);
    printf("OK\n");
}

void test_double_vector_set_get() {
    printf("Test 7: Setting/getting elements (double)... ");
    
    Vector* vec = createVector(3, ofDouble());
    assert(vec != NULL);
    
    double values[] = {3.14, -2.5, 42.0};

    int i;
    for( i = 0; i < 3; i++ ) {
        ErrorCode err = setVectorElement(vec, i, &values[i]);
        assert(err == SUCCESS);
    }
    
    for( i = 0; i < 3; i++ ) {
        double result;
        ErrorCode err = getVectorElement(vec, i, &result);
        assert(err == SUCCESS);
        assert(result == values[i]);
    }
    
    deleteVector(vec);
    printf("OK\n");
}

void test_double_vector_add() {
    printf("Test 8: Vector addition (double)... ");
    
    Vector* v1 = createVector(3, ofDouble());
    Vector* v2 = createVector(3, ofDouble());
    Vector* v3 = createVector(3, ofDouble());
    
    double a[] = {1.5, 2.5, 3.5};
    double b[] = {4.1, 5.2, 6.3};
    double expected[] = {5.6, 7.7, 9.8};
    
    int i;
    for( i = 0; i < 3; i++ ) {
        setVectorElement(v1, i, &a[i]);
        setVectorElement(v2, i, &b[i]);
    }
    
    ErrorCode err = addVector(v1, v2, v3);
    assert(err == SUCCESS);
    
    for( i = 0; i < 3; i++ ) {
        double result;
        getVectorElement(v3, i, &result);
        assert(result - expected[i] < 1e-10 && expected[i] - result < 1e-10);
    }
    
    deleteVector(v1);
    deleteVector(v2);
    deleteVector(v3);
    printf("OK\n");
}

void test_double_vector_subtr() {
    printf("Test 9: Vector subtraction (double)... ");
    
    Vector* v1 = createVector(3, ofDouble());
    Vector* v2 = createVector(3, ofDouble());
    Vector* v3 = createVector(3, ofDouble());
    
    double a[] = {10.5, 20.5, 30.5};
    double b[] = {4.1, 5.2, 6.3};
    double expected[] = {6.4, 15.3, 24.2};
    
    int i;
    for( i = 0; i < 3; i++ ) {
        setVectorElement(v1, i, &a[i]);
        setVectorElement(v2, i, &b[i]);
    }
    
    ErrorCode err = subtrVector(v1, v2, v3);
    assert(err == SUCCESS);
    
    for( i = 0; i < 3; i++ ) {
        double result;
        getVectorElement(v3, i, &result);
        assert(result - expected[i] < 1e-10 && expected[i] - result < 1e-10);
    }
    
    deleteVector(v1);
    deleteVector(v2);
    deleteVector(v3);
    printf("OK\n");
}

void test_double_dot_product() {
    printf("Test 10: Dot product (double)... ");
    
    Vector* v1 = createVector(3, ofDouble());
    Vector* v2 = createVector(3, ofDouble());
    
    double a[] = {1.5, 2.5, 3.5};
    double b[] = {4.1, 5.2, 6.3};
    double expected = 1.5*4.1 + 2.5*5.2 + 3.5*6.3;
    
    for( int i = 0; i < 3; i++ ) {
        setVectorElement(v1, i, &a[i]);
        setVectorElement(v2, i, &b[i]);
    }
    
    double result;
    ErrorCode err = dotProduct(v1, v2, &result);
    assert(err == SUCCESS);
    assert(result - expected < 1e-10 && expected - result < 1e-10);
    
    deleteVector(v1);
    deleteVector(v2);
    printf("OK\n");
}

void test_error_handling() {
    printf("Test 11: Error handling... \n");
    
    Vector* vec1 = createVector(-1, ofInt());
    assert(vec1 == NULL);
    
    vec1 = createVector(5, NULL);
    assert(vec1 == NULL);
    
    vec1 = createVector(3, ofInt());
    Vector* vec2 = createVector(3, ofDouble());
    Vector* vec3 = createVector(3, ofInt());
    
    assert(vec1 != NULL);
    assert(vec2 != NULL);
    assert(vec3 != NULL);
    
    int val = 42;
    double dval = 3.14;
    int result;
    
    ErrorCode err = addVector(vec1, vec2, vec3);
    assert(err == ERR_TYPE_MISMATCH);
    
    err = dotProduct(vec1, vec2, &result);
    assert(err == ERR_TYPE_MISMATCH);
    
    err = setVectorElement(vec1, 5, &val);
    assert(err == ERR_INVALID_INDEX);
    
    err = getVectorElement(vec1, -1, &val);
    assert(err == ERR_INVALID_INDEX);
    
    err = setVectorElement(NULL, 0, &val);
    assert(err == ERR_NULL_POINTER);
    
    err = addVector(vec1, NULL, vec3);
    assert(err == ERR_NULL_POINTER);
    
    deleteVector(vec1);
    deleteVector(vec2);
    deleteVector(vec3);
    
    printf("OK\n");
}

void test_dimension_mismatch() {
    printf("Test 12: Dimension mismatch...\n");
    
    Vector* v1 = createVector(3, ofInt());
    Vector* v2 = createVector(4, ofInt());
    Vector* v3 = createVector(3, ofInt());
    
    assert(v1 != NULL);
    assert(v2 != NULL);
    assert(v3 != NULL);
    
    ErrorCode err = addVector(v1, v2, v3);
    assert(err == ERR_DIMENSION_MISMATCH);
    
    err = subtrVector(v1, v2, v3);
    assert(err == ERR_DIMENSION_MISMATCH);
    
    err = dotProduct(v1, v2, v3);
    assert(err == ERR_DIMENSION_MISMATCH);
    
    deleteVector(v1);
    deleteVector(v2);
    deleteVector(v3);
    
    printf("OK\n");
}

void test_print_vector() {
    printf("Test 13: Print vector function...\n");
    
    Vector* v1 = createVector(3, ofInt());
    int vals1[] = {1, 2, 3};
    int i;
    for( i = 0; i < 3; i++ ) {
        setVectorElement(v1, i, &vals1[i]);
    }
    
    printf("  Printing int vector: ");
    printVector(v1);
    printf("\n");
    
    Vector* v2 = createVector(3, ofDouble());
    double vals2[] = {1.5, 2.5, 3.5};
    for( i = 0; i < 3; i++ ) {
        setVectorElement(v2, i, &vals2[i]);
    }
    
    printf("  Printing double vector: ");
    printVector(v2);
    printf("\n");
    
    deleteVector(v1);
    deleteVector(v2);
    
    printf("    Print test completed\n");
}

void test_read_vector() {
    printf("Test 14: Read vector from console...\n");
    printf("  For this test you have to manually input data\n");
    
    Vector* vec = createVector(3, ofInt());
    printf("  Enter 3 integers:\n");
    ErrorCode err = readVectorFromConsole(vec);
    
    if( err == SUCCESS ) {
        printf("  Vector read: ");
        printVector(vec);
        printf("\n");
        printf("    Read successful\n");
    } 
    else {
        printf("    Read failed\n");
    }
    
    deleteVector(vec);
}

int main(void) {
    printf("\n========================================\n");
    printf("    RUNNING MODULE TESTS\n");
    printf("========================================\n\n");
    
    test_int_vector_creation();
    test_int_vector_set_get();
    test_int_vector_add();
    test_int_vector_subtr();
    test_int_dot_product();
    
    test_double_vector_creation();
    test_double_vector_set_get();
    test_double_vector_add();
    test_double_vector_subtr();
    test_double_dot_product();
    
    test_error_handling();
    test_dimension_mismatch();
    test_print_vector();
    test_read_vector();
    
    printf("\n========================================\n");
    printf("    ALL TESTS COMPLETED SUCCESSFULLY!\n");
    printf("========================================\n\n");
    
    return 0;
}