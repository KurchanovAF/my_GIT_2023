/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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
#define ADC1_OUT1R_Pin GPIO_PIN_0
#define ADC1_OUT1R_GPIO_Port GPIOA
#define ADC2_OUT2R_Pin GPIO_PIN_1
#define ADC2_OUT2R_GPIO_Port GPIOA
#define ADC1_CONTR_Pin GPIO_PIN_2
#define ADC1_CONTR_GPIO_Port GPIOA
#define ADC2_SD2_Pin GPIO_PIN_3
#define ADC2_SD2_GPIO_Port GPIOA
#define LMX_nCS_Pin GPIO_PIN_4
#define LMX_nCS_GPIO_Port GPIOA
#define DAC1_RFI_Pin GPIO_PIN_5
#define DAC1_RFI_GPIO_Port GPIOA
#define RFM_Pin GPIO_PIN_6
#define RFM_GPIO_Port GPIOA
#define ADC1_SD1_Pin GPIO_PIN_7
#define ADC1_SD1_GPIO_Port GPIOA
#define ADC2_OUT0R_Pin GPIO_PIN_4
#define ADC2_OUT0R_GPIO_Port GPIOC
#define RES_Pin GPIO_PIN_5
#define RES_GPIO_Port GPIOC
//=======================================
#define PPS1_Pin GPIO_PIN_7
#define PPS1_GPIO_Port GPIOC
#define PPS2_Pin GPIO_PIN_9
#define PPS2_GPIO_Port GPIOA
//=======================================

#define DAC_CLR_Pin GPIO_PIN_0
#define DAC_CLR_GPIO_Port GPIOB
#define ADC1_OUT3_Pin GPIO_PIN_1
#define ADC1_OUT3_GPIO_Port GPIOB
#define DAC_LDAC_Pin GPIO_PIN_2
#define DAC_LDAC_GPIO_Port GPIOB
#define DAC_nCS_Pin GPIO_PIN_12
#define DAC_nCS_GPIO_Port GPIOB
#define SX100KHZ_Pin GPIO_PIN_8
#define SX100KHZ_GPIO_Port GPIOC
#define DAC_LDACA11_Pin GPIO_PIN_11
#define DAC_LDACA11_GPIO_Port GPIOA
#define NSSA_Pin GPIO_PIN_2
#define NSSA_GPIO_Port GPIOD
#define SY_Pin GPIO_PIN_6
#define SY_GPIO_Port GPIOB
#define EN_Pin GPIO_PIN_7
#define EN_GPIO_Port GPIOB
#define MOD_CRNT_Pin GPIO_PIN_8
#define MOD_CRNT_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
