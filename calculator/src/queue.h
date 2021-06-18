#include <stdio.h>

#ifndef QUEUE_H_
#define QUEUE_H_

// структура для элемента очереди
typedef struct data {
    char *elem;
    struct data *next;
} data;
// струкрута, создаваемая для очереди
typedef struct queue_t {
    data *head;
    data *tail;
} queue_t;
// инициализация пустой очереди

void enqueue(queue_t *queue, char *value);
char* dequeue(queue_t *queue);
int is_empty(queue_t queue);
char* read_string(FILE *input);
int is_digit(float c);
int read_int(char *s, int *i);
double read_double(char *s, int *i);                  //  output the result to a output file
void numbers(FILE *output, char *string, char sign);
void vectors(FILE *output, char *string, char sign);
void calc(FILE *input, char *string);

#endif
