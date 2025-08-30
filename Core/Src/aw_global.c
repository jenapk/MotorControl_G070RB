
#include "aw_typedef.h"

uint8_t g_progMode;				//programming mode
uint8_t g_swAutoMode;			//switch is in Auto/Manual mode. 0-Manual, 1-Auto, //change on the fly
uint8_t g_swAutoModeInstant;	//sensing instant value for display. same will be assigned and applicable when condition meets
uint8_t g_swPhaseCap;			//phase switch for capacitor bank

uint8_t g_progPara, g_progStatus, g_progFlag;	//programing parameter and valiadation status, by key pad
uint8_t g_loadOn;				//load is ON 
uint8_t g_powerOnSec, g_powerOnMin, g_powerOnHour;	//to display device power on duration
uint8_t g_yphMiss;				//1: when YPH missed, 0_YpH present
uint8_t g_errCode;				//error codes
uint8_t g_criticalAlarm;		//critical alarm
uint8_t g_idleMode;				//idle mode
uint8_t g_voltInRange;			// voltage in range or not
uint8_t g_vError;				//only voltage error code
uint8_t	g_modeOfOperation;		//current mode of operation
uint8_t g_motorOffManually;		//mot off manually - by red button
uint8_t g_autoModeCountDownFlag;	//to display auto mode count down before auto mode starting
uint8_t g_defScreen;				//set default screen [switch can start motor in manual mode]
uint8_t g_motorStartBySW23;			//to sense, 2nd button pressing to start motor manually

uint16_t g_rsmVoltage[3];		//calculated value from ADC
uint16_t g_rsmCurrent[3];		//calculated value from ADC

uint32_t g_motorOnSec, g_loadOnSec;	// to stop Motor after configured on time
uint8_t g_dispInitCount;		//number of display init after any relay switched on
uint8_t g_vOK[3], g_iOK[3];
uint16_t g_phVolt[3], g_phCurr[3];
uint8_t g_rlyStatus[5];				//relay status
float g_factVoltage[3], g_factCurrent[3];

st_aw_devConfig	g_devConfig;		//device configuration
