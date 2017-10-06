
#include "alarm.h"
#include "GPIO.h"
#include "LPC1769.h"
#include "display.h"
#include "calculator.h"
#include "RealTimeClock.h"

Problem problem;
char alarm_Time[5] = {'0','0',':','0','0'};
char user_Answer[5] = {' ',' ',' ',' ','0'};
char settings = 0;		//b0 = alarm instellen 	b1 en b2 = positie alarm instellen
						//b3 = alarm aan	b4 en b5 = volume
						//b6 en b7 = positie gebruikers antwoord

void alarm_Init(void){
	calculator_Init();
	GPIO_SetDIR(2, (0x07 << 2));
	GPIO_Set(2, (0x07 << 2));
}

void alarm_On(void){
	settings |= (0x1 << 3);
	gen_Problem();
	display_Set(problem.arr);
	display_Write();
	up_Volume();
}

void check_User_Answer(void){
	if(user_Answer == problem.answer){ //check if array's are the same
		alarm_Off();
		display_Set(RTC_getTime());
		display_Write();
		for(int i = 0; i < 5; i++){
			user_Answer[i] = ' ';
		}
		settings = 0;
	}
	else{
		display_Set("xxxxx");
		display_Write();
		for(int i =0; i < 5000; i++){
			asm("nop");
		}
		display_Set(problem.arr);
		display_Write();
		for(int i = 0; i < 5; i++){
			user_Answer[i] = ' ';
		}
		settings &= 0x3F;
	}
}

void alarm_Off(void){
	settings &= ~(0x1 << 3);
	GPIO_Set(2, (0x07 << 2));
}

void down_Volume(void){
	int vol = ((settings >> 4) & 0x3);
	if(vol > 0){
		settings = (settings & 0xCF) | ((vol - 1) << 4);
	}
	GPIO_Set(2, (0x07 << 2));
	GPIO_Clear(2, (0x1 << (((settings >> 4) & 0x3) + 2)));
}

void up_Volume(void){
	int vol = ((settings >> 4) & 0x3);
	if(vol < 2){
		settings = (settings & 0xCF) | ((vol + 1) << 4);
	}
	GPIO_Set(2, (0x07 << 2));
	GPIO_Clear(2, (0x1 << (((settings >> 4) & 0x3) + 2)));
}

void set_Alarm_Time(char number){
	display_Set(alarm_Time);
	display_Write();
	int pos = ((settings >> 1) & 0x3);
	if(pos > 1){
		pos++;
	}
	alarm_Time[pos] = number;
}

char* get_Alarm_Time(void){
	return alarm_Time;
}

void setButton(char button){
	if(settings & (0x1 << 3)){
		if((button < 8)){
			set_User_Answer(button);
		}
		if(button == buttonEnter){
			check_User_Answer();
		}
	}
	if((button < 8) && (settings & 0x1)){
		char number = (button + 48);
		set_Alarm_Time(number);
	}
	if(settings & 0x1){
		switch(button){
		case statusAlarm: {
			settings &= ~0x1;
			settings &= 0xC5;
			display_Set(get_Alarm_Time());
			display_Write();
		}
			break;
		case buttonVolumeUp:	up_Volume();
			break;
		case buttonVolumeDown:	down_Volume();
			break;
		case buttonLeft:		move_Left();
			break;
		case buttonRight:		move_Right();
			break;
		}
	}
	else{
		switch(button){
		case statusAlarm:
			settings |= 0x1;
			display_Set(get_Alarm_Time());
			display_Write();
			break;
		case buttonVolumeUp:
			up_Volume();
			break;
		case buttonVolumeDown:
			down_Volume();
			break;
		}
	}
}

void move_Left(void){
	int pos = ((settings >> 1) & 0x3);
	if(pos > 0){
		settings = (settings & 0xC5) | ((pos - 1) << 1);
	}
}

void move_Right(void){
	int pos = ((settings >> 1) & 0x3);
	if(pos < 3){
		settings = (settings & 0xC5) | ((pos + 1) << 1);
	}
}

void set_User_Answer(char button){
	int pos = ((settings >> 6) & 0x3);
	user_Answer[pos] = (button + 48);
	if(pos < 4){
		settings = (settings & 0x3F) | ((pos + 1) << 6);
	}
	else{
		check_User_Answer();
	}
}

