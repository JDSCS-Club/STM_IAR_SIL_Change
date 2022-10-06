/*------------------------------------------------------------------------------------------
	Project			: RFM ( RF-Module )
	Description		: RFM Protocol Header

	Writer			: $Author: zlkit $
	Revision		: $Rev: 1446 $
	Date			: 2020. 02.
	Copyright		: Piranti Corp.
	 
	Revision History 
	1. 2020. 02.	: Created
-------------------------------------------------------------------------------------------*/

#include <stdio.h>				//	printf()
#include <stdint.h>				//	uint8_t, ...

#include <string.h>				//	memset()

#include "typedef.h"			//	char_t, int32_t, ...

#include "RFMProtocol.h"		//	RFM Protocol

#include "radio.h"				//	vRadio_StartTx_Variable_Packet()

#include "Adafruit_SSD1306.h"	//	LCDPrintf()

#include "main.h"				//	FLASH_ON_Pin / GPIO_PIN_SET / ...

#include "ProcPkt.h"			//	SendPacekt()

#include "version.h"			//	Version Info

#include "rfm.h"				//	g_nManHopping

#include "audio.h"				//	I2S_DMA_LOOP_SIZE

#include "flash_if.h"			//	FLASH_If_Write()

#include "eeprom.h"				//	AddrEEPUpgrMGN1

#include "diag.h"

#include "upgrade.h"

#include "cli.h"

//==========================================================================
//	Define


//==========================================================================
//	Function


//==========================================================================
//		API
//==========================================================================



//==========================================================================
//		Send Packet
//==========================================================================

//========================================================================
void _MakePktHdr	( RFMPkt *pPkt, uint8_t addrSrc, uint8_t addrDest, uint8_t nLen, uint8_t nPktCmd )
//========================================================================
{
#if	defined(USE_HOPPING)

	if ( nPktCmd == PktStat
		|| nPktCmd == PktCmd
		|| nPktCmd == PktUpgr
		)
	{
		//	상태정보의 경우 Seq / ID : 0x00
		pPkt->hdr.bHdrID		=	HdrID1;		//	Header ID #1
		pPkt->hdr.nSeq			=	0x00;		//	Sequence
		pPkt->hdr.nIDFlag		=	0x00;		//	ID Flag
	}
	else
	{
		g_nPktSeq++;
		if ( g_nPktSeq == 0 )
		{
			g_nPktSeq++;
		}

		pPkt->hdr.nSeq			=	g_nPktSeq;			//

		if ( GetDevID() == DevRF900T )
		{
			//	송신기.
			//		송신기의 송/수신반경과 수신기의 송/수신반경의 차이로 
			//		송신기가 상태정보를 수신후에 수신기에 송신을 할때 범위에 도달하지 못하는 경우가 있으므로, 
			//		수신기에서 중계를 할 수 있도록 송신기 ID만 설정하여 송신함.
			pPkt->hdr.nIDFlag		= (uint16_t)	((uint16_t)0x1 << (uint16_t)GetCarNo());	//	송신기는 자신의 ID만 Set하여 전송.
		}
		else
		{
			//	수신기.
			pPkt->hdr.nIDFlag		=	 g_flagRspID;		//
		}
	}

#else

	pPkt->hdr.addrSrc		=	addrSrc;		//	Src Address
	pPkt->hdr.addrDest		=	addrDest;		//	Broadcast
	pPkt->hdr.nLen			=	nLen;			//	Length

#endif

	pPkt->hdr.nPktCmd		=	nPktCmd;		//	Status
}

#if defined(USE_CH_ISO_DEV)		//	장치별 채널분리.

//========================================================================
void _MakePktHdr2	( RFMPkt *pPkt, uint8_t nPktCmd )
//========================================================================
{
	//	상태정보의 경우 Seq / ID : 0x00
	pPkt->hdr2.bHdrID		=	HdrID2;				//	Header ID #1
	pPkt->hdr2.nSrcCh		=	GetChRx();			//	Source Channel
	pPkt->hdr2.nTS			=	GetTrainSetIdx();	//	ID Flag
	pPkt->hdr2.nPktCmd		=	nPktCmd;			//	Status

//	CLEAR_BIT(pPkt->hdr2.nTS, (0x1<<7));
//	SET_BIT(pPkt->hdr2.nTS, (0x1<<6));

#if defined( USE_RFT_REG_TO_RFM )
	//	자신의 송신기 ID Flag 설정.	-	재수신 받지 않음.
	if( GetRFTID() == 1 )
	{
		pPkt->hdr2.bRFT1	=	1;	//	SET_BIT( pPkt->hdr2.nSrcCh, (0x1<<6) );	//
		if( GetChPARFT() != 0 )
		{
			pPkt->hdr2.bRFT2	=	1;	//	송신기에 직접 전송하는경우.
		}
	}
	else if( GetRFTID() == 2 )
	{
		pPkt->hdr2.bRFT2	=	1;	//	SET_BIT( pPkt->hdr2.nSrcCh, (0x1<<7) );//
		if( GetChPARFT() != 0 )
		{
			pPkt->hdr2.bRFT1	=	1;	//	송신기에 직접 전송하는경우.
		}
	}

#endif
}

#endif	//	defined(USE_CH_ISO_DEV)		//	장치별 채널분리.

//==========================================================================
void _MakeRFCmd( RFMPkt	*pPkt, S8 *sCmd, uint8_t nRSSI )
//==========================================================================
{
	printf( "%s(%d)\n", __func__, __LINE__ );

	memset( pPkt, 0, sizeof( RFMPkt ) );

	//========================================================================
	//	Packet Header
	_MakePktHdr( pPkt, (uint8_t)GetDevID(),(uint8_t) 0xFF, (uint8_t)RFPktDataLen,(uint8_t) PktCmd );

	//========================================================================
	//	Command
	pPkt->dat.cmd.nRSSIOver = (int8_t)nRSSI;		//	명령 동작 RSSI 범위.
	strcpy( pPkt->dat.cmd.sCmd, sCmd );		//	명령 전송.

	//========================================================================
}


//========================================================================
void SendStatReq( uint8_t nDestCh )
//========================================================================
{
	if ( GetDbg() )
	{
		printf( "%s(%d)\n", __func__, __LINE__ );
	}

	RFMPkt			stPkt;
	RFMPktStatReq	*pStatReq;

	memset( &stPkt, 0, sizeof( stPkt ) );
	pStatReq = (RFMPktStatReq *)&stPkt.dat.statReq;

	//========================================================================
	//	Packet Header
	_MakePktHdr( &stPkt, (uint8_t)GetDevID(), (uint8_t)0xFF, (uint8_t)sizeof( RFMPktStatReq ),(uint8_t) PktStatReq );

	//========================================================================
	//	Packet Body
	pStatReq->nSrcCh	=	GetChRx();	//	수신받을 채널

	pStatReq->nCarNo	=	GetCarNo();			//	호차번호.
	pStatReq->nTrainNo	=	GetTrainSetIdx();	//	편성번호.

	//========================================================================
	//	Send RF
	SendPktCh( (uint8_t)nDestCh, (U8 *)&stPkt, (uint8_t)(sizeof( RFMPktHdr ) + sizeof( RFMPktStatReq )) );
}

//========================================================================
void SendStat( uint8_t nDestCh )
//========================================================================
{
	//	RF Mode가 RFMModeNormal인 경우.
	//		상태정보 전송.

	if ( GetDbg() )
	{
		printf( "%s(%d)\n", __func__, __LINE__ );
	}

	RFMPkt		stPkt;
	RFMPktStat	*pStat;

	memset( &stPkt, 0, sizeof( stPkt ) );
	pStat = (RFMPktStat *)&stPkt.dat.stat;

	//========================================================================
	//	Packet Header
	_MakePktHdr( &stPkt, (uint8_t)GetDevID(),(uint8_t) 0xFF,(uint8_t) sizeof( RFMPktStat ),(uint8_t) PktStat );

	//========================================================================
	//	Status Data
	pStat->ver_main		=	APP_MAIN_VER;		//	1;
	pStat->ver_sub		=	APP_SUB_VER;		//	0;
	pStat->ver_det		=	APP_DETAIL_VER;		//	0;
	pStat->ver_build	=	APP_BUILD_VER;		//	0;

	pStat->nMagicNum	=	0xAA55;				//	패킷 요류검출용.

	pStat->nCarNo		=	GetCarNo();
	pStat->nDevID		=	GetDevID();

	pStat->nTrainNo		=	GetTrainSetIdx();	//	편성번호.

	pStat->upTime		=	HAL_GetTick();

	pStat->rspID		=	g_flagRspID;		//	Rsp ID Flag

	pStat->nManHop		=	g_nManHopping;		//	Manual Hopping Setting

	pStat->nDevFlag		=	g_nDevFlag;			//	Device Flag : 조명 상태 등.

	pStat->nChRx		=	GetChRx();			//	수신 채널

	//========================================================================
	//	Send RF
#if defined(USE_CH_ISO_DEV)
	//	상태정보는 송신기로 전송.
	uint8_t nCh;

	//========================================================================
	if ( nDestCh == 0 )
	{
		nCh = (uint8_t)ChTx_1;
	}
	else
	{
		nCh = (uint8_t)nDestCh;
	}
	//========================================================================

	SendPktCh((uint8_t)nCh, (U8 *)&stPkt, (uint8_t)(sizeof( RFMPktHdr ) + sizeof( RFMPktStat )) );
#else
	SendPacket( (U8 *)&stPkt, (U8)sizeof( RFMPktHdr ) + sizeof( RFMPktStat ) );
#endif
	//========================================================================
}


//========================================================================
void SendPA( uint8_t nStartStop )
//========================================================================
{
	printf( "%s(%d)\n", __func__, __LINE__ );

	RFMPkt				stPkt;
	RFMPktCtrlPACall	*pPACall;

	memset( &stPkt, 0, sizeof( stPkt ) );
	pPACall = (RFMPktCtrlPACall *)&stPkt.dat.pacall;

	//========================================================================
	//	Packet Header
#if defined(USE_CH_ISO_DEV)
	_MakePktHdr2( &stPkt, (uint8_t)PktCtrlPaCall );
#else
	_MakePktHdr( &stPkt, GetDevID(), 0xFF, sizeof( RFMPktCtrlPACall ), PktCtrlPaCall );
#endif

	//========================================================================
	//	Status Data
	pPACall->nStartStop		=	nStartStop;

	pPACall->nTypePACall	=	CtrlPA;

	//========================================================================
	//	Send RF

#if defined(USE_CH_ISO_DEV)

	if ( GetChPARFT() != 0 )
	{
		//	송신기에 전송.
		SendPktCh( (uint8_t)GetChPARFT(), (U8 *)&stPkt,
			(uint8_t)(sizeof( RFMPktHdr ) + sizeof( RFMPktCtrlPACall )) );
	}

	//	수신기에 전송
	SendPktCh( (uint8_t)GetChPA(), (U8 *)&stPkt,
			(uint8_t)(sizeof( RFMPktHdr ) + sizeof( RFMPktCtrlPACall )) );

#else
	SendPacket( (U8 *)&stPkt, (U8)sizeof( RFMPktHdr ) + sizeof( RFMPktCtrlPACall ) );
#endif

	//========================================================================
}


//========================================================================
void SendCall( uint8_t nStartStop )
//========================================================================
{
	printf( "%s(%d)\n", __func__, __LINE__ );

	RFMPkt			stPkt;
	RFMPktCtrlPACall	*pPACall;

	memset( &stPkt, 0, sizeof( stPkt ) );
	pPACall = (RFMPktCtrlPACall *)&stPkt.dat.pacall;

	//========================================================================
	//	Packet Header
#if defined(USE_CH_ISO_DEV)
	_MakePktHdr2( &stPkt, (uint8_t)PktCtrlPaCall );
#else
	_MakePktHdr( &stPkt, GetDevID(), 0xFF, sizeof( RFMPktCtrlPACall ), PktCtrlPaCall );
#endif

	//========================================================================
	//	Status Data
	pPACall->nStartStop		=	nStartStop;

	pPACall->nTypePACall	=	CtrlCall;

	//========================================================================
	//	Send RF

#if defined(USE_CH_ISO_DEV)

	if ( GetChPARFT() != 0 )
	{
		//	송신기에 직접 전송.
		SendPktCh( (uint8_t)GetChPARFT(), (U8 *)&stPkt,
				(uint8_t)(sizeof( RFMPktHdr ) + sizeof( RFMPktCtrlPACall )) );
	}
	else
	{
		//	수신기를 통해 전송.
		SendPktCh( (uint8_t)GetChPA(),	//GetChOtherRFT(),
				(U8 *)&stPkt,
				(uint8_t)(sizeof( RFMPktHdr ) + sizeof( RFMPktCtrlPACall )) );
	}

#else

	SendPacket( (U8 *)&stPkt, (U8)sizeof( RFMPktHdr ) + sizeof( RFMPktCtrlPACall ) );

#endif

	//========================================================================
}

//========================================================================
void SendOCCPA( uint8_t nStartStop )
//========================================================================
{
	printf( "%s(%d)\n", __func__, __LINE__ );

	RFMPkt				stPkt;
	RFMPktCtrlPACall	*pPACall;

	memset( &stPkt, 0, sizeof( stPkt ) );
	pPACall = (RFMPktCtrlPACall *)&stPkt.dat.pacall;

	//========================================================================
	//	Packet Header
#if defined(USE_CH_ISO_DEV)
	_MakePktHdr2( &stPkt, (uint8_t)PktCtrlPaCall );
#else
	_MakePktHdr( &stPkt, GetDevID(), 0xFF, sizeof( RFMPktCtrlPACall ), PktCtrlPaCall );
#endif

	//========================================================================
	//	Status Data
	pPACall->nStartStop		=	nStartStop;

	pPACall->nTypePACall	=	CtrlOccPa;

	//========================================================================
	//	Send RF

#if defined(USE_CH_ISO_DEV)

	if ( GetChPARFT() != 0 )
	{
		//	송신기에 전송.
		SendPktCh( (uint8_t)GetChPARFT(), (U8 *)&stPkt,
				(uint8_t)(sizeof( RFMPktHdr ) + sizeof( RFMPktCtrlPACall )) );
	}

	//	수신기에 전송
	SendPktCh( (uint8_t)GetChPA(), (U8 *)&stPkt,
			(uint8_t)(sizeof( RFMPktHdr ) + sizeof( RFMPktCtrlPACall ) ));

#else
	SendPacket( (U8 *)&stPkt, (U8)sizeof( RFMPktHdr ) + sizeof( RFMPktCtrlPACall ) );
#endif

	//========================================================================
}


//========================================================================
void SendLight( uint8_t nOnOff )
//========================================================================
{
	printf( "%s(%d)\n", __func__, __LINE__ );

	RFMPkt			stPkt;
	RFMPktLight		*pLight;

	memset( &stPkt, 0, sizeof( stPkt ) );
	pLight = (RFMPktLight *)&stPkt.dat.light;

	//========================================================================
	//	Packet Header
#if defined(USE_CH_ISO_DEV)

	_MakePktHdr2( &stPkt,(uint8_t) PktLight );

#else

	_MakePktHdr( &stPkt, GetDevID(), 0xFF, sizeof( RFMPktLight ), PktLight );

#endif

	//========================================================================
	//	Status Data
	pLight->nOnOff = nOnOff;

	//========================================================================
	//	Send RF
#if defined(USE_CH_ISO_DEV)

	SendPktCh( (uint8_t)GetChPA(), (U8 *)&stPkt,
			(uint8_t)(sizeof( RFMPktHdr ) + sizeof( RFMPktLight )) );

#else

	SendPacket( (U8 *)&stPkt, (U8)sizeof( RFMPktHdr ) + sizeof( RFMPktLight ) );

#endif

	//========================================================================
}

//==========================================================================
void SendLightOn( void )
//==========================================================================
{
	SendLight((uint8_t) 1 );		//	Light On
}

//==========================================================================
void SendLightOff( void )
//==========================================================================
{
	SendLight((uint8_t) 0 );		//	Light Off
}

//==========================================================================
void SendRFCmdCh( uint8_t nCh, char *sCmd, uint8_t nRSSI )
//==========================================================================
{
	printf( "%s(%d)\n", __func__, __LINE__ );
	//========================================================================
	RFMPkt			stPkt;
	_MakeRFCmd( &stPkt, sCmd, (uint8_t)nRSSI );

	//========================================================================
	//	Send RF
	SendPktCh( (uint8_t)nCh, (U8 *)&stPkt, (uint8_t)(sizeof( RFMPktHdr ) + RFPktDataLen) );
	//========================================================================
}

//==========================================================================
void SendRFCmd( char *sCmd, uint8_t nRSSI )
//==========================================================================
{
	printf( "%s(%d)\n", __func__, __LINE__ );
	//========================================================================
	RFMPkt			stPkt;
	_MakeRFCmd( &stPkt, sCmd, (uint8_t)nRSSI );

	//========================================================================
	//	Send RF
//	SendPacket( (U8 *)&stPkt, (U8)sizeof( RFMPktHdr ) + RFPktDataLen );

	//========================================================================
	//	모든 수신기로 전송.
	for ( uint8_t nCh = (uint8_t)ChTS_base; nCh < (uint8_t)(ChTS1_1 + (ChGap * 10)); nCh++ )
	{
		SendPktCh( (uint8_t)nCh, (U8 *)&stPkt, (uint8_t)(sizeof( RFMPktHdr ) + RFPktDataLen ));

		HAL_Delay((uint32_t)3);	//	Tx Delay
	}
	//========================================================================
}

//==========================================================================
void SendRFCmdReset( void )
//==========================================================================
{
	printf( "%s(%d)\n", __func__, __LINE__ );

	SendRFCmd( "reset", (uint8_t)190 );

	//========================================================================
	//	Reset시 Upgrade채널도 reset
	RFMPkt			stPkt;
	_MakeRFCmd( &stPkt, "reset", (uint8_t)190 );
	SendPktCh((uint8_t) ChUpgrDst, (U8 *)&stPkt, (uint8_t)(sizeof( RFMPktHdr ) + RFPktDataLen) );
	//========================================================================
}

//==========================================================================
void SendRFCmdDFUMode( void )
//==========================================================================
{
	printf( "%s(%d)\n", __func__, __LINE__ );
	//==========================================================================
	SendRFCmd( "stboot", (uint8_t)247 );	//	DFU모드의 경우 아주 근접(RSSI-247)하지 않으면 동작하지 않도록 한다!!!
	//==========================================================================
}

//==========================================================================
void SendRFCmdUpgrade( uint16_t bRetry )
//==========================================================================
{
	//==========================================================================
	//	송신기에서 Upgrade 명령 전송.
	//==========================================================================

	printf( "%s(%d)\n", __func__, __LINE__ );
	//==========================================================================
	//	Upgrade Start Command

	if ( bRetry )
	{
		//	Upgrade 채널로 전송
		//	Upgrade Mode로 변경.
		SendRFCmdCh( (uint8_t)ChUpgrDst, (char *)"upgrade 1", (uint8_t) 200 );	//	DFU모드의 경우 근접(RSSI-200)하지 않으면 동작하지 않도록 한다!!!
	}
	else
	{
		//	Upgrade Mode로 변경.
		SendRFCmd( (char *)"upgrade 1", (uint8_t)200 );	//	DFU모드의 경우 근접(RSSI-200)하지 않으면 동작하지 않도록 한다!!!
	}
	//==========================================================================

	SetUpgrReTry((uint16_t) bRetry );			//	Retry 설정.

	HAL_Delay( (uint32_t)500 );	//	sleep 200 msec

	//========================================================================
	//	Upgrade Image 전송.
	UpgrSendImageApp();
	//========================================================================

	//==========================================================================
	//	Upgrade End Command
//DEL	SendRFCmd( "upgrade 0", 200 );	//	DFU모드의 경우 근접(RSSI-200)하지 않으면 동작하지 않도록 한다!!!
	//==========================================================================
}

//==========================================================================
void	SendUpgrData		( uint32_t nAddrTarget, uint16_t nPktTot, uint16_t nPktIdx, uint8_t *sBuf, uint8_t nSize )	//	Send Upgrade Data
//==========================================================================
{
//	printf( "%s(%d)\n", __func__, __LINE__ );

	RFMPkt			stPkt;
	memset( &stPkt, 0, sizeof( stPkt ) );

	//========================================================================
	//	Packet Header
	_MakePktHdr( &stPkt, (uint8_t)GetDevID(), (uint8_t)0xFF, (uint8_t)RFPktDataLen,(uint8_t) PktUpgr );

	//========================================================================
	//	Packet Body
	RFMPktUpgr	*pUpgr = (RFMPktUpgr *)&stPkt.dat.upgr;

	pUpgr->baseAddr		=	nAddrTarget;
	pUpgr->totPkt		=	nPktTot;
	pUpgr->idxPkt		=	nPktIdx;
	pUpgr->nSize		=	nSize;

	if( GetUpgrReTry() )
	{
		pUpgr->bFlag	|=	PktUpgrFlagRetry;	//	Retry Flag
	}

	memcpy( pUpgr->data, sBuf, (uint32_t)nSize );

	//========================================================================
	//	Send RF
	SendPktCh( (uint8_t)ChUpgrDst, (U8 *)&stPkt, (uint8_t)(sizeof( RFMPktHdr ) + RFPktDataLen) );

	//========================================================================
}

//==========================================================================
void	SendUpgrStat		( uint8_t nUpgrResult )	//	Send Upgrade Data
//==========================================================================
{
	printf( "%s(%d) - %d\n", __func__, __LINE__, nUpgrResult );

	RFMPkt			stPkt;
	memset( &stPkt, 0, sizeof( stPkt ) );

	//========================================================================
	//	Packet Header
	_MakePktHdr( &stPkt, (uint8_t)GetDevID(), (uint8_t)0xFF, (uint8_t)RFPktDataLen, (uint8_t)PktUpgrStat );

	//========================================================================
	//	Packet Body
	RFMPktUpgrStat	*pUpgrStat = (RFMPktUpgrStat *)&stPkt.dat.upgrStat;

	pUpgrStat->nResult		=	nUpgrResult;
	pUpgrStat->nTrainSet	=	g_idxTrainSet;
	pUpgrStat->nCarNo 		=	g_nCarNo;

	//========================================================================
	//	Send RF
#if defined( USE_CH_ISO_DEV )

	//	송신기#1
	SendPktCh( (uint8_t)ChTx_1, (U8 *)&stPkt, (uint8_t)(sizeof( RFMPktHdr ) + RFPktDataLen) );

	HAL_Delay((uint32_t)3);	//	재전송 전 Delay

	//	송신기#2
	SendPktCh( (uint8_t)ChTx_2, (U8 *)&stPkt, (uint8_t)(sizeof( RFMPktHdr ) + RFPktDataLen) );

#else
	int nCh;
	nCh = ChTS1_1 + g_idxTrainSet * 2 + ((g_nCarNo) % 2);	// 현재 호차 채널
	SendPktCh( nCh, (U8 *)&stPkt, (U8)sizeof( RFMPktHdr ) + RFPktDataLen );

	HAL_Delay(5);	//	재전송 전 Delay

	nCh = ChTS1_1 + g_idxTrainSet * 2 + ((g_nCarNo+1) % 2);	// 현재 호차 채널
	SendPktCh( nCh, (U8 *)&stPkt, (U8)sizeof( RFMPktHdr ) + RFPktDataLen );
#endif

	//========================================================================
}

//==========================================================================
//		Process Packet
//==========================================================================

//========================================================================
uint8_t	ProcPktStat			( const RFMPkt *pRFPkt )
//========================================================================
{
	if ( GetDbg() )
	{
		printf( "%s(%d)\n", __func__, __LINE__ );
	}

	uint8_t nRspID = pRFPkt->dat.stat.nCarNo;
	const RFMPktStat *pStat = &pRFPkt->dat.stat;
	//	상태정보 수신.
//		printf ( "[Stat] Car:%d\n", pRFPkt->dat.stat.nCarNo );

	if( nRspID < MaxCarNo	//	MaxCarNo(13)
		&& ( pStat->nDevID == DevRF900M || pStat->nDevID == DevRF900T )
		&& pStat->nMagicNum == 0xAA55
		&& g_bSetRspIDManual == 0		//	수동설정모드가 아닌경우.
		)
	{
		//	장치 응답 Flag 설정.
		SetStat( (uint8_t)nRspID );		//	상태정보 설정.

		UpdateStat((RFMPktStat *) pStat );	//	상태정보 Update. ( 버전정보 갱신 등 )
	}

	//========================================================================
	//	송신기 조명상태에 따른 조명 제어.
#if defined(USE_STAT_LIGHT)
	if( pStat->nDevID == DevRF900T )
	{
		//	조명상태 저장 및 제어.
		if( pStat->nDevFlag & DevFlagLight )
		{
			// 조명 On 명령 수신시.
			g_nDevFlag |= DevFlagLight;
			HAL_GPIO_WritePin ( LIGHT_ON_GPIO_Port, LIGHT_ON_Pin, GPIO_PIN_SET );
		}
		else
		{
			// 조명 Off
			g_nDevFlag &= ~DevFlagLight;
			HAL_GPIO_WritePin ( LIGHT_ON_GPIO_Port, LIGHT_ON_Pin, GPIO_PIN_RESET );
		}
	}
#endif
	//========================================================================

	return (uint8_t)0;
}

//========================================================================
uint8_t	ProcPktStatReq		( const RFMPkt *pRFPkt )
//========================================================================
{
	if ( GetDbg() )
	{
		printf( "%s(%d)\n", __func__, __LINE__ );
	}

	const RFMPktStatReq *pStatReq = &pRFPkt->dat.statReq;

	//	수신기의 경우 송신기 상태정보 갱신.
	//		-> 상태정보 요청한 송신기의 상태정보를 갱신한다.
	if ( GetDevID() == DevRF900M )
	{
		uint8_t idx = pStatReq->nCarNo;

		//========================================================================
		//	장치 응답 Flag 설정.
		SetStat( (uint8_t)idx );		//	상태정보 설정.

		//========================================================================
		//	RSSI 갱신
		g_devStat[idx].stat.nChRx = pStatReq->nSrcCh;
		g_devStat[idx].nRSSI = g_nRSSI;
	}

	//	Source Channel로 상태정보 송신.
	SendStat( pStatReq->nSrcCh );

	return (uint8_t) 0;
}


//========================================================================
uint8_t	ProcPktCtrlPaCall	( const RFMPkt *pRFPkt )
//========================================================================
{
	if ( GetDbg() )
	{
		printf( "%s(%d)\n", __func__, __LINE__ );
	}

	//	방송/통화 시작 종료 명령.
	const RFMPktCtrlPACall	*pCtrl = &pRFPkt->dat.pacall;

	switch ( pCtrl->nStartStop )
	{
	case CtrlStart:
		printf("[Start]");
		SetRFMMode( (uint8_t)RFMModeRx );
		break;
	case CtrlStop:
		printf("[Stop]");
		SetRFMMode( (uint8_t)RFMModeNormal );
		//  송신기 & 수신기 Spk Relay Off
		HAL_GPIO_WritePin( AUDIO_ON_GPIO_Port, AUDIO_ON_Pin, GPIO_PIN_RESET );
		break;
	//default:
	//	printf("%s:Invalid\n", __func__);
	//	return 0;
	}

	switch ( pCtrl->nTypePACall )
	{
	case CtrlPA:
		printf("[PA]");
		break;
	case CtrlCall:
		printf("[Call]");
		break;
	case CtrlOccPa:
		printf("[OccPa]");
		break;
	//default:
	//	printf("%s:Invalid\n", __func__);
	//	return 0;
	}

	printf("\n");

	if ( GetDevID() == DevRF900M )
	{
		//	수신기

		//	가까이 있는 송신기 설정. ( 수신기 -> 송신기 중계시 사용 )
		SetChPARFT( GetChNearRFT() );
	}

	g_nStampRxPkt = (uint16_t)HAL_GetTick();		//	방송/통화 Stamp

	return (uint8_t) 0;
}

//========================================================================
uint8_t	ProcPktPA			( const RFMPkt *pRFPkt )
//========================================================================
{
    static uint8_t sReMode = RFMModeRx;
    static uint8_t sspkVal = 1;
    
	if ( GetDbg() )
	{
		printf( "%s(%d)\n", __func__, __LINE__ );
	}

	//========================================================================
	//  방송 ( PTT )
	if ( GetDevID() == DevRF900M )
	{
		//  수신기
		uint16_t	 *pAudioBuf = (uint16_t*)pRFPkt->dat.data;

		//  방송 : 송신기 -> 수신기
		qBufPut( &g_qBufAudioRx, (uint8_t*)pAudioBuf, ( (uint16_t)I2S_DMA_LOOP_SIZE * 2 ) );

		// 조명 On
		HAL_GPIO_WritePin ( LIGHT_ON_GPIO_Port, LIGHT_ON_Pin, GPIO_PIN_SET );

        //sReMode = RFMModeRx;
        
		SetRFMMode( (uint8_t)sReMode );

		//	Codec Speaker On
        //sspkVal = 1;
		RFM_Spk((uint8_t)sspkVal);
		//  수신기 Spk Relay On
		HAL_GPIO_WritePin( AUDIO_ON_GPIO_Port, AUDIO_ON_Pin, GPIO_PIN_SET );
	}
	else
	{
		//========================================================================
		uint16_t	 *pAudioBuf = (uint16_t*)pRFPkt->dat.data;

#if defined(USE_RFT_ONLY_RX_SPK_ON)
		//  송신기 : 수신중인 경우 SPK ON
//			HAL_GPIO_WritePin( SPK_ON_GPIO_Port, SPK_ON_Pin, GPIO_PIN_SET );
        //sspkVal = 1;
		RFM_Spk((uint8_t)sspkVal);
#endif

		//  방송 : 송신기 -> 수신기
		qBufPut( &g_qBufAudioRx, (uint8_t*)pAudioBuf, (uint16_t)( I2S_DMA_LOOP_SIZE * 2 ) );
		//========================================================================

        //sReMode = RFMModeRx;
		//  송신기
		SetRFMMode( (uint8_t)sReMode );

		//  Red LED On
		HAL_GPIO_WritePin ( LED_ON_B_GPIO_Port, LED_ON_B_Pin, GPIO_PIN_SET ); //  RED LED
	}
	g_nStampRxPkt = (uint16_t)HAL_GetTick();		//	방송/통화 Stamp

	return (uint8_t) 0;
}

//========================================================================
uint8_t	ProcPktCall			( const RFMPkt *pRFPkt )
//========================================================================
{
	if ( GetDbg() )
	{
		printf( "%s(%d)\n", __func__, __LINE__ );
	}

	if( GetDevID() == DevRF900T )
	{
		//	송신기

		//========================================================================
		//  통화 ( SOS )
		uint16_t	 *pAudioBuf = (uint16_t*)pRFPkt->dat.data;

		SetRFMMode( (uint8_t)RFMModeRx );

#if defined(USE_RFT_ONLY_RX_SPK_ON)
		//  송신기 : 수신중인 경우 SPK ON
//		HAL_GPIO_WritePin( SPK_ON_GPIO_Port, SPK_ON_Pin, GPIO_PIN_SET );
		RFM_Spk((uint8_t)1);
#endif

		//  Red LED On
		HAL_GPIO_WritePin ( LED_ON_B_GPIO_Port, LED_ON_B_Pin, GPIO_PIN_SET ); //  RED LED

		//  통화 : 송신기 -> 송신기

		qBufPut( &g_qBufAudioRx, (uint8_t*)pAudioBuf, (uint16_t)( I2S_DMA_LOOP_SIZE * 2 ) );
	}
	else if ( GetDevID() == DevRF900M )
	{
		//	수신기

		SetRFMMode( (uint8_t)RFMModeRx );
	}

	g_nStampRxPkt = (uint16_t)HAL_GetTick();		//	방송/통화 Stamp

	return (uint8_t) 0;
}


//========================================================================
uint8_t	ProcPktDevConn			( const RFMPkt *pRFPkt )
//========================================================================
{
	//	Device Node Connection
	if ( GetDbg() )
	{
		printf( "%s(%d)\n", __func__, __LINE__ );
	}

	const RFMPktDevConn	*pConn = &pRFPkt->dat.devConn;

	if( GetDevID() == DevRF900T )
	{
		//========================================================================
		//	송신기
		//SetDevConn( pConn->nSrcCh, pConn->nDevType, pConn->nConnect );
	}
	else if ( GetDevID() == DevRF900M )
	{
		//========================================================================
		//	수신기
		//SetDevConn( pConn->nSrcCh, pConn->nDevType, pConn->nConnect );
	}

	return (uint8_t) 0;
}

//========================================================================
uint8_t	ProcPktLight		( const RFMPkt *pRFPkt )
//========================================================================
{
	if ( GetDbg() )
	{
		printf( "%s(%d)\n", __func__, __LINE__ );
	}

	if ( GetDevID() == DevRF900M && pRFPkt->hdr.nPktCmd == PktLight )
	{
		//  수신기 조명제어.
		if ( pRFPkt->dat.light.nOnOff == 0 )
		{
			// 조명 Off 명령 수신시.
			HAL_GPIO_WritePin ( LIGHT_ON_GPIO_Port, LIGHT_ON_Pin, GPIO_PIN_RESET );
		}
		else if ( pRFPkt->dat.light.nOnOff == 1 )
		{
			// 조명 On 명령 수신시.
			HAL_GPIO_WritePin ( LIGHT_ON_GPIO_Port, LIGHT_ON_Pin, GPIO_PIN_SET );
		}
	}

	return (uint8_t) 0;
}


//========================================================================
uint8_t	ProcPktCmd			( const RFMPkt *pRFPkt )
//========================================================================
{
	if ( GetDbg() )
	{
		printf( "%s(%d)\n", __func__, __LINE__ );
	}

	//	RSSI Check
	printf( "%s(%d) - %s\n", __func__, __LINE__, pRFPkt->dat.cmd.sCmd );

	if ( (uint8_t)g_nRSSI >= (uint8_t)(pRFPkt->dat.cmd.nRSSIOver) )
	{
		if ( pRFPkt->dat.cmd.nRsp == 1 )
		{
			//	명령 처리 동작 결과 응답.

			//	ToDo
		}

		//	RSSI값 확인 후 해당 범위 내에 있는 경우 명령 동작.
		ProcessCommand( (char *) pRFPkt->dat.cmd.sCmd );
	}
}


//========================================================================
uint8_t	ProcPktCmdRsp		( const RFMPkt *pRFPkt )
//========================================================================
{
	if ( GetDbg() )
	{
		printf( "%s(%d)\n", __func__, __LINE__ );
	}

	//	Command 처리결과 응답.

	//	ToDo
}

//========================================================================
uint8_t	s_bUpgrDataValid[(MaxUpgrDataPacket + 7) / 8];	//	4000];	//	Upgrade Data Valid Check
//========================================================================

//========================================================================
uint8_t	ProcPktUpgr			( const RFMPkt *pRFPkt )
//========================================================================
{
	//========================================================================
	//	Upgrade Flash Image
	//========================================================================

	if ( GetDbg() )
	{
		printf( "%s(%d)\n", __func__, __LINE__ );
	}

	//========================================================================
	//	Data Flash영역에 Write
	const RFMPktUpgr	*pUpgr = &pRFPkt->dat.upgr;

	if ( pUpgr->baseAddr < 0x08080000 || 0x080FFFFF < pUpgr->baseAddr )
	{
		printf("%s(%d) - Out Of Range - baseAddr(0x%08X)\n", __func__, __LINE__, pUpgr->baseAddr );
		return 0;
	}

	//========================================================================
	//	RFM Packet
//	RFMPktUpgr	*pUpgr = (RFMPktUpgr *)pRFPkt->dat.upgr;
//	pUpgr->baseAddr		=	nAddrTarget;
//	pUpgr->totPkt		=	nPktTot;
//	pUpgr->idxPkt		=	nPktIdx;
//	pUpgr->nSize		=	nSize;
//	memcpy( pUpgr->data, sBuf, nSize );

	//========================================================================
	static int	s_rxPkt;

	if ( pUpgr->idxPkt == 0 )
	{
		//	Start Uprade
		printf("%s(%d) - Start Upgrade\n", __func__, __LINE__ );

		if( pUpgr->bFlag & PktUpgrFlagRetry )
		{
			//	No Erase
			printf( "[%08d] Flash Erase - Skip ( Retry - Upgrade )\n", HAL_GetTick() );
		}
		else
		{
			//========================================================================
			//	Flash Erase
	//		 __HAL_RCC_DBGMCU_CLK_ENABLE();
			 __HAL_DBGMCU_FREEZE_IWDG();
	//		MX_IWDG_Disable();		//	Disable Watchdog
			printf( "[%08d] Flash Erase - Start\n", HAL_GetTick() );
	//        FLASH_If_Erase( ADDR_FLASH_IMGAPP );
			FLASH_If_Erase( ADDR_FLASH_IMGBOOT );		//	0x08080000
			printf( "[%08d] Flash Erase - End\n", HAL_GetTick() );
	    	//========================================================================

			memset( s_bUpgrDataValid, 0, sizeof(s_bUpgrDataValid) );
		}

		s_rxPkt = 0;
	}

	s_rxPkt++;

	//========================================================================
	//	Write Upgrade Image Data

	if ( FLASH_If_Write( pUpgr->baseAddr + (pUpgr->idxPkt * PktUpgrDataSize),
						(uint32_t *)pUpgr->data,
						pUpgr->nSize / 4 ) == FLASHIF_OK )
	{
		//	Valid Check Data
		SET_BIT( s_bUpgrDataValid[pUpgr->idxPkt/8], (0x1 << (pUpgr->idxPkt % 8)) );
	}
	else /* An error occurred while writing to Flash memory */
	{
		/* End session */
		printf("%s(%d) - Error idx(%d)\n", __func__, __LINE__, pUpgr->idxPkt );
		CLEAR_BIT( s_bUpgrDataValid[pUpgr->idxPkt/8], (0x1 << (pUpgr->idxPkt % 8)) );	//	Clear
	}

	g_nStampRxPkt = HAL_GetTick();		//	Rx Pkt Stamp
	//========================================================================

	//========================================================================
	if ( pUpgr->idxPkt == (pUpgr->totPkt - 1) )
	{
		//	End Upgrade
//		s_rxPkt++;

		printf("%s(%d) - End Upgrade ( rxPkt : %d / totPkt : %d )\n", __func__, __LINE__,
					s_rxPkt, pUpgr->totPkt );

		int result = UpgrStatSuccess;
		for( int i = 0; i < pUpgr->totPkt; i++ )
		{
			if( READ_BIT( s_bUpgrDataValid[i / 8], (0x1 << (i % 8)) ) == 0 )
			{
				result = UpgrStatFailed;
				break;
			}
		}

		//========================================================================
		if ( result == UpgrStatSuccess )//( s_rxPkt == pUpgr->totPkt )
		{
			//	Upgrade Success

			char buf[10];
			int filesize = pUpgr->totPkt * PktUpgrDataSize;

			printf("%s(%d) - Upgrade Success ( Size : %d )\n", __func__, __LINE__, filesize );

			memset( buf, 0, sizeof( buf ) );

			buf[0] = 0xaa;
			buf[1] = 0x55;
			buf[2] = ( filesize >> 16 ) & 0xFF;
			buf[3] = ( filesize >> 8 ) & 0xFF;
			buf[4] = ( filesize >> 0 ) & 0xFF;

		    M24_HAL_WriteBytes( &hi2c1, (uint16_t)0xA0, (uint16_t)AddrEEPUpgrMGN1, (uint8_t *)buf,(uint16_t) 5 );

			memset( buf, 0, sizeof( buf ) );

		    M24_HAL_ReadBytes( &hi2c1,(uint16_t) 0xA0, (uint16_t)AddrEEPUpgrMGN1, (uint8_t *)buf, (uint16_t)5 );

		    filesize = ( buf[2] << 16 ) | ( buf[3] << 8 ) | ( buf[4] );

			printf( "%s(%d) - EEPROM [0,1] : 0x%02X 0x%02X / ( bin size : %d )\n", __func__, __LINE__, buf[0], buf[1], filesize );

			HAL_Delay( (uint32_t)2000 );	//	Upgrade 결과전송 전 Delay

			//===========================================================================
			//	Send Upgrade Result
			SendUpgrStat( (uint8_t)UpgrStatSuccess );	//	Upgrade 결과전송.
			HAL_Delay((uint32_t) 100 );	//	Upgrade 결과전송 전 Delay
			SendUpgrStat( (uint8_t)UpgrStatSuccess );	//	Upgrade 결과전송.
			HAL_Delay( (uint32_t)100 );	//	Upgrade 결과전송 전 Delay
			SendUpgrStat((uint8_t) UpgrStatSuccess );	//	Upgrade 결과전송.

			//===========================================================================
			//	Reset
			cmd_reset(0, 0);
			//===========================================================================
		}
		else
		{
			HAL_Delay( (uint32_t)2000 );	//	Upgrade 결과전송 전 Delay

			//===========================================================================
			//	Send Upgrade Result
			SendUpgrStat( UpgrStatFailed );		//	Upgrade 결과전송.
			HAL_Delay( (uint32_t)100 );	//	Upgrade 결과전송 전 Delay
			SendUpgrStat( (uint8_t)UpgrStatFailed );	//	Upgrade 결과전송.
			HAL_Delay((uint32_t) 100 );	//	Upgrade 결과전송 전 Delay
			SendUpgrStat( (uint8_t)UpgrStatFailed );	//	Upgrade 결과전송.

			//	Upgrade Failed
			printf("%s(%d) - Upgrade Failed\n", __func__, __LINE__ );
		}
		//========================================================================

		//========================================================================
		SetRFMMode( (uint8_t)RFMModeNormal );	//	Normal 모드로 설정.
		//========================================================================
	}
}


//========================================================================
uint8_t	ProcPktUpgrStat			( const RFMPkt *pRFPkt )
//========================================================================
{
	//========================================================================
	//	Upgrade Status
	//========================================================================

	//	Upgrade 결과 수신후 수신기 LCD창에 표시.
	if ( GetDbg() )
	{
		printf( "%s(%d)\n", __func__, __LINE__ );
	}

	char sBuf[50];

	//========================================================================
	//	Data Flash영역에 Write
	RFMPktUpgrStat	*pUpgrStat = (RFMPktUpgrStat *)&pRFPkt->dat.upgrStat;

	printf( "%s(%d) - %d\n", __func__, __LINE__, pUpgrStat->nResult );

	if ( pUpgrStat->nResult == UpgrStatSuccess )
	{
		//	송신기 : Upgr Success

		sprintf(sBuf, "Success(%d/%d)", pUpgrStat->nTrainSet, pUpgrStat->nCarNo);
		LCDPrintfXY( 0, 13, sBuf );

//		HAL_Delay(2000);
	}
	else if( pUpgrStat->nResult == UpgrStatFailed )
	{
		//	송신기 : Upgr Failed

		sprintf(sBuf, "Failed(%d/%d)", pUpgrStat->nTrainSet, pUpgrStat->nCarNo);
		LCDPrintfXY( 0, 13, sBuf );

//		HAL_Delay(2000);
	}

	return 1;
}

