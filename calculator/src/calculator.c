/*Name        : calculator.c
 Author      : Vladimir Voronov
 Version     : 1.1
 Copyright   : Ivt
 Description : calculator
 Git	     : Вы должны обладать ссылкой (https://github.com/SunnBr0/test_01).
Теперь осталось зайти в Eclipse, зайти в workspace(свой или новый).
Как откроется IDE сверху выбираем Window->Percpective->Open Percpective->Other...->Git.
Откроется специальное окно, нужно нажать clone git repository(где есть желтые значками).
Появится окно, в нем нужно вбить ссылку, либо до откытия clone git repository сохранить в буфер обмена ссылку и Eclipse все сделает сам(Authentication заполнять не нужно, как и все остально кроме location, и в Connection выбрать протокол https).
Жмем Next, снова жмем Next, выбираем путь, где будет хранится репозиторий из гит на вашем компьютере(Путь должен содержать только английские буквы, и не должен содержать пробелы!), а также желательно нажать на галочку в import all esisting Eclipse project after clone finishes.
Жмем finish и видим, что появилась папка в git repositories заходим в эту папку, дальше Working tree.
Видим папку calculator, жмем 1 раз на нее, потом правой кнопкой. И жмем Import Project.
Появляется окно, в нем ничего выбирать не нужно, просто если Eclipse выбрал не ту папку, то стоит ее редактировать.
Жмем finish и уже проект появляется в C/C++. Теперь вы можете смотреть код (calculator/src/calculator.c)

*/
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
	printf("* или / вы можете умножить ( 1 * 3 ) или поделить ( 1 / 2 )\n ");	printf(
			"^ вы можете возвести в степень даже в отрицательную ( 2 ^ 3 ) , ( 5 ^ -2 )\n");
	printf("! вы можете найти факториал числа ( 5 ! )\n\n");
	do {
		scanf("%f %c", &a, &operation);
		if (operation != '!') {	                     // тут необходимое условие тк для факториала нужно только ввести число и операцию
			scanf("%f", &b);
			switch (operation) {                     //тут происходит выбор операции над числом или числами
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
			case ('^'):			                     // помимо простых действий над число ( + - * /),
				stepen = 1;	                         //где нужно ничего особенно пиcать для реализации
				if (b >= 0) {                        // в отличие от возведения в степень,где для реализации нужен цикл for
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
			default:				                 // если операция не определена то всё смэрть
				printf("Error\n");
			}
		} else {
			res = 1;
			if (a >= 0 && (a * 3 < (int)a)) {
				for (int i = 1; i <= a; i++) {       // факториал реализован через цикл for
					res *= i;
				}
				printf("%f %c = %f\n", a, operation, res);
			} else {								 // обработка ошибки
				printf("Error\n");
			}
		}
		printf("Continue (y/n)? \n");				 // y - yes , n - not
		scanf(" %c", &next);
	} while (next == 'y');							 // цикл для того чтобы пользователь продолжил считать либо закончил работу
	return 0;

}
