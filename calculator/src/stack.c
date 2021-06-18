#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

float numberFunction(char operation, float number1, float number2){     //  function for working with numbers
    float factorial = 1, stepen = 1, resultNumber;
    switch (operation){  //  operation fetch block
        case '+':
            resultNumber = number1 + number2;
            return resultNumber;  //  результат сложение
        case '-':
            resultNumber = number1 - number2;
            return resultNumber;  //  результат вычитание
        case '*':
            resultNumber = number1 * number2;
            return resultNumber;  // результат умножение
        case '/':
            if (number2 != 0){
                resultNumber = number1 / number2;
                return resultNumber;  //  результат деления
            }
            else{
                return 0;
            }
        case '!':
            for (int i=1; i <= number1; i++){
                factorial = factorial*i;
            }
            resultNumber = factorial;
            return resultNumber;  //  результат факториала
        case '^':
            for (int i=1; i <= number2; i++){
                stepen = stepen*number1;
            }
            resultNumber = stepen;
            return resultNumber;  //  результат степени
    }
    return number1;
}

void pushElement(stack **head, float data){         //добавить элемент в стек структуру
    stack *pushLocal = malloc(sizeof(stack));
    pushLocal->next = *head;
    pushLocal->data = data;
    *head = pushLocal;
}

float popElement(stack **head){             //  remove element from stack`s struct
    stack *popLocal;
    float data;
    popLocal = *head;
    *head = (*head)->next;
    data = popLocal->data;
    return data;
}
