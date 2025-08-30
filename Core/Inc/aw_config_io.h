//=============================================================================
#ifndef _AW_CONFIG_IO_H_
#define _AW_CONFIG_IO_H_
//=============================================================================
#include "iodefine.h"
#include "aw_typedef.h"

#define BIT0				0x0001
#define BIT1				0x0002
#define BIT2				0x0004
#define BIT3				0x0008
#define BIT4				0x0010
#define BIT5				0x0020
#define BIT6				0x0040
#define BIT7				0x0080
#define BIT8				0x0100
#define BIT9				0x0200
#define BIT10				0x0400
#define BIT11				0x0800
#define BIT12				0x1000
#define BIT13				0x2000
#define BIT14				0x4000
#define BIT15				0x8000

//Relay Index
#define L1  0
#define L2 	1
#define C1	2
#define C2 	3
#define C3	4

//LED
#define LED_ERROR_PIN			P12_bit.no5				//LED1 - Error LED
#define LED_ERROR_ON()			LED_ERROR_PIN = 1
#define LED_ERROR_OFF()			LED_ERROR_PIN = 0
#define LED_ERROR_TOGGLE()		LED_ERROR_PIN = ~LED_ERROR_PIN

#define LED_HEALTH_PIN			P1_bit.no4				//LED2 - Healthy LED
#define LED_HEALTH_ON()			LED_HEALTH_PIN = 1	
#define LED_HEALTH_OFF()		LED_HEALTH_PIN = 0
#define LED_HEALTH_TOGGLE()		LED_HEALTH_PIN = ~LED_HEALTH_PIN

#define LED_RUN_PIN				P1_bit.no3				//LED3 -- as Load LED
#define LED_RUN_ON()			LED_RUN_PIN = 1
#define LED_RUN_OFF()			LED_RUN_PIN = 0
#define LED_RUN_TOGGLE()		LED_RUN_PIN = ~LED_RUN_PIN

//#define DEBUG_PIN				P1_bit.no2				//LED4
//#define DEBUG_HIGH()			DEBUG_PIN = 1
//#define DEBUG_LOW()			DEBUG_PIN = 0
//#define DEBUG_TOGGLE()		DEBUG_PIN = ~DEBUG_PIN

//lcd io pins
#define LCD_RS					P1_bit.no0
#define LCD_EN					P0_bit.no5
#define LCD_DB4					P1_bit.no1				//LCD_RW
#define LCD_DB5					P4_bit.no3				//Buzzer
#define LCD_DB6					P0_bit.no6 				//MISO
#define LCD_DB7					P0_bit.no7				//MOSI

#define LCD_EN_LOW()			LCD_EN = 0x00
#define LCD_EN_HIGH()			LCD_EN = 0x01
#define LCD_RS_LOW()			LCD_RS = 0x00
#define LCD_RS_HIGH()			LCD_RS = 0x01
#define LCD_D4_HIGH()			LCD_DB4 = 1
#define LCD_D4_LOW()			LCD_DB4 = 0
#define LCD_D5_HIGH()			LCD_DB5 = 1
#define LCD_D5_LOW()			LCD_DB5 = 0
#define LCD_D6_HIGH()			LCD_DB6 = 1
#define LCD_D6_LOW()			LCD_DB6 = 0
#define LCD_D7_HIGH()			LCD_DB7 = 1
#define LCD_D7_LOW()			LCD_DB7 = 0

//switches
#define SW_SHIFT				P7_bit.no3				//shift
#define SW_MOVE					P7_bit.no2				//move (left/right)
#define SW_UPDN					P7_bit.no1				//up-down
#define SW_SET					P7_bit.no0				//Enter
//#define SW_CALIB				P7_bit.no4				//for calibration
#define SW_AUTO_MANUAL()		P1_bit.no6				//1: Auto, 0: Manual
#define SW_PHASE()				P13_bit.no7				//1-Phase Switch On, 0-Off

//Relays [L1 - Healthy, L2 - Start-Delta, C1, C2, C3 - Capacitors]
#define RELAY_C1_PIN			P12_bit.no6				//Relay1: J67
#define RELAY_C1_ON()			RELAY_C1_PIN = 1
#define RELAY_C1_OFF()			RELAY_C1_PIN = 0
#define RELAY_C1_TOGGLE()		RELAY_C1_PIN = ~RELAY_C1_PIN

#define RELAY_L1_PIN			P1_bit.no7				//Relay2: J71	--Pulled Up
#define RELAY_L1_ON()			RELAY_L1_PIN = 0		//negative logic
#define RELAY_L1_OFF()			RELAY_L1_PIN = 1
#define RELAY_L1_TOGGLE()		RELAY_L1_PIN = ~RELAY_L1_PIN

#define RELAY_L2_PIN			P6_bit.no2				//Relay3: J69	--Pulled Up
#define RELAY_L2_ON()			RELAY_L2_PIN = 0		//negative logic
#define RELAY_L2_OFF()			RELAY_L2_PIN = 1
#define RELAY_L2_TOGGLE()		RELAY_L2_PIN = ~RELAY_L2_PIN

#define RELAY_C2_PIN			P1_bit.no5				//Relay4 : J70 
#define RELAY_C2_ON()			RELAY_C2_PIN = 1
#define RELAY_C2_OFF()			RELAY_C2_PIN = 0
#define RELAY_C2_TOGGLE()		RELAY_C2_PIN = ~RELAY_C2_PIN

#define RELAY_C3_PIN			P12_bit.no7				//Relay5 : J68
#define RELAY_C3_ON()			RELAY_C3_PIN = 1
#define RELAY_C3_OFF()			RELAY_C3_PIN = 0
#define RELAY_C3_TOGGLE()		RELAY_C3_PIN = ~RELAY_C3_PIN

void aw_ledSetMode(uint8_t a_mode);
void aw_rlyOn(uint8_t a_rly);
void aw_rlyOff(uint8_t a_rly);
//=============================================================================
#endif //_AW_CONFIG_IO_H_
//=============================================================================
