
#include "calculator.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

char problemArr[5] = {' ', ' ', ' ', ' ', ' '};
char problemAwnser[6] = {' ', ' ', ' ', ' ', ' ', '\0'};

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
	problemArr[0] = (char)(a/10) + '0';
	problemArr[1] = (char)(a%10) + '0';
	problemArr[2] = operator;
	problemArr[3] = (char)(b/10) + '0';
	problemArr[4] = (char)(b%10) + '0';
	problemArr[5] = '\0';

	int positionArr = 0;

	if(c / 1000){ //1000
		problemAwnser[positionArr] = (char)((c / 1000) + '0');
		positionArr++;
	}
	if(((c % 1000)/ 100)){ //100
		problemAwnser[positionArr] = (char)(((c % 1000)/ 100) + '0');
		positionArr++;
	}
	if(((c % 1000)% 100)/ 10){ //10
		problemAwnser[positionArr] = (char)((((c % 1000)% 100)/ 10) + '0');
		positionArr++;
	}
	if(((c % 1000)% 100)% 10){ //1
		problemAwnser[positionArr] = (char)((((c % 1000)% 100)% 10) + '0');
		positionArr++;
	}
	for(positionArr ; positionArr < 5 ; positionArr++){
		problemAwnser[positionArr] = ' ';
	}
	problemAwnser[5] = '\0';

}

int get_Random(int max) {
	int r = rand() % (max + 1);
	return r;
}

char* getProblemArr(){
	return problemArr;
}

char* getProblemAwnser(){
	return problemAwnser;
}
