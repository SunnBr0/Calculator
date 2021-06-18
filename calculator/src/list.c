#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// функция для операций с числами
float* func_numb(char operation, float *one_number, float *two_number) {
    float fuctorial, stepen, *result_numb;
    result_numb = malloc(sizeof(float));
    switch (operation) {
        case '+':
            result_numb[0] = one_number[0] + two_number[0];
            return result_numb;
        case '-':
            result_numb[0] = one_number[0] - two_number[0];
            return result_numb;
        case '*':
            result_numb[0] = one_number[0] * two_number[0];
            return result_numb;
        case '/':
            if (two_number != 0) {
                result_numb[0] = one_number[0] / two_number[0];
                return result_numb;
            } else {
                return 0;
            }
        case '!':
            fuctorial = 1;
            for (int i = 1; i <= one_number[0]; i++) {
                fuctorial *= i;
            }
            result_numb[0] = fuctorial;
            return result_numb;
        case '^':
            fuctorial = 1;
            stepen = 1;
            for (int i = 1; i <= two_number[0]; i++) {
                stepen *= one_number[0];
            }
            result_numb[0] = stepen;
            return result_numb;
    }
    return one_number;
}

// функция для операций с векторами
float* func_vect(char operation, int size, float *onevector, float *twovector) {
    float *res_vect;
    switch (operation) {
        case '+':
            res_vect = malloc(size * sizeof(float));
            for (int i = 0; i < size; i++) {
                res_vect[i] = onevector[i] + twovector[i];
            }
            return res_vect;

        case '-':
            res_vect = malloc(size * sizeof(float));
            for (int i = 0; i < size; i++) {
                res_vect[i] = onevector[i] - twovector[i];
            }
            return res_vect;

        case '*':
            res_vect = malloc(sizeof(float));
            res_vect[0] = 0;
            for (int i = 0; i < size; i++) {
                res_vect[0] += onevector[i] * twovector[i];
            }
            return res_vect;
    }
    return onevector;
}

// считывание указателей, добавление чисел
float* add_numb(FILE *input, int size) {
    float *numb;
    numb = malloc(size * sizeof(float));
    for (int i = 0; i < size; i++) {
        fscanf(input, "%f", &numb[i]);
    }
    return numb;
}

// добавление одного элемента списка для входных данных
void add_element(struct inputList *current, FILE *input) {
    struct inputList *current_elem = malloc(sizeof(struct inputList));
    fscanf(input, " %c", &current_elem->vbor);
    fscanf(input, " %c", &current_elem->operation);
    if (current_elem->vbor == 'v') {
        fscanf(input, " %i", &current_elem->size);
    } else {
        current_elem->size = 1;
    }
    if (current_elem->operation != '!') {
        current_elem->x = add_numb(input, current_elem->size);
        current_elem->y = add_numb(input, current_elem->size);
    } else {
        current_elem->x = add_numb(input, current_elem->size);
        current_elem->y = NULL;
    }
    current_elem->next = NULL; // последний элемент списка
    current->next = current_elem; // переустановка указателя
}

// добавление элемента списка для выходных данных
void result_add_element(struct outputList *res_current, struct inputList *current) {
    struct outputList *z_res = malloc(sizeof(struct inputList));
    if (current->vbor == 'v') {
        z_res->result = func_vect(current->operation, current->size, current->x, current->y);
    } else {
        z_res->result = func_numb(current->operation, current->x, current->y);
    }
    z_res->res_next = NULL;
    res_current->res_next = z_res;
}