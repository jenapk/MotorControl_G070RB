
//=================================================================================================
#ifndef _AW_DISPLAY_H_
#define _AW_DISPLAY_H_
//=================================================================================================

#define DISP_PARA_INTERVAL		3	// in seconds
#define DISP_KEYP_INTERVAL		10	// if a key pressed

typedef enum aw_en_notification
{
	ERR_NO_ERROR,
	ERR_PHASE_SEQUENCE,
	ERR_DRY_RUN,
	ERR_OVER_LOAD,
	ERR_PHASE_MISS,
	ERR_VOLT_RANGE_OUT,
	ERR_CURR_RANGE_OUT,
	ERR_PH_Y_MISS,
	ERR_WRONG_CAP_IN_2PH,		//the current limit-out in 2/3 phase system
	ERR_Y_PRESENT_IN_2PH,		//Y-Phase present in 2/3 phase mode
	ERR_CURRENT_FAULT,
	ERR_VOLTAGE_UNBALABCE,
	SPL_DISP_AUTO_MODE_COUNT_DOWN
}aw_en_notification;

void aw_dispProcess(void);
void aw_dispVI(void);
void aw_dispVersion(void);
void aw_dispPhaseSequence(void);
void aw_dispScheduler(void);
void aw_dispPORMessage(void);
void aw_dispTime(void);
void aw_dispMessage(uint8_t* a_pMsg, uint8_t a_Len);
void aw_dispLine4(void);
void aw_dispNoNotification(void);
void aw_dispCalibMsg(uint8_t a_Phase);
void aw_dispCalibStatus(uint8_t a_Status);
void aw_dispNotifyMessage(uint8_t a_notificationCode);
void aw_dispGetNotifications(void);
void aw_setVirtVoltage(uint8_t* a_pBuf);	//setting 3 phase voltage through serial port
void aw_setVirtCurrent(uint8_t* a_pBuf);	//setting 3 phase current through serial port
void aw_dispSetRecoveryCode(uint8_t a_errCode);
void aw_dispResetRecoveryCode(void);		//resetting recovery code
void aw_dispExitFromProgMode(void);
void aw_dispProgStatus(void);				//shows programming status
//=================================================================================================
#endif //_AW_DISPLAY_H_
//=================================================================================================
