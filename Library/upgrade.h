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

void SetUpgrReTry		( int _bUpgrRetry );

int UpgrSendImage		( uint32_t baseAddr, uint32_t nSize );

int UpgrSendImageBoot	( void );

int UpgrSendImageApp	( void );

int cmd_upgrade			( int argc, char * argv[] );

//========================================================================
#endif
//========================================================================


