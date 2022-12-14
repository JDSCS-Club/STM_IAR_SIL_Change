/*!
 * File:
 *  radio_hal.h
 *
 * Description:
 *  This file contains RADIO HAL.
 *
 * Silicon Laboratories Confidential
 * Copyright 2011 Silicon Laboratories, Inc.
 */

#ifndef _RADIO_HAL_H_
#define _RADIO_HAL_H_

                /* ======================================= *
                 *              I N C L U D E              *
                 * ======================================= */

#include "typedef.h"			//	U8
#include "si446x_defs.h"		//	DRIVERS_EXTENDED_SUPPORT

                /* ======================================= *
                 *          D E F I N I T I O N S          *
                 * ======================================= */

                /* ======================================= *
                 *     G L O B A L   V A R I A B L E S     *
                 * ======================================= */

                /* ======================================= *
                 *  F U N C T I O N   P R O T O T Y P E S  *
                 * ======================================= */


extern uint8_t RF_NIRQ;

void radio_hal_AssertShutdown(void);
void radio_hal_DeassertShutdown(void);
void radio_hal_ClearNsel(void);
void radio_hal_SetNsel(void);
BIT radio_hal_NirqLevel(void);

void radio_hal_SpiWriteByte(U8 byteToWrite);
U8 radio_hal_SpiReadByte(void);

void radio_hal_SpiWriteData(U8 byteCount, U8* pData);
void radio_hal_SpiReadData(U8 byteCount, U8* pData);

#ifdef DRIVERS_EXTENDED_SUPPORT
  BIT radio_hal_Gpio0Level(void);
  BIT radio_hal_Gpio1Level(void);
  BIT radio_hal_Gpio2Level(void);
  BIT radio_hal_Gpio3Level(void);
#endif

#endif //_RADIO_HAL_H_
