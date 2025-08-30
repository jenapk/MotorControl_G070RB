#include <string.h>
//#include "typedef.h"
#include "aw_host.h"
//#include "r_cg_sau.h"
//#include "aw_miscFunc.h"
#include "aw_config_app.h"
#include "aw_config_io.h"
//#include "inst_read.h"
#include "aw_por_app.h"
#include "aw_eeprom_map.h"
#include "aw_display.h"
#include "aw_global.h"

#define STATE_HOST_PRE_INIT		0
#define STATE_HOST_INIT			1
#define STATE_HOST_IDLE			2

static uint8_t fg_hostCommand, fg_hostRxTimeout, fg_hostTxCount, fg_hostRxIndex;
static uint8_t fg_hostState, fg_hostReceived, fg_hostFCT;
uint8_t fg_hostRxBuf[KT_HOST_UART_RX_BUF_LEN], fg_hostTxBuf[KT_HOST_UART_TX_BUF_LEN];

static void kt_hostInit(void);
static void kt_hostPreInit(void);
static void kt_hostAnalyze(void);
static void kt_hostMakeFrame(void);
static void aw_rlyTest(void);
static void aw_ledTest(void);

void kt_uartFrameReceived(void);
void kt_uartResetReceiveIndex(void);
void kt_uartSetRxTimeout(uint8_t a_Value);
uint8_t aw_2phGetPerc(void);
//=================================================================================================
void kt_hostProcess(void)
{
	switch(fg_hostState)
	{
        //-------------------------------------------------
		case STATE_HOST_PRE_INIT:
			kt_hostPreInit();
			fg_hostState = STATE_HOST_INIT;
			break;
        //-------------------------------------------------
		case STATE_HOST_INIT:
			kt_hostInit();
			fg_hostState = STATE_HOST_IDLE;
			break;
		//-------------------------------------------------
		case STATE_HOST_IDLE:
			if(fg_hostReceived)
			{
				kt_hostAnalyze();
				fg_hostReceived = 0x00;
				fg_hostState = STATE_HOST_IDLE;
			}
			break;
	}
}

//=================================================================================================
// analyzing incoming uart frame
static void kt_hostAnalyze(void)
{
	uint8_t i = 0;
	
    // check start char 
    if(fg_hostRxBuf[0] != 0xFE) fg_hostRxBuf[2] = 0x00;

    // Checking XOR - in case of non zero value 
    //if(fg_hostRxBuf[fg_hostRxBuf[1] + 4] != 0xFE)
    //{
    //    if(kt_miscGetXOR (&fg_hostRxBuf[1], fg_hostRxBuf[1] + 4))
    //    {
    //    	fg_hostRxIndex = 0x00;
    //    	fg_hostRxBuf[2] = 0x00;
    //    }
    //}

    fg_hostTxCount = 0x00;
    memset(fg_hostTxBuf, 0, KT_HOST_UART_TX_BUF_LEN);
    fg_hostCommand = (fg_hostRxBuf[2] & 0x7F);

    switch(fg_hostCommand)
    {
        //---------------------------------------------------------------
        case CMD_UART_HANDSHAKE:
            memcpy(&fg_hostTxBuf[4], "Ktec,09,3P3W,v", 14);
            fg_hostTxBuf[18]  = AW_FW_VER_MAJOR + 0x30;
			fg_hostTxBuf[19] = '.';
            fg_hostTxBuf[20] = AW_FW_VER_MINOR + 0x30;
            fg_hostTxCount = 17;
            break;
		//---------------------------------------------------------------
		case CMD_UART_GET_INSTANT:			
			aw_instVoltage(&fg_hostTxBuf[4]);
			aw_instCurrent(&fg_hostTxBuf[16]);
			
			fg_hostTxBuf[28] = g_rlyStatus[L1];
			fg_hostTxBuf[29] = g_rlyStatus[L2];
			fg_hostTxBuf[30] = g_rlyStatus[C1];
			fg_hostTxBuf[31] = g_rlyStatus[C2];
			fg_hostTxBuf[32] = g_rlyStatus[C3];
			fg_hostTxBuf[33] = g_errCode;
			fg_hostTxBuf[34] = SW_AUTO_MANUAL();	//physical switch position
			fg_hostTxBuf[35] = SW_PHASE();			//physical switch position
			fg_hostTxBuf[36] = aw_2phGetPerc();		//percentage of current variation in 2phase 
			fg_hostTxBuf[37] = g_modeOfOperation;	//1: Idle, 2: 2Phase, 3: 3Phase - mode of operation
			
			fg_hostTxCount = 34;
			break;
		//---------------------------------------------------------------
		case CMD_UART_GET_CONFIG:
			fg_hostTxCount = aw_configRead(&fg_hostTxBuf[4]);
			break;
		//---------------------------------------------------------------
		case CMD_UART_SET_CONFIG:			
			fg_hostTxBuf[4] = aw_configWrite(&fg_hostRxBuf[4], EEP_BYTE_DEV_CONFIG);	//0x06;
			fg_hostTxCount = 0x01;
			break;
		//---------------------------------------------------------------
		case CMD_UART_CALIB_RESET:
			aw_calibReset(fg_hostRxBuf[4]);
			fg_hostTxBuf[4] = 0x06;
			fg_hostTxCount = 0x01;
			break;
		//---------------------------------------------------------------
		case CMD_UART_GET_2PH_PERC:		//read perc
			fg_hostRxBuf[4] = aw_2phGetPerc();
			fg_hostTxCount = 0x01;
			break;
		//---------------------------------------------------------------
		case CMD_UART_SET_VIRT_VOLTAGE:
			aw_setVirtVoltage(&fg_hostRxBuf[4]);
			fg_hostTxBuf[4] = 0x06;
			fg_hostTxCount = 0x01;
			break;
		//---------------------------------------------------------------
		case CMD_UART_SET_VIRT_CURRENT:
			aw_setVirtCurrent(&fg_hostRxBuf[4]);
			fg_hostTxBuf[4] = 0x06;
			fg_hostTxCount = 0x01;
			break;
		//---------------------------------------------------------------
		case CMD_UART_CALIB_VOLTAGE:
			aw_calibVoltage(&fg_hostRxBuf[4]);
			fg_hostTxBuf[4] = 0x06;
			fg_hostTxCount = 0x01;
			break;
		//---------------------------------------------------------------
		case CMD_UART_CALIB_CURRENT:
			aw_calibCurrent(&fg_hostRxBuf[4]);
			fg_hostTxBuf[4] = 0x06;
			fg_hostTxCount = 0x01;
			break;
		//---------------------------------------------------------------
		case CMD_UART_SET_RELAY:
			aw_rlyTest();
			fg_hostTxBuf[4] = (AW_PROD_TEST_MODE ? 0x06 : 0x15);
			fg_hostTxCount = 0x01;
			break;
		//---------------------------------------------------------------
		case CMD_UART_SET_LED:
			aw_ledTest();
			fg_hostTxBuf[4] = (AW_PROD_TEST_MODE ? 0x06 : 0x15);
			fg_hostTxCount = 0x01;
			break;
    }
    
    //if there are bytes to transmit
    if(fg_hostTxCount)
    {
        kt_hostMakeFrame();								//make the frame
		R_UART2_Send(fg_hostTxBuf, fg_hostTxCount);		//Transmit to UART
    }

    fg_hostRxIndex = 0x00;
}
 
//=================================================================================================
// adds header and footer to UART data frame. start char, no. of bytes, command code, xor etc
static void kt_hostMakeFrame(void)
{
	if(!fg_hostFCT) fg_hostFCT = 0x01;
	
    fg_hostTxBuf[0] = 0xFE;
    fg_hostTxBuf[1] = fg_hostTxCount;
    fg_hostTxBuf[2] = (fg_hostCommand | 0x80);
    fg_hostTxBuf[3] = fg_hostFCT++;		//running serial number (1 to 255)

    //calculate XOR
    fg_hostTxBuf[fg_hostTxCount + 4] = 0xFE;	//(uint8_t) kt_miscGetXOR(&fg_hostTxBuf[1], (fg_hostTxCount + 3));
    fg_hostTxCount += 5;
}

//=================================================================================================
// data receiving function, called form UART RX ISR
void kt_hostReceive(uint8_t a_rxByte)
{
	fg_hostRxTimeout = 10;	//at scheduler
	fg_hostRxBuf[fg_hostRxIndex++] = a_rxByte;
	if(fg_hostRxIndex >= KT_HOST_UART_RX_BUF_LEN) fg_hostRxIndex = 0x00;
	if(fg_hostRxBuf[0] != 0xFE) fg_hostRxIndex = 0x00;

	if(fg_hostRxIndex >= fg_hostRxBuf[1] + 5)
	{
		fg_hostRxTimeout = 0x00;
		fg_hostReceived = 0x01;
	}
}

//=================================================================================================
// for receiving timeout, called form application scheduler @4ms
void kt_hostScheduler(void)
{
	if(fg_hostRxTimeout)
	{
		fg_hostRxTimeout--;
		if(!fg_hostRxTimeout)
		{
			fg_hostRxIndex = 0;
		}
	}
}

//=================================================================================================
static void kt_hostInit(void)
{
	
}

//=================================================================================================
static void kt_hostPreInit(void)
{
	
}

//below function will on/off relay as per uart rx buffer
//voltage must not not be present RYB = 0
static void aw_rlyTest(void)
{
#if(AW_PROD_TEST_MODE)
	if(fg_hostRxBuf[4]) 
		RELAY_C1_ON();
	else
		RELAY_C1_OFF();
		
	if(fg_hostRxBuf[5]) 
		RELAY_C2_ON();
	else
		RELAY_C2_OFF();
		
	if(fg_hostRxBuf[6]) 
		RELAY_C3_ON();
	else
		RELAY_C3_OFF();
		
	if(fg_hostRxBuf[7]) 
		RELAY_L1_ON();
	else
		RELAY_L1_OFF();
		
	if(fg_hostRxBuf[8]) 
		RELAY_L2_ON();
	else
		RELAY_L2_OFF();
		
#endif //AW_PROD_TEST_MODE
}

//below function will on/off LED as per uart rx buffer
static void aw_ledTest(void)
{
#if(AW_PROD_TEST_MODE)
	if(fg_hostRxBuf[4]) 
		LED_ERROR_ON();
	else
		LED_ERROR_OFF();
		
	if(fg_hostRxBuf[5]) 
		LED2_ON();
	else
		LED2_OFF();
		
	if(fg_hostRxBuf[6]) 
		LED3_ON();
	else
		LED3_OFF();
#endif	//AW_PROD_TEST_MODE
}
