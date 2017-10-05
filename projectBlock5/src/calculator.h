
#ifndef CALCULATOR_H_
#define CALCULATOR_H_

typedef struct _Problem{ char arr[5]; char answer[5]; }Problem;
extern Problem problem;

void calculator_Init(void);
void gen_Problem(void);
void subtract(int a, int b, int c, char operator);
void divide(int a, int b, int c, char operator);
void set_Problem(int a, int b, int c, char operator);
int get_Random(int max);

#endif
