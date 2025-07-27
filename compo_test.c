
#include <lpc21xx.h>
#include "types.h"
#include "delay.h"
#include "kpm.h"
#include "lcd.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "lcd_defines.h"
#define SW1_AL 0
#define SW2_AL 1
#define LED_AL
u32 count=0;
#define EINT0_VIC_CHNO 14
void FIQ_Interrupt(void) __irq;
int check_schedule_time(s32,s32);
void EditRTC(void);
void EScheduleTime(void); 
void RTCMenu(void);
s32 hour,min,sec,date,month,year,day;
u32 pass=1234;
//CGRAM ARRAY
u8 lock[8]={0x0e,0x11,0x11,0x1f,0x1f,0x1a,0x1a,0x1f};


int check_schedule_time(s32 sh,s32 eh)
{
	if(HOUR>=sh && HOUR<=eh)
	{
		return 1;
	}
	
	return 0;
	
}

int main()
{
	u32 password;
	s32 sh=8,eh=17;
	InitLCD();
	InitKPM();
	InitRTC();
	
	
	  // Set the initial time (hours, minutes, seconds)
      	SetRTCTime(9,38,30);
	      SetRTCDate(2,4,2025);
	     
	
	//INTERRUPT
	
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
						 if(check_schedule_time(sh,eh))
						 {
						    CmdLCD(CLEAR_LCD);
						    StrLCD("login sucessful");
							   //BuildCGRAM(lock,8);
							 
							   
							 
						    delay_ms(1000);
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
						 //U32LCD(password);
						 delay_ms(1000);
					 }
						 CmdLCD(CLEAR_LCD);	 
				 }		 	
	}
}

void FIQ_Interrupt(void) __irq
{
	u32 key;
	
	//some activity
	count=5;
	CmdLCD(CLEAR_LCD);
	StrLCD("1:E.RTC  3:EXIT");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("2:E.Schedul Time");
	
	 key=KeyScan();
	
	  switch(key)
		{
			case '1':EditRTC();
				      break;
			case '2'://EScheduleTime();
				      break;
			case '3':return ;
				      
		}
		
	delay_ms(200);
	
	EXTINT=1<<0;
	delay_ms(2000);
	
}

void EditRTC()
{
	CCR=RTC_DESABLE ;
   
   RTCMenu();	
	// Enable the RTC
	CCR =RTC_ENABLE;
}
void RTCMenu()
{
	u32 key;
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
			/*case '2':SetRTCMin();
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
				      break;*/
			case '8':return;
				     
			
				      
		}
	}
	delay_ms(100);
}

