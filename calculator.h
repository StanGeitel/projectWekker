/*
 * calculator.h
 *
 *  Created on: 26 Sep 2017
 *      Author: stan
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct _Problem{ char arr[5]; int answer; }Problem;
extern Problem problem;

void calculatorInit(void);
void setProblem(Problem* pProblem);
int getRandom(int max);

#endif /* CALCULATOR_H_ */
