/****************************************FILE DESCRIPTION**************************************/
/* FILE 		: esp.c
* PROJECT 		: WiFi
* PROGRAMMER 	: Brijesh Mehta
* DESCRIPTION 	: esp config functions
*/
/*********************************************************************************************/

/************** Includes ***********************/
#include <esp.h>

/*************** TX RX Buffers *************/
Circular_Buffer_t espRxBuffer;

/**************** SSID PASS *********************/
char SSID[50] = "NA";
char PASSWORD[50] = "\0";
char IPADDRESS[50] = "NA";
availableAP_t ssidList[10] = {0};

/*************** COMMANDS ***********************/
char RESTART_COMMAND[] = "AT+RST\r\n";
char STATION_MODE[]	= "AT+CWMODE=1\r\n";
char LIST_AP[] = "AT+CWLAP\r\n";
char SET_AP_SETTING[] = "AT+CWLAPOPT=1,15\r\n";

/*************GLOBAL VARIABLES*******************/
char weatherRequest[512];
bool gotlocation = false;
location_t geoLocation;
bool gettingNTPTime = false;
bool gotNTP = false;

/********************* Function Description *********************************
 * FUNCTION		:	espInit
 *
 * DESCRIPTION	:	This function is used to configure the esp module
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void espInit(void)
{
	/************* Initializing the RX Buffer ***********/
	espRxBuffer.front = -1;
	espRxBuffer.rear = -1;

	//Enable the RXNE Interrupt to store the response inside the receive buffer
	__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);
}

/********************* Function Description *********************************
 * FUNCTION		:	espWriteCommand
 *
 * DESCRIPTION	:	This function is used to write command to the esp Module
 *
 * PARAMETERS	:	char command
 *
 * RETURN		:	espState
 *
 * **************************************************************************/
espState espWriteCommand(char *command)
{
	//Clear the receive buffer
	circularBufferClear(&espRxBuffer);

	//Find the length of the Command
	uint16_t len = strlen(command);

	//Transmit the command
	if(HAL_UART_Transmit(&huart2, (uint8_t*)command, len, 1000) != HAL_OK)
	{
		return ESP_WRITE_FAILED;
	}

	return ESP_WRITE_SUCCESSFUL;
}

/********************* Function Description *********************************
 * FUNCTION		:	espCheckResponse
 *
 * DESCRIPTION	:	This function checks inside the receive buffer whether we have received the correct
 * 					response or not.
 * 					If the response is not correct it will return error.
 *
 * PARAMETERS	:	char *response - response we want to check
 *
 * RETURN		:	espState
 *
 * **************************************************************************/
espState espCheckResponse(char *response)
{
	uint32_t currPos = 0;
	uint32_t len = strlen(response);
	char temp;

	for(uint32_t i=0; i<BUFFER_SIZE; i++)
	{
		temp = espRxBuffer.data[i];
		if(temp == response[currPos])
		{
			currPos++;
			if(currPos == len)
			{
				return ESP_RESPONSE_CORRECT;
			}
		}
		else
		{
			currPos = 0;
		}
	}

	return ESP_RESPONSE_WRONG;
}

/********************* Function Description *********************************
 * FUNCTION		:	espTraverseBufferUntilStringFound
 *
 * DESCRIPTION	:	This function traverses the RX Buffer to check whether a string is present or not but does not
 * 					change the front value of the buffer
 *
 * PARAMETERS	:	char *response
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espTraverseBufferUntilStringFound(char *response)
{
	char temp = '0';
	uint32_t currPos = 0;
	uint32_t len = strlen(response);

	while(espRxBuffer.front <= espRxBuffer.rear)
	{
		temp = espRxBuffer.data[espRxBuffer.front];
		if(temp == response[currPos])
		{
			currPos++;
			espRxBuffer.front++;
			if(currPos == len)
			{
				return HAL_OK;
			}
		}
		else
		{
			currPos = 0;
			espRxBuffer.front++;
		}
	}

	return HAL_ERROR;
}

/********************* Function Description *********************************
 * FUNCTION		:	espIRQHandler
 *
 * DESCRIPTION	:	This function handles the raised interrupts
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void espIRQHandler(void)
{
	char temp = huart2.Instance->DR;
	if(circularBufferWriteChar(&espRxBuffer,temp) != BUFFER_WRITE_OK)
	{
		__HAL_UART_DISABLE_IT(&huart2,UART_IT_RXNE);
	}
}

/********************* Function Description *********************************
 * FUNCTION		:	espWaitUntilTimeout
 *
 * DESCRIPTION	:	This function prevents getting stuck inside a while loop.
 * 					If the time is greater than timeout then return HAL_TIMEOUT
 *
 * PARAMETERS	:	char *response, uint32_t timeout
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espWaitUntilResponse(char *response, uint32_t timeout)
{
	uint32_t tickstart = HAL_GetTick();

	while((espCheckResponse(response) != ESP_RESPONSE_CORRECT))
	{
		if((HAL_GetTick() - tickstart) > timeout)
		{
			return HAL_TIMEOUT;
		}
	}

	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	espReset
 *
 * DESCRIPTION	:	This function resets the ESP Module
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espReset(void)
{
	espWriteCommand(RESTART_COMMAND);

	if(espWaitUntilResponse("ready", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	return HAL_OK;
}


/********************* Function Description *********************************
 * FUNCTION		:	espRestore
 *
 * DESCRIPTION	:	This function restores the ESP Module to factory settings
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espRestore(void)
{
	espWriteCommand("AT+RESTORE\r\n");

	if(espWaitUntilResponse("ready", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}
	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	espSetApSettings
 *
 * DESCRIPTION	:	This function set the response for format for the AP search
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espSetApSettings(void)
{
	espWriteCommand(SET_AP_SETTING);

	if(espWaitUntilResponse("OK\r\n", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}
	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	espSetMode
 *
 * DESCRIPTION	:	This function sets the module to station mode
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espSetToStationMode(void)
{
	espWriteCommand(STATION_MODE);

	if(espWaitUntilResponse("OK\r\n", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	espConnect
 *
 * DESCRIPTION	:	This function is used to connect the module to wifi
 *
 * PARAMETERS	:	char *ssid - SSID
 * 					char *password - Password
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espConnect(char *ssid, char *password)
{
	char command[BUFFER_SIZE] = "0";

	sprintf(command,"AT+CWJAP=\"%s\",\"%s\"\r\n",ssid,password);

	//Writing to the ESP Module
	espWriteCommand(command);

	if(espWaitUntilResponse("OK\r\n", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}
	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	espDisconnect
 *
 * DESCRIPTION	:	This function is used to disconnect the module to wifi
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espDisconnect(void)
{
	//Writing to the ESP Module
	espWriteCommand("AT+CWQAP\r\n");

	if(espWaitUntilResponse("OK\r\n", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}
	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	espGetIP
 *
 * DESCRIPTION	:	This function is used to get the IP address of the module after connecting to an AP
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espGetIP(void)
{
	char temp = '0';
	uint8_t i = 0;

	memset(IPADDRESS, 0, sizeof(IPADDRESS));

	//Writing to the ESP Module
	espWriteCommand("AT+CIFSR\r\n");

	if(espWaitUntilResponse("OK\r\n", 500) != HAL_OK)
	{
		strcpy(IPADDRESS,"NA");
		return HAL_TIMEOUT;
	}

	if(espTraverseBufferUntilStringFound("\n+CIFSR:STAIP,\"") != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	while(1)
	{
		temp = circularBufferRead(&espRxBuffer);
		if(temp == '\"')
		{
			break;
		}
		IPADDRESS[i] = temp;
		i++;
	}
	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	espGetSSID
 *
 * DESCRIPTION	:	This function is used to get the SSID of the current connected AP
 *
 * PARAMETERS	:	char *ssid
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espGetSSID(char *ssid)
{
	char temp = '0';
	uint8_t i = 0;

	//Writing to the ESP Module
	espWriteCommand("AT+CWJAP?\r\n");

	if(espWaitUntilResponse("OK\r\n", 500) != HAL_OK)
	{
		strcpy(ssid,"NA");
		return HAL_TIMEOUT;
	}

	if(espTraverseBufferUntilStringFound("\n+CWJAP:\"") != HAL_OK)
	{
		return HAL_TIMEOUT;
	}


	while(1)
	{
		temp = circularBufferRead(&espRxBuffer);
		if(temp == '\"')
		{
			break;
		}
		ssid[i] = temp;
		i++;
	}
	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	espEnableMultiConn
 *
 * DESCRIPTION	:	This function is used to enable multiple connections so mulitple clients
 * 					can connect to the TCP Server
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espEnableMultiConn(void)
{
	//Writing to the ESP Module
	espWriteCommand("AT+CIPMUX=1\r\n");

	if(espWaitUntilResponse("OK\r\n", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	espCreateTCPServer
 *
 * DESCRIPTION	:	This function is used to create a TCP Server
 *
 * PARAMETERS	:	uint8_t portNumbe
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espCreateTCPServer(uint8_t portNumber)
{
	char command[BUFFER_SIZE] = "0";

	sprintf(command,"AT+CIPSERVER=1,%d\r\n",portNumber);

	//Writing to the ESP Module
	espWriteCommand(command);

	if(espWaitUntilResponse("OK\r\n", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	espSendDataToServer
 *
 * DESCRIPTION	:	This function is used to send data to server
 *
 * PARAMETERS	:	char *data - data to be sent
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espSendDataToServer(char *data)
{
	char command[BUFFER_SIZE] = "0";

	uint32_t len = strlen(data);

	sprintf(command,"AT+CIPSEND=%ld\r\n",len);

	//Writing to the ESP Module
	espWriteCommand(command);

	// > Indicates that now you can send data
	if(espWaitUntilResponse(">", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	//Send Data
	espWriteCommand(data);

	//Wait for send Okay
	if(espWaitUntilResponse("SEND OK", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

//	//Close the Connection with the client
//	memset(command,'\0',BUFFER_SIZE);
//
//	sprintf(command,"AT+CIPCLOSE\r\n");
//
//	espWriteCommand(command);
//
//	if(espWaitUntilResponse("OK\r\n", ESP_MAX_WAIT) != HAL_OK)
//	{
//		return HAL_TIMEOUT;
//	}

	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	espGetDomainIP
 *
 * DESCRIPTION	:	This function is used to get the IP Address of a domain
 *
 * PARAMETERS	:	char *url, char*ip
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espGetDomainIP(char *url, char*ip)
{
	char temp = '0';
	uint8_t i = 0;

	char command[BUFFER_SIZE] = "0";

	sprintf(command,"AT+CIPDOMAIN=\"%s\"\r\n",url);

	//Writing to the ESP Module
	espWriteCommand(command);

	if(espWaitUntilResponse("CIPDOMAIN:", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	HAL_Delay(100);	//Waiting for rest of the data to come

	while(1)
	{
		temp = circularBufferRead(&espRxBuffer);
		if(temp == '\r')
		{
			break;
		}
		ip[i] = temp;
		i++;
	}
	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	espEstablishTCPConnection
 *
 * DESCRIPTION	:	This function is used to establish a tcp connection
 *
 * PARAMETERS	:	char *ip
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espEstablishTCPConnection(char *ip)
{
	char command[BUFFER_SIZE] = "0";

	sprintf(command,"AT+CIPSTART=\"TCP\",\"%s\",80\r\n",ip);

	//Writing to the ESP Module
	espWriteCommand(command);

	if(espWaitUntilResponse("OK\r\n", ESP_MAX_WAIT) != HAL_OK)
	{
		if(espWaitUntilResponse("ALREADY CONNECT\r\n", ESP_MAX_WAIT) != HAL_OK)
		{
			return HAL_TIMEOUT;
		}
	}

	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	espGetLinkId
 *
 * DESCRIPTION	:	This function is used to find the LinkId
 *
 * PARAMETERS	:	char *linkId variable to store the linkId
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
char espGetLinkId(void)
{
	//Clearing the circular buffer
	circularBufferClear(&espRxBuffer);

	//Wait for +IPD. this will be received in the RX buffer when a TCP Client tries to connect to server
	while((espCheckResponse("+IPD,")) != ESP_RESPONSE_CORRECT);

	//Wait for the rest of the data to be received
	HAL_Delay(100);

	//Extract the Link Id
	char linkId = circularBufferRead(&espRxBuffer);

	//Return the Link Id
	return linkId;
}

/********************* Function Description *********************************
 * FUNCTION		:	espGetAvailableNetwork
 *
 * DESCRIPTION	:	This function is used to get all the available networks
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef espGetAvailableNetwork(void)
{
	uint8_t ssidCount = 0;

    // Clear the ssid array (optional, but good practice)
	for(int i=0; i<10; i++)
	{
		memset(ssidList[i].ssid, 0, sizeof(ssidList[i].ssid));
		memset(ssidList[i].signalStrength, 0, sizeof(ssidList[i].signalStrength));
		memset(ssidList[i].macAddress, 0, sizeof(ssidList[i].macAddress));
	}
	//Writing to the ESP Module
	espWriteCommand(LIST_AP);

	if(espWaitUntilResponse("OK\r\n", ESP_MAX_WAIT) != HAL_OK)
	{
		//return HAL_TIMEOUT;
	}

	while(espRxBuffer.front <= espRxBuffer.rear)
	{
		if(ssidCount >= 10)
		{
			break;
		}

		//Find \n+CWLAP:( string
		if(espTraverseBufferUntilStringFound("\n+CWLAP:(") != HAL_OK)
		{
			return HAL_ERROR;

		}

		//Storing Security
		ssidList[ssidCount].security = ((espRxBuffer.data[espRxBuffer.front]) - '0');

		//Storing SSID Name
		espRxBuffer.front = espRxBuffer.front + 3;
		for(int i=0; i<20; i++)
		{
			if((espRxBuffer.data[espRxBuffer.front]) == '"')
			{
				break;
			}
			strncat(ssidList[ssidCount].ssid, &(espRxBuffer.data[espRxBuffer.front]), 1);
			espRxBuffer.front++;
		}

		//Store Strength
		if(espTraverseBufferUntilStringFound(",-") != HAL_OK)
		{
			return HAL_ERROR;

		}

		strcat(ssidList[ssidCount].signalStrength, "-");

		for(int i=0; i<2; i++)
		{
			strncat(ssidList[ssidCount].signalStrength, &(espRxBuffer.data[espRxBuffer.front]), 1);
			espRxBuffer.front++;
		}

		//Store Mac Address
		if(espTraverseBufferUntilStringFound("\"") != HAL_OK)
		{
			return HAL_ERROR;

		}

		for(int i=0; i<17; i++)
		{
			strncat(ssidList[ssidCount].macAddress, &(espRxBuffer.data[espRxBuffer.front]), 1);
			espRxBuffer.front++;
		}

		//Remove repeated or false SSIDs
		for(int i=0; i<10; i++)
		{
			if(i == ssidCount)
			{
				continue;
			}

			if(!(strcmp((ssidList[i].ssid),(ssidList[ssidCount].ssid))))
			{
				memset(ssidList[ssidCount].ssid, 0, sizeof(ssidList[ssidCount].ssid));
				memset(ssidList[ssidCount].signalStrength, 0, sizeof(ssidList[ssidCount].signalStrength));
				memset(ssidList[ssidCount].macAddress, 0, sizeof(ssidList[ssidCount].macAddress));
			}
		}

		if(!(strcmp((ssidList[ssidCount].ssid),"\0")))
		{
			memset(ssidList[ssidCount].ssid, 0, sizeof(ssidList[ssidCount].ssid));
			memset(ssidList[ssidCount].signalStrength, 0, sizeof(ssidList[ssidCount].signalStrength));
			memset(ssidList[ssidCount].macAddress, 0, sizeof(ssidList[ssidCount].macAddress));
		}
		else
		{
			ssidCount++;
		}
	}
	return HAL_OK;
}


/********************* Function Description *********************************
 * FUNCTION		:	getGeolocation
 *
 * DESCRIPTION	:	This function is used to get the geolocation using google API
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef getGeolocation(void)
{
	if(wifiConnected)
	{
		//Create JSON Payload
		char jsonPayload[256];  // Ensure the buffer is large enough for your JSON data

		sprintf(jsonPayload, "{"
		                     "\"wifiAccessPoints\": ["
		                     "{"
		                     "\"macAddress\": \"%s\","
		                     "\"signalStrength\": %s"
		                     "},"
		                     "{"
		                     "\"macAddress\": \"%s\","
		                     "\"signalStrength\": %s"
		                     "}"
		                     "]"
		                     "}",
		                     ssidList[0].macAddress, ssidList[0].signalStrength, ssidList[1].macAddress, ssidList[1].signalStrength);

		int contentLength = strlen(jsonPayload);

		//Establish a SSL connection to Google's server
		espWriteCommand("AT+CIPSTART=\"SSL\",\"www.googleapis.com\",443\r\n");
		if(espWaitUntilResponse("OK\r\n", ESP_MAX_WAIT) != HAL_OK)
		{
			return HAL_TIMEOUT;
		}

	    char postRequest[512];
	    snprintf(postRequest, sizeof(postRequest),
	             "POST /geolocation/v1/geolocate?key=apiKey HTTP/1.1\r\n"
	             "Host: www.googleapis.com\r\n"
	             "Content-Type: application/json\r\n"
	             "Content-Length: %d\r\n\r\n"
	             "%s\r\n",
	             contentLength, jsonPayload);

	    char temp[25];

	    //Send Lenght of Data
	    snprintf(temp,sizeof(temp),"AT+CIPSEND=%d\r\n",(int)strlen(postRequest));
	    espWriteCommand(temp);
		if(espWaitUntilResponse(">", ESP_MAX_WAIT) != HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		//Send Data
		espWriteCommand(postRequest);
		if(espWaitUntilResponse("SEND OK", ESP_MAX_WAIT) != HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		//Wait for Response
		if(espWaitUntilResponse("},", ESP_MAX_WAIT) != HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		//Extracting Location
		if(espTraverseBufferUntilStringFound("lat\": ") != HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		//Extracting Latitude
		char lat[20] = {0};
		while(espRxBuffer.data[espRxBuffer.front] != ',')
		{
			strncat(lat, &(espRxBuffer.data[espRxBuffer.front]), 1);
			espRxBuffer.front++;
		}
		geoLocation.latitude = atof(lat);

		//Extracting Longitude
		if(espTraverseBufferUntilStringFound("lng\": ") != HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		char longitude[20] = {0};
		while(espRxBuffer.data[espRxBuffer.front] != '\n')
		{
			strncat(longitude, &(espRxBuffer.data[espRxBuffer.front]), 1);
			espRxBuffer.front++;
		}

		//Closing the Connection
		espWriteCommand("AT+CIPCLOSE\r\n");

		if(espWaitUntilResponse("OK\r\n", ESP_MAX_WAIT) != HAL_OK)
		{
			return HAL_TIMEOUT;
		}

		geoLocation.longitude = atof(longitude);

		gotlocation = true;

		return HAL_OK;
	}
	else
	{
		return HAL_ERROR;
	}

	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	getWeather
 *
 * DESCRIPTION	:	This function is used to get the weather
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef getWeather(void)
{
	snprintf(weatherRequest, sizeof(weatherRequest),
			"GET /data/2.5/weather?lat=%f&lon=%f&appid=apiKey&units=metric HTTP/1.1\r\n"
	        "Host: api.openweathermap.org\r\n"
	        "Connection: close\r\n\r\n"
			,geoLocation.latitude,geoLocation.longitude);

	//Establish TCP Connection
	if(espEstablishTCPConnection("api.openweathermap.org") != HAL_OK)
	{
		return HAL_ERROR;
	}

	//Send data to server and check response
	if(espSendDataToServer(weatherRequest) != HAL_OK)
	{
		return HAL_ERROR;
	}

	if(espWaitUntilResponse("\"cod\":", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	//Extracting weather type
	if(espTraverseBufferUntilStringFound("main\":\"") != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	memset(weatherType, '\0', sizeof(weatherType));

	while(espRxBuffer.data[espRxBuffer.front] != '\"')
	{
		strncat(weatherType, &(espRxBuffer.data[espRxBuffer.front]), 1);
		espRxBuffer.front++;
	}

	//Extracting Icon
	if(espTraverseBufferUntilStringFound("icon\":\"") != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	for(int i=0; i<3; i++)
	{
		weatherIcon[i] = espRxBuffer.data[espRxBuffer.front];
		espRxBuffer.front++;
	}

	//Extracting Temperature
	if(espTraverseBufferUntilStringFound("temp\":") != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	char tempTemperature[2] = {0};
	tempTemperature[0] = espRxBuffer.data[espRxBuffer.front];
	espRxBuffer.front++;
	tempTemperature[1] = espRxBuffer.data[espRxBuffer.front];

	weatherTemperature = atoi(tempTemperature);

	return HAL_OK;
}

/********************* Function Description *********************************
 * FUNCTION		:	convertToTimestamp
 *
 * DESCRIPTION	:	This function is used to convert string time and date to a timestamp
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
time_t convertToTimestamp(const char *input) {
    // Array of month abbreviations to convert month string to an integer
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // Create a struct to store parsed time
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));

    // Temporary variables to hold parts of the date string
    char weekday[4], month[4];
    int day, hour, minute, second, year;

    // Parse the input string
    sscanf(input, "%3s%3s%02d%02d:%02d:%02d%d", weekday, month, &day, &hour, &minute, &second, &year);

    // Find the month index
    for (int i = 0; i < 12; i++) {
        if (strncmp(month, months[i], 3) == 0) {
            tm.tm_mon = i;  // Set the month in struct tm (0-11)
            break;
        }
    }

    // Set the rest of the fields in struct tm
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;
    tm.tm_year = year - 1900; // Year since 1900

    // Convert to time_t timestamp
    time_t timestamp = mktime(&tm);
    return timestamp;
}


/********************* Function Description *********************************
 * FUNCTION		:	settingTime
 *
 * DESCRIPTION	:	This function is used to set the time got from the NTP Server to rtc
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
void settingTime(time_t timestamp)
{
    // Convert the timestamp to UTC time
    struct tm *tm_info = gmtime(&timestamp);

    int hour24 = tm_info->tm_hour;
    gTime.Hours = (hour24 % 12 == 0) ? 12 : hour24 % 12;
    gTime.Minutes = tm_info->tm_min;
    gTime.Seconds = tm_info->tm_sec;
    gTime.TimeFormat = (hour24 >= 12) ? 1 : 0;

    gDate.Date = tm_info->tm_mday;
    gDate.Month = tm_info->tm_mon + 1;
    gDate.WeekDay = tm_info->tm_wday;
    gDate.Year = (tm_info->tm_year % 100);

    HAL_RTC_SetDate(&hrtc,&gDate,RTC_FORMAT_BIN);
    HAL_RTC_SetTime(&hrtc,&gTime,RTC_FORMAT_BIN);

    gettingNTPTime = false;
    gotNTP = true;
}


/********************* Function Description *********************************
 * FUNCTION		:	getNTPTime
 *
 * DESCRIPTION	:	This function is used to get the time from the NTP server
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	HAL_StatusTypeDef
 *
 * **************************************************************************/
HAL_StatusTypeDef getNTPTime(void)
{
	gettingNTPTime = true;

	espWriteCommand("AT+CIPSNTPCFG=1,0,\"time.google.com\"\r\n");

	if(espWaitUntilResponse("TIME_UPDATED\r\n", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	espWriteCommand("AT+CIPSNTPTIME?\r\n");

	if(espWaitUntilResponse("OK\r\n", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	//Extracting the Time and Date
	char timeString[50] = {0};

	if(espTraverseBufferUntilStringFound("NTPTIME:") != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	while(espRxBuffer.data[espRxBuffer.front] != '\r')
	{
		if(espRxBuffer.data[espRxBuffer.front] == ' ')
		{
			espRxBuffer.front++;
			continue;
		}
		strncat(timeString, &(espRxBuffer.data[espRxBuffer.front]), 1);
		espRxBuffer.front++;
	}

	//Converting it to TimeStamp
	time_t timestamp = convertToTimestamp(timeString);

	//Establish a SSL connection to Google's server
	espWriteCommand("AT+CIPSTART=\"SSL\",\"maps.googleapis.com\",443\r\n");
	if(espWaitUntilResponse("OK\r\n", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

    //Prepare the HTTP GET request
    char request[512];
    snprintf(request, sizeof(request),
             "GET /maps/api/timezone/json?location=%f,%f&timestamp=%ld&key=apikey HTTP/1.1\r\n"
             "Host: maps.googleapis.com\r\n"
             "Connection: close\r\n\r\n",
             geoLocation.latitude, geoLocation.longitude, (long int)timestamp);

    //Sending length of Request
    char temp[25];
    snprintf(temp,sizeof(temp),"AT+CIPSEND=%d\r\n",(int)strlen(request));
    espWriteCommand(temp);
	if(espWaitUntilResponse(">", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	//Sending the request
	espWriteCommand(request);
	if(espWaitUntilResponse("SEND OK", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	//Waiting for Response
	if(espWaitUntilResponse("}", ESP_MAX_WAIT) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	//Extracting dstOffset
	if(espTraverseBufferUntilStringFound("dstOffset\" : ") != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	char dstOffsetString[10] = {0};

	while(espRxBuffer.data[espRxBuffer.front] != ',')
	{
		strncat(dstOffsetString, &(espRxBuffer.data[espRxBuffer.front]), 1);
		espRxBuffer.front++;
	}

	int32_t dstOffset = atoi(dstOffsetString);

	//Extracting raw Offset
	if(espTraverseBufferUntilStringFound("rawOffset\" : ") != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	char rawOffsetString[10] = {0};

	while(espRxBuffer.data[espRxBuffer.front] != ',')
	{
		strncat(rawOffsetString, &(espRxBuffer.data[espRxBuffer.front]), 1);
		espRxBuffer.front++;
	}
	int32_t rawOffset = atoi(rawOffsetString);

	//Getting Local Time
	int64_t localTime = (long int)timestamp + rawOffset + dstOffset;

	//Setting the Time
	settingTime((time_t)localTime);

	return HAL_OK;
}
