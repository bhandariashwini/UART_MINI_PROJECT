
//kpm.c
#include<lpc21xx.h>
#include "kpm_defines.h"
#include "types.h"
#include "lcd.h"
#include "delay.h"
#include "kpm.h"
#include "lcd_defines.h"

u8 kpmLUT[4][4]={{'1','2','3',' '},
                  {'4','5','6','-'},
                  {'7','8','9','/'},
                  {'&','0','^','*'}};
u32  ColScan()
{
	return (((IOPIN1>>COL0)&15)<15) ? 0:1;
}
u32  RowCheck()
{
	u32 r;
	for(r=0;r<=3;r++)
	{
		IOPIN1=((IOPIN1&~(15<<ROW0)) | ((~(1<<r))<<ROW0));
		if(ColScan()==0)
		{
			break;
		}
	}
	
	IOCLR1=15<<ROW0;
	return r;
	
}

u32  ColCheck()
{
	u32 c;
	for(c=0;c<=3;c++)
	{
		if(((IOPIN1>>(COL0 + c))&1)==0)
		{
			break;
		}
	}	
  return c;	
}
u32  KeyScan(void)
{
	u32 r,c,keyV;
	while(ColScan());
	r=RowCheck();
	c=ColCheck();
	
	keyV=kpmLUT[r][c];
	return keyV;	
}
void InitKPM(void)
{
	IODIR1 |=15<<ROW0;
}

u32 KPM_Read_Num(void)
{
	u32 key,sum=0;
	s32 pos=0;
	while(1)
	{
		key=KeyScan();
		if(key==' ')
		{
			pos--;
			if(pos>=0)
			{
			  CmdLCD(GOTO_LINE2_POS0 + pos);
			  CharLCD(' ');
			  CmdLCD(GOTO_LINE2_POS0 + pos);
			  sum=sum/10;
			}
			else
			{
				pos=0;
			}
			while(ColScan()==0);
			
		}
		else if(key>=48 && key<=57)
		{
			
			
			 CmdLCD(GOTO_LINE2_POS0 + pos);
			 CharLCD(key);
			  CmdLCD(GOTO_LINE2_POS0 + pos);
			
			delay_ms(100);
			CmdLCD(GOTO_LINE2_POS0 + pos);
			 CharLCD('*');
			  CmdLCD(GOTO_LINE2_POS0 + pos);
			
			sum=sum*10 + (key-48);
			while(ColScan()==0);
			pos++;
		}
		else
		{
			break;
		}
	}
return sum;	
}

u32 KPM_Read_Data(void)
{
	u32 key,sum=0;
	s32 pos=0;
	while(1)
	{
		key=KeyScan();
		if(key==' ')
		{
			pos--;
			if(pos>=0)
			{
			  CmdLCD(GOTO_LINE2_POS0 + pos);
			  CharLCD(' ');
			  CmdLCD(GOTO_LINE2_POS0 + pos);
			  sum=sum/10;
			}
			else
			{
				pos=0;
			}
			while(ColScan()==0);
			
		}
		else if(key>=48 && key<=57)
		{
       CharLCD(key);
			sum=sum*10 + (key-48);
			while(ColScan()==0);
			pos++;
		}
		else
		{
			break;
		}
	}
return sum;	
}

