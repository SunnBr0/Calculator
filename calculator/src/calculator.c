#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "stack.h"
#include "list.h"


int main(int argc, char *argv[]){
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    char n, stringLine[255], line = '0',module;
    FILE *inFile, *outFile;
    char input[255], output[255];
    int i = 0;
    float localNum, onenumber, twonumber;
    struct inputList *head, *current; //указатели на начало inputList списка и текущий элемент
    struct outputList *head_result, *current_result;//указатели на начало outputList списка и текущий элемент
    stack *headStack = NULL;
    do {
        printf("What do you want to work with?(l - list, q - queue, s - stack) ");
        scanf(" %c", &module);
        switch (module) {
            case 'l':
                printf("Enter input file name: ");         // просит ввести файл откуда брать данные
                scanf("%s", input);
                inFile = fopen(input,"r");
                if (inFile == NULL){                     // проверка на существование файла ввода
                    printf("Error enter again\n");
                    while (inFile == NULL){
                        printf("Enter input file name: ");
                        scanf("%s", input);
                        inFile = fopen(input,"r");
                    }
                }
                printf("\nEnter output file name: ");   //просит ввести файл куда записовать данные
                scanf("%s", output);
                outFile = fopen(output,"w");
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
                    outFile = fopen(output, "w");
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
                break;
            case 'q':
                printf("Enter input file name: ");
                scanf("%s", input);
                inFile = fopen(input, "r");
                if (inFile == NULL) {           // проверка на существование файла ввода
                    printf("Error enter again\n");
                    while (inFile == NULL) {
                        printf("Enter input file name: ");
                        scanf("%s", input);
                        inFile = fopen(input, "r");
                    }
                }
                queue_t init_queue();
                queue_t queue = init_queue();            // создаём пустую очередь
                while (!feof(inFile))
                    enqueue(&queue, read_string(inFile)); // добавляем в очередь строки
                fclose(inFile);
                printf("Enter output file name: ");
                scanf("%s", output);
                outFile = fopen(output, "w");
                while (!is_empty(queue)) {         // пока не кончится очередь
                    calc(outFile, dequeue(&queue)); // вычисляем выражение
                }
                fclose(outFile);
                break;
            case 's':
                printf("Enter input file name:");
                scanf("%s", input);
                inFile = fopen(input,"r");  //   открыть входной файл
                if (inFile == NULL){
                    printf("Error enter again\n");
                    while (inFile == NULL){
                        printf("Enter input file name:");
                        scanf(" %s", input);
                        inFile = fopen(input,"r");
                    }
                }
                printf("Enter output file name:");
                scanf(" %s", output);
                outFile = fopen(output, "w");  //  открыть выходной файл
                while (feof(inFile) == 0){
                    fscanf(inFile, "%c", &stringLine[i]);
                    if (stringLine[i] == ' '){
                        if (line == '0'){
                            localNum = strtof(stringLine, NULL); //  разделите выражение на символы
                            pushElement(&headStack, localNum);
                            i = 0;
                        }
                    }
                    else if (stringLine[i] == '*' || stringLine[i] == '+' || stringLine[i] == '-'	|| stringLine[i] == '/' || stringLine[i] == '^'){
                        onenumber = popElement(&headStack);
                        twonumber = popElement(&headStack);
                        pushElement(&headStack, numberFunction(stringLine[i], onenumber, twonumber));
                        fprintf(outFile, "%.3f %c %.3f = %.3f \n", onenumber, stringLine[i], twonumber, numberFunction(stringLine[i], onenumber, twonumber));
                        line = '1';
                    }
                    else if (stringLine[i] == 'n'){
                        while (headStack != NULL){
                            popElement(&headStack);
                        }
                        fprintf(outFile, "\n");
                    }
                    else{
                        line = '0';
                        i = i + 1;
                    }
                }
                fclose(inFile);
                fclose(outFile);
                break;
        }

        printf("Want to work with new files(input and output)?");
        scanf(" %c", &n);
    } while (n == 'y');
    return 0;
}
