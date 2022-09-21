/*------------------------------------------------------------------------------------------
	Project			: It Library
	Description		: 

	Writer			: $Author: zlkit $
	Revision		: $Rev: 1891 $
	Date			: 2019. 10.
	Copyright		: Piranti Corp.	( sw@piranti.co.kr )
	 
	Revision History 
	1. 2019. 10.	: Created
-------------------------------------------------------------------------------------------*/

//========================================================================
// Header

#include <stdio.h>			//	printf()

#include <stdint.h>			//	uint32_t

#include <string.h>			//	memset()

#include "typedef.h"			//	uint32_t, ...
#include "compiler_defs.h"		//	U8,

#include "upgrade.h"

#include "rfm.h"				//	g_idxTrainSet

#include "radio.h"				//	pRadioConfiguration

#include "flash_if.h"			//	ADDR_FLASH_BOOT

#include "main.h"				//	hiwdg

//========================================================================
// Define

static uint16_t s_bUpgrRetry = 0;		//	Upgrade Retry

//========================================================================
// Function

//========================================================================
void SetUpgrReTry( uint16_t _bUpgrRetry )
//========================================================================
{
	s_bUpgrRetry = _bUpgrRetry;
}

//========================================================================
uint16_t GetUpgrReTry( void )
//========================================================================
{
	return (uint16_t)s_bUpgrRetry;
}


//========================================================================
uint32_t UpgrSendImage		( uint32_t nAddrBase, uint32_t nSizeImage )
//========================================================================
{
	//	송신기 Upgrade 명령.
	printf( "%s(%d) - baseAddr(0x%08X) / size(%d)\n", __func__, __LINE__, nAddrBase, nSizeImage );

	uint32_t	nAddrTarget;

	uint8_t		sBuf[100];
	uint32_t	nSize;

	//========================================================================
	//	0x0800 0000 ~ 0x0807 FFFF	:	Bootloader + Application
	//========================================================================
	//	0x0808 0000 ~ 0x080F FFFF	:	Upgrade Image
	//========================================================================
	nAddrTarget		=	nAddrBase + 0x80000;// + SIZE_FLASH_BOOTAPP;

	uint32_t i, j;
//	int nTotPkt = ( ( nSizeImage + 49 ) / 50 );
	uint32_t nTotPkt = (uint32_t)( ( (uint32_t)nSizeImage + ((uint32_t)PktUpgrDataSize - 1) ) / (uint32_t)PktUpgrDataSize );

	char	sLCD[100];

	LCDEnableDebug( 0 );	//	LCD - console printf Off

	for ( i = 0; i < nTotPkt; i++ )
	{
		//	Flash Data 전송.
//		memcpy( sBuf, (__IO uint8_t*)(nAddrBase + (i * 50)), 50 );
//		SendUpgrData( nAddrTarget, nTotPkt, i, sBuf, 50 );
		memcpy( &sBuf[0], ( uint8_t *)(nAddrBase + (i * PktUpgrDataSize)),(uint32_t) PktUpgrDataSize );
        
		SendUpgrData( nAddrTarget, (uint16_t)nTotPkt, (uint16_t)i, &sBuf[0], (uint8_t)PktUpgrDataSize );

		//========================================================================
		if ( i == 0 && GetUpgrReTry() == 0 )
		{
			//	첫번째 패킷 전송후  Flash Erase Delay : 3 sec
			__HAL_IWDG_RELOAD_COUNTER(&hiwdg);
			sprintf( sLCD, "Upgr:FL Erase", i, nTotPkt );
			LCDSetCursor( 1, 13 );
			LCDPrintf( sLCD );
//			HAL_Delay( 3000 );		//	sleep 3 sec
			for( j = 0; j < 7; j++ )	//	sleep 7 sec
			{
				HAL_Delay( (uint32_t)1000 );
				__HAL_IWDG_RELOAD_COUNTER(&hiwdg);	//	Watchdog Re-Flash
			}
		}
		//========================================================================

		//	수신기 Message 표시.
		//	159,596 Byte = 3191 Pkt * 50 Byte
		//	Upgr:[   1 / 3191 ]
		if ( ( i % 10 ) == 0 )
		{
			sprintf( sLCD, "Upgr:[%4d/%4d]", i, nTotPkt );
			LCDSetCursor( 1, 13 );
			LCDPrintf( sLCD );
		}

//		HAL_Delay( 4 );	//	4 msec Delay
//		HAL_Delay( 3 );	//	2 msec Delay
		HAL_Delay( (uint32_t)2 );	//	2 msec Delay

		//========================================================================
		//	Watchdog Reload
		if ( ( i % 50 ) == 0 )
		{
			__HAL_IWDG_RELOAD_COUNTER(&hiwdg);
		}
		//========================================================================
	}

	sprintf( sLCD, "Upgr:[%4d/%4d]", i, nTotPkt );
	LCDSetCursor( 1, 13 );
	LCDPrintf( sLCD );
}


//========================================================================
uint32_t UpgrSendImageBoot	( void )
//========================================================================
{
	//	송신기 Upgrade 명령. - Bootloader
	UpgrSendImage( ADDR_FLASH_BOOT, FLASH_If_GetBootSize() );
}

//========================================================================
uint32_t UpgrSendImageApp	( void )
//========================================================================
{
	//	송신기 Upgrade 명령. - Application
	UpgrSendImage( ADDR_FLASH_APP, FLASH_If_GetAppSize() );
}

//========================================================================
uint8_t cmd_upgrade	( uint8_t argc, char * argv[] )
//========================================================================
{
	//========================================================================
	//	Upgrade 수신측에서 동작.
	//========================================================================
	//	upgrade ch 1	//	Upgrade 채널 변경.
	//	upgrade [1/0]	//	1(Start) / 0(End)

	int nVal = 1;

	printf( "%s(%d)\n", __func__, __LINE__ );

	//========================================================================
	switch ( argc )
	{
	case 2:		sscanf( argv[2], "%d", &nVal );			//	cmd [address] [value]
//    case 2:		sscanf( argv[1], "%d", &nAddr );		//	cmd [address]
		break;
	}

	if ( nVal == 1 )
	{
		//========================================================================
		//	Upgrade Start

		//========================================================================
		//	채널변경. => CH #1
		g_nChRx = ChUpgrDst;		//	Upgrade Channel

		vRadio_StartRX (
			g_nChRx,	//g_idxTrainSet,	//	pRadioConfiguration->Radio_ChannelNumber,
			pRadioConfiguration->Radio_PacketLength );

		//========================================================================
		//	Upgrade시 수신기 조명 점등.
		HAL_GPIO_WritePin ( LIGHT_ON_GPIO_Port, LIGHT_ON_Pin, GPIO_PIN_SET );

		//========================================================================
		//	Log 출력 Off

		//========================================================================
		//	Upgrade Mode
		SetRFMMode( (uint8_t)RFMModeUpgr );		//	Upgrade Mode 설정. ( 상태정보 전송 X )
		//========================================================================
	}
	else if ( nVal == 0 )
	{
		//========================================================================
		//	Normal Mode
		SetRFMMode( (uint8_t)RFMModeNormal );	//	Normal Mode 로 변경
		//========================================================================

		//  RF 수신 Start
		g_nChRx = GetChRx();	//	ChTS1_1 + g_idxTrainSet * 2 + ((g_nCarNo+1) % 2);	// 현재 호차 채널

		vRadio_StartRX(
			g_nChRx,	//g_idxTrainSet,	//		pRadioConfiguration->Radio_ChannelNumber,
			pRadioConfiguration->Radio_PacketLength );
	}
}
//========================================================================

