/**
  ******************************************************************************
  * @file    IAP/IAP_Main/Src/flash_if.c 
  * @author  MCD Application Team
  * @brief   This file provides all the memory related operation functions.
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

/** @addtogroup STM32F2xx_IAP_Main
  * @{
  */


#include <stdio.h>			//	printf()

#include <stdint.h>			//	uint32_t

#include <string.h>			//	memset()

#include "typedef.h"			//	uint32_t, ...
#include "compiler_defs.h"		//	U8,



/* Includes ------------------------------------------------------------------*/
#include "flash_if.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint32_t GetSector(uint32_t Address);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Unlocks Flash for write access
  * @param  None
  * @retval None
  */
void FLASH_If_Init(void)
{ 
  HAL_FLASH_Unlock(); 

  /* Clear pending flags (if any) */  
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                         FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
}

/**
  * @brief  This function does an erase of all user flash area
  * @param  StartSector: start of user flash area
  * @retval 0: user flash area successfully erased
  *         1: error occurred
  */
uint32_t FLASH_If_Erase(uint32_t StartSector)
{
  uint32_t UserStartSector;
  uint32_t SectorError;
  FLASH_EraseInitTypeDef pEraseInit;

  /* Unlock the Flash to enable the flash control register access *************/ 
  FLASH_If_Init();
  
  /* Get the sector where start the user flash area */
  UserStartSector = GetSector(StartSector);
  
  pEraseInit.TypeErase = TYPEERASE_SECTORS;
  pEraseInit.Sector = UserStartSector;
  pEraseInit.NbSectors = 10;
  pEraseInit.VoltageRange = VOLTAGE_RANGE_3;
    
  if (HAL_FLASHEx_Erase(&pEraseInit, &SectorError) != HAL_OK)
  {
     /* Error occurred while page erase */
     return (uint32_t)(1);
  }
  
  return (uint32_t)(0);
}

//========================================================================
uint32_t FLASH_If_EraseSectors(uint32_t StartSector, uint32_t nSectorNum)
//========================================================================
{
  uint32_t UserStartSector;
  uint32_t SectorError;
  FLASH_EraseInitTypeDef pEraseInit;

  /* Unlock the Flash to enable the flash control register access *************/
  FLASH_If_Init();

  /* Get the sector where start the user flash area */
  UserStartSector = GetSector(StartSector);

  pEraseInit.TypeErase = TYPEERASE_SECTORS;
  pEraseInit.Sector = UserStartSector;
  pEraseInit.NbSectors = nSectorNum;
  pEraseInit.VoltageRange = VOLTAGE_RANGE_3;

  if (HAL_FLASHEx_Erase(&pEraseInit, &SectorError) != HAL_OK)
  {
     /* Error occurred while page erase */
     return (uint32_t)(1);
  }

  return (uint32_t)(0);
}

/**
  * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
  * @note   After writing data buffer, the flash content is checked.
  * @param  FlashAddress: start address for writing data buffer
  * @param  Data: pointer on data buffer
  * @param  DataLength: length of data buffer (unit is 32-bit word)   
  * @retval 0: Data successfully written to Flash memory
  *         1: Error occurred while writing data in Flash memory
  *         2: Written Data in flash memory is different from expected one
  */
uint32_t FLASH_If_Write(uint32_t FlashAddress, uint32_t* Data ,uint32_t DataLength)
{
  uint32_t i = 0;

  uint32_t *spDate = (uint32_t *)Data;

  for (i = 0;
		  (
			((i < DataLength) != 0) &&
		    (FlashAddress <= ((uint32_t)USER_FLASH_END_ADDRESS-4))
		   )
		    ; i++)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */ 
    if (HAL_FLASH_Program((uint32_t)TYPEPROGRAM_WORD,(uint32_t) FlashAddress, *(uint64_t*)spDate[i]) == HAL_OK)
    {
     /* Check the written value */

     // if (*(uint32_t*)FlashAddress != *(uint32_t*)(Data+i))
    	if (*(uint32_t*)FlashAddress != *(uint32_t*)spDate[i])
      {
        /* Flash content doesn't match SRAM content */
        return (uint32_t)(FLASHIF_WRITINGCTRL_ERROR);
      }
      /* Increment FLASH destination address */
      FlashAddress += 4;
    }
    else
    {
      /* Error occurred while writing data in Flash memory */
      return (uint32_t)(FLASHIF_WRITING_ERROR);
    }
  }

  return (uint32_t)(FLASHIF_OK);
}

/**
  * @brief  Returns the write protection status of user flash area.
  * @param  None
  * @retval 0: No write protected sectors inside the user flash area
  *         1: Some sectors inside the user flash area are write protected
  */
uint16_t FLASH_If_GetWriteProtectionStatus(void)
{
  uint32_t ProtectedSECTOR = 0xFFF;
  FLASH_OBProgramInitTypeDef OptionsBytesStruct;

  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();

  /* Check if there are write protected sectors inside the user flash area ****/
  HAL_FLASHEx_OBGetConfig(&OptionsBytesStruct);

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASH_Lock();

  /* Get pages already write protected ****************************************/
  ProtectedSECTOR = ~(OptionsBytesStruct.WRPSector) & FLASH_SECTOR_TO_BE_PROTECTED;

  /* Check if desired pages are already write protected ***********************/
  if(ProtectedSECTOR != 0)
  {
    /* Some sectors inside the user flash area are write protected */
    return (uint16_t)FLASHIF_PROTECTION_WRPENABLED;
  }
  else
  { 
    /* No write protected sectors inside the user flash area */
    return (uint16_t)FLASHIF_PROTECTION_NONE;
  }
}

/**
  * @brief  Gets the sector of a given address
  * @param  Address: Flash address
  * @retval The sector of a given address
  */
static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_SECTOR_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_SECTOR_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_SECTOR_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_SECTOR_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_SECTOR_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_SECTOR_10;  
  }
  else /*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_SECTOR_11;  
  }
  return sector;
}

/**
  * @brief  Configure the write protection status of user flash area.
  * @param  modifier DISABLE or ENABLE the protection
  * @retval HAL_StatusTypeDef HAL_OK if change is applied.
  */
HAL_StatusTypeDef FLASH_If_WriteProtectionConfig(uint32_t modifier)
{
  uint32_t ProtectedSECTOR = 0xFFF;
  FLASH_OBProgramInitTypeDef config_new, config_old;
  HAL_StatusTypeDef result = HAL_OK;
  
  /* Get pages write protection status ****************************************/
  HAL_FLASHEx_OBGetConfig(&config_old);

  /* The parameter says whether we turn the protection on or off */
  config_new.WRPState = modifier;

  /* We want to modify only the Write protection */
  config_new.OptionType = OPTIONBYTE_WRP;
  
  /* No read protection, keep BOR and reset settings */
  config_new.RDPLevel = OB_RDP_LEVEL_0;
  config_new.USERConfig = config_old.USERConfig;  
  /* Get pages already write protected ****************************************/
  ProtectedSECTOR = config_old.WRPSector | FLASH_SECTOR_TO_BE_PROTECTED;

  /* Unlock the Flash to enable the flash control register access *************/ 
  HAL_FLASH_Unlock();

  /* Unlock the Options Bytes *************************************************/
  HAL_FLASH_OB_Unlock();
  
  config_new.WRPSector    = ProtectedSECTOR;
  result = HAL_FLASHEx_OBProgram(&config_new);
  
  return result;
}

//========================================================================
uint32_t	FLASH_If_FindLastData	( uint32_t baseAddr, uint32_t endAddr )
//========================================================================
{
	//	해당영역의 마지막 Data를 찾는다.
	//	Flash 영역 Binary Data Size 확인용.
	printf( "%s(%d)\n", __func__, __LINE__ );

	uint32_t findAddr;

	uint32_t	nFound = 0;

	for( findAddr = endAddr; findAddr > baseAddr; findAddr -= 4 )
	{
		if( *(__IO uint32_t*)findAddr != 0xFFFFFFFF )
		{
			//	Found Last Valid Data.
			nFound = 1;
			break;
		}
	}

	if ( nFound == 0 )
	{
		return (uint32_t)0;		//	Not Found
	}
	else
	{
		return (uint32_t)(findAddr - baseAddr) + 4;
	}
}

//========================================================================
uint32_t	FLASH_If_GetBootSize	( void )
//========================================================================
{
	printf( "%s(%d)\n", __func__, __LINE__ );

	return FLASH_If_FindLastData( ADDR_FLASH_BOOT, (ADDR_FLASH_CONF - 4) );
}

//========================================================================
uint32_t	FLASH_If_GetAppSize		( void )
//========================================================================
{
	printf( "%s(%d)\n", __func__, __LINE__ );

	return FLASH_If_FindLastData( ADDR_FLASH_APP, (ADDR_FLASH_IMGBOOT - 4) );
}


/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
