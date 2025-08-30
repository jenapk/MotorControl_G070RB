
#include <string.h>
#include "aw_lcd_gdm.h"
#include "aw_display.h"
#include "aw_config_app.h"
#include "aw_config_io.h"
#include "aw_miscFunc.h"
#include "aw_global.h"
#include "aw_config_app.h"
#include "aw_programming.h"
#include "aw_eeprom_map.h"
#include "aw_eeprom.h"

uint8_t fg_prgTickCount;		//to enter programming mode
uint8_t fg_prgMode;				//programming mode
uint8_t fg_keyValue;
uint8_t fg_currPara = 0xFF;		//for loading actual value for 1st time
uint8_t fg_valChangeFlag;		//a flag used to keep track for change in value
uint8_t fg_decValue[6];			//to hold value to change
uint8_t fg_decMinValue[6], fg_decMaxValue[6];

st_aw_ProgInfo fg_prgInfo;

extern uint8_t fg_dispBuffer1[LCD_BUFFER_LEN];
extern uint8_t fg_dispBuffer2[LCD_BUFFER_LEN];
extern uint8_t fg_dispBuffer3[LCD_BUFFER_LEN];
extern uint8_t fg_dispBuffer4[LCD_BUFFER_LEN];

//=======================================================================================
void aw_prgProcess(void)
{
	if(fg_prgMode == 2)	//overload current
	{	
		fg_prgInfo.Para = PROG_PARA_OVERLOAD_CURRENT;
	}
	
	memset(fg_dispBuffer4, ' ', LCD_BUFFER_LEN);
	memcpy(fg_dispBuffer1, "---Motor Settings---", LCD_BUFFER_LEN);
		
	switch(fg_prgInfo.Para)
	{
		//--------------------------------------------------------
		case PROG_PARA_MOTOR_ON_TIME:		
			memcpy(fg_dispBuffer2, "On Duration:   HH:MM", 20);
			
			//update line 3
			fg_dispBuffer3[15] = fg_decValue[0] + 0x30;
			fg_dispBuffer3[16] = fg_decValue[1] + 0x30;
			fg_dispBuffer3[17] = fg_decValue[2];	//separator
			fg_dispBuffer3[18] = fg_decValue[3] + 0x30;
			fg_dispBuffer3[19] = fg_decValue[4] + 0x30;
			break;
		//--------------------------------------------------------
		case PROG_PARA_DRYRUN_CURRENT:	
			memcpy(fg_dispBuffer2, "DryRun Current    AA", 20);
			//update line 3
			fg_dispBuffer3[18] = fg_decValue[0] + 0x30;
			fg_dispBuffer3[19] = fg_decValue[1] + 0x30;
			break;
		//--------------------------------------------------------
		case PROG_PARA_OVERLOAD_CURRENT:
			memcpy(fg_dispBuffer2, "OvLoad Current    AA", 20);
			fg_dispBuffer3[18] = fg_decValue[0] + 0x30;
			fg_dispBuffer3[19] = fg_decValue[1] + 0x30;
			break;
		//--------------------------------------------------------
		case PROG_PARA_OVER_VOLTAGE:
			memcpy(fg_dispBuffer2, "Over Voltage     VVV", 20);
			fg_dispBuffer3[17] = fg_decValue[0] + 0x30;
			fg_dispBuffer3[18] = fg_decValue[1] + 0x30;
			fg_dispBuffer3[19] = fg_decValue[2] + 0x30;
			break;
		//--------------------------------------------------------
		case PROG_PARA_UNDER_VOLTAGE:
			memcpy(fg_dispBuffer2, "Under Voltage    VVV", 20);
			fg_dispBuffer3[17] = fg_decValue[0] + 0x30;
			fg_dispBuffer3[18] = fg_decValue[1] + 0x30;
			fg_dispBuffer3[19] = fg_decValue[2] + 0x30;
			break;
		//--------------------------------------------------------
		case PROG_PARA_STAR_DELTA_TIME:
			memcpy(fg_dispBuffer2, "Start-Delta Time  SS", 20);
			fg_dispBuffer3[18] = fg_decValue[0] + 0x30;
			fg_dispBuffer3[19] = fg_decValue[1] + 0x30;
			break;
		//--------------------------------------------------------
		case PROG_PARA_DRYRUN_TIME:
			memcpy(fg_dispBuffer2, "Dry Run Time      MM", 20);
			fg_dispBuffer3[18] = fg_decValue[0] + 0x30;
			fg_dispBuffer3[19] = fg_decValue[1] + 0x30;
			break;
		//--------------------------------------------------------
		case PROG_PARA_2PH_SET_AMP_PERC:
			memcpy(fg_dispBuffer2, "2Ph Set Current   AA", 20);
			fg_dispBuffer3[18] = fg_decValue[0] + 0x30;
			fg_dispBuffer3[19] = fg_decValue[1] + 0x30;
			break;
		//--------------------------------------------------------
		case PROG_PARA_DRYRUN_RETRY:
			memcpy(fg_dispBuffer2, "Dry Run Retrying  MM", 20);
			fg_dispBuffer3[18] = fg_decValue[0] + 0x30;
			fg_dispBuffer3[19] = fg_decValue[1] + 0x30;
			break;
		//--------------------------------------------------------
		case PROG_PARA_AUTO_ON_DELAY:
			memcpy(fg_dispBuffer2, "Auto On Delay    SSS", 20);
			fg_dispBuffer3[17] = fg_decValue[0] + 0x30;
			fg_dispBuffer3[18] = fg_decValue[1] + 0x30;
			fg_dispBuffer3[19] = fg_decValue[2] + 0x30;
			break;
	}
	
	aw_prgLoadValue(fg_prgInfo.Para);
	
	//refresh the LCD
	aw_lcdDisplay(LCD_LINE_1, fg_dispBuffer1);
	aw_lcdDisplay(LCD_LINE_2, fg_dispBuffer2);
	aw_lcdDisplay(LCD_LINE_3, fg_dispBuffer3);
	aw_lcdDisplay(LCD_LINE_4, fg_dispBuffer4);
	
	aw_lcdCommand(0x94 + 20 - fg_prgInfo.Length + fg_prgInfo.Pose);	//curser On
	aw_lcdCommand(0x0E);	//curser On
	
	//chnage the value as per keyboard
	if(fg_prgMode == 0x01)
	{
		aw_prgSetKeyBoardValue();
	}
	else if(fg_prgMode == 0x02)
	{
		aw_prgSetOvrldValue();		//setting overload valie
	}
}

/* setting overload valie */
void aw_prgSetOvrldValue(void)		
{
	uint16_t l_xVal = 0;
	
	l_xVal = fg_decValue[0] * 10 + fg_decValue[1];
		
	switch(fg_keyValue)
	{
		case KEY_MOVE_UP:
			l_xVal++;
			if(l_xVal > 99) l_xVal = 2;		//set rollover value
			fg_valChangeFlag = 0x01;
			break;
			
		case KEY_MOVE_DOWN:
			if(l_xVal >= 2) l_xVal--;
			if( l_xVal == 1) l_xVal = 99;		//set max value
			fg_valChangeFlag = 0x01;
			break;
			
		case KEY_SET:
			if(fg_valChangeFlag)
			{
				fg_decValue[0] = l_xVal / 10;
				fg_decValue[1] = l_xVal % 10;
				aw_prgSaveValue(fg_prgInfo.Para);
				
				fg_valChangeFlag = 0x00;
				aw_progExitProgMode();
			}
			break;
	}
	
	fg_decValue[0] = l_xVal / 10;
	fg_decValue[1] = l_xVal % 10;
	
	fg_keyValue = 0x00;
}

void aw_prgSetKeyBoardValue(void)
{
	switch(fg_keyValue)
	{
		case KEY_MOVE_RIGHT:
			if(fg_prgInfo.Pose < (fg_prgInfo.Length -1))
			{
				fg_prgInfo.Pose++;
				if((fg_decValue[fg_prgInfo.Pose] == '.') || (fg_decValue[fg_prgInfo.Pose] == ':') )
				{
					fg_prgInfo.Pose++;	//to skip separator character
				}
			}
			break;
			
		case KEY_MOVE_LEFT:
			if(fg_prgInfo.Pose)
			{
				fg_prgInfo.Pose--;
				if((fg_decValue[fg_prgInfo.Pose] == '.') || (fg_decValue[fg_prgInfo.Pose] == ':') )
				{
					fg_prgInfo.Pose--;	//to skip separator character
				}
			}
			break;
			
		case KEY_MOVE_UP:	//3rd button
			if(fg_decValue[fg_prgInfo.Pose] < fg_decMaxValue[fg_prgInfo.Pose])
			{
				fg_decValue[fg_prgInfo.Pose]++;
			}
			break;
			
		case KEY_MOVE_DOWN: //2nd button
			if(fg_decValue[fg_prgInfo.Pose] > fg_decMinValue[fg_prgInfo.Pose])
			{
				fg_decValue[fg_prgInfo.Pose]--;
			}
			break;
			
		case KEY_SET:
			aw_prgSaveValue(fg_prgInfo.Para);
			break;
			
		case KEY_PROG_MODE:
			break;
	}
	
	fg_keyValue = 0x00;
}
//=======================================================================================
//saves the modified values into eeprom
uint8_t aw_prgSaveValue(uint8_t a_paraValue)
{
	uint8_t l_retVal = 0;	
	uint16_t l_tmpVal = 0;
	
	switch(a_paraValue)
	{
		//--------------------------------------------------------
		case PROG_PARA_MOTOR_ON_TIME:
			g_devConfig.MotorOn.Hour = fg_decValue[0] * 10 + fg_decValue[1];
			g_devConfig.MotorOn.Minute  = fg_decValue[3] * 10 + fg_decValue[4];
			
			g_motorOnSec = g_devConfig.MotorOn.Hour * 3600 + g_devConfig.MotorOn.Minute * 60;	//convert to seconds
			l_retVal = 0x01;
			break;
		//--------------------------------------------------------
		case PROG_PARA_DRYRUN_CURRENT:	
			g_devConfig.DryRunCurrent = fg_decValue[0] * 10 + fg_decValue[1];
			l_retVal = 0x01;
			break;
		//--------------------------------------------------------
		case PROG_PARA_OVERLOAD_CURRENT:
			l_tmpVal = 	fg_decValue[0] * 10 + fg_decValue[1];
			if(l_tmpVal <= MAX_APP_CURRENT_VAL)
			{
				g_devConfig.OverloadCurrent = l_tmpVal;
				l_retVal = 0x01;
			}
			break;
		//--------------------------------------------------------
		case PROG_PARA_OVER_VOLTAGE:
			g_devConfig.OverVoltage = fg_decValue[0] * 100 + fg_decValue[1] * 10 + fg_decValue[2];
			l_retVal = 0x01;
			break;
		//--------------------------------------------------------
		case PROG_PARA_UNDER_VOLTAGE:
			g_devConfig.UnderVoltage = fg_decValue[0] * 100 + fg_decValue[1] * 10 + fg_decValue[2];
			l_retVal = 0x01;
			break;
		//--------------------------------------------------------
		case PROG_PARA_STAR_DELTA_TIME:
			g_devConfig.StarDeltaTime = fg_decValue[0] * 10 + fg_decValue[1];
			l_retVal = 0x01;
			break;
		//--------------------------------------------------------
		case PROG_PARA_DRYRUN_TIME:
			g_devConfig.DryRunTime = fg_decValue[0] * 10 + fg_decValue[1];
			l_retVal = 0x01;
			break;
		//--------------------------------------------------------
		case PROG_PARA_2PH_SET_AMP_PERC:
			g_devConfig.Ph2AmpPercMax = fg_decValue[0] * 10 + fg_decValue[1];
			l_retVal = 0x01;
			break;
		//--------------------------------------------------------
		case PROG_PARA_DRYRUN_RETRY:
			g_devConfig.DryRunRetry = fg_decValue[0] * 10 + fg_decValue[1];
			l_retVal = 0x01;
			break;
		//--------------------------------------------------------
		case PROG_PARA_AUTO_ON_DELAY:
			g_devConfig.AutoOnDelay  = fg_decValue[0] * 100 + fg_decValue[1] * 10 + fg_decValue[2];
			if(!((g_devConfig.AutoOnDelay >= 5) && (g_devConfig.AutoOnDelay <= 999)))  g_devConfig.AutoOnDelay = 5;
			l_retVal = 0x01;
			break;
	}
	
	//write to EEPROM
	if(l_retVal == 0x01)
	{	
		EPR_Write(EEP_ADRS_DEV_CONFIG, (uint8_t*) &g_devConfig, EEP_BYTE_DEV_CONFIG);	
	}
	else
	{
		if(!g_progStatus)					//once set, failure will be displayed, 1st failure parameter
		{
			g_progPara = a_paraValue;		//1st failed programming parameters
			g_progStatus = 0x01;			// failed		
			aw_progExitProgMode();
			return(0);
		}
	}
	
	//move to next parameter
	fg_prgInfo.Para++;
	if(fg_prgInfo.Para == PROG_PARA_COUNT) aw_progExitProgMode();

	return(0);
}

/* while exiting from prog mode */
void aw_progExitProgMode(void)
{
	fg_keyValue = 0x00;
	fg_prgMode = 0x00;				//exit from programming mode
	aw_dispExitFromProgMode();
	aw_lcdCommand(0x0C);			//set curser off
}
//=======================================================================================
//load values to program
void aw_prgLoadValue(uint8_t a_paraValue)
{
	if(fg_currPara == a_paraValue) return;	//if equal already loaded
	fg_currPara = a_paraValue;
	memset(fg_decValue, 0, sizeof(fg_decValue));
	
	switch(a_paraValue)
	{
		//--------------------------------------------------------
		case PROG_PARA_MOTOR_ON_TIME:
			fg_prgInfo.Length = 5;
			fg_prgInfo.Pose = 0;
			
			fg_decMinValue[0] = 0; fg_decMinValue[1] = 0; 
			fg_decMinValue[2] = ':';
			fg_decMinValue[3] = 0; fg_decMinValue[4] = 0;
			
			fg_decMaxValue[0] = 0; fg_decMaxValue[1] = 9; 
			fg_decMaxValue[2] = ':';
			fg_decMaxValue[3] = 5; fg_decMaxValue[4] = 9;
			
			aw_miscConvertToDecDigits(&fg_decValue[0], g_devConfig.MotorOn.Hour, 2);
			fg_decValue[2] = ':';
			aw_miscConvertToDecDigits(&fg_decValue[3], g_devConfig.MotorOn.Minute, 2);
			break;
		//--------------------------------------------------------
		case PROG_PARA_DRYRUN_CURRENT:	
			fg_prgInfo.Length = 2;
			fg_prgInfo.Pose = 0;
			
			fg_decMinValue[0] = 0; fg_decMinValue[1] = 0; 
			fg_decMaxValue[0] = 9; fg_decMaxValue[1] = 9; 
			aw_miscConvertToDecDigits(&fg_decValue[0], g_devConfig.DryRunCurrent, 2);
			break;			
		//--------------------------------------------------------
		case PROG_PARA_OVERLOAD_CURRENT:
			fg_prgInfo.Length = 2;
			fg_prgInfo.Pose = 0;
			
			fg_decMinValue[0] = 0; fg_decMinValue[1] = 0; 
			fg_decMaxValue[0] = 9; fg_decMaxValue[1] = 9; 
			aw_miscConvertToDecDigits(&fg_decValue[0], g_devConfig.OverloadCurrent, 2);
			break;
		//--------------------------------------------------------
		case PROG_PARA_OVER_VOLTAGE:
			fg_prgInfo.Length = 3;
			fg_prgInfo.Pose = 0;
			
			fg_decMinValue[0] = 0; fg_decMinValue[1] = 0; fg_decMinValue[2] = 0; 
			fg_decMaxValue[0] = 9; fg_decMaxValue[1] = 9; fg_decMaxValue[2] = 9; 
			aw_miscConvertToDecDigits(&fg_decValue[0], g_devConfig.OverVoltage, 3);
			break;
		//--------------------------------------------------------
		case PROG_PARA_UNDER_VOLTAGE:
			fg_prgInfo.Length = 3;
			fg_prgInfo.Pose = 0;
			
			fg_decMinValue[0] = 0; fg_decMinValue[1] = 0; fg_decMinValue[2] = 0; 
			fg_decMaxValue[0] = 9; fg_decMaxValue[1] = 9; fg_decMaxValue[2] = 9; 
			aw_miscConvertToDecDigits(&fg_decValue[0], g_devConfig.UnderVoltage, 3);
			break;
		//--------------------------------------------------------
		case PROG_PARA_STAR_DELTA_TIME:
			fg_prgInfo.Length = 2;
			fg_prgInfo.Pose = 0;
			
			fg_decMinValue[0] = 0; fg_decMinValue[1] = 2; 
			fg_decMaxValue[0] = 1; fg_decMaxValue[1] = 9; 
			aw_miscConvertToDecDigits(&fg_decValue[0], g_devConfig.StarDeltaTime, 2);
			break;
		//--------------------------------------------------------
		case PROG_PARA_DRYRUN_TIME:
			fg_prgInfo.Length = 2;
			fg_prgInfo.Pose = 0;
			
			fg_decMinValue[0] = 0; fg_decMinValue[1] = 0; 
			fg_decMaxValue[0] = 0; fg_decMaxValue[1] = 9; 
			aw_miscConvertToDecDigits(&fg_decValue[0], g_devConfig.DryRunTime, 2);
			break;
		//--------------------------------------------------------
		case PROG_PARA_2PH_SET_AMP_PERC:
			fg_prgInfo.Length = 2;
			fg_prgInfo.Pose = 0;
			
			fg_decMinValue[0] = 0; fg_decMinValue[1] = 0; 
			fg_decMaxValue[0] = 9; fg_decMaxValue[1] = 9; 
			aw_miscConvertToDecDigits(&fg_decValue[0], g_devConfig.Ph2AmpPercMax , 2);
			break;
		//--------------------------------------------------------
		case PROG_PARA_DRYRUN_RETRY:
			fg_prgInfo.Length = 2;
			fg_prgInfo.Pose = 0;
			
			fg_decMinValue[0] = 0; fg_decMinValue[1] = 0; 
			fg_decMaxValue[0] = 9; fg_decMaxValue[1] = 9; 
			aw_miscConvertToDecDigits(&fg_decValue[0], g_devConfig.DryRunRetry , 2);
			break;
		//--------------------------------------------------------
		case PROG_PARA_AUTO_ON_DELAY:
			fg_prgInfo.Length = 3;
			fg_prgInfo.Pose = 0;
			
			fg_decMinValue[0] = 0; fg_decMinValue[1] = 0; fg_decMinValue[2] = 0; 
			fg_decMaxValue[0] = 9; fg_decMaxValue[1] = 9; fg_decMaxValue[2] = 9; 
			aw_miscConvertToDecDigits(&fg_decValue[0], g_devConfig.AutoOnDelay, 3);
			break;
	}
}

//=======================================================================================
//keys will be used as a keyboard
void aw_prgKeyBoardUse(void)
{
	//jena: below SW pins are to be taken care of
//	if(!SW_MOVE) 	fg_keyValue = 0x01;
//	if(!SW_UPDN) 	fg_keyValue = 0x02;
//	if(!SW_SET)  	fg_keyValue = 0x03;
//	if(!SW_SHIFT) 	fg_keyValue|= 0x80;
}

void aw_dispConfigValues(void)
{
	memcpy(fg_dispBuffer1, "---Configurations---", LCD_BUFFER_LEN);
	memcpy(fg_dispBuffer2, "Overload(A)  [00]   ", LCD_BUFFER_LEN);
	memcpy(fg_dispBuffer3, " Dry run(A)  [00]   ", LCD_BUFFER_LEN);
	memcpy(fg_dispBuffer4, " Runtime(T)  [00:00]", LCD_BUFFER_LEN);
	
	aw_miscConvertToDecAsc(&fg_dispBuffer2[17], g_devConfig.OverloadCurrent, 2);
	aw_miscConvertToDecAsc(&fg_dispBuffer3[17], g_devConfig.DryRunCurrent, 2);
	aw_miscConvertToDecAsc(&fg_dispBuffer4[14], g_devConfig.MotorOn.Hour, 2);
	aw_miscConvertToDecAsc(&fg_dispBuffer4[14], g_devConfig.MotorOn.Minute, 2);
	
	//refresh the LCD
	aw_lcdDisplay(LCD_LINE_1, fg_dispBuffer1);
	aw_lcdDisplay(LCD_LINE_2, fg_dispBuffer2);
	aw_lcdDisplay(LCD_LINE_3, fg_dispBuffer3);
	aw_lcdDisplay(LCD_LINE_4, fg_dispBuffer4);
}

//=======================================================================================
//scan the keys
uint8_t aw_prgKeyScan(void)
{
	fg_keyValue = 0x00;
	//jena: below SW pins need to take care of
//	if(!SW_MOVE) 	fg_keyValue = 0x01;
//	if(!SW_UPDN) 	fg_keyValue = 0x02;
//	if(!SW_SET)  	fg_keyValue = 0x03;
//	if(!SW_SHIFT) 	fg_keyValue|= 0x80;
	
	if(fg_prgMode)
	{
		if(fg_prgTickCount)
		{
			fg_prgTickCount--;
			if(!fg_prgTickCount) aw_progExitProgMode();
		}
	
		aw_prgKeyBoardUse();	//for entering values
	}
	else if (!fg_prgMode)
	{	
		if(fg_keyValue == KEY_SET)	//for overload current control
		{
			if(fg_prgTickCount < 5) fg_prgTickCount++;			//continous for 5 seconds
			if(fg_prgTickCount == 5)
			{
				fg_prgMode = 0x02;								//set mode
				fg_prgTickCount = 254;							//set timeout
				fg_prgInfo.Para = PROG_PARA_OVERLOAD_CURRENT;	//set to 1st programming parameter
			}			
		}
		else if(fg_keyValue == KEY_PROG_MODE)
		{
			if(fg_prgTickCount < 2) fg_prgTickCount++;	
			if(fg_prgTickCount == 2)
			{
				fg_prgMode = 0x01;							//set mode
				fg_prgTickCount = 254;						//set timeout
				fg_prgInfo.Para = PROG_PARA_MOTOR_ON_TIME;	//set to 1st programming parameter
			}
		}
		else if(fg_keyValue == 0x80)
		{
			aw_dispConfigValues();
		}
		else
		{
			fg_prgTickCount = 0;
			fg_prgMode = 0x00;
		}
	}
	
	return(fg_keyValue);
}

