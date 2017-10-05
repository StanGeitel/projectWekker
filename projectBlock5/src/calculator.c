
#include "calculator.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void calculator_Init(void) {
	srand(time(NULL));
}

void gen_Problem(void) {
	int a = get_Random(99);
	int b = get_Random(99);
	int operator = get_Random(3);
	int c;
	switch (operator) {
	case 0: {c = a + b; set_Problem(a, b, c, '+');}
			break;
	case 1: {c = a - b; subtract(a, b, c, '-');}
			break;
	case 2: {c = a * b; set_Problem(a, b, c, '*');}
			break;
	case 3: {c = a / b; divide(a, b, c, '/');}
			break;
	}
}

void subtract(int a, int b, int c, char operator){
	int d = a, e = b, f = c;
	while(d < e){
		d = get_Random(99);
		e = get_Random(99);
	}
	f = d - e;
	set_Problem(d, e, f, operator);
}

void divide(int a, int b, int c, char operator){
	int d = a, e = b;
	float f = c;
	while(!(ceilf(f)== f && floorf(f) == f)){
		d = get_Random(99);
		e = get_Random(99);
		f = d / e;
	}
	set_Problem(d, e, f, operator);
}

void set_Problem(int a, int b, int c,  char operator){
	Problem* pProblem = &problem;
	char arr[5];
		arr[0] = (char)((a / 10) + '0');
		arr[1] = (char)((a % 10) + '0');
		arr[2] = operator;
		arr[3] = (char)((b / 10) + '0');
		arr[4] = (char)((b % 10) + '0');
	strcpy(pProblem->arr, arr);
	pProblem->answer = c;
}

int get_Random(int max) {
	int r = rand() % (max + 1);
	return r;
}
