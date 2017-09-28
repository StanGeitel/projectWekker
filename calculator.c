/*
 * calculator.c
 *
 *  Created on: 26 Sep 2017
 *      Author: stan
 */


#include "calculator.h"

void calculatorInit(void) {
	srand(time(NULL));
}

void setProblem(Problem* pProblem) {
	int a = getRandom(99);
	int b = getRandom(99);
	int c = getRandom(3);
	int d;
	char operator;
	switch (c) {
	case 0: {d = a + b; operator = '+';}
			break;
	case 1: {d = a - b; operator = '-';}
			break;
	case 2: {d = a * b; operator = 'x';}
			break;
	case 3: {d = a / b; operator = '%';}
			break;
	}
	char arr[5];
		arr[0] = (char)(b % 10);
		arr[1] = (char)(b / 10);
		arr[2] = operator;
		arr[3] = (char)(a % 10);
		arr[4] = (char)(a / 10);

	strcpy(pProblem->arr, arr);
	pProblem->answer = d;
}

int getRandom(int max) {
	int r = rand() % (max + 1);
	return r;
}
