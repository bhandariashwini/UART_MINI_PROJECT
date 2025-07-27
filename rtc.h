
//rtc.h
#include "types.h"
void InitRTC(void);
void GetRTCTime(s32 *,s32 *,s32 *);
void DisplayRTCTime(u32,u32,u32);
void GetRTCDate(s32 *,s32 *,s32 *);
void DisplayRTCDate(u32,u32,u32);

void SetRTCTime(u32,u32,u32);
void SetRTCDate(u32,u32,u32);

void GetRTCDay(s32 *);
void DisplayRTCDay(u32);



void SetRTCHour(void);
void SetRTCMin(void);
void SetRTCSec(void);
void SetRTCMonth(void);
void SetRTCYear(void);
void SetRTCDay(void);
void SetRTCDa(void);
