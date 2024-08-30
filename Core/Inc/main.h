/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "../../lvgl/lvgl.h"
#include "../../XPT2064/XPT2064.h"
#include "../../XPT2064/lv_drv.h"
#include "../../ili9341/core.h"
#include "../../ili9341/lv_driver.h"
#include "smartHome.h"
#include <esp.h>

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern RTC_DateTypeDef gDate;
extern RTC_TimeTypeDef gTime;
extern RTC_HandleTypeDef hrtc;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PC14_OSC32_IN_Pin GPIO_PIN_14
#define PC14_OSC32_IN_GPIO_Port GPIOC
#define PC15_OSC32_OUT_Pin GPIO_PIN_15
#define PC15_OSC32_OUT_GPIO_Port GPIOC
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define TOUCH_CLK_Pin GPIO_PIN_5
#define TOUCH_CLK_GPIO_Port GPIOA
#define TOUCH_DO_Pin GPIO_PIN_6
#define TOUCH_DO_GPIO_Port GPIOA
#define TOUCH_DIN_Pin GPIO_PIN_7
#define TOUCH_DIN_GPIO_Port GPIOA
#define TOUCH_CS_Pin GPIO_PIN_4
#define TOUCH_CS_GPIO_Port GPIOC
#define TOUCH_IRQ_Pin GPIO_PIN_5
#define TOUCH_IRQ_GPIO_Port GPIOC
#define TOUCH_IRQ_EXTI_IRQn EXTI9_5_IRQn
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define TFT_CS_Pin GPIO_PIN_12
#define TFT_CS_GPIO_Port GPIOB
#define TFT_SCK_Pin GPIO_PIN_13
#define TFT_SCK_GPIO_Port GPIOB
#define TFT_MISO_Pin GPIO_PIN_14
#define TFT_MISO_GPIO_Port GPIOB
#define TFT_MOSI_Pin GPIO_PIN_15
#define TFT_MOSI_GPIO_Port GPIOB
#define TFT_RESET_Pin GPIO_PIN_8
#define TFT_RESET_GPIO_Port GPIOD
#define TFT_DC_Pin GPIO_PIN_9
#define TFT_DC_GPIO_Port GPIOD
#define CoolingRelay_Pin GPIO_PIN_10
#define CoolingRelay_GPIO_Port GPIOD
#define HeatingRelay_Pin GPIO_PIN_11
#define HeatingRelay_GPIO_Port GPIOD
#define LD4_Pin GPIO_PIN_12
#define LD4_GPIO_Port GPIOD
#define LD3_Pin GPIO_PIN_13
#define LD3_GPIO_Port GPIOD
#define LD5_Pin GPIO_PIN_14
#define LD5_GPIO_Port GPIOD
#define LD6_Pin GPIO_PIN_15
#define LD6_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */
extern SemaphoreHandle_t lvglMutex;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
