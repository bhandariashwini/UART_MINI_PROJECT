
//rtc.c
#include<lpc21xx.h>
#include "types.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "delay.h"
#include "kpm.h"


char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

// RTC Initialization: Configures and enables the RTC
void InitRTC(void) 
{
    // Disable & Reset the RTC 
	  
	    CCR =RTC_RESET;
    // Set prescaler integer part
	    PREINT =PREINT_VAL;
    // Set prescaler fractional part
	    PREFRAC=PREFRAC_VAL;

    // Enable the RTC
	   CCR =RTC_ENABLE;
}

// RTC_SetTime: Sets the time and date on the RTC
void SetRTCTime(u32 hour, u32 min, u32 sec) 
{

    // Set hours
	 HOUR=hour;
	  
    // Set minutes
	 MIN=min;
	
	// Set seconds
	 SEC =sec;

}


void GetRTCTime(s32 *hr,s32 *mi,s32 *se)
{
	*hr=HOUR;
	*mi=MIN;
	*se=SEC;
}
void DisplayRTCTime(u32 hour,u32 min,u32 sec)
{
	CmdLCD(GOTO_LINE1_POS0);
	CharLCD((hour/10)+48);
	CharLCD((hour%10)+48);
	CharLCD(':');
	CharLCD((min/10)+48);
	CharLCD((min%10)+48);
	CharLCD(':');
	CharLCD((sec/10)+48);
	CharLCD((sec%10)+48);
}

void GetRTCDate(s32 *day,s32 *month,s32 *year)
{
	*day=DOM;
	*month=MONTH;
	*year=YEAR;
	
}
void DisplayRTCDate(u32 d,u32 m,u32 y)
{
	CmdLCD(GOTO_LINE2_POS0);
	CharLCD((d/10)+48);
	CharLCD((d%10)+48);
	CharLCD(':');
	CharLCD((m/10)+48);
	CharLCD((m%10)+48);
	CharLCD(':');
	U32LCD(y);
}

void SetRTCDate(u32 d,u32 m,u32 y)
{
	DOM=d;
	MONTH=m;
	YEAR=y;
}

void GetRTCDay(s32 *day)
{
	*day = DOW;
}

void DisplayRTCDay(u32 day)
{
	CmdLCD(GOTO_LINE2_POS0+12);
	StrLCD(week[day]);
}

/*void SetRTCDay(u32 day)
{
	DOW=day;
}*/

void SetRTCHour(void)
{
	s32 key;
	CmdLCD(CLEAR_LCD);
	StrLCD("HOUR:");
	while(ColScan()==0);
	key=KPM_Read_Data();
		 

	if(key>=0 && key<=23)
	{
		StrLCD("valid");
		HOUR=key;
	}
	else
	{
		StrLCD("Invalid");
	}
	 delay_ms(100);
}
void SetRTCMin(void)
{
	s32 key;
	CmdLCD(CLEAR_LCD);
	StrLCD("MIN:");
	while(ColScan()==0);
	key=KPM_Read_Data();
		 

	if(key>=0 && key<=59)
	{
		StrLCD("valid");
		MIN=key;
	}
	else
	{
		StrLCD("Invalid");
	}
	 delay_ms(100);
}
void SetRTCSec(void)
{
	s32 key;
	CmdLCD(CLEAR_LCD);
	StrLCD("SEC:");
	while(ColScan()==0);
	key=KPM_Read_Data();
		 

	if(key>=0 && key<=59)
	{
		StrLCD("valid");
		SEC=key;
	}
	else
	{
		StrLCD("Invalid");
	}
	 delay_ms(100);
}
void SetRTCDay(void)
{
	s32 key;
	CmdLCD(CLEAR_LCD);
	StrLCD("Day:");
	while(ColScan()==0);
	key=KPM_Read_Data();
		 

	if(key>=0 && key<=6)
	{
		StrLCD("valid");
		DOW=key;
	}
	else
	{
		StrLCD("Invalid");
	}
	 delay_ms(100);
}
void SetRTCDa(void)
{
	s32 key;
	CmdLCD(CLEAR_LCD);
	StrLCD("DATE:");
	while(ColScan()==0);
	key=KPM_Read_Data();
		 

	if(key>=0 && key<=31)
	{
		StrLCD("valid");
		DOM=key;
	}
	else
	{
		StrLCD("Invalid");
	}
	 delay_ms(100);
}
void SetRTCMonth(void)
{
	s32 key;
	CmdLCD(CLEAR_LCD);
	StrLCD("MONTH:");
	while(ColScan()==0);
	key=KPM_Read_Data();
		 

	if(key>=0 && key<=11)
	{
		StrLCD("valid");
	MONTH=key;
	}
	else
	{
		StrLCD("Invalid");
	}
	 delay_ms(100);
}
void SetRTCYear(void)
{
	s32 key;
	CmdLCD(CLEAR_LCD);
	StrLCD("YEAR:");
	while(ColScan()==0);
	key=KPM_Read_Data();
		 
		YEAR=key;
	
	 delay_ms(100);
}
