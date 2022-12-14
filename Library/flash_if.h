/**
  ******************************************************************************
  * @file    IAP/IAP_Main/Inc/flash_if.h 
  * @author  MCD Application Team
  * @brief   This file provides all the headers of the flash_if functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_IF_H
#define __FLASH_IF_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbyte */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbyte */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbyte */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbyte */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbyte */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbyte */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbyte */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbyte */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbyte */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbyte */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbyte */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbyte */

/* Error code */
enum 
{
  FLASHIF_OK = 0,
  FLASHIF_ERASEKO,
  FLASHIF_WRITINGCTRL_ERROR,
  FLASHIF_WRITING_ERROR
};
  
enum{
  FLASHIF_PROTECTION_NONE         = 0,
  FLASHIF_PROTECTION_PCROPENABLED = 0x1,
  FLASHIF_PROTECTION_WRPENABLED   = 0x2,
  FLASHIF_PROTECTION_RDPENABLED   = 0x4,
};

/* Define the address from where user application will be loaded.
   Note: the 1st sector 0x08000000-0x08003FFF is reserved for the IAP code */

//========================================================================
//			FLASH Address Define
//========================================================================
#define ADDR_FLASH_BOOT		((uint32_t)0x08000000)	//	64 KB	| Bootloader Address
#define ADDR_FLASH_CONF		((uint32_t)0x08010000)	//	64 KB	| Configuration Address
#define ADDR_FLASH_APP		((uint32_t)0x08020000)	//	384 KB	| Application Address

#define ADDR_FLASH_IMGBOOT	((uint32_t)0x08080000)	//	64 KB	| Boot Image
#define ADDR_FLASH_RESV		((uint32_t)0x08090000)	//	64 KB	| Reserved
#define ADDR_FLASH_IMGAPP	((uint32_t)0x080A0000)	//	384 KB	| App Image

//========================================================================
//			FLASH Size Define
#define SIZE_FLASH_BOOT		(ADDR_FLASH_CONF - ADDR_FLASH_BOOT + 1)		//	Bootloader Size
#define SIZE_FLASH_APP		(ADDR_FLASH_IMGBOOT - ADDR_FLASH_APP + 1)	//	Application Size

#define SIZE_FLASH_BOOTAPP	(ADDR_FLASH_IMGBOOT - ADDR_FLASH_BOOT)		//	Boot + App Size

//========================================================================

/* End of the Flash address */
#define USER_FLASH_END_ADDRESS        0x080FFFFF
/* Define the user application size */
#define USER_FLASH_SIZE   (USER_FLASH_END_ADDRESS - ADDR_FLASH_APP + 1)

/* Define bitmap representing user flash area that could be write protected (check restricted to pages 8-39). */
#define FLASH_SECTOR_TO_BE_PROTECTED (OB_WRP_SECTOR_0 | OB_WRP_SECTOR_1 | OB_WRP_SECTOR_2 | OB_WRP_SECTOR_3 |\
                                      OB_WRP_SECTOR_4 | OB_WRP_SECTOR_5 | OB_WRP_SECTOR_6 | OB_WRP_SECTOR_7 |\
                                      OB_WRP_SECTOR_8 | OB_WRP_SECTOR_9 | OB_WRP_SECTOR_10 | OB_WRP_SECTOR_11 )

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void				FLASH_If_Init(void);
uint32_t			FLASH_If_Erase(uint32_t StartSector);

uint32_t 			FLASH_If_EraseSectors(uint32_t StartSector, uint32_t nSectorNum);

uint32_t			FLASH_If_Write(uint32_t FlashAddress, uint32_t* Data, uint32_t DataLength);
uint16_t			FLASH_If_GetWriteProtectionStatus(void);
HAL_StatusTypeDef	FLASH_If_WriteProtectionConfig(uint32_t modifier);

uint32_t			FLASH_If_FindLastData	( uint32_t baseAddr, uint32_t endAddr );

uint32_t			FLASH_If_GetBootSize	( void );
uint32_t			FLASH_If_GetAppSize		( void );

#endif  /* __FLASH_IF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
