//=============================================================================
#ifndef _AW_CONFIG_IO_H_
#define _AW_CONFIG_IO_H_
//=============================================================================
#include "stm32g0xx_hal.h"
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

//===============================================
#define ADC_VR_Pin 				GPIO_PIN_0
#define ADC_VR_GPIO_Port 		GPIOA
#define ADC_VY_Pin 				GPIO_PIN_1
#define ADC_VY_GPIO_Port 		GPIOA
#define ADC_VB_Pin 				GPIO_PIN_2
#define ADC_VB_GPIO_Port 		GPIOA
#define ADC_IR_Pin 				GPIO_PIN_3
#define ADC_IR_GPIO_Port 		GPIOA
#define ADC_IY_Pin 				GPIO_PIN_4
#define ADC_IY_GPIO_Port 		GPIOA
#define ADC_IB_Pin 				GPIO_PIN_5
#define ADC_IB_GPIO_Port 		GPIOA

#define SW_LEFT_Pin 			GPIO_PIN_6
#define SW_LEFT_GPIO_Port 		GPIOA
#define SW_RIGHT_Pin 			GPIO_PIN_7
#define SW_RIGHT_GPIO_Port 		GPIOA
#define SW_UP_Pin 				GPIO_PIN_4
#define SW_UP_GPIO_Port 		GPIOC
#define SW_DN_Pin 				GPIO_PIN_5
#define SW_DN_GPIO_Port 		GPIOC

#define LCD_PWR_Pin 			GPIO_PIN_8
#define LCD_PWR_GPIO_Port 		GPIOB
#define LCD_RS_Pin 				GPIO_PIN_6
#define LCD_RS_GPIO_Port 		GPIOD
#define LCD_WR_Pin 				GPIO_PIN_11
#define LCD_WR_GPIO_Port 		GPIOC
#define LCD_D0_Pin 				GPIO_PIN_0
#define LCD_D0_GPIO_Port 		GPIOB
#define LCD_D1_Pin 				GPIO_PIN_1
#define LCD_D1_GPIO_Port 		GPIOB
#define LCD_D2_Pin 				GPIO_PIN_2
#define LCD_D2_GPIO_Port 		GPIOB
#define LCD_D3_Pin 				GPIO_PIN_3
#define LCD_D3_GPIO_Port 		GPIOB
#define LCD_D4_Pin 				GPIO_PIN_4
#define LCD_D4_GPIO_Port 		GPIOB
#define LCD_D5_Pin 				GPIO_PIN_5
#define LCD_D5_GPIO_Port 		GPIOB
#define LCD_D6_Pin 				GPIO_PIN_6
#define LCD_D6_GPIO_Port 		GPIOB
#define LCD_D7_Pin 				GPIO_PIN_7
#define LCD_D7_GPIO_Port 		GPIOB

#define LED_RUN_Pin 			GPIO_PIN_10
#define LED_RUN_GPIO_Port 		GPIOB
#define LED_ERR_Pin 			GPIO_PIN_11
#define LED_ERR_GPIO_Port 		GPIOB

#define UART1_TX_GSM_Pin 		GPIO_PIN_9
#define UART1_TX_GSM_GPIO_Port 	GPIOA
#define UART1_RX_GSM_Pin 		GPIO_PIN_10
#define UART1_RX_GSM_GPIO_Port 	GPIOA
#define UART2_TX_USER_Pin 		GPIO_PIN_14
#define UART2_TX_USER_GPIO_Port GPIOA
#define UART2_RX_USER_Pin 		GPIO_PIN_15
#define UART2_RX_USER_GPIO_Port GPIOA

#define GSM_PWR_Pin 			GPIO_PIN_12
#define GSM_PWR_GPIO_Port 		GPIOA
#define GSM_RESET_Pin 			GPIO_PIN_13
#define GSM_RESET_GPIO_Port 	GPIOA

#define RELAY_HEALTH_Pin 		GPIO_PIN_6
#define RELAY_HEALTH_GPIO_Port 	GPIOC
#define RELAY_SD_Pin 			GPIO_PIN_7
#define RELAY_SD_GPIO_Port 		GPIOC
#define RELAY_CAP_1_Pin 		GPIO_PIN_8
#define RELAY_CAP_1_GPIO_Port 	GPIOD
#define RELAY_CAP_2_Pin 		GPIO_PIN_9
#define RELAY_CAP_2_GPIO_Port 	GPIOD
#define RELAY_CAP_3_Pin 		GPIO_PIN_11
#define RELAY_CAP_3_GPIO_Port 	GPIOA

#define SW_ON_Pin 				GPIO_PIN_9
#define SW_ON_GPIO_Port 		GPIOC
#define SW_OFF_Pin 				GPIO_PIN_0
#define SW_OFF_GPIO_Port 		GPIOD
#define SW_AUTO_Pin 			GPIO_PIN_1
#define SW_AUTO_GPIO_Port 		GPIOD
#define SW_2PH_Pin 				GPIO_PIN_2
#define SW_2PH_GPIO_Port 		GPIOD

#define DBG_PIN_IN_Pin 			GPIO_PIN_3
#define DBG_PIN_IN_GPIO_Port 	GPIOD
#define DBG_PIN_OUT_Pin 		GPIO_PIN_4
#define DBG_PIN_OUT_GPIO_Port 	GPIOD
#define DBG_PIN_LED_Pin 		GPIO_PIN_5
#define DBG_PIN_LED_GPIO_Port 	GPIOD

#define LED_HEALTH_Pin 			GPIO_PIN_9
#define LED_HEALTH_GPIO_Port 	GPIOB
#define LCD_EN_Pin 				GPIO_PIN_10
#define LCD_EN_GPIO_Port 		GPIOC
//===============================================
//HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState)
//HAL_GPIO_TogglePin(LED_ERR_GPIO_Port, LED_ERR_Pin)
//LED
#define LED_ERROR_ON()			HAL_GPIO_WritePin(LED_ERR_GPIO_Port, LED_ERR_Pin, 1)
#define LED_ERROR_OFF()			HAL_GPIO_WritePin(LED_ERR_GPIO_Port, LED_ERR_Pin, 0)
#define LED_ERROR_TOGGLE()		HAL_GPIO_TogglePin(LED_ERR_GPIO_Port, LED_ERR_Pin)

#define LED_HEALTH_ON()			HAL_GPIO_WritePin(LED_HEALTH_GPIO_Port, LED_HEALTH_Pin, 1)
#define LED_HEALTH_OFF()		HAL_GPIO_WritePin(LED_HEALTH_GPIO_Port, LED_HEALTH_Pin, 0)
#define LED_HEALTH_TOGGLE()		HAL_GPIO_TogglePin(LED_HEALTH_GPIO_Port, LED_HEALTH_Pin)

#define LED_RUN_ON()			HAL_GPIO_WritePin(LED_RUN_GPIO_Port, LED_RUN_Pin, 1)
#define LED_RUN_OFF()			HAL_GPIO_WritePin(LED_RUN_GPIO_Port, LED_RUN_Pin, 0)
#define LED_RUN_TOGGLE()		HAL_GPIO_TogglePin(LED_RUN_GPIO_Port, LED_RUN_Pin)

//lcd io pins
#define LCD_EN_LOW()			HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, 0)
#define LCD_EN_HIGH()			HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, 1)
#define LCD_RS_LOW()			HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, 0)
#define LCD_RS_HIGH()			HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, 1)

#define LCD_DATA(n)

////switches
//#define SW_SHIFT				P7_bit.no3				//shift
//#define SW_MOVE					P7_bit.no2				//move (left/right)
//#define SW_UPDN					P7_bit.no1				//up-down
//#define SW_SET					P7_bit.no0				//Enter

#define SW_AUTO_MANUAL()		HAL_GPIO_ReadPin(SW_AUTO_GPIO_Port, SW_AUTO_Pin)			//1: Auto, 0: Manual
#define SW_PHASE()				HAL_GPIO_ReadPin(SW_2PH_GPIO_Port, SW_2PH_Pin)				//1-Phase Switch On, 0-Off

//Relays [L1 - Healthy, L2 - Start-Delta, C1, C2, C3 - Capacitors]
#define RELAY_C1_ON()			HAL_GPIO_WritePin(RELAY_CAP_1_GPIO_Port, RELAY_CAP_1_Pin, 1)	//Relay1: J67
#define RELAY_C1_OFF()			HAL_GPIO_WritePin(RELAY_CAP_1_GPIO_Port, RELAY_CAP_1_Pin, 0)

//Relay2: J71	--Pulled Up
#define RELAY_L1_ON()			HAL_GPIO_WritePin(RELAY_HEALTH_GPIO_Port, RELAY_HEALTH_Pin, 0)		//negative logic
#define RELAY_L1_OFF()			HAL_GPIO_WritePin(RELAY_HEALTH_GPIO_Port, RELAY_HEALTH_Pin, 1)

//Relay3: J69	--Pulled Up
#define RELAY_L2_ON()			HAL_GPIO_WritePin(RELAY_SD_GPIO_Port, RELAY_SD_Pin, 0)		//negative logic
#define RELAY_L2_OFF()			HAL_GPIO_WritePin(RELAY_SD_GPIO_Port, RELAY_SD_Pin, 1)

//Relay4 : J70
#define RELAY_C2_ON()			HAL_GPIO_WritePin(RELAY_CAP_2_GPIO_Port, RELAY_CAP_2_Pin, 1)
#define RELAY_C2_OFF()			HAL_GPIO_WritePin(RELAY_CAP_2_GPIO_Port, RELAY_CAP_2_Pin, 0)

//Relay5 : J68
#define RELAY_C3_ON()			HAL_GPIO_WritePin(RELAY_CAP_3_GPIO_Port, RELAY_CAP_3_Pin, 1)
#define RELAY_C3_OFF()			HAL_GPIO_WritePin(RELAY_CAP_3_GPIO_Port, RELAY_CAP_3_Pin, 0)

void aw_ledSetMode(uint8_t a_mode);
void aw_rlyOn(uint8_t a_rly);
void aw_rlyOff(uint8_t a_rly);
//=============================================================================
#endif //_AW_CONFIG_IO_H_
//=============================================================================
