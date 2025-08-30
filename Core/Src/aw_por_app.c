
#include <string.h>
#include "aw_config_app.h"
#include "aw_config_io.h"
#include "aw_miscFunc.h"
#include "aw_global.h"
#include "aw_eeprom.h"
#include "aw_eeprom_map.h"
#include "aw_por_app.h"
#include "aw_typedef.h"
#include "inst_read.h"

void aw_porRead(void)
{
	EPR_Read(EEP_ADRS_DEV_CONFIG, (uint8_t*) &g_devConfig, EEP_BYTE_DEV_CONFIG); 
	
	if(g_devConfig.MotorOn.Hour > 99) 
	{
		g_devConfig.MotorOn.Hour = 0x00;
		g_devConfig.MotorOn.Minute = 0x00;
	}
	
	if(g_devConfig.DryRunCurrent > 99) g_devConfig.DryRunCurrent = 0x02;
	if(g_devConfig.OverloadCurrent > MAX_APP_CURRENT_VAL) g_devConfig.OverloadCurrent = MAX_APP_CURRENT_VAL;
	if(g_devConfig.StarDeltaTime < 3) g_devConfig.StarDeltaTime = 2;
	if(g_devConfig.StarDeltaTime > 10) g_devConfig.StarDeltaTime = 10;
	if(!((g_devConfig.DryRunRetry >= 4) && (g_devConfig.DryRunRetry <= 99)))  g_devConfig.DryRunRetry = 4;
	if(!((g_devConfig.AutoOnDelay >= 5) && (g_devConfig.AutoOnDelay <= 999)))  g_devConfig.AutoOnDelay = 5;
	
	EPR_Read(EEP_ADRS_CALIB_VOLTAGE, (uint8_t*) &g_factVoltage[0], EEP_BYTE_CALIB_VOLTAGE); 
	EPR_Read(EEP_ADRS_CALIB_CURRENT, (uint8_t*) &g_factCurrent[0], EEP_BYTE_CALIB_CURRENT); 	
	
	//converting motor on duartion to seconds
	g_motorOnSec = g_devConfig.MotorOn.Hour * 3600 + g_devConfig.MotorOn.Minute * 60;
	if((!g_motorOnSec) || (g_motorOnSec > 86400))
	{
		g_devConfig.MotorOn.Hour = 0;
		g_devConfig.MotorOn.Minute = 30;
		g_motorOnSec = 1800;	
	}
}

//Resetting calibration
uint8_t aw_calibReset(uint8_t a_resetType)
{
	uint8_t i = 0;
	
	if(a_resetType == 1)	//voltage
	{
		for(i = 0; i < 3; i++)
		{
			g_factVoltage[i] = 1.0f;
		}
		
		EPR_Write(EEP_ADRS_CALIB_VOLTAGE, (uint8_t*) &g_factVoltage[0], EEP_BYTE_CALIB_VOLTAGE); 
	}
	else if(a_resetType == 2)	//current
	{
		for(i = 0; i < 3; i++)
		{
			g_factCurrent[i] = 1.0f;
		}
		
		EPR_Write(EEP_ADRS_CALIB_CURRENT, (uint8_t*) &g_factCurrent[0], EEP_BYTE_CALIB_CURRENT); 
	}
	else
	{
		return(1);	//error
	}
	
	return(0);
}

//3-phase voltage through by reference
uint8_t aw_calibVoltage(uint8_t* a_pVoltage)
{	
	un_aw_2B l_2B;
	uint8_t i = 0;
	
	for(i = 0; i < 3; i++)
	{
		l_2B.Value = 0x00;
		memcpy(l_2B.Byte, (a_pVoltage + i * 2), 2);
		l_2B.Value *= 100;
		
		g_factVoltage[i] =  (float) l_2B.Value / (float) g_inst_read_params.vrms[i];
	}
	
	//write to EEPROM
	EPR_Write(EEP_ADRS_CALIB_VOLTAGE, (uint8_t*) &g_factVoltage[0], EEP_BYTE_CALIB_VOLTAGE); 
	
	return(0);
}
//3-phase current through by reference
uint8_t aw_calibCurrent(uint8_t* a_pCurrent)
{
	un_aw_2B l_2B;
	uint8_t i = 0;
	
	for(i = 0; i < 3; i++)
	{
		l_2B.Value = 0x00;
		memcpy(l_2B.Byte, (a_pCurrent + i * 2), 2);
		g_factCurrent[i] =  (float) l_2B.Value / (float) g_inst_read_params.irms[i];
	}
	
	//write to EEPROM
	EPR_Write(EEP_ADRS_CALIB_CURRENT, (uint8_t*) &g_factCurrent[0], EEP_BYTE_CALIB_CURRENT); 
	
	return(0);
}

//reading all configuration
uint8_t aw_configRead(uint8_t* a_pBuff)
{
	memcpy(a_pBuff, (uint8_t*) &g_devConfig, sizeof(g_devConfig));
	return(sizeof(g_devConfig));
}

uint8_t aw_configWrite(uint8_t* a_pBuff, uint8_t a_Len)
{
	uint8_t l_retVal = 0x06;	//ack
	st_aw_devConfig l_tmpConfig;
	
	memset(&l_tmpConfig, 0, sizeof(l_tmpConfig));
	memcpy((uint8_t*) &l_tmpConfig, a_pBuff, sizeof(l_tmpConfig));
	
	//check overload current
	if(l_tmpConfig.OverloadCurrent > MAX_APP_CURRENT_VAL)
	{
		l_retVal = 0x15;	//NAK
	}
	
	if(l_retVal == 0x06)	//check for correctness
	{
		memcpy((uint8_t*) &g_devConfig, a_pBuff, sizeof(g_devConfig));
		EPR_Write(EEP_ADRS_DEV_CONFIG, (uint8_t*) &g_devConfig, EEP_BYTE_DEV_CONFIG);	//write to EEPROM
	}
	
	return(l_retVal);
}

//sets off any relay
void aw_rlyOff(uint8_t a_rly)
{
	switch(a_rly)
	{
		case L1: 
			RELAY_L1_OFF(); 
			aw_ledSetMode(0);	//Run LED
			LED_HEALTH_OFF();	//Healthy Relay
			g_loadOn = 0x00;
			break;
		case L2: RELAY_L2_OFF(); break;
		case C1: RELAY_C1_OFF(); break;
		case C2: RELAY_C2_OFF(); break;
		case C3: RELAY_C3_OFF(); break;
	}
	
	g_rlyStatus[a_rly] = 0;
	g_dispInitCount = LCD_RE_INIT_COUNT;	//number of re-intialization
}

//sets on any relay as per parameter
void aw_rlyOn(uint8_t a_rly)
{
	if(!((a_rly >= L1) && (a_rly <= C3))) return;		//check for relay validity
	
	//relay interlocking only in case of 3Ph mode (not in 2/3 mode)
	if(a_rly == L1) 
	{
		RELAY_L1_ON();
		g_rlyStatus[L1] = 1; 	
	}
	
	if(g_rlyStatus[L1] == 0x01)		//for 3PH and 2PH
	{
		switch(a_rly)
		{
			case L2: RELAY_L2_ON(); break;
		}
		
		g_rlyStatus[a_rly] = 1; 	
	}
	
	if(g_modeOfOperation == 0x02)	//Only for 2PH
	{
		switch(a_rly)
		{
			case C1: RELAY_C1_ON(); break;
			case C2: RELAY_C2_ON(); break;
			case C3: RELAY_C3_ON(); break;
		}
		
		g_rlyStatus[a_rly] = 1; 	
	}
	
	g_dispInitCount = LCD_RE_INIT_COUNT;	//number of re-intialization
}