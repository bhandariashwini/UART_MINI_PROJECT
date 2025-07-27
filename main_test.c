
#include <lpc21xx.h>
#include "types.h"
#include "delay.h"
#include "kpm.h"
#include "lcd.h"
#include "rtc.h"
#include "main.h"
#include "rtc_defines.h"
#include "lcd_defines.h"
#include "main_defines.h"
s32 hour,min,sec,date,month,year,day;
u32 pass=1234;

int main()
{
	u32 password;
  IODIR0 |=1<<LED_AL;
	InitLCD();
	InitKPM();
	InitRTC();
	CfgInterrupt();
	
	 
	
	while(1)
	{
		    GetRTCTime(&hour,&min,&sec);
		    DisplayRTCTime(hour,min,sec);
			  GetRTCDate(&date,&month,&year);
			  DisplayRTCDate(date,month,year);
			
			  GetRTCDay(&day);
        DisplayRTCDay(day);
		  
		     if(((IOPIN0>>SW1_AL)&1)==0)
				 {
					  while(((IOPIN0>>SW1_AL)&1)==0);
					  CmdLCD(CLEAR_LCD);
					 StrLCD("Enter Password:");	 
					 CmdLCD(GOTO_LINE2_POS0);
			     
					 password=KPM_Read_Num();
					 if(password==pass)
					 {  
						 if(check_schedule_time())
						 {
						    CmdLCD(CLEAR_LCD);
						    StrLCD("login sucessful");
							   IOSET0=1<<LED_AL;
							   //BuildCGRAM(lock,8);
							 
							   
							 
						    delay_ms(1000);
							  IOCLR0=1<<LED_AL;
						 }
						 else
						 {
							  CmdLCD(CLEAR_LCD);
						    StrLCD("TIME OVER");
						    delay_ms(100);
						 }
					 }
					 else
					 {
						  CmdLCD(CLEAR_LCD);
						 StrLCD("failed");
						 delay_ms(1000);
					 }
						 CmdLCD(CLEAR_LCD);	 
				 }		 	
	}
}

