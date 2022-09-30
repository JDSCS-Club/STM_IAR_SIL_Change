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
#ifndef MENU_H
#define MENU_H
//========================================================================

#include "RFMProtocol.h"		//	

//========================================================================
//	Define


//========================================================================
//	Menu Structure

typedef struct _Menu
{
	char 		**sItem;						//	Item Name
	uint8_t			cntItem;						//	Menu Item Count
	uint8_t			currIdx;						//	Current Item Index
	void		(*cbFunc)( uint8_t idxItem );		//	Callback Func
} Menu_t;

uint8_t 	IsMenuMaint			( void );			//	MainMenu Maintenace Menu활성화.
void 	EnableMenuMaint		( uint8_t bEnable );	//	MainMenu Maintenace Menu활성화.

extern Menu_t	g_MenuMain;						//	Main Menu
extern Menu_t	g_MenuLightCtrl;				//	Light Ctrl
extern Menu_t	g_MenuTrainSet;					//	TrainSet

extern char 	_sVerList[16][20];				//	Version Info

//========================================================================
//	Menu Procedure

void 	ProcMenuMain		( uint8_t idxItem );	//	Main
void	ProcMenuTrainSet	( uint8_t idxItem );	//	TrainSet
void 	ProcMenuLightCtrl	( uint8_t idxItem );	//	LightCtrl

void 	ProcMenuRFTID		( uint8_t idxItem );	//	송신기 ID설정.

//========================================================================
void 	ProcMenuSelfTest	( uint8_t idxItem );	//	자가진단 ( 호차별 상태정보 점검 )

void 	ProcMenuSetting		( uint8_t idxItem );	//	설정

void 	ProcMenuSetMic		( uint8_t idxItem );
void 	ProcMenuSetSpk		( uint8_t idxItem );
void 	ProcMenuSetTxPwr	( uint8_t idxItem );

//========================================================================

void 	ProcMenuDiag		( uint8_t idxItem );	//	Diag
void	ProcMenuVer			( uint8_t idxItem );	//	Menu Version
void	ProcMenuCmd			( uint8_t idxItem );	//	Command

//========================================================================

void	ProcLightOn			( void );
void	ProcLightOff		( void );
void	ProcDispVer			( void );
void	ProcDispStat 		( void );

//========================================================================
//	Menu LCD Disp

void    UpdateLCDMain		( void );
void    UpdateLCDMenu		( void );

void	UpdateLCDMonitor	( uint16_t nTick );		//	LCD : 모니터링 상태 Update

//========================================================================
//	Menu Key Proc

void    ProcBtnUp			( void );
void    ProcBtnDown			( void );

void    ProcBtnMenu			( void );
void    ProcBtnOK			( void );


void	SetActiveMenu( Menu_t *pActiveMenu );
Menu_t	*GetActiveMenu( void );
//========================================================================
#endif
//========================================================================


