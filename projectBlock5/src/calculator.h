
#ifndef CALCULATOR_H_
#define CALCULATOR_H_

typedef struct _Problem{ char arr[5]; char answer[5]; }Problem;


void calculator_Init(void);
void gen_Problem(void);
void subtract(int a, int b);
void divide(void);
void set_Problem(int a, int b, int c, char operator);
int get_Random(int max);

int get_Random(int max);
char* getProblemAwnser();
char* getProblemArr();

#endif
