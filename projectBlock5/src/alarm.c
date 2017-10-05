
#include "alarm.h"
#include "GPIO.h"

Problem problem;
char alarm_Time[5] = {'0','0',':','0','0'};
char vol = 0;
int user_Answer;

void alarm_Init(void){
	calculator_Init();
	GPIO_Set(2, (0x07 << 2));
}

void alarm_On(void){
	Problem* pProblem = &problem;
	gen_Problem();
	display_Set(pProblem->arr);
	up_Volume();
	if(user_Answer == pProblem->answer){
		alarm_Off();
	}
}

void alarm_Off(void){
	GPIO_Set(2, (0x07 << 2));
}

void up_Volume(void){
	(vol  == 2) ? (vol == 2) : (++vol);
	GPIO_Set(2, (0x07 << 2));
	GPIO_Clear(2, (0x1 << (vol + 2)));
}

void down_Volume(void){
	(vol  == 0) ? (vol == 0) : (--vol);
	GPIO_Set(2, (0x07 << 2));
	GPIO_Clear(2, (0x1 << (vol + 2)));
}

void set_Alarm_Time(void){
	display_Set(alarm_Time);
	display_Write();


}

char* get_Alarm_Time(void){
	return alarm_Time;
}




