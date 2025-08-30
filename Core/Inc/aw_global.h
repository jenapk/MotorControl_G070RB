
//=================================================================================================
#ifndef _AW_GLOBAL_H_
#define _AW_GLOBAL_H_
//=================================================================================================
#include "aw_typedef.h"
extern uint8_t g_progPara, g_progStatus, g_progFlag;
extern uint8_t g_progMode;
extern uint8_t g_swAutoMode;
extern uint8_t g_swAutoModeInstant;
extern uint8_t g_swPhaseCap;
extern uint8_t g_loadOn;
extern uint8_t g_powerOnSec, g_powerOnMin, g_powerOnHour;	//to display 

extern uint8_t g_yphMiss;
extern uint8_t g_errCode;
extern uint8_t g_criticalAlarm;
extern uint8_t g_idleMode;	
extern uint8_t g_voltInRange;
extern uint8_t g_vError;
extern uint8_t	g_modeOfOperation;
extern uint8_t g_autoModeCountDownFlag;
extern uint8_t g_motorOffManually;
extern uint8_t g_dispInitCount;
extern uint8_t g_defScreen;
extern uint8_t g_motorStartBySW23;

extern uint32_t g_motorOnSec, g_loadOnSec;

extern uint16_t g_rsmVoltage[3];
extern uint16_t g_rsmCurrent[3];

extern uint8_t g_vOK[3], g_iOK[3];
extern uint16_t g_phVolt[3], g_phCurr[3];
extern uint8_t g_rlyStatus[5];
extern float g_factVoltage[3], g_factCurrent[3];

extern uint8_t fg_dispBuffer4[];

extern st_aw_devConfig	g_devConfig;

//some function prototypes
void aw_setIdleMode(void);
//=================================================================================================
#endif //_AW_GLOBAL_H_
//=================================================================================================

