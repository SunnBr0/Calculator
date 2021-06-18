#include <stdio.h>

#ifndef LIST_H_
#define LIST_H_

// some variables are moved to the top for comfortably work
struct inputList {
    char operation, vbor;
    int size;
    float *x, *y;
    struct inputList *next;
};

// список для выходных данных
struct outputList {
    float *result;
    struct outputList *res_next;
};

float* func_numb(char operation, float *one_number, float *two_number);                     //  function for working with numbers
float* func_vect(char operation, int size, float *onevector, float *twovector);                //  function for working with vectors
float* add_numb(FILE *input, int size);                                                      //  adding numbers
void add_element(struct inputList *current, FILE *input);                                         //  adding current items to the `listIn`
void result_add_element(struct outputList *res_current, struct inputList *current);

#endif