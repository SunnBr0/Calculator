/*
 ============================================================================
 Name        : h.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	int a,b;
	char key ;
	scanf("%i\n",&a);
	scanf("%i\n",&b);
	scanf("%c\n",&key);
	switch (key) {
		case '+':
			printf("%i plus %i",a,b);
			break;
		case '-':
			printf("%i minus %i",a,b);
			break;
		case '*':
			printf("%i multiply by %i",a,b);
			break;
		case '/':
			printf("%i divide by %i",a,b);
			break;
		default:
			printf("nop");
			break;
	}
}

