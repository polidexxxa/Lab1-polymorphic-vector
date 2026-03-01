#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "vector.h"

typedef struct {
    Vector* v1;
    Vector* v2;
    Vector* v3;
} VectorSet;

void clearVectors( VectorSet* set ) {
    if( set->v1 ) deleteVector(set->v1);
    if( set->v2 ) deleteVector(set->v2);
    if( set->v3 ) deleteVector(set->v3);
    set->v1 = set->v2 = set->v3 = NULL;
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printHeader(void) {
    printf("\n======================================\n");
    printf("POLYMORPHIC VECTOR REALISATION\n");
    printf("======================================\n");
    printf("Types: int, double\n");
    printf("Operations: addition, subtraction, dot product\n\n");
}

void printMenu(void) {
    printf("\n======================================\n");
    printf("MENU:\n");
    printf("======================================\n");
    printf("1. Create int vectors (v1, v2, v3)\n");
    printf("2. Create double vectors (v1, v2, v3)\n");
    printf("3. Delete all vectors\n");
    printf("4. Show all vectors\n");
    printf("======================================\n");
    printf("5. Set element in v1\n");
    printf("6. Get element from v1\n");
    printf("7. Enter v1 from keyboard\n");
    printf("8. Enter v2 from keyboard\n");
    printf("======================================\n");
    printf("9. Add v1 + v2 -> v3\n");
    printf("10. Subtract v1 - v2 -> v3\n");
    printf("11. Compute dot product (v1,v2)\n");
    printf("======================================\n");
    printf("0. Exit\n");
    printf("======================================\n");
    printf("Choose action: ");
}

void printVectors( const VectorSet* set ) {
    printf("\nCURRENT STATE:\n");
    printf("v1 = "); 
    if( set->v1 ) printVector(set->v1); else printf("NULL");
    printf("\n");
    
    printf("v2 = "); 
    if( set->v2 ) printVector(set->v2); else printf("NULL");
    printf("\n");
    
    printf("v3 = "); 
    if( set->v3 ) printVector(set->v3); else printf("NULL");
    printf("\n");
}


int main() {
    VectorSet set = {NULL, NULL, NULL};
    int choice, dim, index;
    int int_val;
    double double_val;
    ErrorCode err;
    
    printHeader();

    while(1) {
        printMenu();

        if( scanf("%d", &choice) != 1 ) {
            printf("Input error. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
                
            case 1: {
                printf("Enter vector dimension: ");
                if( scanf("%d", &dim) != 1 || dim <= 0 ) {
                    printf("Invalid dimension.\n");
                    clearInputBuffer();
                    break;
                }
                
                clearVectors(&set);
                set.v1 = createVector(dim, ofInt());
                set.v2 = createVector(dim, ofInt());
                set.v3 = createVector(dim, ofInt());
                
                if( set.v1 && set.v2 && set.v3 ) {
                    printf("int vectors of dimension %d created (and initialised with zeros)\n", dim);
                } 
                else {
                    printf("Error creating vectors\n");
                    clearVectors(&set);
                }
                break;
            }

            case 2: {
                printf("Enter vector dimension: ");
                if( scanf("%d", &dim) != 1 || dim <= 0 ) {
                    printf("Invalid dimension.\n");
                    clearInputBuffer();
                    break;
                }
                
                clearVectors(&set);
                set.v1 = createVector(dim, ofDouble());
                set.v2 = createVector(dim, ofDouble());
                set.v3 = createVector(dim, ofDouble());
                
                if( set.v1 && set.v2 && set.v3 ) {
                    printf("double vectors of dimension %d created (and initialised with zeros)\n", dim);
                } 
                else {
                    printf("Error creating vectors\n");
                    clearVectors(&set);
                }
                break;
            }

            case 3: {
                clearVectors(&set);
                printf("All vectors deleted\n");
                break;
            }

            case 4: {
                printVectors(&set);
                break;
            }

            case 5: {
                if( !set.v1 ) {
                    printf("Create vectors first\n");
                    break;
                }
                
                printf("Enter index: ");
                if( scanf("%d", &index) != 1 ) {
                    printf("Invalid index.\n");
                    clearInputBuffer();
                    break;
                }
                
                printf("Enter value: ");
                if( set.v1->type == ofInt() ) {
                    if( scanf("%d", &int_val) != 1 ) {
                        printf("Invalid input. Expected integer.\n");
                        clearInputBuffer();
                        break;
                    }
                    err = setVectorElement(set.v1, index, &int_val);
                } 
                else {
                    if( scanf("%lf", &double_val ) != 1 ) {
                        printf("Invalid input. Expected double.\n");
                        clearInputBuffer();
                        break;
                    }
                    err = setVectorElement(set.v1, index, &double_val);
                }
                
                if( err == SUCCESS ) {
                    printf("Element set. New vector: ");
                    printVector(set.v1);
                    printf("\n");
                } 
                else {
                    printError(err, "setVectorElement");
                }
                break;
            }

            case 6: {
                if( !set.v1 ) {
                    printf("Create vectors first\n");
                    break;
                }
                
                printf("Enter index: ");
                if( scanf("%d", &index) != 1 ) {
                    printf("Invalid index.\n");
                    clearInputBuffer();
                    break;
                }
                
                if( set.v1->type == ofInt() ) {
                    err = getVectorElement(set.v1, index, &int_val);
                    if (err == SUCCESS) {
                        printf("v1[%d] = %d\n", index, int_val);
                    }
                } 
                else {
                    err = getVectorElement(set.v1, index, &double_val);
                    if( err == SUCCESS ) {
                        printf("v1[%d] = %.2f\n", index, double_val);
                    }
                }
                
                if( err != SUCCESS ) {
                    printError(err, "getVectorElement");
                }
                break;
            }

            case 7: {
                if( !set.v1 ) {
                    printf("Create vectors first\n");
                    break;
                }
                err = readVectorFromConsole(set.v1);
                if( err == SUCCESS ) {
                    printf("v1 successfully entered: ");
                    printVector(set.v1);
                    printf("\n");
                } 
                else {
                    printError(err, "readVectorFromConsole");
                }
                break;
            }

            case 8: {
                if( !set.v2 ) {
                    printf("Create vectors first\n");
                    break;
                }
                err = readVectorFromConsole(set.v2);
                if( err == SUCCESS ) {
                    printf("v2 successfully entered: ");
                    printVector(set.v2);
                    printf("\n");
                } 
                else {
                    printError(err, "readVectorFromConsole");
                }
                break;
            }

            case 9: {
                if( !set.v1 || !set.v2 || !set.v3 ) {
                    printf("Create vectors first\n");
                    break;
                }
                err = addVector(set.v1, set.v2, set.v3);
                if( err == SUCCESS ) {
                    printf("Addition result: ");
                    printVector(set.v3);
                    printf("\n");
                } 
                else {
                    printError(err, "addVector");
                }
                break;
            }

            case 10: {
                if( !set.v1 || !set.v2 || !set.v3 ) {
                    printf("Create vectors first\n");
                    break;
                }
                err = subtrVector(set.v1, set.v2, set.v3);
                if( err == SUCCESS ) {
                    printf("Subtraction result: ");
                    printVector(set.v3);
                    printf("\n");
                } 
                else {
                    printError(err, "subtrVector");
                }
                break;
            }

            case 11: {
                if( !set.v1 || !set.v2 ) {
                    printf("Create vectors first\n");
                    break;
                }
                
                if( set.v1->type == ofInt() ) {
                    int result;
                    err = dotProduct(set.v1, set.v2, &result);
                    if( err == SUCCESS ) {
                        printf("Dot product (v1,v2) = %d\n", result);
                    }
                } 
                else {
                    double result;
                    err = dotProduct(set.v1, set.v2, &result);
                    if( err == SUCCESS ) {
                        printf("Dot product (v1,v2) = %.2f\n", result);
                    }
                }
                
                if( err != SUCCESS ) {
                    printError(err, "dotProduct");
                }
                break;
            }

            case 0: {
                clearVectors(&set);
                printf("Program terminated. Thank you for using it!\n");
                return 0;
            }

            default: {
                printf("Unknown command. Please choose 0-12.\n");
                break;
            }
        }
    }


    return 0;
}