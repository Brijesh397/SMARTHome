/****************************************FILE DESCRIPTION**************************************/
/* FILE 		: esp8266.h
* PROJECT 		: WiFi
* PROGRAMMER 	: Brijesh Mehta
* DESCRIPTION 	: esp8266 config
*/
/*********************************************************************************************/

#ifndef ESP_H_
#define ESP_H_

/************** Includes ***********************/
#include "main.h"
#include "circularBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**********EXTERN VARIABLES***************/
extern UART_HandleTypeDef huart2;

/*************ENUM & STRUCTS*****************/
typedef enum
{
	ESP_WRITE_SUCCESSFUL  =	0x00,
	ESP_WRITE_FAILED	  =	0x01,
	ESP_RESPONSE_CORRECT  =	0x02,
	ESP_RESPONSE_WRONG	  = 0x03,
	ESP_WAIT			  =	0x04
}espState;

typedef struct
{
	uint8_t security;
	char ssid[20];
	char signalStrength[5];
	char macAddress[20];

}availableAP_t;

typedef struct
{
	float latitude;
	float longitude;
}location_t;

#define ESP_MAX_WAIT			10000

/**************** SSID PASS *******************s**/
extern char SSID[50];
extern char PASSWORD[50];
extern char IPADDRESS[50];

/*************** COMMANDS ***********************/
extern char RESTART_COMMAND[];
extern char STATION_MODE[];
extern char LIST_AP[];
extern char SET_AP_SETTING[];
extern availableAP_t ssidList[10];
extern bool gotlocation;
extern location_t geoLocation;
extern bool gettingNTPTime;
extern bool gotNTP;

/*************** Function Prototype ***************/
void espInit(void);
espState espWriteCommand(char *command);
espState espCheckResponse(char *response);
void espIRQHandler(void);
HAL_StatusTypeDef espWaitUntilTimeout(uint32_t time);

/************ Command Functions *****************/
HAL_StatusTypeDef espReset(void);
HAL_StatusTypeDef espRestore(void);
HAL_StatusTypeDef espSetApSettings(void);
HAL_StatusTypeDef espSetToStationMode(void);
HAL_StatusTypeDef espGetAvailableNetwork(void);
HAL_StatusTypeDef espConnect(char *ssid, char *password);
HAL_StatusTypeDef espDisconnect(void);
HAL_StatusTypeDef espGetIP(void);
HAL_StatusTypeDef espGetSSID(char *ssid);
HAL_StatusTypeDef espEnableMultiConn(void);
HAL_StatusTypeDef espCreateTCPServer(uint8_t portNumber);
char espGetLinkId(void);
HAL_StatusTypeDef espSendDataToServer(char *data);
HAL_StatusTypeDef espGetDomainIP(char *url, char *ip);
HAL_StatusTypeDef espEstablishTCPConnection(char *ip);
HAL_StatusTypeDef espWaitUntilResponse(char *response, uint32_t timeout);
HAL_StatusTypeDef getGeolocation(void);
HAL_StatusTypeDef getWeather(void);
HAL_StatusTypeDef getNTPTime(void);

#endif
