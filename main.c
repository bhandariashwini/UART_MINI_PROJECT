
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
//default scheduled time
	 s32 sh=8,eh=18;
void CfgInterrupt()
{
   //Cfg p0.1 as eint0 via pcb
	PINSEL0=((PINSEL0&~(3<<2)) | (3<<2));
	//Cfg VIC block
	//select eint0 as fiq
	 VICIntSelect=1<<EINT0_VIC_CHNO;
	//VICIntSelect=0;
	//enable eint0
  VICIntEnable=(1<<EINT0_VIC_CHNO);	
	//Cfg EXT block
	//enable eint0
	//EXTINT=0;
	//selet mode
	EXTMODE=(1<<0);
	//select falling edge
	//EXTPOLAR=0;
}

int check_schedule_time()
{
	if(HOUR>=sh && HOUR<=eh)
	{
		return 1;
	}
	
	return 0;
	
}

void FIQ_Interrupt(void) __irq
{
	u32 key,flag=0;
	
	//some activity
	
	CmdLCD(CLEAR_LCD);
	StrLCD("1:E.RTC  3:EXIT");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("2:E.Schedul Time");
	
	 key=KeyScan();
	
	  switch(key)
		{
			case '1':EditRTC();
				      break;
			case '2':EScheduleTime(&sh,&eh);
				      break;
			case '3':flag=1;
			         break;
			
				      
		}
		if(flag==1)
		{
			CmdLCD(CLEAR_LCD);
				 EXTINT=1<<0;
				 return ;
		}
		
//	delay_ms(200);
	
	
	//delay_ms(2000);
	
}


void EditRTC()
{
	u32 key,flag=0;
	while(1)
	{
	CmdLCD(CLEAR_LCD);
	StrLCD("1.H 2.M 3.S 4.Da");
	CmdLCD(GOTO_LINE2_POS0);
  StrLCD("5.d 6.M 7.Y 8.E");
	 delay_ms(100);
	
	    key=KeyScan();
	
	 switch(key)
		{
			case '1':SetRTCHour();
				      break;
		  case '2':SetRTCMin();
				      break;
			case '3':SetRTCSec();
			         break;
			case '4':SetRTCDay();
				      break;
			case '5':SetRTCDa();
				      break;
			case '6':SetRTCMonth();
			          break;
			case '7':SetRTCYear();
				      break;
			case '8':flag=1;
			        break;
			
				      
		}
		if(flag)
		{
			CmdLCD(CLEAR_LCD);
			break;
		}
	}
	//delay_ms(100);
}

void EScheduleTime(s32 *SH,s32 *EH)
{
	s32 key1,key2;
	CmdLCD(CLEAR_LCD);
	StrLCD("Start Time:");
	while(ColScan()==0);
	key1=KPM_Read_Data();
 
	if(key1>=0 && key1<=23)
	{
	   *SH=key1;
	}
	else
	{
		StrLCD("Invalid");
	}
	 delay_ms(100);
	CmdLCD(CLEAR_LCD);
	StrLCD("End Time:");
  while(ColScan()==0);
	key2=KPM_Read_Data();
	delay_ms(100);
	if((key2>*SH)&&(key2>=0 && key2<=23))
	{
	   *EH=key2;
	}
	else
	{
		StrLCD("Invalid");
	}
	delay_ms(100);
	
}	
