/*------------------------------------------------------------------------------------------
	Project			: LED
	Description		: 

	Writer			: $Author: zlkit $
	Revision		: $Rev: 1891 $
	Date			: 2019. 01.
	Copyright		: Piranti Corp. ( zlkit@piranti.co.kr )
	 
	Revision History 
	1. 2019. 01.	: Created
-------------------------------------------------------------------------------------------*/

#ifndef VERINFO_H
#define VERINFO_H

//========================================================================
// Header

//#include <tchar.h>			// TCHAR

#include "typedef.h"		//	char_t, uint32_t, ...

//========================================================================
// Define

typedef struct ver_info{
// Version
	UINT16	ver_main;			//	0
    UINT16	ver_sub;			//	2
    UINT16	ver_det;			//	4
    UINT16	ver_build;			//	6

// Compile Time
    UINT16	year;				//	8
    UINT8	month;				//	10
    UINT8	day;				//	11

    UINT8	hour;				//	12
    UINT8	min;				//	13
    UINT8	sec;				//	14

    UINT8	ver_id;				//	15	-	해당 모듈의 ID 아래 참고

    U32	fileSize;			//	16

	// Line Kimhae / Shinbundang / Maglev
    char_t	line[	12	];		//	20

#ifdef __cplusplus		//	.cpp 에서만 적용.

	void	init_Version(	void	);			// Init Version	버전정포 Parsing

	ver_info()									// 버전 초기화. ( 생성자 )
	{
//		init_Version();
	}

	ver_info(	WORD _ver_main,
				WORD _ver_sub,
				WORD _ver_det,
				WORD _ver_build		)			// 버전 초기화. ( 생성자 )
	{
		this->ver_main	=	_ver_main;
		this->ver_sub	=	_ver_sub;
		this->ver_det	=	_ver_det;
		this->ver_build	=	_ver_build;

		init_Version();
	}

#endif	//	 __cplusplus		//	.cpp 에서만 적용.

} VER_INFO;

extern const char_t		*g_sCompileDate;
extern const char_t		*g_sCompileTime;
extern const char_t		*g_sBoard;

extern VER_INFO			g_Version;				// Version Information

void	init_Version( void );			// Init Version	버전정포 Parsing

VER_INFO *GetAppVer();

#endif	//VERINFO_H

