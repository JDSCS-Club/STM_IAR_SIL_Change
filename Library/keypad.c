/*------------------------------------------------------------------------------------------
	Project			: RFM
	Description		:

	Writer			: $Author: zlkit $
	Revision		: $Rev: 1891 $
	Date			: 2019. 10.
	Copyright		: Piranti Corp.	( sw@piranti.co.kr )
	 
	Revision History 
	1. 2020. 02.	: Created
-------------------------------------------------------------------------------------------*/

//========================================================================
// Header

//#include <stdarg.h>
#include <stdio.h>			//	printf()

#include <stdint.h>			//	uint32_t

#include <string.h>			//	memset()

#include "typedef.h"			//	uint32_t, ...
#include "compiler_defs.h"		//	U8,

#include <stdio.h>

#include "main.h"				//	DOME_GPIO_Port, ...

#include "rfm.h"				//	g_nSpkLevel, ...

#include "keypad.h"

#include "Adafruit_SSD1306.h"	//	OLED Display

#include "menu.h"				//	g_bEnMenuMaint

#include "audio.h"

//#include "audio.h"				//	Audio Function

//========================================================================
// Define


//========================================================================
// Function

static uint8_t s_btnStat[9] = { 0, };	//	Default ( 1 - pull-up )

//========================================================================
uint8_t	GetKey( uint8_t eKey )
//========================================================================
{
	return (uint8_t)(s_btnStat[eKey]);
}


//========================================================================
void GetKeyStat( uint8_t *btnStat )
//========================================================================
{
	//	Pull-Up ( Active Low )

	if(( HAL_GPIO_ReadPin( DOME1_GPIO_Port, DOME1_Pin ) == 0 ))
	{
		btnStat[0] = 1;;	//	Menu
	}

	if(( HAL_GPIO_ReadPin( DOME2_GPIO_Port, DOME2_Pin ) == 0 ))
	{
		btnStat[1] = 1 ;	//	Up
	}

	if(( HAL_GPIO_ReadPin( DOME3_GPIO_Port, DOME3_Pin )== 0 ))
	{
		btnStat[2] = 1;	//	OK
	}

	if(( HAL_GPIO_ReadPin( DOME4_GPIO_Port, DOME4_Pin )== 0 ))
	{
		btnStat[3] = 1;	//	Light
	}

	if(( HAL_GPIO_ReadPin( DOME5_GPIO_Port, DOME5_Pin )== 0 ))
	{
		btnStat[4] = 1;	//	Down
	}

	if(( HAL_GPIO_ReadPin( DOME6_GPIO_Port, DOME6_Pin )== 0 ))
	{
		btnStat[5] = 1;	//	Vol
	}

	if(( HAL_GPIO_ReadPin( PTT_KEY_GPIO_Port, PTT_KEY_Pin )== 0 ))
	{
		btnStat[6] = 1;
	}

	if(( HAL_GPIO_ReadPin( SOS_KEY_GPIO_Port, SOS_KEY_Pin )== 0 ))
	{
		btnStat[7] = 1;
	}


		//	Pull-Down ( Active High )
	btnStat[8] = ( HAL_GPIO_ReadPin( ON_OFF_KEY_GPIO_Port, ON_OFF_KEY_Pin ) );


}

#include <string.h>		//	memcmp()

//========================================================================
void LoopProcKey ( uint32_t tickCurr )
//========================================================================
{
	//========================================================================
	static uint32_t tickBase = 0;
	uint8_t 	btnStat[9];

	//    if( ( HAL_GetTick() - tickBase ) >= 1000 )
	if ( ( tickCurr - tickBase ) >= 100 )
	{
		//========================================================================
		//  Period : 100 ms

		//========================================================================
		//	Key 값 얻기.
		GetKeyStat( btnStat );

		if ( memcmp( s_btnStat, btnStat, sizeof( btnStat ) ) != 0 )
		{
			//	Key Value Changed.
//			int i;
//			printf("[s_btnStat] ");
//			for( i = 0; i < 9; i++ ) printf("%d ", s_btnStat[i]);
//			printf("\n");
//			printf("[btnStat] ");
//			for( i = 0; i < 9; i++ ) printf("%d ", btnStat[i]);
//			printf("\n");

			if ( s_btnStat[0] != btnStat[0] )
			{
				KeyMenu		( btnStat[0] );	//	DOME1
			}
			if ( s_btnStat[1] != btnStat[1] )
			{
				KeyUp		( btnStat[1] );	//	DOME2
			}
			if ( s_btnStat[2] != btnStat[2] )
			{
				KeyOK		( btnStat[2] );	//	DOME3
			}
			if ( s_btnStat[3] != btnStat[3] )
			{
				KeyLight	( btnStat[3] );	//	DOME4
			}
			if ( s_btnStat[4] != btnStat[4] )
			{
				KeyDown		( btnStat[4] );	//	DOME5
			}
			if ( s_btnStat[5] != btnStat[5] )
			{
				KeyVol		( btnStat[5] );	//	DOME6

			}
			if ( s_btnStat[6] != btnStat[6] )
			{
				KeyPtt		( btnStat[6] );	//	PTT
			}
			if ( s_btnStat[7] != btnStat[7] )
			{
				KeySos		( btnStat[7] );	//	SOS
			}
			if ( s_btnStat[8] != btnStat[8] )
			{
				KeyPwrOnOff	( btnStat[8] );	//	ON/OFF
			}

			//	값 저장.
			memcpy( s_btnStat, btnStat, sizeof( btnStat ) );
		}

		tickBase = tickCurr;
	}

	//========================================================================
	//	* [송신기][MENU] : 유지보수 메뉴 진입 기능 추가.
	//		- [OK]버튼을 누른상태에서 [MENU]버튼을 3초간 누를 경우 Maintance모드로 진입함.

	static uint32_t tickBase2 = 0;

	if ( ( tickCurr - tickBase2 ) >= (1000 & IsMenuMaint()) )
	{
		//	Period : 1 sec
		static uint8_t s_cntKeyOkMenu = 0;
		if ( (s_btnStat[eKeyOk] != 0) && (s_btnStat[eKeyMenu] != 0) )
		{
			s_cntKeyOkMenu++;
		}
		else
		{
			s_cntKeyOkMenu = 0;
		}

		if ( s_cntKeyOkMenu > 3 )	//	3초 이상 누를 경우.
		{
			EnableMenuMaint((uint8_t) 1 );
		}

		tickBase2 = tickCurr;
	}

	//========================================================================


#if defined(USE_FREERTOS)
	osDelay( 1 );		//	1 msec
#else
//        HAL_Delay( 1 );
#endif
}

//========================================================================
//		KeyPad ( Dome Button )
//========================================================================

//========================================================================
void KeyMenu( uint8_t bValue )
//========================================================================
{
	//========================================================================
	//	bValue : 0(Up) / 1(Down)
	printf( "%s(%d) - %d\n", __func__, __LINE__, bValue );

	if ( bValue != 0 )
	{
//		LCDMenu();
		ProcBtnMenu();
	}
}

//========================================================================
void KeyOK( uint8_t bValue )
//========================================================================
{
	//========================================================================
	//	bValue : 0(Up) / 1(Down)
	printf( "%s(%d) - %d\n", __func__, __LINE__, bValue );

	if ( bValue != 0)
	{
		ProcBtnOK();
	}
}


//========================================================================
void KeyLight( uint8_t bValue )
//========================================================================
{
	//========================================================================
	//	bValue : 0(Up) / 1(Down)
	printf( "%s(%d) - %d\n", __func__, __LINE__, bValue );

	//========================================================================
	//	Light On/Off Toggle
	static uint8_t bOnOff = 0;

	//========================================================================
	//	GPIO제어.
	if ( bValue != 0 )
	{
		if ( bOnOff == 0 )
		{
			//	Flash Light On
			HAL_GPIO_WritePin( FLASH_ON_GPIO_Port, FLASH_ON_Pin, GPIO_PIN_SET );

			LCDLight( 1 );
			bOnOff = 1;
		}
		else
		{
			//	Flash Light Off
			HAL_GPIO_WritePin( FLASH_ON_GPIO_Port, FLASH_ON_Pin, GPIO_PIN_RESET );

			LCDLight( 0 );
			bOnOff = 0;
		}
	}
}

//========================================================================
void KeyUp( uint8_t bValue )
//========================================================================
{
	//========================================================================
	//	bValue : 0(Up) / 1(Down)
	printf( "%s(%d) - %d\n", __func__, __LINE__, bValue );

	if( bValue != 0)
	{
		ProcBtnUp();
	}
}

//========================================================================
void KeyDown( uint8_t bValue )
//========================================================================
{
	//========================================================================
	//	bValue : 0(Up) / 1(Down)
	printf( "%s(%d) - %d\n", __func__, __LINE__, bValue );

	if( bValue != 0)
	{
		ProcBtnDown();
	}
}

//========================================================================
void KeyVol( uint8_t bValue )
//========================================================================
{
	//========================================================================
	//	bValue : 0(Up) / 1(Down)
	printf( "%s(%d) - %d\n", __func__, __LINE__, bValue );

	if( bValue != 0 )
	{

		g_nSpkLevel = ( g_nSpkLevel + 1 ) % 4;  //  0, 1, 2, 3

		//========================================================================
		SetSpkVol( g_nSpkLevel );
		//========================================================================

		if ( g_nSpkLevel != 0 )
		{
			//	RFM SPK On
//				HAL_GPIO_WritePin( SPK_ON_GPIO_Port, SPK_ON_Pin, GPIO_PIN_SET );
			//	RFM SPK Off
//			HAL_GPIO_WritePin( SPK_ON_GPIO_Port, SPK_ON_Pin, GPIO_PIN_RESET );
			RFM_Spk((uint8_t)0);

			LCDSpeaker( g_nSpkLevel );
		}
		else
		{
			//	RFM SPK Off
//			HAL_GPIO_WritePin( SPK_ON_GPIO_Port, SPK_ON_Pin, GPIO_PIN_RESET );
			RFM_Spk((uint8_t)0);

			LCDSpeaker( (uint8_t)0 );
		}
	}
}

//========================================================================
//		Side Button
//========================================================================


//========================================================================
void KeyPtt( uint8_t bValue )
//========================================================================
{
	//========================================================================
#if defined( USE_TEST_PTT_AUDIO_LOOP )

	//	Audio Loopback Test
	KeyTestLoopback( bValue );

	return ;
#endif
	//========================================================================

	//========================================================================
	//	bValue : 0(Up) / 1(Down)
	printf( "%s(%d) - %d\n", __func__, __LINE__, bValue );

	//	송신기 -> 수신기	:	방송

	if ( bValue != 0)
	{
#if defined(USE_CH_ISO_DEV)
		SetChPA( GetChNearRFM() );		//	가장 가까운 수신기 설정.

		SetChPARFT( GetChNearRFT() );	//	가까운 송신기 설정.
#endif

		LCDSetCursor( 20, 13 );

		if ( IsMenuMaint() )
		{
			//	Maint Mode : 송신채널 표시.
			S8 sBuf[20];
			sprintf( sBuf, "방송중...(%d)", GetChPA() );
			LCDPrintf( sBuf );
		}
		else
		{
			LCDPrintf( "방송중..." );
		}

		SetRFMMode( (uint8_t)RFMModeTx );

		//  Green LED On
		HAL_GPIO_WritePin ( LED_ON_A_GPIO_Port, LED_ON_A_Pin, GPIO_PIN_SET ); //  Green LED

		//	방송 - 시작
		SendPA((uint8_t) 1 );		//	SendRF - Send PA ( 송신기 -> 수신기 )
	}
	else
	{
		//========================================================================
		//  편성 : XXX
		UpdateLCDMain();

		SetRFMMode( (uint8_t)RFMModeNormal );

#if defined(USE_CH_ISO_DEV)
		SetChPA( GetChNearRFM() );		//	가장 가까운 수신기 설정.

		SetChPARFT( GetChNearRFT() );	//	가까운 송신기 설정.
#endif

		//  Green LED Off
		HAL_GPIO_WritePin ( LED_ON_A_GPIO_Port, LED_ON_A_Pin, GPIO_PIN_RESET ); //  Green LED

		//	방송 - 종료
		SendPA((uint8_t) 0 );		//	SendRF - Send PA ( 송신기 -> 수신기 )
	}
}


//========================================================================
void KeySos( uint8_t bValue )
//========================================================================
{
	//	bValue : 0(Up) / 1(Down)
	printf( "%s(%d) - %d\n", __func__, __LINE__, bValue );

	//	송신기 -> 송신기	:	통화

	if ( bValue != 0 )
	{
#if defined(USE_CH_ISO_DEV)
		SetChPARFT( GetChNearRFT() );	//	가까운 송신기 설정.

		SetChPA( GetChNearRFM() );		//	가장 가까운 수신기 설정.
#endif

		//	송신중
		LCDSetCursor( 20, 13 );
		LCDPrintf( "통화중..." );

		SetRFMMode((uint8_t) RFMModeTx );

		//	통화 - 시작
		SendCall((uint8_t) CtrlStart );		//	SendRF - Send Call ( 송신기 -> 송신기 )
	}
	else
	{
#if defined(USE_CH_ISO_DEV)
		SetChPARFT( GetChNearRFT() );	//	가까운 송신기 설정.

		SetChPA( GetChNearRFM() );		//	가장 가까운 수신기 설정.
#endif

		//    편성 : 100
		UpdateLCDMain();
//		LCDSetCursor( 20, 13 );
//		LCDPrintf( "편성 : 100" );

		SetRFMMode( (uint8_t)RFMModeNormal );

		//	통화 - 종료
		SendCall( (uint8_t)CtrlStop );		//	SendRF - Send Call ( 송신기 -> 송신기 )
	}
}


//========================================================================
//		Power Button
//========================================================================

//========================================================================
void	KeyPwrOnOff		( uint8_t bValue )
//========================================================================
{
	//	bValue : 0(Up) / 1(Down)
	printf( "%s(%d) - %d\n", __func__, __LINE__, bValue );

	static uint8_t bPowerOn = 0;

	if ( bValue != 0)
	{
		bPowerOn = 1;
	}
	else
	{
		if( bPowerOn != 0)
		{
			//========================================================================
			//	Power Off
			printf( "%s(%d) - Power Off\n", __func__, __LINE__  );

			HAL_GPIO_WritePin( ON_OFF_EN_GPIO_Port, ON_OFF_EN_Pin, GPIO_PIN_RESET );
		}
	}
}

//========================================================================


//========================================================================
//		Power Button
//========================================================================


void	KeyTestLoopback( uint8_t bValue )
{

#if 1

	//	Speex Loopback Test
	//	Audio Loopback Proc

	if ( bValue != 0 )
	{
		//	송신중
		LCDSetCursor( 10, 13 );
		LCDPrintf( "Audio Loop" );

		//	Spk On
//		LCDSpeaker( 1 );
//		LCDSpeaker( 1 );

		HAL_GPIO_WritePin( SPK_ON_GPIO_Port, SPK_ON_Pin, GPIO_PIN_SET );

		//	Codec Loopback On
//		AudioRxTxLoop();
		AudioDMALoopback();

		//	Codec Loopback On
//		AudioPlayDMASine();

//DEL		AudioLoopbackDMASpeex();
		//	-> Speex는 성능문제로 사용 X
//		AudioLoopbackDMACompress();
	}
	else
	{
		//    편성 : 100
		UpdateLCDMain();
//		LCDSetCursor( 20, 13 );
//		LCDPrintf( "편성 : 100" );

		//	Spk Off
//		LCDSpeaker( 0 );

		HAL_GPIO_WritePin( SPK_ON_GPIO_Port, SPK_ON_Pin, GPIO_PIN_RESET );

		//	Codec Loopback Off
		AudioStop();
	}
#endif

}


//========================================================================
