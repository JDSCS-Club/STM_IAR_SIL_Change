/*------------------------------------------------------------------------------------------
	Project			: RFM
	Description		: 보드 시험용 함수 모음들

	Writer			: $Author: zlkit $
	Revision		: $Rev: 1891 $
	Date			: 2020. 08.
	Copyright		: Piranti Corp. ( zlkit@piranti.co.kr )
	 
	Revision History 
	1. 2020. 08.	: Created
-------------------------------------------------------------------------------------------*/

#ifndef	_DIAG_H_
#define	_DIAG_H_

//========================================================================

extern	unsigned char *mem_addr;
extern	int	dumpsize, data_option;
extern	int	debug_level;

int		GetDbg		( void );

void	memory_modify	( void *mem_addr, int unit );

//========================================================================

//int		cmd_test		( int argc, char *argv[] );
int		cmd_test1		( int argc, char *argv[] );
int		cmd_test2		( int argc, char *argv[] );
int		cmd_test3		( int argc, char *argv[] );
int		cmd_test4		( int argc, char *argv[] );
int		cmd_test4		( int argc, char *argv[] );

int		cmd_test_rf1		( int argc, char *argv[] );
int		cmd_test_rf2		( int argc, char *argv[] );
int		cmd_test_rf3		( int argc, char *argv[] );
int		cmd_test_rf_init	( int argc, char *argv[] );
int		cmd_test_rf_vinit	( int argc, char *argv[] );
int		cmd_test_rf_debug	( int argc, char *argv[] );

int		cmd_ttest		( int argc, char *argv[] );
int		cmd_md			( int argc, char *argv[] );
int		cmd_mm			( int argc, char *argv[] );
int		cmd_do			( int argc, char *argv[] );

uint8_t		cmd_diag		( uint8_t argc, char *argv[] );

//========================================================================

void	display_diag_RF	( void );
int		cmd_diag_RF		( int argc, char *argv[] );

void	display_diag_RF_WDS	( void );
int		cmd_diag_RF_WDS		( int argc, char *argv[] );

int		cmd_rfwds_info	( int argc, char *argv[] );
int		cmd_rfwds1		( int argc, char *argv[] );
int		cmd_rfwds2		( int argc, char *argv[] );
int		cmd_rfwds3		( int argc, char *argv[] );
int		cmd_rfwds_init	( int argc, char *argv[] );
int		cmd_rfwds_vinit	( int argc, char *argv[] );
int		cmd_rfwds_debug	( int argc, char *argv[] );

int		cmd_diag_Audio	( int argc, char *argv[] );

//========================================================================

uint8_t		cmd_debug		( uint8_t argc, char *argv[] );
uint8_t		cmd_uptime		( uint8_t argc, char *argv[] );
uint8_t		cmd_ver			( uint8_t argc, char *argv[] );
uint8_t		cmd_help		( uint8_t argc, char *argv[] );
uint8_t		cmd_wr			( uint8_t argc, char *argv[] );
int		cmd_rd			( int argc, char *argv[] );
uint8_t		cmd_reset		( uint8_t argc, char *argv[] );
int		logprintf		( const char *fmt, ... );
int		cmd_logpr		( int argc, char *argv[] );
int		cmd_logx		( int argc, char *argv[] );

int		cmd_id			( int argc, char *argv[] );

int		cmd_rts			( int argc, char *argv[] );

int		cmd_test		( int argc, char * argv[] );

//========================================================================

//uint8_t 	cmd_audio	( uint8_t argc, S8 *argv[] );
//uint8_t 	cmd_codec	( uint8_t argc, S8 *argv[] );

//========================================================================


#endif	/* _DIGA_H_ */

