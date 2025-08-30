//=================================================================================================
#ifndef _AW_PROGRAMMING_H_
#define _AW_PROGRAMMING_H_
//=================================================================================================
#include "aw_typedef.h"


//programming parameters
typedef enum
{
	PROG_PARA_MOTOR_ON_TIME = 1,	
	PROG_PARA_DRYRUN_CURRENT,
	PROG_PARA_OVERLOAD_CURRENT,
	PROG_PARA_OVER_VOLTAGE,
	PROG_PARA_UNDER_VOLTAGE,
	PROG_PARA_STAR_DELTA_TIME,
	PROG_PARA_DRYRUN_TIME,
	PROG_PARA_2PH_SET_AMP_PERC,
	PROG_PARA_DRYRUN_RETRY,			/* retrying pumping interval in case of dryrun */
	PROG_PARA_AUTO_ON_DELAY,
	PROG_PARA_COUNT
}aw_en_prog_para;
	

//key values
#define KEY_MOVE_RIGHT			0x82	
#define KEY_MOVE_LEFT			0x81	
#define KEY_MOVE_UP				0x02	//0 0 1 0
#define KEY_MOVE_DOWN			0x01	//0 1 0 0
#define KEY_SET					0x03
#define	KEY_PROG_MODE			0x83
#define KEY_OVRLD_CURR_SET		KEY_MOVE_DOWN


void aw_prgProcess(void);
void aw_prgProcess2(void);
void aw_prgParaDisplay(void);
uint8_t aw_prgKeyScan(void);
void aw_prgLoadValue(uint8_t a_paraValue);
void aw_prgSetKeyBoardValue(void);
void aw_prgSetOvrldValue(void);	
uint8_t aw_prgSaveValue(uint8_t a_paraValue);
void aw_progExitProgMode(void);
//=================================================================================================
#endif	//_AW_PROGRAMMING_H_
//=================================================================================================
