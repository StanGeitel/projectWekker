#include "calculator.h"

void calculatorInit(void) {
	srand(time(NULL));
}

void solveProblem(void) {
	int a = getRandom(3);
	switch (a) {
	case 0: sum();
			break;
	case 1: subtract();
			break;
	case 2: multiply();
			break;
	case 3: divide();
			break;
	}
}

void sum(void){
	int a = getRandom(99);
	int b = getRandom(99);
	int c = a + b;
	int d;
	do {
		printf("%d+%d=", a, b);		
		scanf("%d", &d);
		if (d != c) {
			//volumeUp();
		}
	} while (d != c);
}

void subtract(void) {
	int a = getRandom(99);
	int b = getRandom(99);
	int c = a - b;
	int d;
	do {
		printf("%d-%d=", a, b);
		scanf("%d", &d);
		if (d != c) {
			//volumeUp();
		}
	} while (d != c);
}
void multiply(void) {
	int a = getRandom(99);
	int b = getRandom(99);
	int c = a * b;
	int d;
	do {
		printf("%dx%d=", a, b);
		scanf("%d", &d);
		if (d != c) {
			//volumeUp();
		}
	} while (d != c);
}

void divide(void) {
	int a = getRandom(99);
	int b = getRandom(99);
	int c = a / b;
	int d;
	do {
		printf("%d/%d=", a, b);
		scanf("%d", &d);
		if (d != c) {
			//volumeUp();
		}
	} while (d != c);
}

int getRandom(int max) {
	int r = rand() % (max + 1);
	return r;
}