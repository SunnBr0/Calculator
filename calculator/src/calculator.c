/*Name        : calculator.c
 Author      : Vladimir Voronov
 Version     : 3.5
 Copyright   : VoronovVladimirIVT.VSU
 Description : calculator
 Git	     : Вы должны обладать ссылкой (https://github.com/SunnBr0/calculator).
Калькулятор поддерживает работу с числами и с векторами,
операция для чисел(+,*,-,/,^,!) операции для векторов (+,-,*(скалярное умножение))
 Калькулятор может работать с входными файлами и также выводить результат в файл
Обновление:
Теперь выполнение операций идёт не синхронно с чтением из файла, а из списка.
Теперь через структуру inputList делаем односвязанный-список с входными данными,а через структуру outputList
делаем односвязанный-список с результатами вычислений
Пример:
Назовём файл input.txt ,запишем туда эти выражения:
s - алгебраический калькулятор
v - векторный калькулятор
s + 1.1 5.9
s - 4.25 0.25
s / 2.5 1.25
s * 5.2 2
s ^ 2.1 6
v + 3 1 4 1 2 2 3
v - 3 1 4 1 2 -1 2
v * 3 1 4 1 2 -2 -2
вывод пусть будет output.txt
результат увидете сами
*/
#include <stdio.h>
#include <stdlib.h>

// список для входных данных
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
    return two_number;
    free(one_number);
    free(two_number);
    free(result_numb);
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
    return twovector;
    free(onevector);
    free(twovector);
    free(res_vect);
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

int main(int argc, char *argv[]) {

    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    char in[100], out[100];
    char n = 'y';
    FILE *inFile, *outFile;
    struct inputList *head, *current; //указатели на начало inputList списка и текущий элемент
    struct outputList *head_result, *current_result;//указатели на начало outputList списка и текущий элемент
    while (n == 'y') {

        printf("Enter input file name: ");         // просит ввести файл откуда брать данные
        scanf("%s", in);
        inFile = fopen(in,"r");
        if (inFile == NULL){                     // проверка на существование файла ввода
            printf("Error enter again\n");
            while (inFile == NULL){
                printf("Enter input file name: ");
                scanf("%s", in);
                inFile = fopen(in,"r");
            }
        }
        printf("\nEnter output file name: ");   //просит ввести файл куда записовать данные
        scanf("%s", out);
        outFile = fopen(out,"w");
        if (feof(inFile) == 0) {
            head = malloc(sizeof(struct inputList)); //  head - указатель на структуру,на его начало
            fscanf(inFile, " %c", &head->vbor);
            fscanf(inFile, " %c", &head->operation);
            if (head->vbor == 'v') {
                fscanf(inFile, " %i", &head->size);
            } else {
                head->size = 1;
            }
            if (head->operation != '!') {
                head->x = add_numb(inFile, head->size);
                head->y = add_numb(inFile, head->size);
            } else {
                head->x = add_numb(inFile, head->size);
                head->y = NULL;
            }
            current = head; // current указатель на структуру а именно на текущие положение
            while (feof(inFile) == 0) { // заполнение односвязанного списка вхожными данными из файла
                add_element(current, inFile);
                current = current->next;
            }
            head_result = malloc(sizeof(struct outputList)); // head - указатель на структуру,на его начало
            current = head;
            if (current->vbor == 'v') {
                head_result->result = func_vect(current->operation, current->size, current->x,
                                     current->y);
            } else {
                head_result->result = func_numb(current->operation, current->x, current->y);
            }
            head_result->res_next = NULL;
            current = current->next;
            current_result = head_result;
            while (current != NULL) { // пока элемент списка не последниий
                result_add_element(current_result, current);
                // переустановка указателей на следующий элемент
                current = current->next;
                current_result = current_result->res_next;
            }
            current = head;
            current_result = head_result;
            fclose(inFile);
            outFile = fopen(out, "w");
            while (current != NULL) //запись ответа в output
            {
                fprintf(outFile,"What will you work with with numbers or vectors?  (s - numbers, v-vectors)\n"); // выбор с чем работать с числами или с векторами
                fprintf(outFile,"%c\n",current->vbor);
                if (current->vbor == 'v') {
                    fprintf(outFile,"Enter the size of the vector:\n");
                    fprintf(outFile,"%i\n",current->size);
                    fprintf(outFile,"Enter vector one:\n");
                    for(int i = 0; i < current->size ;i++){fprintf(outFile,"%f\n",current->x[i]);} // заполняем первый вектор
                    fprintf(outFile,"Enter vector two:\n");
                    for(int i = 0; i < current->size ;i++){fprintf(outFile,"%f\n",current->y[i]);} // заполняем второй вектор
                    fprintf(outFile,"Enter the operation on the vectors(+ - *):\n");
                    fprintf(outFile,"%c\n",current->operation);
                    fprintf(outFile, "(");
                    for (int i = 0; i < current->size; i++) {
                        fprintf(outFile, " %.2f", current->x[i]);
                    }
                    fprintf(outFile, ") %c (", current->operation);
                    for (int i = 0; i < current->size; i++) {
                        fprintf(outFile, " %.2f", current->y[i]);
                    }
                    fprintf(outFile, " ) = ");
                    if (current->operation != '*') {
                        fprintf(outFile, "( ");
                        for (int i = 0; i < current->size; i++) {
                            fprintf(outFile, "%.2f ", current_result->result[i]);
                        }
                        fprintf(outFile, ")\n\n");
                    } else {
                        fprintf(outFile, "%.2f\n\n", current_result->result[0]);
                    }
                } else if (current->vbor == 's') {
                    fprintf(outFile, "%.2f %c %.2f = %.2f\n\n", current->x[0], current->operation,current->y[0], current_result->result[0]);
                }
                current = current->next;
                current_result = current_result->res_next;
            }
            fclose(outFile);
        }
        printf("\nWant to work with new files(input and output)?\n");
        scanf( "%s", &n);
    }
    return 0;
}

