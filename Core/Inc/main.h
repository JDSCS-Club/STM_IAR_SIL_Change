/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

//========================================================================
#if	defined(USE_BOOTLOADER)
//	Bootloader : Exclude Code
#else	//	Application
//========================================================================

#include "compiler_defs.h"		//	U8,
#include "si446x_defs.h"

//========================================================================
#endif	//	Application
//========================================================================

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

extern ADC_HandleTypeDef hadc1;		//	ADC1 - ADC Battery

extern SPI_HandleTypeDef hspi1;		//	SPI1 - RF SPI

extern I2C_HandleTypeDef hi2c1;		//	I2C1 - Audio Codec Control I/F
extern I2S_HandleTypeDef hi2s3;		//	I2S3 - Audio Stream

extern I2C_HandleTypeDef hi2c3;		//	I2C3 - LCD I/F

extern UART_HandleTypeDef huart2;

extern IWDG_HandleTypeDef hiwdg;	//	Watchdog

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

#define SILABS_RADIO_SI446X

//#define SI4463_USE_FIFO_MODE
////#define SI4463_USE_DIRECT_MODE
//
//#ifdef SI4463_USE_FIFO_MODE
//#define RADIO_DRIVER_EXTENDED_SUPPORT
//#endif

#define RADIO_DRIVER_FULL_SUPPORT


//#define SILABS_RADIO_SI446X
#define DRIVERS_EXTENDED_SUPPORT
//#define RADIO_DRIVER_FULL_SUPPORT
#define RADIO_CONFIGURATION_USE_PATCH

#define RADIO_DRIVER_EXTENDED_SUPPORT


#ifdef SI4463_USE_DIRECT_MODE
#define DIRECT_TX 0
#define DIRECT_RX 1
#endif

//========================================================================
//DEL	#define	USE_SPI_DMA		1		//	SPI DMA 사용.
//	DMA방식 사용시 SPI Error발생하는 경우 있음 : SpiReadWrite(118) Error (1)!!
//========================================================================

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

void LoopProcMain( int nTick );

void MX_IWDG_Disable( void );

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PWR_RF_Pin          GPIO_PIN_2
#define PWR_RF_GPIO_Port    GPIOE
#define PWR_AUDIO_Pin       GPIO_PIN_3
#define PWR_AUDIO_GPIO_Port GPIOE
#define SPK_ON_Pin          GPIO_PIN_5
#define SPK_ON_GPIO_Port    GPIOE
#define GPIO1_Pin           GPIO_PIN_6
#define GPIO1_GPIO_Port     GPIOE
#define USB_ID_Pin          GPIO_PIN_15
#define USB_ID_GPIO_Port    GPIOC
#define BAT_CHRG_Pin        GPIO_PIN_0
#define BAT_CHRG_GPIO_Port  GPIOC
#define BAT_ADC_Pin         GPIO_PIN_1
#define BAT_ADC_GPIO_Port   GPIOC
#define MOSI_Pin            GPIO_PIN_3
#define MOSI_GPIO_Port      GPIOC
#define SPI_CSN_Pin         GPIO_PIN_4
#define SPI_CSN_GPIO_Port   GPIOA
#define SPI_SCK_Pin         GPIO_PIN_5
#define SPI_SCK_GPIO_Port   GPIOA
#define SPI_MISO_Pin        GPIO_PIN_6
#define SPI_MISO_GPIO_Port  GPIOA
#define SPI_MOSI_Pin        GPIO_PIN_7
#define SPI_MOSI_GPIO_Port  GPIOA

//#define DEBUG_TX            GPIO_PIN_2
//#define DEBUG_RX            GPIO_PIN_3
//#define DEBUG_GPOP_Port     GPIOA

#define RF_INT_Pin          GPIO_PIN_4
#define RF_INT_GPIO_Port    GPIOC
#define RF_INT_EXTI_IRQn    EXTI4_IRQn
#define TRN_RST_Pin         GPIO_PIN_5
#define TRN_RST_GPIO_Port   GPIOC
#define RX_EN_Pin           GPIO_PIN_0
#define RX_EN_GPIO_Port     GPIOB
#define RF_TX_Pin           GPIO_PIN_1
#define RF_TX_GPIO_Port     GPIOB
#define RF_RX_Pin           GPIO_PIN_2
#define RF_RX_GPIO_Port     GPIOB
#define STANDBY_Pin         GPIO_PIN_7
#define STANDBY_GPIO_Port   GPIOE
#define AUDIO_ON_Pin        GPIO_PIN_8
#define AUDIO_ON_GPIO_Port  GPIOE
#define LIGHT_ON_Pin        GPIO_PIN_9
#define LIGHT_ON_GPIO_Port  GPIOE
#define OVERRIDE_ON_Pin     GPIO_PIN_10
#define OVERRIDE_ON_GPIO_Port GPIOE
#define SCK_Pin             GPIO_PIN_10
#define SCK_GPIO_Port       GPIOB
#define SS_Pin              GPIO_PIN_12
#define SS_GPIO_Port        GPIOB
#define LED_ON_A_Pin        GPIO_PIN_13
#define LED_ON_A_GPIO_Port  GPIOB
#define LED_ON_B_Pin        GPIO_PIN_14
#define LED_ON_B_GPIO_Port  GPIOB
#define ON_OFF_KEY_Pin      GPIO_PIN_9
#define ON_OFF_KEY_GPIO_Port GPIOD
#define ON_OFF_EN_Pin       GPIO_PIN_10
#define ON_OFF_EN_GPIO_Port GPIOD
#define LED_ST_Pin          GPIO_PIN_15
#define LED_ST_GPIO_Port    GPIOD
#define DOME1_Pin           GPIO_PIN_0
#define DOME1_GPIO_Port     GPIOD
#define DOME2_Pin           GPIO_PIN_1
#define DOME2_GPIO_Port     GPIOD
#define DOME3_Pin           GPIO_PIN_2
#define DOME3_GPIO_Port     GPIOD
#define DOME4_Pin           GPIO_PIN_3
#define DOME4_GPIO_Port     GPIOD
#define DOME5_Pin           GPIO_PIN_4
#define DOME5_GPIO_Port     GPIOD
#define DOME6_Pin           GPIO_PIN_5
#define DOME6_GPIO_Port     GPIOD
#define SOS_KEY_Pin         GPIO_PIN_6
#define SOS_KEY_GPIO_Port   GPIOD
#define PTT_KEY_Pin         GPIO_PIN_7
#define PTT_KEY_GPIO_Port   GPIOD
#define FLASH_ON_Pin        GPIO_PIN_8
#define FLASH_ON_GPIO_Port  GPIOB
#define VDD_3_3V_RF_Pin     GPIO_PIN_0
#define VDD_3_3V_RF_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
