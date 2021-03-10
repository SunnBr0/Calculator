// Online C compiler to run C program online
#include <stdio.h>

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	float a, b, res, stepen;
	char operation;
	char next;
	printf("Hello , i am cancilator\n");
	printf("My operation:\n");
	printf("+- вы можете plus два числа ( 1 + 2 ) или minus ( 3 - 2 )\n");
	printf("* или / вы можете умножить ( 1 * 3 ) или поделить ( 1 / 2 )\n ");
	printf(
			"^ вы можете возвести в степень даже в отрицательную ( 2 ^ 3 ) , ( 5 ^ -2 )\n");
	printf("! вы можете найти факториал числа ( 5 ! )\n\n");
	do {
		scanf("%f %c", &a, &operation);
		if (operation != '!') {	// тут необходимое условие тк для факториала нужно только ввести число и операцию
			scanf("%f", &b);
			switch (operation) {//тут происходит выбор операции над числом или числами
			case ('+'):
				printf("%f %c %f = %f\n", a, operation, b, a + b);
				break;
			case ('-'):
				printf("%f %c %f = %f\n", a, operation, b, a - b);
				break;
			case ('/'):
				printf("%f %c %f = %f\n", a, operation, b, a / b);
				break;
			case ('*'):
				printf("%f %c %f = %f\n", a, operation, b, a * b);
				break;
			case ('^'):			// помимо простых действий над число ( + - * /),
				stepen = 1;	//где нужно ничего особенно пиcать для реализации
				if (b >= 0) {// в отличие от возведения в степень,где для реализации нужен цикл for
					for (int i = 1; i <= b; i++) {
						stepen *= a;
					}
					printf("%f %c %f = %f\n", a, operation, b, stepen);
				} else if (b < 0) {
					for (int i = 0; i > b; i--) {
						stepen *= a;
					}
					printf("%f %c %f = %f\n", a, operation, b, 1 / stepen);
				}
				break;
			default:				// если операция не определена то всё смэрть
				printf("error,смэрть\n");
			}
		} else {
			res = 1;
			if (a >= 0) {
				for (int i = 1; i <= a; i++) {// факториал реализован через цикл for
					res *= i;
				}
				printf("%f %c = %f\n", a, operation, res);
			} else {
				printf("хехе, вы чего то ожидали\n");
			}
		}
		printf("Continue (y/n)? \n"); // y - yes , n - not
		scanf(" %c", &next);
	} while (next == 'y');// цикл для того чтобы пользователь продолжил считать либо закончил работу
	return 0;

}
