/*------------------------------------------------------------------------------------------
	Project			: It Library
	Description		: Queue

	Writer			: $Author: zlkit $
	Revision		: $Rev: 1891 $
	Date			: 2019. 10.
	Copyright		: Piranti Corp.	( zlkit@piranti.co.kr )
	 
	Revision History 
	1. 2019. 10.	: Created
-------------------------------------------------------------------------------------------*/

//========================================================================
#ifndef QUEUE_BUF_H
#define QUEUE_BUF_H
//========================================================================

//#include "typedef.h"	//	uint8_t
#include <stdint.h>		//	uint8_t

typedef struct _Queue_t
{
#define QMAX 256

	UINT8 queue[QMAX];

	uint16_t front, rear;

} Queue_t;

//========================================================================
uint8_t				qcount		( Queue_t *q );
void			init_queue	( Queue_t *q );
void			clear_queue	( Queue_t *q );
uint8_t				qput		( Queue_t *q, S8 k );
uint8_t 	qget		( Queue_t *q );
//========================================================================


typedef struct _QBuf_t
{
//#define QBUFMAX 128

	uint8_t	*qBuf;
	uint16_t	size;

	uint16_t front, rear;

} QBuf_t;

//===========================================================================
void	qBufInit	( QBuf_t *q, uint8_t *_qBuf, uint16_t _size );
void	qBufClear	( QBuf_t *q );
uint16_t		qBufCnt		( QBuf_t *q );
uint16_t		qBufPut		( QBuf_t *q, uint8_t *pBuf, uint16_t size );
uint16_t		qBufGet		( QBuf_t *q, uint8_t *pBuf, uint16_t size );
//===========================================================================

//===========================================================================
void	QBufTest	( QBuf_t *q, uint16_t blkSize );
//===========================================================================


//========================================================================
#endif		//	QUEUE_BUF_H
//========================================================================


