/*------------------------------------------------------------------------------------------
	Project			: RFM
	Description		: console과 관련된 함수들 및 command line 처리

	Writer			: $Author: zlkit $
	Revision		: $Rev: 1891 $
	Date			: 2020. 08.
	Copyright		: Piranti Corp. ( zlkit@piranti.co.kr )
	 
	Revision History 
	1. 2020. 08.	: Created
-------------------------------------------------------------------------------------------*/

#ifndef	_CLI_H_
#define _CLI_H_


#include "typedef.h"	//	uint8_t

#define	OPENED_COMMAND_IDX	5	/* for release version: 3 */
#define	CLOSED_COMMAND_IDX	0

extern	int	open_command_idx;

typedef	struct	user_commnand
{
	char	*command_name;
	char	*command_help1;
	char	*command_help2;
	uint8_t		( *func )(uint8_t argc, char *argv[]);
} user_command_t;

//extern	user_command_t	user_command_table[];

uint8_t 	a2hex		( S8 *pv );
int8_t 	readline	( S8 *bufp );
void 	dump_Cli		(  S8 *a, uint8_t delta, uint8_t width );
int8_t 	cmd_period	( int8_t argc, S8 *argv[] );
//uint8_t 	cmd_ts		( uint8_t argc, char *argv[] );

void	LoopProcCLI ( void );

#if defined(_WIN32)
DWORD	vCLITask	( void *pvParameters );
#else	//	RTOS
void	vCLITask	( void *pvParameters );	//	LED Task
#endif

extern int			data_option;

//========================================================================
//	Default CLI Process
void	CLIPrompt		( void );
uint8_t		ProcessCommand	( char *cmd );
//========================================================================
uint8_t getarg(S8 *buffer, S8 *argv[]);

//========================================================================
void	SetCLIPrompt	( void ( *fnPrompt )( void ) );
void	SetCLIProc		( uint8_t ( *fnProc )( char *cmd ) );
//========================================================================

//========================================================================
//	Default Command

//uint8_t cmd_help	( uint8_t argc, char *argv[] );
//uint8_t cmd_reset	( uint8_t argc, char *argv[] );
//uint8_t cmd_uptime	( uint8_t argc, char *argv[] );
//uint8_t cmd_ver		( uint8_t argc, char *argv[] );

//========================================================================

#endif	/* _CLI_H_ */


#define _CLI_H_
