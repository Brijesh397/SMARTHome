/* USER CODE BEGIN Header */

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

#define ILI_SCR_HORIZONTAL 320
#define ILI_SCR_VERTICAL   240
#define BUFFOR_SCR_ROWS 40

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi2_tx;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

//Task Handles
TaskHandle_t lvglTaskHandle;
TaskHandle_t temperatureTaskHandle;
TaskHandle_t temperatureSensorTaskHandle;
TaskHandle_t rtcTaskHandle;
TaskHandle_t wifiTaskkHandle;
TaskHandle_t weatherTaskkHandle;

//Mutex Handle
SemaphoreHandle_t lvglMutex;

//Queue Handle
QueueHandle_t adcRawDataQueue;

//RTC Structures
RTC_DateTypeDef gDate;
RTC_TimeTypeDef gTime;

//LVGL
lv_indev_drv_t indev_drv;
static lv_disp_draw_buf_t disp_buf;
static lv_color_t buf_1[ILI_SCR_HORIZONTAL * BUFFOR_SCR_ROWS] ;
static lv_disp_drv_t disp_drv;

//Global Variables
char timeArray[14] = {0};
char dateArray[21] = {0};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_ADC1_Init(void);
static void MX_RTC_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

void lcdInit(void);
void LVGLTask(void *parameters);
void temperatureControlTask(void *parameters);
void temperatureSensorTask(void *parameters);
void rtcTask(void *parameters);
void wifiTask(void *parameters);
void weatherTask(void *parameters);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_ADC1_Init();
  MX_RTC_Init();
  MX_USART2_UART_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
  BaseType_t status;

  //Display Initialization
  lcdInit();

  /*************MUTEX CREATION***********************/
  lvglMutex = xSemaphoreCreateMutex();

  /*************QUEUE CREATION***********************/
  //Raw ADC value queue
  adcRawDataQueue = xQueueCreate(2,sizeof(uint16_t));
  configASSERT(adcRawDataQueue != NULL);

  /*************TASK CREATION***********************/
  //LVGL Task
  if(lvglMutex != NULL)
  {
	  status = xTaskCreate(LVGLTask, "LVGLTask", 2048, NULL, 2, &lvglTaskHandle);
	  configASSERT(status == pdPASS);
  }

  //Temperature Relay Control Task
  status = xTaskCreate(temperatureControlTask, "temperatureControlTask", 1024, NULL, 1, &temperatureTaskHandle);
  configASSERT(status == pdPASS);

  //Temperature Sensor Task
  status = xTaskCreate(temperatureSensorTask, "temperatureSensorTask", 1024, NULL, 1, &temperatureSensorTaskHandle);
  configASSERT(status == pdPASS);

  //RTC Task
  status = xTaskCreate(rtcTask, "rtcTask", 1024, NULL, 1, &rtcTaskHandle);
  configASSERT(status == pdPASS);

  //WiFi Task
  status = xTaskCreate(wifiTask, "wifiTask", 10240, NULL, 1, &wifiTaskkHandle);
  configASSERT(status == pdPASS)

  //Weather Task
  status = xTaskCreate(weatherTask, "weatherTask", 1024, NULL, 1, &weatherTaskkHandle);
  configASSERT(status == pdPASS)

  //Start Scheduler
  vTaskStartScheduler();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* EXTI9_5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
  /* DMA1_Stream4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_12;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 1;
  sTime.Minutes = 30;
  sTime.Seconds = 0;
  sTime.TimeFormat = RTC_HOURFORMAT12_AM;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_TUESDAY;
  sDate.Month = RTC_MONTH_AUGUST;
  sDate.Date = 13;
  sDate.Year = 24;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TOUCH_CS_GPIO_Port, TOUCH_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, TFT_RESET_Pin|TFT_DC_Pin|LD4_Pin|LD3_Pin
                          |LD5_Pin|LD6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, CoolingRelay_Pin|HeatingRelay_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TOUCH_CS_Pin */
  GPIO_InitStruct.Pin = TOUCH_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TOUCH_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TOUCH_IRQ_Pin */
  GPIO_InitStruct.Pin = TOUCH_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(TOUCH_IRQ_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TFT_CS_Pin */
  GPIO_InitStruct.Pin = TFT_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TFT_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TFT_RESET_Pin TFT_DC_Pin CoolingRelay_Pin HeatingRelay_Pin
                           LD4_Pin LD3_Pin LD5_Pin LD6_Pin */
  GPIO_InitStruct.Pin = TFT_RESET_Pin|TFT_DC_Pin|CoolingRelay_Pin|HeatingRelay_Pin
                          |LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/**************FUNCTIONS**********************/

/********************* Function Description *********************************
 * FUNCTION		:	lcdInit
 *
 * DESCRIPTION	:	This function initializes the LCD along with touch drivers with LVGL
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void lcdInit(void)
{
	//Initializing Display
	ILI9341_Init();

	//Initializing Touch
	XPT2046_Init(&hspi1, EXTI9_5_IRQn);

	HAL_Delay(30);

	//Initializing LVGL
	lv_init();

	//Registering Display
	lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, ILI_SCR_HORIZONTAL * BUFFOR_SCR_ROWS);
	lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
	disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
	disp_drv.flush_cb = ILI9341_flush;        /*Set a flush callback to draw to the display*/
	disp_drv.hor_res = ILI_SCR_HORIZONTAL;                 /*Set the horizontal resolution in pixels*/
	disp_drv.ver_res = ILI_SCR_VERTICAL;                 /*Set the vertical resolution in pixels*/
	lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/

	//Registering Touch
	lv_indev_drv_init(&indev_drv);
	indev_drv.type =LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = lvXPT2064_Read;
	lv_indev_drv_register(&indev_drv);

	 HAL_Delay(10);
}

/*********************TASKS**************************/

/********************* Function Description *********************************
 * FUNCTION		:	LVGLTask
 *
 * DESCRIPTION	:	This function handles the LVGL tasks
 *
 * PARAMETERS	:	void *parameters
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void LVGLTask(void *parameters)
{
	//Creating Boot Screen
	if(xSemaphoreTake(lvglMutex,pdMS_TO_TICKS(100)))
	{
		createBootScreen();
		xSemaphoreGive(lvglMutex);
	}

	for(;;)
	{
		if(xSemaphoreTake(lvglMutex,pdMS_TO_TICKS(100)))
		{
			//Getting Touch Data
			XPT2046_Task();
			//lvXPT2064_Read(&indev_drv,(lv_indev_data_t*) &indev_drv.user_data);

			//Updating Homescreen
			if(activeScreen == HOMESCREEN)
			{
				lv_label_set_text_fmt(roomTemperatureLabel, "%d", roomTemperature);
				lv_label_set_text_fmt(timeLabel, "%s",timeArray);
				lv_label_set_text_fmt(dateLabel, "%s",dateArray);
			}

			//LVGL Functions
			lv_task_handler();
			lv_tick_inc(5);  // Assuming FreeRTOS tick is 1 ms
			xSemaphoreGive(lvglMutex);
		}
		vTaskDelay(pdMS_TO_TICKS(5));
	}
}

/********************* Function Description *********************************
 * FUNCTION		:	temperatureControlTask
 *
 * DESCRIPTION	:	This function handles the heating and cooling relays
 *
 * PARAMETERS	:	void *parameters
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void temperatureControlTask(void *parameters)
{
	for(;;)
	{
		if(coolingEnabled)
		{
			if(roomTemperature >= temperature)
			{
				HAL_GPIO_WritePin(CoolingRelay_GPIO_Port, CoolingRelay_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(CoolingRelay_GPIO_Port, CoolingRelay_Pin, GPIO_PIN_SET);
			}
		}
		else
		{
			HAL_GPIO_WritePin(CoolingRelay_GPIO_Port, CoolingRelay_Pin, GPIO_PIN_SET);
		}

		if(heatingEnabled)
		{
			if(roomTemperature <= temperature)
			{
				HAL_GPIO_WritePin(HeatingRelay_GPIO_Port, HeatingRelay_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(HeatingRelay_GPIO_Port, HeatingRelay_Pin, GPIO_PIN_SET);
			}
		}
		else
		{
			HAL_GPIO_WritePin(HeatingRelay_GPIO_Port, HeatingRelay_Pin, GPIO_PIN_SET);
		}
	}
}

/********************* Function Description *********************************
 * FUNCTION		:	temperatureSensorTask
 *
 * DESCRIPTION	:	This function handles the Temperature Sensor data from the ADC interrupts
 *
 * PARAMETERS	:	void *parameters
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void temperatureSensorTask(void *parameters)
{
	BaseType_t adcWait;
	uint32_t temp = 0;
	float tempSensorRawValue = 0;
	float tempSensorAverage = 0;
	uint8_t i = 0;

	for(;;)
	{
		if(activeScreen != BOOT)
		{
			//Enabling the ADC in Interrupt Mode
			if(HAL_ADC_Start_IT(&hadc1) != HAL_OK)
			{
				Error_Handler();
			}

			//Waiting to receive ADC data from interrupts
			adcWait = xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
			if(adcWait == pdTRUE)
			{
				//Reading the ADC data
				xQueueReceive(adcRawDataQueue, &temp, portMAX_DELAY);

				//Converting the Value to Voltage
				tempSensorRawValue = (2.7 * temp)/4095;

				if(i != 50)	//Taking average of 50 values
				{
					//Converting Voltage to Temperature
					tempSensorRawValue = ((tempSensorRawValue - 0.5)/0.01);

					if(tempSensorRawValue < 50)
					{
						tempSensorAverage += tempSensorRawValue;
						i++;
					}
				}
				else
				{
					//Converting the Voltage to actual Temperature
					roomTemperature = tempSensorAverage / 50;
					i = 0;
					tempSensorAverage = 0;

					//Disabling the ADC Interrupts
					if(HAL_ADC_Stop_IT(&hadc1) != HAL_OK)
					{
						Error_Handler();
					}
					vTaskDelay(pdMS_TO_TICKS(10000));
				}
			}
		}
	}
}

/********************* Function Description *********************************
 * FUNCTION		:	rtcTask
 *
 * DESCRIPTION	:	This function handles the RTC related task
 *
 * PARAMETERS	:	void *parameters
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void rtcTask(void *parameters)
{
	for(;;)
	{
		if((activeScreen != DATE) && (activeScreen != TIME) && (gettingNTPTime != true))
		{
			/* Get the RTC current Time */
			HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
			/* Get the RTC current Date */
			HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);

			sprintf((char*)timeArray,"%02d:%02d %s",gTime.Hours, gTime.Minutes, (gTime.TimeFormat? "PM" : "AM"));

			sprintf((char*)dateArray,"%s, %s %02d",dayOfWeekToString((day_t)gDate.WeekDay), monthToString((month_t)gDate.Month), gDate.Date);
		}
		else if(activeScreen == DATE)
		{
			HAL_RTC_SetDate(&hrtc,&gDate,RTC_FORMAT_BIN);
		}
		else if(activeScreen == TIME)
		{
			HAL_RTC_SetTime(&hrtc,&gTime,RTC_FORMAT_BIN);
		}
	}
}

/********************* Function Description *********************************
 * FUNCTION		:	wifiTask
 *
 * DESCRIPTION	:	This function handles WiFi related task
 *
 * PARAMETERS	:	void *parameters
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void wifiTask(void *parameters)
{
	espInit();

	//Reseting the ESP Module
	if(espReset() != HAL_OK)
	{
		espInitialised = false;
	}

	//Restoring the ESP Module to factory settings
	if(espRestore() != HAL_OK)
	{
		espInitialised = false;
	}

	//Setting the Module to Station Mode
	if(espSetToStationMode() != HAL_OK)
	{
		espInitialised = false;
	}

	//Setting the AP format
	if(espSetApSettings() != HAL_OK)
	{
		espInitialised = false;
	}
	else
	{
		espInitialised = true;
	}

	//Creating the Temperature Screen
	if(xSemaphoreTake(lvglMutex,pdMS_TO_TICKS(100)))
	{
		lv_obj_del(lv_disp_get_scr_act(NULL));
		createTemperatureScreen();
		xSemaphoreGive(lvglMutex);
	}

	for(;;)
	{
		//If the ESP module was not initialised correctly on boot it will try to reinitialize it
		if(activeScreen == WIFITURNINGON)
		{
			//Reseting the ESP Module
			if(espRestore() != HAL_OK)
			{
				espInitialised = false;
			}

			//Setting the Module to Station Mode
			if(espSetToStationMode() != HAL_OK)
			{
				espInitialised = false;
			}

			if(espSetApSettings() != HAL_OK)
			{
				espInitialised = false;

				createWifiErrorMessageBox();
				xSemaphoreGive(lvglMutex);

				vTaskDelay(pdMS_TO_TICKS(5000));

				lv_obj_del(lv_disp_get_scr_act(NULL));
				createNavScreen();
			}
			else	//If Initialization was successful
			{
				espInitialised = true;

				lv_obj_del(lv_disp_get_scr_act(NULL));
				createWifiScreen();
			}
		}


		//Searching WiFi
		if(activeScreen == WIFILOADING)
		{
			//Connecting the Module to the Internet
			if(espGetAvailableNetwork() == HAL_OK)
			{
				if(xSemaphoreTake(lvglMutex,pdMS_TO_TICKS(100)))
				{
					lv_obj_del(lv_disp_get_scr_act(NULL));
					createWifiConnectScreen();

					xSemaphoreGive(lvglMutex);
				}

			}
			else
			{
				if(xSemaphoreTake(lvglMutex,pdMS_TO_TICKS(100)))
				{
					lv_obj_del(lv_disp_get_scr_act(NULL));
					createWifiScreen();

					xSemaphoreGive(lvglMutex);
				}
			}
		}

		//Connecting WiFi
		if(activeScreen == WIFICONNECTING)
		{
			if(espConnect(SSID, PASSWORD) == HAL_OK)
			{
				if(xSemaphoreTake(lvglMutex,pdMS_TO_TICKS(100)))
				{
					createWifiConnectingSuccessfullMessageBox();
					wifiConnected = true;
					xSemaphoreGive(lvglMutex);
				}

				vTaskDelay(pdMS_TO_TICKS(5000));

				if(xSemaphoreTake(lvglMutex,pdMS_TO_TICKS(100)))
				{
					lv_obj_del(wifiConnectingMessageBox);
					lv_obj_del(wifiConnectingSuccessfullMessageBox);
					lv_obj_del(wifiPasswordScreen);
					createWifiScreen();
					xSemaphoreGive(lvglMutex);
				}

				if(wifiConnected)
				{
					getGeolocation();
					getNTPTime();
				}
			}
			else
			{
				if(xSemaphoreTake(lvglMutex,pdMS_TO_TICKS(100)))
				{
					createWifiConnectingFailedMessageBox();
					wifiConnected = false;
					xSemaphoreGive(lvglMutex);
				}

				vTaskDelay(pdMS_TO_TICKS(5000));

				if(xSemaphoreTake(lvglMutex,pdMS_TO_TICKS(100)))
				{
					lv_obj_del(wifiConnectingMessageBox);
					lv_obj_del(wifiConnectingFailedMessageBox);
					lv_obj_del(wifiPasswordScreen);
					createWifiConnectScreen();
					xSemaphoreGive(lvglMutex);
				}
			}
		}
	}
}

/********************* Function Description *********************************
 * FUNCTION		:	weatherTask
 *
 * DESCRIPTION	:	This function handles weather related tsdk
 *
 * PARAMETERS	:	void *parameters
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void weatherTask(void *parameters)
{
	for(;;)
	{
		if((wifiConnected) && (gotlocation) && (gotNTP))
		{
			getWeather();
			if(activeScreen == HOMESCREEN)
			{
				if(xSemaphoreTake(lvglMutex,pdMS_TO_TICKS(100)))
				{
					lv_label_set_text_fmt(weatherTemperatureLabel, "%d°", weatherTemperature);
					lv_label_set_text_fmt(weatherCelciusLabel, "%s", weatherType);
					setWeatherIcon();
					xSemaphoreGive(lvglMutex);
				}
			}

			//Get weather update every 10mins
			vTaskDelay(pdMS_TO_TICKS(600000));
		}
	}
}

/*****************IRQ HANDLERS********************/
//UART IRQ Handler for ESP module
void USART2_IRQHandler(void)
{
	espIRQHandler();
}


//Touch IRQ
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == TOUCH_IRQ_Pin)
	{
		XPT2046_IRQ();
	}
}

//Temp Sensor IRQ
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	//Get the RAW ADC Value
	uint32_t adcRawValue = HAL_ADC_GetValue(hadc);

	//Store the RAW value in Queue
	if(!(xQueueIsQueueFullFromISR(adcRawDataQueue)))	//If queue is not full
	{
		//Enqueue data
		xQueueSendFromISR(adcRawDataQueue,(void*)&adcRawValue,NULL);
		//Notify Task
		xTaskNotifyFromISR(temperatureSensorTaskHandle,0,eNoAction,NULL);
	}
}

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
