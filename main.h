
//main.h
#include "types.h"
void CfgInterrupt(void);
void FIQ_Interrupt(void) __irq;
int check_schedule_time(void);
void EditRTC(void);
void EScheduleTime(s32 *,s32 *); 
void RTCMenu(void);
