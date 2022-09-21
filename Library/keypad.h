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
#ifndef KEY_PAD_H
#define KEY_PAD_H
//========================================================================

enum eKeypad
{
	eKeyMenu		=	0,
	eKeyUp			=	1,
	eKeyOk			=	2,
	eKeyLight		=	3,
	eKeyDown		=	4,
	eKeyVol			=	5,
	eKeyPtt			=	6,
	eKeySos			=	7,
	eKeyPwrOnOff	=	8,
};

uint8_t		GetKey			( uint8_t eKey );

void	GetKeyStat		( uint8_t *btnStat );

void	LoopProcKey 	( uint32_t tickCurr );

//========================================================================
//		KeyPad ( Dome Button )
//========================================================================

void	KeyMenu			( uint8_t bValue );
void	KeyUp			( uint8_t bValue );
void	KeyOK			( uint8_t bValue );

void	KeyLight		( uint8_t bValue );
void	KeyDown			( uint8_t bValue );
void	KeyVol			( uint8_t bValue );

//========================================================================
//		Side Button
//========================================================================

void	KeyPtt			( uint8_t bValue );
void	KeySos			( uint8_t bValue );

//========================================================================
//		Side Button
//========================================================================

void	KeyPwrOnOff		( uint8_t bValue );


void	KeyTestLoopback( uint8_t bValue );
//========================================================================
#endif
//========================================================================


