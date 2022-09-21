/*------------------------------------------------------------------------------------------
	Project			: RFM
	Description		: 

	Writer			: $Author: zlkit $
	Revision		: $Rev: 1891 $
	Date			: 2020. 08.
	Copyright		: Piranti Corp.	( sw@piranti.co.kr )
	 
	Revision History 
	1. 2020. 08.	: Created
-------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
	[ 구현목록 정의 ]
	* RFM 공통함수 모음.
-------------------------------------------------------------------------------------------*/


//========================================================================
#ifndef RFM_H
#define RFM_H
//========================================================================

#include "RFMProtocol.h"		//

//========================================================================
//	Configuration

#include "rfm_config.h"

//========================================================================
// Define

enum eRFMMode
{
	RFMModeNormal	=	0,	//	Rx/Tx
	RFMModeTx		=	1,	//	Tx Only
	RFMModeRx		=	2,	//	Rx Only
	RFMModeOcc		=	3,	//	OCC Mode
	RFMModeUpgr		=	4,	//	Upgrade Mode
};

//========================================================================

enum eRFMConfig
{
	DefaultSpkVol	=	1,
	MaxSpkVol		=	3,			//	Spk 볼륨 최대값.

	DefaultMicVol	=	5,
	MaxMicVol		=	9,			//	Mic 볼륨 최대값.

	MaxTrainSet		=	10,			//	100 ~ 109 편성 ( 10개 편성 )
//	MaxCarNo		=	12,			//	1 ~ 10호차 / 11(수신기#1) / 12(수신기#2)
//	MaxCarNo		=	15,			//	1 ~ 10호차 / 11(수신기#1) / 12(수신기#2) / 13~15(Test)

	RFTCarNo1		=	11,			//	송신기 #1 ( 11호차 )
	RFTCarNo2		=	12,			//	송신기 #2 ( 12호차 )

	MaxCarNo		=	13,			//	1 ~ 10호차 / 11(수신기#1) / 12(수신기#2)
};

//	Device Status


extern uint8_t			g_nDevID;			//  Device ID ( 1 : RF900M / 2 : RF900T )

extern uint8_t			g_nDevFlag;			//  Device Flag

extern uint8_t			g_nSpkLevel;		//  Default (2) - 0(Mute) / 1 / 2(Normal) / 3

extern uint8_t			g_idxTrainSet;		//  Train Set Index
extern uint8_t			g_nCarNo;			//  Car Number

extern uint8_t			g_nChRx;			//  RF Rx Channel

extern uint8_t			g_offsetCA;			//	충돌회피 Offset ( msec )

extern uint8_t			g_nStampRxPkt;		//	방송/통화 Stamp

extern uint8_t			g_nRSSI;			//	RSSI Value

extern RFMDevStat	g_devStat[MaxCarNo];		//	Device Status


#if defined(USE_HOP_MANUAL)
extern uint8_t			g_nManHopping;		//	On(1) / Off(2) / Unused(0 : Other)
#endif	//	defined(USE_HOP_MANUAL)

//========================================================================
uint8_t		GetRFMMode		( void );
void	SetRFMMode		( uint8_t nRFMMode );

U8	*StrRFMMode		( int8_t nRFMMode );
//========================================================================
uint8_t		GetChPARFT( void );
uint8_t		GetChPARFT( void );

uint8_t		GetRFTID( void );
uint8_t 	GetChRx			( void );

uint8_t		GetChOtherRFT	( void );			//	타 송신기 채널.
uint8_t		GetChNearRFM	( void );			//	가장 가까운 수신기 채널.

void	SetChPA			( uint8_t nCh );		//	수신기로 송신할 방송채널 설정.
uint8_t		GetChPA			( void );

uint8_t		GetDevID		( void );
void	SetDevID		( uint8_t nDevID );

uint8_t		GetTrainSetIdx	( void );
void	SetTrainSetIdx	( uint8_t idxTrainSet );

uint8_t		GetCarNo		( void );
void	SetCarNo		( uint8_t nCarNo );
int8_t		LoadCarNo		( void );			//	I2C에서 Loading

int8_t		GetSpkVol	    ( void );
void	SetSpkVol	    ( uint8_t nSpkVol );

#if defined(USE_HOP_MANUAL)
int8_t		GetManHop		( void );
void	SetManHop		( uint8_t nManHop );
#endif	//	defined(USE_HOP_MANUAL)

void SetStat( uint8_t nRspID );
void	SetChPARFT( uint8_t nCh );
uint8_t		GetChNearRFT	( void );
int8_t		GetMicVol	    ( void );
void	SetMicVol	    ( uint8_t nMicVol );

uint8_t		IsNearRFT	( void );
int8_t		LoadTrainSetIdx	( void );

void UpdateStat( RFMPktStat *pStat );
//========================================================================
//	GPIO Setting

void	RFM_Spk			( uint8_t bOnOff );		//	1(On) / 0(Off)

void	RF_RSSI			( void );

//========================================================================

void	PrintVerInfo	( void );

//========================================================================
//	Command

uint8_t 	cmd_ts      	( uint8_t argc, char * argv[] );
uint8_t		cmd_ch			( uint8_t argc, char * argv[] );
uint8_t		cmd_car			( uint8_t argc, char * argv[] );
uint8_t 	cmd_swinfo    	( uint8_t argc, char * argv[] );
uint8_t		cmd_info		( uint8_t argc, char * argv[] );
uint8_t 	cmd_rfstat		( uint8_t argc, char * argv[] );

uint8_t 	cmd_rftx    	( uint8_t argc, char * argv[] );	//	RF Tx Test

uint8_t 	cmd_txpwr		( uint8_t argc, char * argv[] );	//	Tx Pwr Setting

uint8_t		cmd_rspid		( uint8_t argc, char * argv[] );

uint8_t		cmd_OccPa		( uint8_t argc, char * argv[] );	//	대승객방송 시작/종료

uint8_t		cmd_hop			( uint8_t argc, char * argv[] );	//	Hopping

void ReflashStat( uint8_t nTick );
void ReloadStampStat( void );



#if defined(USE_ENV_TEST)

void	SetLoopRFTx		( uint8_t bEnable );	//	RF Data 전송 유지..
uint8_t		cmd_rftx		( uint8_t argc, char * argv[] );

#endif	//	defined(USE_ENV_TEST)

//========================================================================
//		RFM Procedure
//========================================================================

uint8_t		InitRFM			( void );
uint8_t		RFM_main		( void );
void	LoopProcRFM		( uint8_t nTick );

//========================================================================
#endif
//========================================================================


