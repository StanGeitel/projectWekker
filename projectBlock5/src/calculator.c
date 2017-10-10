
#include "calculator.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

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
	case 1: subtract(a, b);
			break;
	case 2: {c = a * b; set_Problem(a, b, c, '*');}
			break;
	case 3: divide();
			break;
	}
}

void subtract(int a, int b){
	while(a < b){
		a = get_Random(99);
		b = get_Random(99);
	}
	int c = a - b;
	set_Problem(a, b, c, '-');
}

void divide(void){
	int b = 1 + get_Random(8);
	int c = get_Random(9);
	int a = b * c;
	set_Problem(a, b, c, '/');
}

void set_Problem(int a, int b, int c,  char operator){
	char arr[5] = {' ','0',' ',' ','0'};
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
		else if(c / 100) answer[3] = '0';
		if(((c % 1000)% 100)% 10){
			answer[4] = (char)((((c % 1000)% 100)% 10) + '0');
		}
	strcpy(problem.answer, answer);
}

int get_Random(int max) {
	int r = rand() % (max + 1);
	return r;
}
