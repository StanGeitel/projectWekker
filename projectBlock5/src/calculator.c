
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
	case 2: {c = a * b; set_Problem(a, b, c, 'x');}
			break;
	case 3: {divide(a, b, '/');}
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

void divide(int a, int b, char operator){
	int d = a, e = b;
	float f = (float)d / (float)e;
	while(!(ceilf(f)== f && floorf(f) == f)){
		d = get_Random(99);
		e = get_Random(99);
		f = (float)d / (float)e;
	}
	set_Problem(d, e, f, operator);
}

void set_Problem(int a, int b, int c,  char operator){
	char arr[5] = {' ',' ',' ',' ',' '};
		if(a / 10){
			arr[0] = (char)((a / 10) + '0');
		}
		if(a % 10){
			arr[1] = (char)((a % 10) + '0');
		}
		else if(a / 10) arr[1] = '0';
		arr[2] = operator;
		if(b / 10){
			arr[3] = (char)((b / 10) + '0');
		}
		if(b % 10){
			arr[4] = (char)((b % 10) + '0');
		}
		else if(b / 10) arr[4] = '0';
	strcpy(problem.arr, arr);
	char answer[5] = {' ',' ',' ',' ','0'};
		answer[0] = ' ';
		if(c / 1000){
			answer[1] = (char)((c / 1000) + '0');
		}
		if((c % 1000)/ 100){
			answer[2] = (char)(((c % 1000)/ 100) + '0');
		}
		else if(c / 1000) answer[2] = '0';
		if(((c % 1000)% 100)/ 10){
			answer[3] = (char)((((c % 1000)% 100)/ 10) + '0');
		}
		else if(c / 100) answer[1] = '0';
		if(((c % 1000)% 100)% 10){
			answer[4] = (char)((((c % 1000)% 100)% 10) + '0');
		}
		else if(c / 10) answer[1] = '0';
	strcpy(problem.answer, answer);
}

int get_Random(int max) {
	int r = rand() % (max + 1);
	return r;
}
