
#include <lpc21xx.h>
#include "types.h"
#include "delay.h"
#include "kpm.h"
#include "lcd.h"
#include "rtc.h"
#include "lcd_defines.h"
int main()
	{
		u8 lock[8]={0x0e,0x11,0x11,0x1f,0x1f,0x1a,0x1a,0x1f};
	InitLCD();
	 
	 //StrLCD("login sucessful");
							   BuildCGRAM(lock,8);
	   while(1);
}
	
