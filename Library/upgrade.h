/*------------------------------------------------------------------------------------------
	Project			: It Library
	Description		: 

	Writer			: $Author: zlkit $
	Revision		: $Rev: 1891 $
	Date			: 2020. 09.
	Copyright		: Piranti Corp.	( sw@piranti.co.kr )
	 
	Revision History 
	1. 2020. 09.	: Created
-------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
	[ 구현목록 정의 ]
	* Func1 구현. 
		- Func1 기능 세부내용.

	* Func2 구현. 
-------------------------------------------------------------------------------------------*/

//========================================================================
#ifndef UPGRADE_H
#define UPGRADE_H
//========================================================================

#include <stdint.h>			//	uint32_t,

void SetUpgrReTry		( uint16_t _bUpgrRetry );

uint32_t UpgrSendImage		( uint32_t nAddrBase, uint32_t nSizeImage );

uint32_t UpgrSendImageBoot	( void );

uint32_t UpgrSendImageApp	( void );

uint8_t cmd_upgrade			( uint8_t argc, char * argv[] );

uint16_t GetUpgrReTry( void );

//========================================================================
#endif
//========================================================================


