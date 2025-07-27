
//lcd.c
#include<lpc21xx.h>
#include "delay.h"
#include "types.h"
#include "lcd.h"
#include "lcd_defines.h"

void WriteLCD(u8 Dat)
{
	//write on data pins
	IOPIN0=((IOPIN0&~(0XFF<<LCD_DATA)) | (Dat<<LCD_DATA));
	 
	//activate write operation
	IOCLR0=1<<LCD_RW;
	
	//latch into cmd/data register
	IOSET0=1<<LCD_EN;
	delay_us(1);
	IOCLR0=1<<LCD_EN;
	
	//internal operation upper bond time
	delay_ms(2);	
}
void CmdLCD(u8 cmd)
{ //select cmd register
	IOCLR0=1<<LCD_RS;
	
	//write to cmd reg
	 WriteLCD(cmd);
}
void CharLCD(u8 ascii)
{
	//select data register
	 IOSET0=1<<LCD_RS;
	
	//writer to DDRAM/Display via data reg.
	WriteLCD(ascii);
}
void InitLCD(void)
{
	//cfg data  & control pin as gpio out.
	
	IODIR0 |=0XFF<<LCD_DATA | 1<<LCD_RS | 1<<LCD_RW | 1<<LCD_EN;
	delay_ms(15);
	CmdLCD(0x30);
	delay_ms(2);
	delay_us(100);
	CmdLCD(0x30);
	delay_us(100);
	CmdLCD(0X30);
	CmdLCD(MODE_8BIT_2LINE);
	CmdLCD(DSP_ON_CUR_OFF);
	CmdLCD(CLEAR_LCD);
	CmdLCD(SHIFT_CUR_RIGHT);
}
void StrLCD(s8 *str)
{
	while(*str)
		CharLCD(*str++);
}
void U32LCD(u32 num)
{
	s8 a[10];
	s32 i=0;
	if(num==0)
	{
		CharLCD('0');
	}
	else
	{
		while(num>0)
		{
			a[i]=(num%10) + 48;
			i++;
			num/=10;
		}
		for(--i;i>=0;i--)
		{
			CharLCD(a[i]);
		}
	}
}
void S32LCD(s32 num)
{
	if(num<0)
	{
		CharLCD('-');
		num=-num;
	}
	U32LCD(num);
}
void F32LCD(f32 fnum, u32 Dp)
{
	u32 temp,i;
	if(fnum<0)
	{
		CharLCD('-');
		fnum=-fnum;
	}
	temp=fnum;
	U32LCD(temp);
	CharLCD('.');
	for(i=0;i<Dp;i++)
	{
		fnum=(fnum-temp)*10;
		temp=fnum;
		CharLCD(temp+48);
	}
	
	
}
void HEXLCD(u32 num)
{
	s8 a[8];
	s32 i=0;
	if(num==0)
	{
		CharLCD('0');
	}
	else
	{
		 while(num)
		 {
			if((num%16)<10)
			{
				a[i]=num%16 + 48;
				i++;
			}
			else
			{
				a[i]=(num%16) -10+ 'A';
				i++;
			}
			num/=16;
		 }
		 for(--i;i>=0;i--)
		 {
			 CharLCD(a[i]);
		 }	
	}
	
}
void OCTLCD(u32 num)
{ s8 a[11];s32 i=0;
	if(num==0)
	{
		CharLCD('0');
	}
	else
	{
		
		while(num)
		{
				a[i]=(num%8) + 48;
			  i++;
			num/=8;
					
		}
   for(--i;i>=0;i--)
   {
		 CharLCD(a[i]);
   }	
	}	
}
void BinLCD(u32 num,u32 nBD)
{ 
	s32 i;
	for(i=nBD-1;i>=0;i--)
	{
		CharLCD(((num>>i)&1) +48);
	}
}
void BuildCGRAM(u8 *str,u8 nBytes)
{  
	u32 i=0; 
	//position cursor to CGRAM
	CmdLCD(GOTO_CGRAM_START);
	//write in to CGRAM via data reg
	for(i=0;i<nBytes;i++)
	{
		CharLCD(str[i]);
	}
	CmdLCD(GOTO_LINE2_POS0);
}
