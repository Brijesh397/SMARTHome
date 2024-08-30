/****************************************FILE DESCRIPTION**************************************/
/* FILE 		: circularbuffer.c
* PROJECT 		: WiFi
* PROGRAMMER 	: Brijesh Mehta
* DESCRIPTION 	: circular buffer functions
*/
/*********************************************************************************************/

/************** Includes *******************/
#include "circularBuffer.h"

/********************* Function Description *********************************
 * FUNCTION		:	circularBufferIsFull
 *
 * DESCRIPTION	:	This function checks whether the circular buffer is full or not
 *
 * PARAMETERS	:	Circular_Buffer_t *buffer - buffer pointer
 *
 * RETURN		:	uint8_t
 *
 * **************************************************************************/
uint8_t circularBufferIsFull(Circular_Buffer_t *buffer)
{
	if(buffer->front == buffer->rear + 1 && buffer->rear == BUFFER_SIZE - 1)
	{
		return 1;
	}
	else if(buffer->front == 0 && buffer->rear == BUFFER_SIZE - 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/********************* Function Description *********************************
 * FUNCTION		:	circularBufferIsEmpty
 *
 * DESCRIPTION	:	This function checks whether the circular buffer is empty or not
 *
 * PARAMETERS	:	Circular_Buffer_t *buffer - buffer pointer
 *
 * RETURN		:	uint8_t
 *
 * **************************************************************************/
uint8_t circularBufferIsEmpty(Circular_Buffer_t *buffer)
{
	if(buffer->front == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/********************* Function Description *********************************
 * FUNCTION		:	circularBufferClear
 *
 * DESCRIPTION	:	This function clears the buffer contents
 *
 * PARAMETERS	:	Circular_Buffer_t *buffer - buffer pointer
 *
 * RETURN		:	uint8_t
 *
 * **************************************************************************/
void circularBufferClear(Circular_Buffer_t *buffer)
{
	memset(buffer->data,'\0',BUFFER_SIZE);
	buffer->front = -1;
	buffer->rear = -1;
}

/********************* Function Description *********************************
 * FUNCTION		:	circularBufferWrite
 *
 * DESCRIPTION	:	This function writes a char to the buffer
 *
 * PARAMETERS	:	Circular_Buffer_t *txBuffer
 * 					char *data
 * 					uint32_t len
 *
 * RETURN		:	uint8_t
 *
 * **************************************************************************/
CircularBufferState circularBufferWriteChar(Circular_Buffer_t *txBuffer, char data)
{
	if(circularBufferIsEmpty(txBuffer))
	{
		txBuffer->front = 0;
		txBuffer->rear = 0;

		txBuffer->data[txBuffer->rear] = data;
	}
	else if(circularBufferIsFull(txBuffer))
	{
		return BUFFER_OVERFLOW;
	}
	else
	{
		txBuffer->rear++;

		txBuffer->data[txBuffer->rear] = data;
	}
	return BUFFER_WRITE_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	circularBufferWriteString
 *
 * DESCRIPTION	:	This function writes a string to the buffer
 *
 * PARAMETERS	:	Circular_Buffer_t *txBuffer
 * 					char *data
 * 					uint32_t len
 *
 * RETURN		:	uint8_t
 *
 * **************************************************************************/
CircularBufferState circularBufferWriteString(Circular_Buffer_t *txBuffer, char *data)
{
	uint32_t len = strlen(data);

	//Check whether the buffer is full
	if(circularBufferIsFull(txBuffer))
	{
		return BUFFER_OVERFLOW;
	}

	//Check whether the data will fit inside the buffer
	if(len > BUFFER_SIZE)
	{
		return BUFFER_OVERFLOW;
	}

	//Write to the Buffer
	while(len > 0)
	{
		if(circularBufferIsEmpty(txBuffer))
		{
			txBuffer->front = 0;
			txBuffer->rear = 0;

			txBuffer->data[txBuffer->rear] = *data;
			data++;
			len--;
		}
		else
		{
			txBuffer->rear++;

			txBuffer->data[txBuffer->rear] = *data;
			data++;
			len--;
		}
	}
	return BUFFER_WRITE_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	circularBufferRead
 *
 * DESCRIPTION	:	This function reads data from the buffer
 *
 * PARAMETERS	:	Circular_Buffer_t *rxBuffer
 *
 * RETURN		:	uint8_t
 *
 * **************************************************************************/
char circularBufferRead(Circular_Buffer_t *rxBuffer)
{
	char readData;

	if(rxBuffer->front <= rxBuffer->rear)
	{
		readData = rxBuffer->data[rxBuffer->front];
		rxBuffer->front++;
	}
	return readData;
}
