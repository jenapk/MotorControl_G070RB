/*
 * kt_host.h
 *
 *  Created on: 14-Jun-2020
 *      Author: Administrator
 */
//=======================================================================================
#ifndef _KT_HOST_H_
#define _KT_HOST_H_
//=======================================================================================
#include "aw_typedef.h"

#define KT_HOST_UART_RX_BUF_LEN		    32
#define KT_HOST_UART_TX_BUF_LEN		    40

//host command list
#define CMD_UART_HANDSHAKE 			    0x09
#define CMD_UART_GET_INSTANT		    0x0A    //voltage, current, 
#define CMD_UART_GET_CONFIG				0x0B
#define CMD_UART_SET_CONFIG				0x0C
#define CMD_UART_GET_2PH_PERC			0x0D
#define CMD_UART_SET_VIRT_VOLTAGE		0x0E
#define CMD_UART_SET_VIRT_CURRENT		0x0F

#define CMD_UART_CALIB_RESET			0x20
#define CMD_UART_CALIB_VOLTAGE			0x21
#define CMD_UART_CALIB_CURRENT			0x22

//HW Test
#define CMD_UART_SET_RELAY				0x50
#define CMD_UART_SET_LED				0x51

//-------------------------------------------------
//function proto types
void kt_hostProcess(void);
void kt_hostScheduler(void);
void kt_hostSetRxTxBufPointer(uint8_t* a_pRx, uint8_t* a_pTx);
void kt_hostUsbReceive(uint8_t* a_prxBuf, uint8_t a_rxLen);
void kt_hostUartReceive(uint8_t a_rxByte);
//=======================================================================================
#endif /* _KT_HOST_H_ */
//=======================================================================================


