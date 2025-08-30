/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
//#define LCD_WR_Pin GPIO_PIN_11
//#define LCD_WR_GPIO_Port GPIOC
//#define ADC_VR_Pin GPIO_PIN_0
//#define ADC_VR_GPIO_Port GPIOA
//#define ADC_VY_Pin GPIO_PIN_1
//#define ADC_VY_GPIO_Port GPIOA
//#define ADC_VB_Pin GPIO_PIN_2
//#define ADC_VB_GPIO_Port GPIOA
//#define ADC_IR_Pin GPIO_PIN_3
//#define ADC_IR_GPIO_Port GPIOA
//#define ADC_IY_Pin GPIO_PIN_4
//#define ADC_IY_GPIO_Port GPIOA
//#define ADC_IB_Pin GPIO_PIN_5
//#define ADC_IB_GPIO_Port GPIOA
//#define SW_LEFT_Pin GPIO_PIN_6
//#define SW_LEFT_GPIO_Port GPIOA
//#define SW_RIGHT_Pin GPIO_PIN_7
//#define SW_RIGHT_GPIO_Port GPIOA
//#define SW_UP_Pin GPIO_PIN_4
//#define SW_UP_GPIO_Port GPIOC
//#define SW_DN_Pin GPIO_PIN_5
//#define SW_DN_GPIO_Port GPIOC
//#define LCD_D0_Pin GPIO_PIN_0
//#define LCD_D0_GPIO_Port GPIOB
//#define LCD_D1_Pin GPIO_PIN_1
//#define LCD_D1_GPIO_Port GPIOB
//#define LCD_D2_Pin GPIO_PIN_2
//#define LCD_D2_GPIO_Port GPIOB
//#define LED_RUN_Pin GPIO_PIN_10
//#define LED_RUN_GPIO_Port GPIOB
//#define LED_ERR_Pin GPIO_PIN_11
//#define LED_ERR_GPIO_Port GPIOB
//#define UART1_TX_GSM_Pin GPIO_PIN_9
//#define UART1_TX_GSM_GPIO_Port GPIOA
//#define RELAY_HEALTH_Pin GPIO_PIN_6
//#define RELAY_HEALTH_GPIO_Port GPIOC
//#define RELAY_SD_Pin GPIO_PIN_7
//#define RELAY_SD_GPIO_Port GPIOC
//#define RELAY_CAP_1_Pin GPIO_PIN_8
//#define RELAY_CAP_1_GPIO_Port GPIOD
//#define RELAY_CAP_2_Pin GPIO_PIN_9
//#define RELAY_CAP_2_GPIO_Port GPIOD
//#define UART1_RX_GSM_Pin GPIO_PIN_10
//#define UART1_RX_GSM_GPIO_Port GPIOA
//#define RELAY_CAP_3_Pin GPIO_PIN_11
//#define RELAY_CAP_3_GPIO_Port GPIOA
//#define GSM_PWR_Pin GPIO_PIN_12
//#define GSM_PWR_GPIO_Port GPIOA
//#define GSM_RESET_Pin GPIO_PIN_13
//#define GSM_RESET_GPIO_Port GPIOA
//#define UART2_TX_USER_Pin GPIO_PIN_14
//#define UART2_TX_USER_GPIO_Port GPIOA
//#define UART2_RX_USER_Pin GPIO_PIN_15
//#define UART2_RX_USER_GPIO_Port GPIOA
//#define SW_ON_Pin GPIO_PIN_9
//#define SW_ON_GPIO_Port GPIOC
//#define SW_OFF_Pin GPIO_PIN_0
//#define SW_OFF_GPIO_Port GPIOD
//#define SW_AUTO_Pin GPIO_PIN_1
//#define SW_AUTO_GPIO_Port GPIOD
//#define SW_2PH_Pin GPIO_PIN_2
//#define SW_2PH_GPIO_Port GPIOD
//#define DBG_PIN_IN_Pin GPIO_PIN_3
//#define DBG_PIN_IN_GPIO_Port GPIOD
//#define DBG_PIN_OUT_Pin GPIO_PIN_4
//#define DBG_PIN_OUT_GPIO_Port GPIOD
//#define DBG_PIN_LED_Pin GPIO_PIN_5
//#define DBG_PIN_LED_GPIO_Port GPIOD
//#define LCD_RS_Pin GPIO_PIN_6
//#define LCD_RS_GPIO_Port GPIOD
//#define LCD_D3_Pin GPIO_PIN_3
//#define LCD_D3_GPIO_Port GPIOB
//#define LCD_D4_Pin GPIO_PIN_4
//#define LCD_D4_GPIO_Port GPIOB
//#define LCD_D5_Pin GPIO_PIN_5
//#define LCD_D5_GPIO_Port GPIOB
//#define LCD_D6_Pin GPIO_PIN_6
//#define LCD_D6_GPIO_Port GPIOB
//#define LCD_D7_Pin GPIO_PIN_7
//#define LCD_D7_GPIO_Port GPIOB
//#define LCD_PWR_Pin GPIO_PIN_8
//#define LCD_PWR_GPIO_Port GPIOB
//#define LED_HEALTH_Pin GPIO_PIN_9
//#define LED_HEALTH_GPIO_Port GPIOB
//#define LCD_EN_Pin GPIO_PIN_10
//#define LCD_EN_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
