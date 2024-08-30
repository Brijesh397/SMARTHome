/****************************************FILE DESCRIPTION**************************************/
/* FILE 		: circularbuffer.h
* PROJECT 		: WiFi
* PROGRAMMER 	: Brijesh Mehta
* DESCRIPTION 	: circular buffer implementation
*/
/*********************************************************************************************/

#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

/************** Includes *******************/
#include "main.h"

#define BUFFER_SIZE		2048

typedef enum
{
	BUFFER_OVERFLOW		= 	0x00,
	BUFFER_UNDERFLOW	=	0x01,
	BUFFER_WRITE_OK		=	0x02,
	BUFFER_READ_OK		=	0x03
}CircularBufferState;

typedef struct
{
	char data[BUFFER_SIZE];
	volatile int32_t front;
	volatile int32_t rear;
}Circular_Buffer_t;


/**************Function Prototype *****************/
uint8_t circularBufferIsFull(Circular_Buffer_t *buffer);
uint8_t circularBufferIsEmpty(Circular_Buffer_t *buffer);
CircularBufferState circularBufferWriteChar(Circular_Buffer_t *txBuffer, char data);
CircularBufferState circularBufferWriteString(Circular_Buffer_t *txBuffer, char *data);
char circularBufferRead(Circular_Buffer_t *rxBuffer);
void circularBufferClear(Circular_Buffer_t *buffer);

#endif /* CIRCULARBUFFER_H_ */
