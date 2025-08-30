#include <string.h>
#include "r_cg_wdt.h"
#include "inst_read.h"
#include "em_measurement.h"
#include "aw_lcd_gdm.h"
#include "aw_display.h"
#include "aw_config_app.h"
#include "aw_config_io.h"
#include "aw_miscFunc.h"
#include "aw_global.h"
#include "aw_programming.h"

#define SQRT_OF_3		1.73205f

uint8_t g_dispReInitFlag;
uint8_t fg_dispLastNotifCode;				//Last notification code, to display after LCD refreshment
uint8_t fg_dispErrRecoveryFlag;				//error like dryrun is a recovery state, msg need to persistant
uint8_t fg_dispNotifyCounter;
uint8_t fg_dispSecDelay;
uint8_t fg_dispTick;
uint8_t fg_dispAlarmLocked;					//display alarm locked due to critical alarm
uint8_t fg_phaseSequence, fg_phSeqCheckCount;
uint8_t fg_virtSource;						//set source (real or virtual)
uint8_t fg_progDispCounter;					//to display programming status for a while (3 seconds)
aw_en_notification fg_notifyCode;			//alert, error and notification code 

extern uint8_t fg_prgMode;
extern uint16_t fg_3phWaitCounter;

uint8_t fg_dispBuffer1[LCD_BUFFER_LEN];
uint8_t fg_dispBuffer2[LCD_BUFFER_LEN];
uint8_t fg_dispBuffer3[LCD_BUFFER_LEN];
uint8_t fg_dispBuffer4[LCD_BUFFER_LEN];

uint8_t aw_getPhSeq(void);
//=================================================================================================
void aw_dispProcess(void)
{	uint8_t l_temp = 0;
	
	//clear display buffer
	memset(fg_dispBuffer1, ' ', LCD_BUFFER_LEN);
	memset(fg_dispBuffer2, ' ', LCD_BUFFER_LEN);
	memset(fg_dispBuffer3, ' ', LCD_BUFFER_LEN);
	
	l_temp = aw_prgKeyScan();		//scan the keys
	
	if(fg_prgMode)					//configuration mode
	{
		g_defScreen = 0x00;			//
		g_progFlag = 0x01;			//flag says device entered to programming mode, so that it can display status
		fg_progDispCounter = 30;		//to displat status for 3 seconds @100ms
		aw_prgProcess();			//programming process
	}
	else if ((!l_temp) && (!g_progFlag))
	{
		if(++fg_dispTick < 10) return;
		fg_dispTick = 0x00;
		
		if(g_dispReInitFlag)
		{
			g_dispReInitFlag = 0;
			fg_dispAlarmLocked = 0x00;
			aw_lcdReInit();
			g_defScreen = 0x01;
			return;
		}
		
		if(!g_progFlag)		//in normal case
		{
			aw_dispVI();		//regular display process
			g_defScreen = 0x01;
			
			//refresh the LCD
			aw_lcdDisplay(LCD_LINE_1, fg_dispBuffer1);
			aw_lcdDisplay(LCD_LINE_2, fg_dispBuffer2);
			aw_lcdDisplay(LCD_LINE_3, fg_dispBuffer3);
			
			aw_dispGetNotifications();				//check for notifications
			aw_dispNotifyMessage(fg_notifyCode);	//display notification
		}
	}
	else if(g_progFlag)								//after programming to display programming status
	{
		aw_dispProgStatus();
		
		if(fg_progDispCounter)						//condition to exit from prog status display
		{
			fg_progDispCounter--;
			if(!fg_progDispCounter)
			{
				g_progFlag = 0x00;
				g_progStatus = 0x00;
				g_progPara = 0x00;
			}
		}
	}
}

/* shows the programming status after programming */
void aw_dispProgStatus(void)
{
	memset(fg_dispBuffer1, ' ', LCD_BUFFER_LEN);
	memset(fg_dispBuffer2, ' ', LCD_BUFFER_LEN);
	memset(fg_dispBuffer3, ' ', LCD_BUFFER_LEN);
	memset(fg_dispBuffer4, ' ', LCD_BUFFER_LEN);

	memcpy(fg_dispBuffer2,     " Programming Status ", LCD_BUFFER_LEN);
	
	if(g_progStatus == 0x00)
	{
		memcpy(fg_dispBuffer3, "         OK         ", LCD_BUFFER_LEN);
	}
	else if(g_progStatus == 0x01)
	{
		memcpy(fg_dispBuffer3,     "       Failed       ", LCD_BUFFER_LEN);
	}
	
	aw_lcdDisplay(LCD_LINE_1, fg_dispBuffer1);
	aw_lcdDisplay(LCD_LINE_2, fg_dispBuffer2);
	aw_lcdDisplay(LCD_LINE_3, fg_dispBuffer3);
	aw_lcdDisplay(LCD_LINE_4, fg_dispBuffer4);
}

/* set variables so that after exit from prog mode */
void aw_dispExitFromProgMode(void)
{
	fg_dispTick = 10;
	g_dispInitCount = 0;
	g_dispReInitFlag = 0x00;
}

void aw_dispVI(void)
{
	uint8_t i = 0;
	uint16_t fg_num = 0, fg_dec = 0;
	uint16_t l_remVal = 0;
	
	g_defScreen = 0x01;		//set default screen [switch can start motor in manual mode]
	
	memcpy(fg_dispBuffer1, "  000   000   000  V", LCD_BUFFER_LEN);
	memcpy(fg_dispBuffer2, " R:00  Y:00  B:00  A", LCD_BUFFER_LEN);  
	memcpy(fg_dispBuffer3, "OL:00 DR:00 00:00  T", LCD_BUFFER_LEN);  
	
	if(!fg_virtSource)		//normal supply
	{
		//Get voltage and current
		for(i = 0; i < 3; i++)
		{
			g_phVolt[i] = g_inst_read_params.vrms[i];	
			g_phVolt[i] *= g_factVoltage[i];
			
			g_phCurr[i] = g_inst_read_params.irms[i];
			if(g_phCurr[i] < 100) g_phCurr[i] = 0x00;	//discard for 1000mA
			g_phCurr[i] *= g_factCurrent[i];
		}
	}
	else //from virtual source
	{
		//set from serial port
	}
	
	//voltage R PH
	fg_num = (uint16_t) (g_phVolt[0] / 100);
	aw_miscConvertToDecAsc(&fg_dispBuffer1[2], fg_num, 3);
	
	//voltage Y PH
	fg_num = (uint16_t) (g_phVolt[1] / 100);
	aw_miscConvertToDecAsc(&fg_dispBuffer1[8], fg_num, 3);
	
	//voltage B PH
	fg_num = (uint16_t) (g_phVolt[2] / 100);
	aw_miscConvertToDecAsc(&fg_dispBuffer1[14], fg_num, 3);
	
	//Current
	//R PH
	fg_num = (uint16_t) (g_phCurr[0] / 100);
	l_remVal = (g_phCurr[0] % 100);				//check fractional part of current to rounding up to next Amp
	if(l_remVal >= 50) fg_num++;
	aw_miscConvertToDecAsc(&fg_dispBuffer2[3], fg_num, 2);
	
	//Y PH
	fg_num = (uint16_t) (g_phCurr[1] / 100);
	l_remVal = (g_phCurr[1] % 100);
	if(l_remVal >= 50) fg_num++;
	aw_miscConvertToDecAsc(&fg_dispBuffer2[9], fg_num, 2);
	
	//B PH
	fg_num = (uint16_t) (g_phCurr[2] / 100);
	l_remVal = (g_phCurr[2] % 100);
	if(l_remVal >= 50) fg_num++;
	aw_miscConvertToDecAsc(&fg_dispBuffer2[15], fg_num, 2);
	
	//Power On Duration
	aw_miscConvertToDecAsc(&fg_dispBuffer3[3], g_devConfig.OverloadCurrent, 2);
	aw_miscConvertToDecAsc(&fg_dispBuffer3[9], g_devConfig.DryRunCurrent, 2);
	aw_miscConvertToDecAsc(&fg_dispBuffer3[12], g_devConfig.MotorOn.Hour, 2);
	aw_miscConvertToDecAsc(&fg_dispBuffer3[15], g_devConfig.MotorOn.Minute, 2);
}

//display power on message
void aw_dispPORMessage(void)
{
	memset(fg_dispBuffer1, ' ', LCD_BUFFER_LEN);
	memset(fg_dispBuffer2, ' ', LCD_BUFFER_LEN);
	memset(fg_dispBuffer3, ' ', LCD_BUFFER_LEN);
	memset(fg_dispBuffer4, ' ', LCD_BUFFER_LEN);
	
	memcpy(fg_dispBuffer2, "       KALPA        ", LCD_BUFFER_LEN); 
	memcpy(fg_dispBuffer3, "   Motor Starters   ", LCD_BUFFER_LEN); 
	
#if(AW_TEST_BINARY) 
	memcpy(fg_dispBuffer4, "Testing:            ", LCD_BUFFER_LEN); 
	aw_miscConvertToDecAsc(&fg_dispBuffer4[9], AW_TEST_COUNTER, 3);
#endif //AW_TEST_BINARY
	
	memcpy(&fg_dispBuffer4[16 - strlen(MAX_APP_CURRENT_STR)], MAX_APP_CURRENT_STR, strlen(MAX_APP_CURRENT_STR));

	fg_dispBuffer4[16] = 'v';
	fg_dispBuffer4[17] = AW_FW_VER_MAJOR + 0x30;
	fg_dispBuffer4[18] = '.';
	fg_dispBuffer4[19] = AW_FW_VER_MINOR + 0x30;
	
	aw_lcdDisplay(LCD_LINE_1, fg_dispBuffer1);
	aw_lcdDisplay(LCD_LINE_2, fg_dispBuffer2);
	aw_lcdDisplay(LCD_LINE_3, fg_dispBuffer3);
	aw_lcdDisplay(LCD_LINE_4, fg_dispBuffer4);
	
	fg_dispSecDelay = POR_SCREEN_DELAY;
	
	while(fg_dispSecDelay)
	{
		R_WDT_Restart(); 	
	}
}

//check for notifications
void aw_dispGetNotifications(void)
{	
	//if(fg_phaseSequence)
	//{	
	//	fg_notifyCode = ERR_PHASE_SEQUENCE;		//phase sequence error
	//}
	//else 
	if(g_errCode)
	{
		 fg_notifyCode = g_errCode;		
	}
	else if(g_autoModeCountDownFlag)		//auto mode starting mode count down
	{
		fg_notifyCode = SPL_DISP_AUTO_MODE_COUNT_DOWN;
	}
	else if(fg_dispErrRecoveryFlag)					//need to display during the time
	{
		fg_notifyCode = fg_dispLastNotifCode;
	}	
	else
	{
		fg_notifyCode = ERR_NO_ERROR;
	}
}

void aw_dispSetRecoveryCode(uint8_t a_errCode)
{
	fg_dispErrRecoveryFlag = 0x01;	//need to display during the time
	fg_dispLastNotifCode = a_errCode;		//to retain display line			
}

void aw_dispResetRecoveryCode(void)
{
	fg_dispErrRecoveryFlag = 0x00;	//need to display during the time
	fg_dispLastNotifCode = 0x00;		//to retain display line			
}

//displays no notification message
void aw_dispNotifyMessage(uint8_t a_notificationCode)
{
	if(fg_dispAlarmLocked) return;
	if(g_criticalAlarm) fg_dispAlarmLocked = 0x01;;
	memset(fg_dispBuffer4, ' ', LCD_BUFFER_LEN);
	
	switch(a_notificationCode)
	{
		//---------------------------------------------------------------------
		case ERR_NO_ERROR:	
			if(g_idleMode)
			{	
				if(g_modeOfOperation == 2)
					memcpy(fg_dispBuffer4, "Motor Off [2/3]     ", LCD_BUFFER_LEN);
				else if(g_swAutoModeInstant)	//only for display
					memcpy(fg_dispBuffer4, "Motor Off [AUTO ON] ", LCD_BUFFER_LEN);
				else if(!g_swAutoModeInstant)	//only for display
					memcpy(fg_dispBuffer4, "Motor Off [AUTO OFF] ", LCD_BUFFER_LEN);
			}
			else if(g_modeOfOperation == 2)
			{
				memcpy(fg_dispBuffer4, "2/3 AUTO,   No Alarm", LCD_BUFFER_LEN);
			}
			else if(g_swAutoModeInstant)
			{
				memcpy(fg_dispBuffer4, "AUTO ON,    No Alarm", LCD_BUFFER_LEN);
			}
			else if(!g_swAutoModeInstant)
			{
				memcpy(fg_dispBuffer4, "AUTO OFF,   No Alarm", LCD_BUFFER_LEN);
			}
			break;
		//---------------------------------------------------------------------	
		case ERR_PHASE_SEQUENCE:
			memcpy(fg_dispBuffer4, "Phase Sequence Err  ", LCD_BUFFER_LEN);
			aw_miscConvertToDecAsc(&fg_dispBuffer4[18], fg_phaseSequence, 2);
			break;
		//---------------------------------------------------------------------	
		case ERR_DRY_RUN:
			memcpy(fg_dispBuffer4, "Dry Run Error       ", LCD_BUFFER_LEN);
			break;
		//---------------------------------------------------------------------	
		case ERR_OVER_LOAD:
			memcpy(fg_dispBuffer4, "Over Load Error    *", LCD_BUFFER_LEN);
			break;
		//---------------------------------------------------------------------	
		case ERR_PHASE_MISS:
			memcpy(fg_dispBuffer4, "Phase Miss Error   *", LCD_BUFFER_LEN);
			break;
		//---------------------------------------------------------------------	
		case ERR_VOLT_RANGE_OUT:
			memcpy(fg_dispBuffer4, "3 Phase Not OK      ", LCD_BUFFER_LEN);
			break;
		//---------------------------------------------------------------------	
		case ERR_CURR_RANGE_OUT:
			memcpy(fg_dispBuffer4, "Load Unbalance      ", LCD_BUFFER_LEN);
			break;
		//---------------------------------------------------------------------	
		case ERR_PH_Y_MISS:
			memcpy(fg_dispBuffer4, "Y-Phase Miss        ", LCD_BUFFER_LEN);
			break;
		//---------------------------------------------------------------------	
		case ERR_WRONG_CAP_IN_2PH:
			memcpy(fg_dispBuffer4, "Wrong Capacitor     ", LCD_BUFFER_LEN);
			break;
		//---------------------------------------------------------------------	
		case ERR_Y_PRESENT_IN_2PH:
			memcpy(fg_dispBuffer4, "Y-Phase in 2/3 Mode ", LCD_BUFFER_LEN);
			break;
		//---------------------------------------------------------------------	
		case ERR_CURRENT_FAULT:
			memcpy(fg_dispBuffer4, "Load Fault         *", LCD_BUFFER_LEN);
			break;
		//---------------------------------------------------------------------	
		case ERR_VOLTAGE_UNBALABCE:
			memcpy(fg_dispBuffer4, "Voltage Unbalance   ", LCD_BUFFER_LEN);
			break;
		//---------------------------------------------------------------------	
		case SPL_DISP_AUTO_MODE_COUNT_DOWN:
			memcpy(fg_dispBuffer4, "Auto On in   :   Sec", LCD_BUFFER_LEN);
			aw_miscConvertToDecAsc(&fg_dispBuffer4[14], fg_3phWaitCounter, 2);
			break;
		//---------------------------------------------------------------------	
		default:
			memcpy(fg_dispBuffer4, "Invalid Err Code    ", LCD_BUFFER_LEN);
			aw_miscConvertToDecAsc(&fg_dispBuffer4[18], a_notificationCode, 2);
			break;
	}
	
	aw_lcdDisplay(LCD_LINE_4, fg_dispBuffer4);
	//RED Led Indication (0x00-On, 0x01: off)
	LED_ERROR_PIN = ((a_notificationCode && (a_notificationCode != SPL_DISP_AUTO_MODE_COUNT_DOWN)) ? 0x01 : 0x00);		//negated as transistor used for LEDs
}

void aw_dispScheduler(void)
{
	if(fg_dispNotifyCounter) fg_dispNotifyCounter--;
	if(fg_dispSecDelay) fg_dispSecDelay--;
	
	if(g_loadOn)
	{	
		g_powerOnSec++;
		if(g_powerOnSec >= 60)
		{
			g_powerOnSec = 0;
			g_powerOnMin++;
			if(g_powerOnMin >= 60)
				g_powerOnHour++;
		}
	}
	else
	{
		g_powerOnSec = 0;
		g_powerOnMin = 0;
		g_powerOnHour = 0;
	}
}


//returns number of bytes, 3 phase voltage will be filled by reference
uint8_t aw_instVoltage(uint8_t* a_pBuf)
{
	uint8_t i = 0;
	
	for(i = 0; i < 3; i++)
	{
		memcpy( (a_pBuf +i * 4), (uint8_t*) &g_phVolt[i], 2);
	}
	
	return(12);
}

//returns number of bytes, 3 phase voltage will be filled by reference
uint8_t aw_instCurrent(uint8_t* a_pBuf)
{
	uint8_t i = 0;
	
	for(i = 0; i < 3; i++)
	{
		memcpy((a_pBuf +i * 4), (uint8_t*) &g_phCurr[i], 2);
	}
	
	return(12);
}

//setting 3 phase voltage through serial port
void aw_setVirtVoltage(uint8_t* a_pBuf)
{
	uint8_t i = 0;
	
	fg_virtSource = 0x01;		//Stop reading ADC value and accept from serial port 
	g_errCode = 0;				//clear error on modified source
	//g_criticalAlarm = 0x00;		//clear critical alarm
	//fg_dispAlarmLocked = 0x00;	//clear alarm display lock
	
	for(i = 0; i < 3; i++)
	{
		memcpy(&g_phVolt[i], (a_pBuf + i * 2), 2);
	}
}

//setting 3 phase current through serial port
void aw_setVirtCurrent(uint8_t* a_pBuf)
{
	uint8_t i = 0;
	
	fg_virtSource = 0x01;		//Stop reading ADC value and accept from serial port 
	g_errCode = 0x00;			//clear error on modified source
	//g_criticalAlarm = 0x00;	//clear critical alarm
	//fg_dispAlarmLocked = 0x00;	//clear alarm display lock
	
	for(i = 0; i < 3; i++)
	{
		memcpy(&g_phCurr[i], (a_pBuf + i * 2), 2);
	}
}