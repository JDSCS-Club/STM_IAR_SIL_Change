/*------------------------------------------------------------------------------------------
	Project			: RFM
	Description		: 

	Writer			: $Author: zlkit $
	Revision		: $Rev: 1891 $
	Date			: 2020. 07.
	Copyright		: Piranti Corp.	( zlkit@piranti.co.kr )
	 
	Revision History 
	1. 2020. 07.	: Created
-------------------------------------------------------------------------------------------*/

//========================================================================
#ifndef PROC_PKT_H
#define PROC_PKT_H
//========================================================================

#include "RFMProtocol.h"	//	RFMPkt

//========================================================================
extern uint8_t nTxPkt;		//	Tx Packet Count
extern uint8_t nRxPkt;		//	Rx Packet Count
extern uint8_t nHopPkt;		//	Hopping Packet Count
extern uint8_t nDropPkt;	//	Drop Packet Count

//========================================================================
extern uint8_t nRxErr;
extern uint8_t nCrcErr;

//========================================================================

extern uint32_t nTxStamp;	//	Tx Tick Stamp
extern uint32_t nRxStamp;	//	Rx Tick Stamp


extern uint8_t			g_bSetRspIDManual;	//  RspID Flag 수동설정. ( 디버깅용 )
extern uint16_t	 	g_flagRspID;		//  범위 안의 Device ID Flag ( 0 ~ 15 bit )
extern uint8_t	 	g_nPktSeq;			//  Packet Sequence

//========================================================================
//	Dump Function

void	Dump				( const S8 *sTitle, const S8 *sBuf, uint8_t nSize );

//========================================================================
//	Packet Procedure
uint8_t		InitProcPkt 		( void );

void	LoopProcPkt			( uint16_t nTick );

uint8_t		SendPacket			( const S8 *sBuf, uint8_t nSize );

uint8_t		SendPktCh			( uint8_t nCh, const U8 *sBuf, uint8_t nSize );

uint8_t 	ProcPktHdr1			( const RFMPkt *pRFPkt, uint8_t nSize  );
uint8_t 	ProcPktHdr2			( const RFMPkt *pRFPkt, uint8_t nSize  );
//int 	ProcPktHdr			( const RFMPkt *pRFPkt, int nSize  );

void 	CallbackRecvPacket	( const S8 *pData, uint8_t nSize );


uint8_t _ChkDropPktSeq( uint8_t _nRxSeq, uint8_t _currSeq );

//========================================================================
//	Demo Example
void	TestProcPkt	( void );

uint8_t 	cmd_pktmon	( uint8_t argc, char * argv[] );

//========================================================================
#endif
//========================================================================

