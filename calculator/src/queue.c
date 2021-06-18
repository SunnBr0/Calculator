#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


queue_t init_queue() {
    queue_t queue; // создаём саму очередь
    queue.head = NULL;
    queue.tail = NULL;
    return queue;
}

// добавление элемента в конец очереди
void enqueue(queue_t *queue, char *value) {
    data *node = (data*) malloc(sizeof(data));
    node->elem = value;

    node->next = NULL;
    if (queue->tail == NULL) {
        queue->head = node;
    } else {
        queue->tail->next = node;
    }
    queue->tail = node;
}
// удаление элемента из очереди
char* dequeue(queue_t *queue) {
    char *elem = queue->head->elem;

    data *tmp = queue->head;
    queue->head = queue->head->next;
    free(tmp);
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
    return elem;
}
// проверка очереди на пустоту
int is_empty(queue_t queue) {
    return queue.head == NULL;
}
// считывание строки из файла
char* read_string(FILE *input) {
    int size = 0; // размер строки
    int len_size = 1;  // ёмкость строки
    char *string = (char*) malloc(len_size * sizeof(char));
    for (char c = fgetc(input); !feof(input) && c != '\n'; c = fgetc(input)) {
        string[size++] = c;
        if (size >= len_size) { // если ёмкости недостаточно
            len_size *= 2;      // увеличиваем её в 2 раза
            string = (char*) realloc(string, len_size * sizeof(char)); // и перераспределяем память
        }
    }
    string[size] = '\0';
    return string;
}
// проверка на цифру
int is_digit(float digit) {
    return (digit >= '0' && digit <= '9');
}
// ввод числа из строки
int read_int(char *string, int *i) {
    int value = 0;
    while (string[*i] == ' ') {
        (*i)++;
    }
    while (string[*i] && is_digit(string[*i])) {
        value = value * 10 + string[(*i)++] - '0';
    }
    return value;
}
double read_double(char *string, int *i) {
    int start = *i;
    char prev = string[*i];
    while (string[*i] == ' ') {
        (*i)++;
    }
    while (string[*i] && (is_digit(string[*i]) || string[*i] == '.')) {
        (*i)++;
    }
    string[*i] = '\0';
    double value = atof(string + start); // переводим строку в число
    string[*i] = prev;
    return value;
}
double factorial(int number) {
    double factorial = 1;
    for (int i = 2; i <= number; i++) {
        factorial *= i;
    }
    return factorial;
}
void numbers(FILE *output, char *string, char sign) {
    fprintf(output,"What will you work with with numbers or vectors?  (s - numbers, v-vectors)\n"); // выбор с чем работать с числами или с векторами
    fprintf(output,"s\n");
    int index = 3;
    if (sign == '!') {
        int x = read_int(string, &index);
        fprintf(output, "%.0lf\n", factorial(x));
        return;
    }
    double x = read_double(string, &index);
    double y = read_double(string, &index);
    if (sign == '+') {
        fprintf(output, "%.2lf %c %.2lf = %.2lf\n\n", x,sign,y,x + y);
    } else if (sign == '-') {
        fprintf(output, "%.2lf %c %.2lf = %.2lf\n\n", x,sign,y,x - y);
    } else if (sign == '*') {
        fprintf(output, "%.2lf %c %.2lf = %.2lf\n\n", x,sign,y,x * y);
    } else if (sign == '/') {
        if (y == 0)
            fprintf(output, "division by zero\n");
        else
            fprintf(output, "%.2lf %c %.2lf = %.2lf\n\n", x,sign,y,(double)x / y);
    } else if (sign == '^') {
        float stepen = 1;
        for (int i = 1; i <= y; i++) {
            stepen *= x;
        }
        fprintf(output, "%.2lf %c %.2lf = %.2lf\n\n", x,sign,y,stepen);
    } else {
        fprintf(output, "unknown operation '%c'\n", sign);
    }
}
void vectors(FILE *output, char *string, char sign) {
    fprintf(output,"What will you work with with numbers or vectors?  (s - numbers, v-vectors)\n"); // выбор с чем работать с числами или с векторами
    fprintf(output,"v\n");
    int index = 3;
    int size = read_int(string, &index); // размерность вектора
    fprintf(output,"Enter the size of the vector:\n");
    fprintf(output,"%i\n",size);
    double *onevector = (double*) malloc(size * sizeof(double));
    double *twovector= (double*) malloc(size * sizeof(double));
    // считываем вектора
    fprintf(output,"Enter vector one:\n");
    for (int i = 0; i < size; i++){
        onevector[i] = read_double(string, &index);
        fprintf(output,"%f\n",onevector[i]);
    }
    fprintf(output,"Enter vector two:\n");
    for (int i = 0; i < size; i++){
        twovector[i] = read_double(string, &index);
        fprintf(output,"%f\n",twovector[i]);
    }
    fprintf(output,"Enter the operation on the vectors(+ - *):\n");
    fprintf(output,"%c\n",sign);
    if (sign == '*') {
        double res = 0;
        fprintf(output, "( ");
        for (int i = 0; i < size; i++)
            fprintf(output, "%.2f ", onevector[i]);
        fprintf(output, ") * ( ");
        for (int i = 0; i < size; i++)
            fprintf(output, "%.2f ", twovector[i]);
        fprintf(output, ") = ");
        for (int i = 0; i < size; ++i) {
            if (i != size - 1 ){fprintf(output, "%.2f ", onevector[i]*twovector[i]);
                fprintf(output,"+ ");
            }
            else{
                fprintf(output, "%.2f ", onevector[i]*twovector[i]);
            }
        }
        fprintf(output, " = ");
        for (int i = 0; i < size; i++)
            res += onevector[i] * twovector[i];
        fprintf(output, "%.2f ", res);
        fprintf(output,"\n\n");
    } else if (sign == '+' || sign == '-') {
        if (sign == '+') {
            fprintf(output, "(");
            for (int i = 0; i < size; i++) {
                fprintf(output, " %.2f", onevector[i]);
            }
            fprintf(output, ") %c (",sign);
            for (int i = 0; i < size; i++) {
                fprintf(output, " %.2f", twovector[i]);
            }
            fprintf(output, " ) = ");
            for (int i = 0; i < size; i++){
                fprintf(output, "%.2lf ", onevector[i] + twovector[i]);
            }
            fprintf(output, "\n\n");
        } else {
            fprintf(output, "(");
            for (int i = 0; i < size; i++) {
                fprintf(output, " %.2f", onevector[i]);
            }
            fprintf(output, ") %c (",sign);
            for (int i = 0; i < size; i++) {
                fprintf(output, " %.2f", twovector[i]);
            }
            fprintf(output, " ) = ");
            for (int i = 0; i < size; i++){
                fprintf(output, "%.2lf ", onevector[i] - twovector[i]);
            }
            fprintf(output, "\n\n");
        }
    } else {
        fprintf(output, "unknown operation '%c'\n", sign);
    }
    free(onevector);
    free(twovector);
}
// вычисление значения выражения
void calc(FILE *input, char *string) {
    char vbor = string[0];  // выбор калькулятора(алгебраический или векторный)
    char sign = string[2];
    if (vbor == 's') {
        numbers(input, string, sign);
    } else if (vbor == 'v') {
        vectors(input, string, sign);
    }
}
