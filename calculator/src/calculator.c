/*Name        : calculator.c
 Author      : Vladimir Voronov
 Version     : 3
 Copyright   : VoronovVladimirIVT.VSU
 Description : calculator
 Git	     : Вы должны обладать ссылкой (https://github.com/SunnBr0/calculator).
Калькулятор поддерживает работу с числами и с векторами,
операция для чисел(+,*,-,/,^,!) операции для векторов (+,-,*(скалярное умножение))
Обновление:
Калькулятор может работать с входными файлами и также выводить результат в файл
Пример:
Назовём файл input.txt ,запишем туда эти выражения:
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

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    char in[100],out[100],vbor,operation,next;
    FILE *inFile,*outFile;
    float *onevector,*twovector;
    int size;
    float a, b, res, stepen;
    printf("you want to work with vectors ");
    printf("Hello , i am cancilator\n");
    printf("My operation:\n");
    printf("+- you can add two numbers ( 1 + 2 ) or minus ( 3 - 2 )\n");
    printf("* or / you can multiply ( 1 * 3 ) or divide it ( 1 / 2 )\n ");
    printf("^ you can raise to a power even to a negative one ( 2 ^ 3 ) , ( 5 ^ -2 )\n");
    printf("! you can find the factorial of a number ( 5 ! )\n");
    printf("Also, the calculator works with vectors,you can (+ - *)\n\n");
    do{
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
        do {
            fprintf(outFile,"What will you work with with numbers or vectors?  (s - numbers, v-vectors)\n"); // выбор с чем работать с числами или с векторами
            fscanf(inFile," %c",&vbor);     // читает с файла с чем работать(с векторами или числами)
            fprintf(outFile,"%c\n",vbor);
            if(vbor == 'v'){
                fscanf(inFile," %c",&operation); // читает с файла операцию
                fprintf(outFile,"Enter the size of the vector:\n");
                fscanf(inFile,"%i",&size);        // читает с файла размер вектора
                fprintf(outFile,"%i\n",size);
                onevector = malloc(size*sizeof(int));
                twovector = malloc(size*sizeof(int));
                fprintf(outFile,"Enter vector one:\n");
                for(int i = 0; i < size ;i++){fscanf(inFile," %f",&onevector[i]);fprintf(outFile,"%f\n",onevector[i]);} // заполняем первый вектор
                fprintf(outFile,"Enter vector two:\n");
                for(int i = 0; i < size ;i++){fscanf(inFile," %f",&twovector[i]);fprintf(outFile,"%f\n",twovector[i]);} // заполняем второй вектор
                fprintf(outFile,"Enter the operation on the vectors(+ - *):\n");
                fprintf(outFile,"%c\n",operation);     // выводит в файл операцию
                switch(operation){		// операции с векторами
                    case('+'):
                        fprintf(outFile, "( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", onevector[i]);
                        fprintf(outFile, ") + ( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", twovector[i]);
                        fprintf(outFile, ") = ( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", onevector[i] + twovector[i]);
                        fprintf(outFile, ")");
                        fprintf(outFile,"\n\n");
                        break;
                    case('-'):
                        fprintf(outFile, "( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", onevector[i]);
                        fprintf(outFile, ") + ( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", twovector[i]);
                        fprintf(outFile, ") = ( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", onevector[i] - twovector[i]);
                        fprintf(outFile, ")");
                        fprintf(outFile,"\n\n");
                        break;
                    case('*'):
                        fprintf(outFile, "( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", onevector[i]);
                        fprintf(outFile, ") * ( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", twovector[i]);
                        fprintf(outFile, ") = ");
                        for (int i = 0; i < size; ++i) {
                            if (i != size - 1 ){fprintf(outFile, "%.2f ", onevector[i]*twovector[i]);
                                fprintf(outFile,"+ ");
                            }
                            else{
                                fprintf(outFile, "%.2f ", onevector[i]*twovector[i]);
                            }
                        }
                        fprintf(outFile, " = ");
                        for (int i = 0; i < size; i++)
                            res += onevector[i] * twovector[i];
                        fprintf(outFile, "%.2f ", res);
                        fprintf(outFile,"\n\n");
                        break;
                    default:				                 // если операция не определена то будет ошибка
                        printf("Error\n");
                }
                free(onevector);            //очистка памяти
                free(twovector);
            }else{
                fscanf(inFile," %c",&operation);        // читает с файла операцию
                if (operation != '!') {	                     // тут необходимое условие тк для факториала нужно только ввести число и операцию
                    fscanf(inFile," %f %f",&a,&b);
                    switch (operation) {                     //тут происходит выбор операции над числом или числами
                        case ('+'):
                            fprintf(outFile,"%f %c %f = %f\n", a, operation, b, a + b);
                            fprintf(outFile,"\n");
                            break;
                        case ('-'):
                            fprintf(outFile,"%f %c %f = %f\n", a, operation, b, a - b);
                            fprintf(outFile,"\n");
                            break;
                        case ('/'):
                            fprintf(outFile,"%f %c %f = %f\n", a, operation, b, a / b);
                            fprintf(outFile,"\n");
                            break;
                        case ('*'):
                            fprintf(outFile,"%f %c %f = %f\n", a, operation, b, a * b);
                            fprintf(outFile,"\n");
                            break;
                        case ('^'):			                     // помимо простых действий над число ( + - * /),
                            stepen = 1;	                         //где нужно ничего особенно пиcать для реализации
                            if (b >= 0) {                        // в отличие от возведения в степень,где для реализации нужен цикл for
                                for (int i = 1; i <= b; i++) {
                                    stepen *= a;
                                }
                                fprintf(outFile,"%f %c %f = %f\n", a, operation, b, stepen);
                            } else if (b < 0) {
                                for (int i = 0; i > b; i--) {
                                    stepen *= a;
                                }
                                fprintf(outFile,"%f %c %f = %f\n", a, operation, b, 1 / stepen);

                            }
                            fprintf(outFile,"\n");
                            break;
                        default:				                 // если операция не определена то будет ошибка
                            fprintf(outFile,"Error\n");
                    }
                } else {
                    fscanf(inFile," %f",&a);
                    res = 1;
                    if (a >= 0 && (a <= (int)a)) {
                        for (int i = 1; i <= a; i++) {       // факториал реализован через цикл for
                            res *= i;
                        }
                        fprintf(outFile,"%f %c = %f\n", a, operation, res);
                        fprintf(outFile,"\n");
                    } else {								 // обработка ошибки
                        fprintf(outFile,"Error\n");
                    }
                }
            }
        } while (feof(inFile) == 0);							 // цикл для того чтобы пользователь продолжил считать либо закончил работу
        fclose(outFile);        // закрывает файл при завершении работы с файлом ввода
        clearerr(outFile);     // очистка
        printf("\nWant to work with new files(input and output)?\n");  // хотите работать с новыми файлами
        scanf(" %c", &next);
    }while (next == 'y');
    return 0;
}
