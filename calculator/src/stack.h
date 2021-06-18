#include <stdio.h>

#ifndef STACK_H_
#define STACK_H_

// some variables are moved to the top for comfortably work
typedef struct element {
    float data;
    struct element *next;
} stack;

void pushElement(stack **head, float data);                                             //  add element in stack`s struct
float popElement(stack **head);                                                         //  remove element from stack`s struct
float numberFunction(char operation, float number1, float number2);                //  function for working with numbers

#endif