//=================================================================================================
#ifndef _AW_POR_APP_H_
#define _AW_POR_APP_H_
//=================================================================================================
void aw_porRead(void);
uint8_t aw_calibReset(uint8_t a_resetType); //Resetting calibration
uint8_t aw_calibVoltage(uint8_t* a_pVoltage); //3-phase voltage through by reference
uint8_t aw_calibCurrent(uint8_t* a_pCurrent); //3-phase current through by reference

uint8_t aw_configRead(uint8_t* a_pBuff);		//reading configuration
uint8_t aw_configWrite(uint8_t* a_pBuff, uint8_t a_Len);	//writting configuration
//=================================================================================================
#endif //_AW_POR_APP_H_
//=================================================================================================
