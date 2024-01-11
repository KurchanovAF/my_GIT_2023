/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "my_FUN.h"
#include "tim.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#include "var.h"

#include "my_FUN.h"


static inline void UpdateRS232(void);
static inline void UpdateDataADC1(void);
static inline void UpdateDataADC2(void);

static inline void funWork_SCAN_CRNT(void);
static inline void funWork_TEST_ADC(void);
static inline void funWork_TEST_ADC_2(void);
static inline void funWork_TEST_ADC_3(void);
static inline void funWork_SCAN_FREQ(void);
static inline void funWork_TEST_FACTOR_OUT(void);
static inline void funWork_TEST_TEMP_CELL(void);
static inline void funWork_VOID_TEST(void);

static inline void Difference(void);
static inline void funWork_HIST(void);

static inline void my_ADC2_1(void);

extern DAC_HandleTypeDef hdac1;
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc2;
extern DMA_HandleTypeDef hdma_adc3;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart3;
/* USER CODE BEGIN EV */
extern I2C_HandleTypeDef hi2c3;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */
  my_Tick += uwTickFreq;
  // my_Tick -= uwTickFreq;
  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel1 global interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */
	// ADC1 Priority Medium
	my_N_DMA1_1++;
	uint32_t flag_it = DMA1->ISR;
	if(my_N_DMA1_1 == 1) my_Flag_DMA1_1_1 = flag_it;
	if(my_N_DMA1_1 == 2) my_Flag_DMA1_1_2 = flag_it;
	if(my_N_DMA1_1 == 3) my_Flag_DMA1_1_3 = flag_it;
	// ������ �������� ������ ���������
	if ( (flag_it & DMA_FLAG_HT1) == DMA_FLAG_HT1){
		// ��������� ���������� �� ���������� ������ ��������
		DMA1_Channel1->CCR &= ~DMA_IT_HT;
		// ����� ����������� ����� ������ = 1
		itemPartResultDMA1_ADC1 = 1;
		// ����� 1 ������ ��� ���������
		}
	else if ((flag_it & DMA_ISR_TCIF1) == DMA_ISR_TCIF1){
		// �������� ���������� �� ���������� ������ ��������
		DMA1_Channel1->CCR |= DMA_IT_HT;
		// ����� ����������� ����� ������ = 2
		itemPartResultDMA1_ADC1 = 2;
	}
	// Clear all interrupt flags ERRATA �� ������� CGIF, ������ HTIFx, TCIFx � TEIFx
	//DMA1->IFCR |= DMA_IFCR_CGIF1;
	DMA1->IFCR |= DMA_IFCR_CTCIF1;		// Channel 1 Transfer Complete clear
	DMA1->IFCR |= DMA_IFCR_CHTIF1;		// Channel 1 Half Transfer clear
	DMA1->IFCR |= DMA_IFCR_CTEIF1;		// Channel 1 Transfer Error clear

	// ��� ������ ������ ��������
	if ( itemPartResultDMA1_ADC1 != 0 &&
		 itemPartResultDMA1_ADC2 != 0 &&
		 itemPartResultDMA1_ADC3 != 0 &&
		((EXTI->PR1 & EXTI_PR1_PIF0) != EXTI_PR1_PIF0)){
			EXTI->SWIER1 |= EXTI_SWIER1_SWI0;
	}

	#if defined(AUTODMA1)
  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */
	#endif
  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel2 global interrupt.
  */
void DMA1_Channel2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel2_IRQn 0 */
	// ADC2 Priority Very High
	my_N_DMA1_2++;
	uint32_t flag_it = DMA1->ISR;
	if(my_N_DMA1_2 == 1) my_Flag_DMA1_2_1 = flag_it;
	if(my_N_DMA1_2 == 2) my_Flag_DMA1_2_2 = flag_it;
	if(my_N_DMA1_2 == 3) my_Flag_DMA1_2_3 = flag_it;
	// ������ �������� ������ ���������
	if ( (flag_it & DMA_FLAG_HT2) == DMA_FLAG_HT2){
		// ��������� ���������� �� ���������� ������ ��������
		DMA1_Channel2->CCR &= ~DMA_IT_HT;
		// ����� ����������� ����� ������ = 1
		itemPartResultDMA1_ADC2 = 1;
		// ����� 1 ������ ��� ���������
		}
	else if ((flag_it & DMA_ISR_TCIF2) == DMA_ISR_TCIF2){
		// �������� ���������� �� ���������� ������ ��������
		DMA1_Channel2->CCR |= DMA_IT_HT;
		// ����� ����������� ����� ������ = 2
		itemPartResultDMA1_ADC2 = 2;
	}
	// Clear all interrupt flags ERRATA �� ������� CGIF, ������ HTIFx, TCIFx � TEIFx
	//DMA1->IFCR |= DMA_IFCR_CGIF2;
	DMA1->IFCR |= DMA_IFCR_CTCIF2;
	DMA1->IFCR |= DMA_IFCR_CHTIF2;
	DMA1->IFCR |= DMA_IFCR_CTEIF2;

	// ��� ������ ������ ��������
	if ( itemPartResultDMA1_ADC1 != 0 &&
		 itemPartResultDMA1_ADC2 != 0 &&
		 itemPartResultDMA1_ADC3 != 0 &&
		((EXTI->PR1 & EXTI_PR1_PIF0) != EXTI_PR1_PIF0)){
			EXTI->SWIER1 |= EXTI_SWIER1_SWI0;
	}

  /* USER CODE END DMA1_Channel2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc2);
  /* USER CODE BEGIN DMA1_Channel2_IRQn 1 */

  /* USER CODE END DMA1_Channel2_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel3 global interrupt.
  */
void DMA1_Channel3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel3_IRQn 0 */
	// ADC3 Priority High
	my_N_DMA1_3++;
	uint32_t flag_it = DMA1->ISR;
	if(my_N_DMA1_3 == 1) my_Flag_DMA1_3_1 = flag_it;
	if(my_N_DMA1_3 == 2) my_Flag_DMA1_3_2 = flag_it;
	if(my_N_DMA1_3 == 3) my_Flag_DMA1_3_3 = flag_it;
	// ������ �������� ������ ���������
	if ( (flag_it & DMA_FLAG_HT3) == DMA_FLAG_HT3){
		// ��������� ���������� �� ���������� ������ ��������
		DMA1_Channel3->CCR &= ~DMA_IT_HT;
		// ����� ����������� ����� ������ = 1
		itemPartResultDMA1_ADC3 = 1;
		// ����� 1 ������ ��� ���������
		}
	else if ((flag_it & DMA_ISR_TCIF3) == DMA_ISR_TCIF3){
		// �������� ���������� �� ���������� ������ ��������
		DMA1_Channel3->CCR |= DMA_IT_HT;
		// ����� ����������� ����� ������ = 2
		itemPartResultDMA1_ADC3 = 2;
		}
	// Clear all interrupt flags ERRATA �� ������� CGIF, ������ HTIFx, TCIFx � TEIFx
	//DMA1->IFCR |= DMA_IFCR_CGIF3;
	DMA1->IFCR |= DMA_IFCR_CTCIF3;
	DMA1->IFCR |= DMA_IFCR_CHTIF3;
	DMA1->IFCR |= DMA_IFCR_CTEIF3;

	// ��� ������ ������ ��������
	if ( itemPartResultDMA1_ADC1 != 0 &&
		 itemPartResultDMA1_ADC2 != 0 &&
		 itemPartResultDMA1_ADC3 != 0 &&
		((EXTI->PR1 & EXTI_PR1_PIF0) != EXTI_PR1_PIF0)){
			EXTI->SWIER1 |= EXTI_SWIER1_SWI0;
	}

  /* USER CODE END DMA1_Channel3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc3);
  /* USER CODE BEGIN DMA1_Channel3_IRQn 1 */

  /* USER CODE END DMA1_Channel3_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */
  // 1) ��������� ������� �1
  // 2) ���� ���� ����� 19 ���������� ������� 2-� ����� ������� ���� ���� ������ � ������������
  // �������� ������ �������� � ������� sConfigOC.Pulse
  //htim4->Instance->
  num_TIM4++;
  if(num_TIM4 == 40)	// 10 ==> 5 + 5
  {
	  if(b_TIM4)
	  {
		  // ������ �������� ����������
		  //htim4.Instance->CCR3 = (uint32_t)69;//40;//55;//40;
		  b_TIM4 = false;
	  }
	  else
	  {
		  // ������ �������� ����������
		  //htim4.Instance->CCR3 = (uint32_t)65;//85;//70;//85;
		  b_TIM4 = true;
	  }
	  num_TIM4 = 0;
  }
  //TIM4->SR &= ~TIM_SR_UIF; // ���������� ����������
  TIM4->SR = ~TIM_SR_UIF; // ���������� ����������

  // ������� ����:
  // HAL_TIM_IRQHandler(&htim4);
  // ����� ���������������� !!
  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */
	UpdateRS232();
	#if defined(AUTOUSART3)
  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */
	#endif
  /* USER CODE END USART3_IRQn 1 */
}

/* USER CODE BEGIN 1 */
// ���������� ������������ ����������
void EXTI0_IRQHandler(void){			//	HAL_NVIC_SetPriority(EXTI0_IRQn, 6, 0);
										//	HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 2, 0);
										//	HAL_NVIC_SetPriority(DMA2_Channel4_IRQn, 3, 0);
										//	HAL_NVIC_SetPriority(USART3_IRQn, 1, 0);					main()
										//	HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);					HAL_UART_MspInit()
										//	HAL_NVIC_SetPriority(SysTick_IRQn, TickPriority, 0U);		��������� = 11
										//	���������� �� �������� ������ ���� �� ����������� (� ������ TIM4)
										//  HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
										//  UART3 - ��������� ��������� (�����?)

	my_N_EXTI++;

	//=================================
	//iT1__ = DWT->CYCCNT;	// ������ = 119992 - 119995 // 119985 - 119990
	//DWT->CYCCNT = 0;

	/*
	if (DWT->CYCCNT > DEBUG_maxDWT3){
		DEBUG_maxDWT3 = DWT->CYCCNT;
	}
	//*/
	DEBUG_maxDWT3 = DWT->CYCCNT;	// 59984 59986 59993 60007
	// DEBUG_maxDWT3 = 68437, 60 ���, 1141 ��� > 1 �� !!!
	// UpdateDataADC1() ==> maxDWT = 8329
	 
	DEBUG_maxDWT2 = DWT->CYCCNT;
	//if(DEBUG_maxDWT2 > iT1__)
		//iT1__ = DEBUG_maxDWT3;
	//iT1__ = DWT->CYCCNT;
	//DWT->CYCCNT = 0;
	iT__n++;

	// �������� ��� ������ �� ������
	if(itemPartResultDMA1_ADC1 != itemPartResultDMA1_ADC2) my_alarm |= 0x10;	// �� �����������
	if(itemPartResultDMA1_ADC1 != itemPartResultDMA1_ADC3) my_alarm |= 0x10;	// �� �����������
	if(itemPartResultDMA1_ADC2 != itemPartResultDMA1_ADC3) my_alarm |= 0x10;	// �� �����������

	if(itemPartResultDMA1_ADC2 == itemPartResultDMA1_ADC3) my_alarm |= 0x20;	// �����������

	my_ms_num++;
	if(!b_my_ms_num)
	{
		if(my_ms_num == 16) b_my_ms_num = true;
	}

    // ��������� ���������� �� ��� ����������� ����� ������� DMA
	switch(itemPartResultDMA1_ADC2){
	case 1:
		//pDataDMA1 = (volatile uint16_t*)&DMA1_Data[0];	// ��� ����
		pDataDMA1_1 = (volatile uint16_t*)&DMA1_1_Data[0];
		pDataDMA1_2 = (volatile uint16_t*)&DMA1_2_Data[0];
		pDataDMA1_3 = (volatile uint16_t*)&DMA1_3_Data[0];
		break;
	case 2:
		pDataDMA1_1 = (volatile uint16_t*)&DMA1_1_Data[ADC1_SH_HALF_SIZE];
		pDataDMA1_2 = (volatile uint16_t*)&DMA1_2_Data[ADC2_SH_HALF_SIZE];
		pDataDMA1_3 = (volatile uint16_t*)&DMA1_3_Data[ADC3_SH_HALF_SIZE];
		break;
		}
	itemPartResultDMA1_ADC1 = 0;
	itemPartResultDMA1_ADC2 = 0;
	itemPartResultDMA1_ADC3 = 0;
	// �������� ���� ����������
	EXTI->PR1 |= EXTI_PR1_PIF0;

	// ����������� ����������� ������ ������� DMA � ������ ��� ������� � ���������
	pDataDMA = pDataDMA1_1;
	pDataADC = &my_ADC1_Data[0];
	my_DataADC__0();

	pDataDMA = pDataDMA1_2;
	pDataADC = &my_ADC2_Data[0];
	my_DataADC__0();

	pDataDMA = pDataDMA1_3;
	pDataADC = &my_ADC3_Data[0];
	my_DataADC__0();

	// ��������� ������ ADC1, ������� Vref � CONT, ������ Vref �����������
	my_DataADC1__1();	// ����� sum_CONT1, sum_CONT2, sum_CONT � abs_diff_CONT
	// ��������� ������ ADC2, ������� Out0, OUT2 � OUT1, ������ OUT0 �����������
	my_DataADC2__1();	// ����� sum_OUT1, ������ ������ my_F0
	// ��������� ������ ADC3, ������� TS, OUT2N � OUT1N, ��� ������� ����������
	my_DataADC3__1();	// ����� sum_OUT1N, ������ ������ my_F0N, ����� sum_TS


	//UpdateDataADC1(); // ==>
	// my_DMA1_Data_F0[j] =
	// sum_OUT_DC +=
	// sum_CONTR +=
	// sum_SD1 +=
	index_CONTR += 240; // index_CONTR += 120;
	index_OUT_3R += 120;
	index_OUT_DC += 120;
	index_SD1 += 120;

	// ������� �������� ���������� ������������ sum_OUT1
	if (index_OUT_DC >= count_OUT_DC){
		avrResult_OUT_DC = (float)(sum_OUT_1) / (float)index_OUT_DC;	// ���� sum_OUT_DC
		flagUpdateCompute_OUT1_OPTICS_PWR = true;
		index_OUT_DC = 0;
		sum_OUT_1 = 0;
		sum_OUT_1A = 0;
	}
	// ������� �������� ������� ������� � �������������� ������
	if (index_CONTR >= count_CONTR){
		avrResult_CONTR = (float)sum_CONT / (float)index_CONTR;	// ���� sum_CONTR
		flagUpdateCompute_TEC_CTRL = true;
		index_CONTR = 0;
		sum_CONT = 0;
		sum_CONT1 = 0;
		sum_CONT2 = 0;
	}

	//=============================================

	//UpdateDataADC2();
	index_SD2 		+= 120;
	index_OUT_0R	+= 120;
	index_OUT2_CPT_FREQ += 10;
	index_OUT2_CPT_CRNT += 12;

	my_ADC2_1();

	if (index_OUT_0R >= count_OUT_0R){
		index_OUT_0R = 0;
	}

	// ����� ����� ����
	if (index_OUT2_CPT_FREQ >= count_OUT2_CPT_FREQ){
		index_OUT2_CPT_FREQ = 0;
		result_OUT2_CPT_FREQ_CPT += shift_OUT2_FREQ;
		result_OUT2_CPT_FREQ_CPT += shift_Freq_GNSS;
		result_OUT2_CPT_FREQ_CPT_tmp = result_OUT2_CPT_FREQ_CPT;
		flagUpdateCompute_OUT2_CPT_FREQ = true;
	}

	if(my_ms_num == 16){
		index_OUT2_CPT_CRNT = 0;
		// ���� ��� �� 16 ��
		result_OUT2_CPT_CRNT_DOPLER += shift_OUT2_DOPLER_CRNT;								// ??
		result_OUT2_CPT_CRNT_DOPLER += delta_DOPLER_DC;										// ??
		result_OUT2_CPT_FREQ_CPT -= result_OUT2_CPT_CRNT_DOPLER*value_mult_To_FREQ;			// !!!!!!!
		result_OUT2_CPT_CRNT_DOPLER_tmp = result_OUT2_CPT_CRNT_DOPLER;

		flag_SCAN_CRNT = true;									// �������� ����� ������������ ��� ���������� � ����������� ������
		flagUpdateCompute_OUT2_DOPLER_CRNT = true;				// ??
		// �������� ������������
		result_OUT2_DOPLER_TEC = result_OUT2_CPT_CRNT_DOPLER;	// ??
		flagUpdateCompute_OUT2_DOPLER_TEC = true;
	}
	//==============================
	


	//my_alarm = 1;
	// ��������� ����������� ����������,
	// �������� 12 ���������������� ������
	// ������ - � ���� ������ ���� �� ������
	// ������������
	//
	/*
	switch(itemWork)
	{
	case WORK_SCAN_CRNT:
	case WORK_NONE:
		break;
	}
	//*/

	// ��� ������� !!
	if (flagUpdate_U2R == true){
		flagUpdate_U2R = false;
		AD5668_WriteValue(AD5668_DAC_U2R , value_U2R);

	}
	if (flagUpdate_VY == true){
		flagUpdate_VY = false;
		AD5668_WriteValue(AD5668_DAC_VY , value_VY);
	}
	if(b_my_ms_num)			// 1-� ���� �� 16 �� ��� �������
	switch(my_ms_num){
		case 0:
			// ��������� �� ��������
			//  1 - ������ ���������� �������� (UT1A - ��������� � UT2A)
			//  2 - �������� ������� ������
			//  3 - ������ ��������� ���� ������
			//  4 - ���������� ������� ����������� ������
			//  5 - ��������� ���� �������
			//  6 - �������� ������� ������
			//  7 - ������ ��������� ���� ������
			//  8 - ������ ��������� ������� (UT2A)
			//  9 - ������� ���
			// 10 - ��������� �������� ����
			// 11 - �������� �������������
			//HAL_GPIO_WritePin(PPS1_GPIO_Port, PPS1_Pin, GPIO_PIN_RESET);	// �� ��������
			break;
		case 1:
			//HAL_GPIO_WritePin(PPS1_GPIO_Port, PPS1_Pin, GPIO_PIN_RESET);
			// ��������������� ��������� ���������, ������ ���������� ��������
			if (flagUpdate_UT1A == true){
				flagUpdate_UT1A = false;
				iT2__ = DWT->CYCCNT;
				AD5668_WriteValue(AD5668_DAC_UT1A , value_UT1A);
				iT3__ = DWT->CYCCNT;
				iT3__ -= iT2__;	// 20720 - 20722
			}
			//my_ms_num++;
			break;
		case 2:
			// ��������������� ��������� 2-� �������, �������� ������� ������
			if (flagUpdate_DTX == true){
				flagUpdate_DTX = false;
				AD5668_WriteValue(AD5668_DAC_DTX , value_DTX);
			}
			//my_ms_num++;
			break;
		case 3:
			// ��������������� ��������� 3-� �������, ������ ��������� ���� ������
			/*
			if (flagUpdate_VY == true){
				flagUpdate_VY = false;
				AD5668_WriteValue(AD5668_DAC_VY , value_VY);
			}
			//*/
			//my_ms_num++;
			break;
		case 4:
			// ��������������� ��������� 4-� �������, ���������� ������� �����������
			// ���������� ������ ������� ����������� ������
			//HAL_GPIO_WritePin(PPS1_GPIO_Port, PPS1_Pin, GPIO_PIN_SET);
			if (flagUpdate_VT1 == true){
				flagUpdate_VT1 = false;
				AD5668_WriteValue(AD5668_DAC_VT1 , value_VT1);
			}
			//my_ms_num++;
			break;
		case 5:
			// ��������������� ��������� 5-� �������, ��������� ���� �������
			if (flagUpdate_L1 == true){
				flagUpdate_L1 = false;
				AD5668_WriteValue(AD5668_DAC_L1 , value_L1);
			}
			//my_ms_num++;
			break;
		case 6:
			// ��������������� ��������� 6-� �������, �������� ������� ������
			if (flagUpdate_T5 == true){
				flagUpdate_T5 = false;
				AD5668_WriteValue(AD5668_DAC_T5 , value_T5);
			}
			//my_ms_num++;
			break;
		case 7:
			// ��������������� ��������� 7-� �������, ������ ��������� ���� ������
			/*
			if (flagUpdate_U2R == true){
				flagUpdate_U2R = false;
				AD5668_WriteValue(AD5668_DAC_U2R , value_U2R);
			}
			//*/
			//my_ms_num++;
			break;
		case 8:
			// ��������������� ��������� 8-� �������, ������ ��������� �������
			if (flagUpdate_UT2A == true){
				flagUpdate_UT2A = false;
				AD5668_WriteValue(AD5668_DAC_UT2A , value_UT2A);
			}
			//my_ms_num++;
			break;
		case 9:
			// ��������������� ��������� 9-� �������, ������� ���
			if (flagUpdate_RFI == true){
				flagUpdate_RFI = false;
				value_RFI = value_RFI & 0xFFF;
				//HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, (uint32_t)value_RFI);
				//my_alarm |= 0x80;
			}
			//my_ms_num++;
			break;
		case 10:
			// ��������������� ��������� 10-� �������, ��������� �������� ����
			if (flagUpdate_LMX2486 == true){
				flagUpdate_LMX2486 = false;
				LMX2486_SetFreq(LMX_ValueN, LMX_ValueFN, LMX_ValueFD);
				//my_alarm |= 0x40;
			}
			//my_ms_num++;
			break;
		case 11:
			// ��������������� ��������� 11-� �������, �������� �������������
			if (flagUpdate_OutFactor == true){
				flagUpdate_OutFactor = false;
				AD8400_SetValue(value_OutFactor);
			}
			//my_ms_num = 0;	// СТОП
			break;
		default:
			break;
	}
	if(my_ms_num == 16) my_ms_num = 0;

	// ����������� ���������
	switch(itemMOD_CRNT){
		case 0:
			//value_U2R = fixValue_U2R + MOD_CRNT_width;
			//flagUpdate_U2R = true;
			itemMOD_CRNT = 1;
			break;
		case 1:
			//value_U2R = fixValue_U2R - MOD_CRNT_width;			
			//flagUpdate_U2R = true;
			itemMOD_CRNT = 0;
			break;
	}
	
	switch(itemMOD_FREQ){
		case 0:
			//LMX2486_SetFreq(459, 1265177, 2000000);
			itemMOD_FREQ = 1;
			break;
		case 1:
			itemMOD_FREQ = 2;
			break;
		case 2:
			//LMX2486_SetFreq(459, 1267177, 2000000);
			itemMOD_FREQ = 3;
			break;
		case 3:
			itemMOD_FREQ = 0;
			break;
	}
	
	// ��������� �������
	switch(itemWork){
		case WORK_NONE:
			funWork_VOID_TEST();
			break;
		case WORK_SCAN_CRNT:
			funWork_SCAN_CRNT();
			break;
		case WORK_TEST_ADC:
			funWork_TEST_ADC();
			break;
		case WORK_SCAN_FREQ:
			funWork_SCAN_FREQ();			
			break;
		case WORK_TEST_ADC_2:
			funWork_TEST_ADC_2();
			break;
		case WORK_TEST_ADC_3:
			//i_MESSAGE_3 = 1000;
			funWork_TEST_ADC_3();
			break;
		case WORK_HIST:
			funWork_HIST();   //kislov
			break;

		// TOLIK
		/*
		case WORK_TEST_FACTOR_OUT:
			funWork_TEST_FACTOR_OUT();
			break;
		case WORK_TEST_TEMP_CELL:
			funWork_TEST_TEMP_CELL();
		//*/
		//case WORK_VOID_TEST:
		//	funWork_VOID_TEST();
		default:
			break;
	}



	/*
	if (flagUpdate_DTX == true){
		flagUpdate_DTX = false;
		AD5668_WriteValue(AD5668_DAC_DTX , value_DTX);
	}
	if (flagUpdate_VT1 == true){
		flagUpdate_VT1 = false;
		AD5668_WriteValue(AD5668_DAC_VT1 , value_VT1);
	}
	if (flagUpdate_VY == true){
		flagUpdate_VY = false;
		AD5668_WriteValue(AD5668_DAC_VY , value_VY);
	}
	if (flagUpdate_U2R == true){
		flagUpdate_U2R = false;
		AD5668_WriteValue(AD5668_DAC_U2R , value_U2R);
	}
	if (flagUpdate_UT1A == true){
		flagUpdate_UT1A = false;
		AD5668_WriteValue(AD5668_DAC_UT1A , value_UT1A);
	}
	if (flagUpdate_UT2A == true){
		flagUpdate_UT2A = false;
		AD5668_WriteValue(AD5668_DAC_UT2A , value_UT2A);
	}
	if (flagUpdate_T5 == true){
		flagUpdate_T5 = false;
		AD5668_WriteValue(AD5668_DAC_T5 , value_T5);
	}
	if (flagUpdate_L1 == true){
		flagUpdate_L1 = false;
		AD5668_WriteValue(AD5668_DAC_L1 , value_L1);
	}
	// 0 % 4095
	if (flagUpdate_RFI == true){
		flagUpdate_RFI = false;
		value_RFI = value_RFI & 0xFFF;
		HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, (uint32_t)value_RFI);
	}
	if (flagUpdate_LMX2486 == true){
		flagUpdate_LMX2486 = false;
		LMX2486_SetFreq(LMX_ValueN, LMX_ValueFN, LMX_ValueFD);
	}
	
	if (flagUpdate_OutFactor == true){
		flagUpdate_OutFactor = false;
		AD8400_SetValue(value_OutFactor);
	}
	//*/
	
	//itemPartResultDMA1_ADC1 = 0;
	//itemPartResultDMA2_ADC2 = 0;

	if (DWT->CYCCNT > DEBUG_maxDWT1){
		DEBUG_maxDWT1 = DWT->CYCCNT;
	}

	iT4__ = DWT->CYCCNT;
	iF0 ++;
	my_Tick -= uwTickFreq;
	if(iF0 >= 2000)
	{
		flagUpdateTempCell = true;
		iF0 = 0;
		i_MESSAGE_1 = iT1__; // ������ �������� ����������
		i_MESSAGE_2 = iT4__; // ������������ �������� ����������
		i_MESSAGE_3 = (int)delta_DOPLER_DC; // ���������� ������������ ������� ����������
		//i_MESSAGE_3 = 141570;	// TEST


		// uwTick += uwTickFreq;

		//i_MESSAGE_3 = my_Tick;

		//my_tst_1();
		//i_MESSAGE_3 = my_dat_2;
		//i_MESSAGE_3 = iT__n;
		//i_MESSAGE_2 = iT4__;
		//if(b_eq == false) i_MESSAGE_1 = 0;
		b_MESSAGE = true;
	};
	// �������� ���� ����������
	//EXTI->PR1 |= EXTI_PR1_PIF0;
}

// ��������� ������ � ADC1
static inline void UpdateDataADC1(void){
// ������������ �������������� ����� DMA1
	int i, j;
	for(j = 0; j < 56; j++)
	{
		//
		my_DMA1_Data_F0[j] = my_DMA1_Data_F0[ADC_ARRAY_DMA12_HALF_SIZE + j];
	}


	// my_DataADC2_0();my_DMA1_Data
	//*

	for (int i = 0, j = 0; i < ADC_ARRAY_DMA1_HALF_SIZE-3; i+=4, j++){
		my_DMA1_Data_F0[j + 56] = my_DMA1_Data[i];
		sum_OUT_DC += my_DMA1_Data[i + 1];
		sum_CONTR += my_DMA1_Data[i + 3];
		sum_SD1 += my_DMA1_Data[i + 2];
		}
	//*/

	/*
	switch(itemPartResultDMA1_ADC1){
		// ������ ����� ������
		case 1:
			for (int i = 0, j = 0; i < ADC_ARRAY_DMA1_HALF_SIZE-3; i+=4, j++){
				my_DMA1_Data_F0[j + 56] = DMA1_Data[i];
				//sum_OUT_DC += DMA1_Data[i];
				sum_OUT_DC += DMA1_Data[i + 1];
				//sum_CONTR += DMA1_Data[i + 1];
				sum_CONTR += DMA1_Data[i + 3];
				sum_SD1 += DMA1_Data[i + 2];
				//sum_OUT_3R += DMA1_Data[i + 3];
			}			
			pDataDMA1 = &DMA1_Data[0];
			break;
		// ������ ����� ������
		case 2:
			for (int i = 0, j = 0; i < ADC_ARRAY_DMA1_HALF_SIZE-3; i+=4, j++){
				my_DMA1_Data_F0[j + 56] = DMA1_Data[ADC_ARRAY_DMA1_HALF_SIZE + i];
				//sum_OUT_DC += DMA1_Data[ADC_ARRAY_DMA1_HALF_SIZE + i];
				sum_OUT_DC += DMA1_Data[ADC_ARRAY_DMA1_HALF_SIZE + i +1];
				//sum_CONTR += DMA1_Data[ADC_ARRAY_DMA1_HALF_SIZE + i + 1];
				sum_CONTR += DMA1_Data[ADC_ARRAY_DMA1_HALF_SIZE + i + 3];
				sum_SD1 += DMA1_Data[ADC_ARRAY_DMA1_HALF_SIZE + i + 2];
				//sum_OUT_3R += DMA1_Data[ADC_ARRAY_DMA1_HALF_SIZE + i + 3];
			}
			pDataDMA1 = &DMA1_Data[ADC_ARRAY_DMA1_HALF_SIZE];
			break;
	}
	//*/
	//index_CONTR++;
	//index_OUT_3R++;
	//index_OUT_DC++;
	//index_SD1++;

	index_CONTR += 120;
	index_OUT_3R += 120;
	index_OUT_DC += 120;
	index_SD1 += 120;
	for(int i = 56; i < ADC_ARRAY_DMA12_HALF_SIZE + 56; i++)
	{
		//sum_OUT_1A
		//sum_OUT_1A += my_DMA1_Data_F0[i];
		sum_OUT_1A += my_DMA2_Data_F0[i];
	}
	//*/
	
	/*
	// ���������� �������� ����� ����� Kurchanov 08.07.2020
	//for (int i = 12; i < ADC_ARRAY_DMA2_HALF_SIZE; i += 4*12){
	for (int i = 0; i < ADC_ARRAY_DMA1_HALF_SIZE - 36; i += 4*10){ // Kurchanov 08.07.2020
		sum_OUT1_CPT_CRNT[0] += pDataDMA1[i] 		- 	pDataDMA1[i + 20];
		sum_OUT1_CPT_CRNT[1] += pDataDMA1[i + 4] 	-  	pDataDMA1[i + 24];
		sum_OUT1_CPT_CRNT[2] += pDataDMA1[i + 8] 	-  	pDataDMA1[i + 28];
		sum_OUT1_CPT_CRNT[3] += pDataDMA1[i + 12] 	- 	pDataDMA1[i + 32];
		sum_OUT1_CPT_CRNT[4] += pDataDMA1[i + 16]	- 	pDataDMA1[i + 36];
		
		//sum_OUT1_CRNT_2;
		sum_OUT1_CRNT_2[0] += pDataDMA1[i] 		+ 	pDataDMA1[i + 20];
		sum_OUT1_CRNT_2[1] += pDataDMA1[i + 4] 	+  	pDataDMA1[i + 24];
		sum_OUT1_CRNT_2[2] += pDataDMA1[i + 8] 	+  	pDataDMA1[i + 28];
		sum_OUT1_CRNT_2[3] += pDataDMA1[i + 12] +  	pDataDMA1[i + 32];
		sum_OUT1_CRNT_2[4] += pDataDMA1[i + 16] +   pDataDMA1[i + 36];
		
		index_OUT1_CPT_CRNT++;
	}
	if (index_OUT1_CPT_CRNT >= count_OUT1_CPT_CRNT){
		count_OUT1_CPT_CRNT = index_OUT1_CPT_FREQ;
		for (int i = 0; i < 5; i++){
			result_OUT1_CPT_CRNT[i] = (float)(sum_OUT1_CPT_CRNT[i]) /(float)index_OUT1_CPT_CRNT;
			result_OUT1_CRNT_2[i] = (float)(sum_OUT1_CRNT_2[i]) /(float)index_OUT1_CPT_CRNT;
			sum_OUT1_CPT_CRNT[i] = 0;
			sum_OUT1_CRNT_2[i] = 0;
		}
		index_OUT1_CPT_CRNT = 0;
	}
	//*/
	
	/*
	// ���������� �������� �������
	for (int i = 12; i < ADC_ARRAY_DMA2_HALF_SIZE; i += 4*12){
	// for (int i = 12; i < ADC_ARRAY_DMA1_HALF_SIZE - 32; i += 4*12){ // Kurchanov 08.07.2020
		sum_OUT1_CPT_FREQ[0] += pDataDMA1[i-12] - 	pDataDMA1[i + 12];
		sum_OUT1_CPT_FREQ[1] += pDataDMA1[i-8] 	-  	pDataDMA1[i + 16];
		sum_OUT1_CPT_FREQ[2] += pDataDMA1[i-4] 	-  	pDataDMA1[i + 20];
		sum_OUT1_CPT_FREQ[3] += pDataDMA1[i] 	-  	pDataDMA1[i + 24];
		sum_OUT1_CPT_FREQ[4] += pDataDMA1[i+4] 	-  	pDataDMA1[i + 28];
		sum_OUT1_CPT_FREQ[5] += pDataDMA1[i+8] 	-  	pDataDMA1[i + 32];
		index_OUT1_CPT_FREQ++;
	}
	if (index_OUT1_CPT_FREQ >= count_OUT1_CPT_FREQ){
		count_OUT1_CPT_FREQ = index_OUT1_CPT_FREQ;
		for (int i = 0; i < 6; i++){
			result_OUT1_CPT_FREQ[i] = (float)(-sum_OUT1_CPT_FREQ[i]) /(float)index_OUT1_CPT_FREQ;
			sum_OUT1_CPT_FREQ[i] = 0;
		}
		index_OUT1_CPT_FREQ = 0;
	}
	//*/
	
	/*
	// ���������� �������� ����������� ��������� ����
	if (index_OUT1_DOPLER_CRNT >= count_OUT1_DOPLER_CRNT){		
		result_OUT1_DOPLER_CRNT = (float)(sum_OUT1_DOPLER_CRNT[0]-sum_OUT1_DOPLER_CRNT[1])/(float)index_OUT1_DOPLER_CRNT;
		result_OUT1_DOPLER_CRNT /= -120.0f;
		flagUpdateCompute_OUT1_DOPLER_CRNT = true;
		index_OUT1_DOPLER_CRNT = 0;
		sum_OUT1_DOPLER_CRNT[0] = 0;
		sum_OUT1_DOPLER_CRNT[1] = 0;
	}
	//*/

	// ������� �������� ���������� ������������
	if (index_OUT_DC >= count_OUT_DC){
		avrResult_OUT_DC = (float)(sum_OUT_DC) / (float)index_OUT_DC;
		avrResult_OUT_1A = (float)(sum_OUT_1A) / (float)index_OUT_DC;		// !!!
		flagUpdateCompute_OUT1_OPTICS_PWR = true;
		index_OUT_DC = 0;
		sum_OUT_DC = 0;
		sum_OUT_1A = 0;
	}
	// ������� �������� ������� ������� � �������������� ������
	if (index_CONTR >= count_CONTR){
		avrResult_CONTR = (float)sum_CONTR / (float)index_CONTR;
		flagUpdateCompute_TEC_CTRL = true;
		index_CONTR = 0;
		sum_CONTR = 0;
	}
	// ������� �������� ��� ��������
	if (index_OUT_3R >= count_OUT_3R){	// count_OUT_3R = 6000 (6 ������)
		avrResult_OUT_3R = (float)sum_OUT_3R / (float)index_OUT_3R;
		flagUpdateCompute_MICROWAVE = true;
		index_OUT_3R = 0;
		sum_OUT_3R = 0;
	}
	//*
	// ���������� ���������� �������� 1 (���)
	// ������ ����������� ����������� (������ ����)
	// 1000 ��� � ������� sum_SD1 = ����� ������� �� 120 ��������
	if (index_SD1 >= count_SD1){							// count_SD1 = 1920 = 120*16, 1 ��� � 16 ��
		avrResult_SD1 = (float)sum_SD1 / (float)index_SD1;
		index_SD1 = 0;
		sum_SD1 = 0;
		// ��� ���� ���������� �������� ������� � ��������� ���
		// ��� ������ ��������� ������ ����������� ���������� avrResult_SD1_start = avrResult_SD1
		// � ����� ������� �������� SD1_d = avrResult_SD1 - avrResult_SD1_start
		// ��������� �������� ������ �������������� ������� shift_OUT2_FREQ
		//shift_OUT2_FREQ = 0;
		if(bCompFreqTK)	//  ����������� ������� �� ����������� �����������
		{
			if(!bCompFreqTK_1)
			{
				avrResult_SD1_start = avrResult_SD1;
				bCompFreqTK_1 = true;
			}
			SD1_d = avrResult_SD1 - avrResult_SD1_start;
			SD1_d *= 1.2e-10f;			// ������������� ��������� �������
			//SD1_d /= 6.95e-11f;		// �������� ������ ��� ��� �� ��������� �������						//SD1_d /= 6.07e-11f;			// �������� ������ ��� ��� �� ��������� �������
			//SD1_d /= 5.7e-11f;		// �������� ������ ��� ��� �� ��������� �������
			SD1_d /= 11.0e-11f;			// �������� ������ ��� ��� �� ��������� �������
			//shift_OUT2_FREQ = -SD1_d;	// ����������� ���������� ������ ��� ��������������
			shift_OUT2_FREQ = shift_OUT2_FREQ*0.999f-SD1_d*0.001f;	// ����������� ���������� ������ ��� ��������������, ���������� ������� 16 �������
		}
		else
		{
			if(bCompFreqTK_1) bCompFreqTK_1 = false;
		}
	}
	//*/
}

static inline void my_ADC2_0(void){
	// ������� ��������
	switch(itemPartResultDMA1_ADC2){
		case 1:
			for (int i = 0; i < ADC_ARRAY_DMA2_HALF_SIZE-3; i+=3){
				sum_OUT_2RN += DMA2_Data[i];
				sum_OUT_0RN += DMA2_Data[i + 1];
			}
			break;
		case 2:
			for (int i = 0, j = 0; i < ADC_ARRAY_DMA2_HALF_SIZE-3; i+=3, j++){
				sum_OUT_2RN += DMA2_Data[ADC_ARRAY_DMA2_HALF_SIZE + i];
				sum_OUT_0RN += DMA2_Data[ADC_ARRAY_DMA2_HALF_SIZE + i + 1];
			}
			break;
		}
	if (index_OUT_0R >= count_OUT_0R){
		avrResult_OUT2_DC = (float)sum_OUT_2RN / (float)index_OUT_0R;
		avrResult_OUT_0RN = (float)sum_OUT_0RN / (float)index_OUT_0R;
		resultTemp_CELL = avrResult_OUT_0RN;
		resultTemp_CELL = resultTemp_CELL - levelTemp_CELL;
		flagUpdateCompute_CELL = true;
		sum_OUT_2RN = 0;
		sum_OUT_0RN = 0;
	}
	for (int i = 0; i < ADC_ARRAY_DMA2_HALF_SIZE-33; i += 3*12){
		sum_OUT2_CPT_FREQ[0] += pDataDMA2[i] 	- 	pDataDMA2[i + 18];
		sum_OUT2_CPT_FREQ[1] += pDataDMA2[i+3] 	-  	pDataDMA2[i + 21];
		sum_OUT2_CPT_FREQ[2] += pDataDMA2[i+6] 	-  	pDataDMA2[i + 24];
		sum_OUT2_CPT_FREQ[3] += pDataDMA2[i+9] 	- 	pDataDMA2[i + 27];
		sum_OUT2_CPT_FREQ[4] += pDataDMA2[i+12] -  	pDataDMA2[i + 30];
		sum_OUT2_CPT_FREQ[5] += pDataDMA2[i+15] - 	pDataDMA2[i + 33];
	}
	if (index_OUT2_CPT_FREQ >= count_OUT2_CPT_FREQ){
		count_OUT2_CPT_FREQ = index_OUT2_CPT_FREQ;
		for (int i = 0; i < 6; i++){
			// �������� �� 2 ��� ���������� ������� � ����������� ��� ��������
			result_OUT2_CPT_FREQ[i] = (float)(sum_OUT2_CPT_FREQ[i])*2.0f /(float)index_OUT2_CPT_FREQ;
			sum_OUT2_CPT_FREQ[i] = 0;
		}
		result_OUT2_CPT_FREQ_CPT = result_OUT2_CPT_FREQ[0];
	}
	for(int i = 0; i < 5; i++)
	{
		my_F1F2_P_rez[i] = 0;
	}
	for (int i = 0; i < ADC_ARRAY_DMA2_HALF_SIZE-27; i += 3*10){
		sum_OUT2_CPT_CRNT[0] += ((volatile uint16_t*)pDataDMA2)[i] 		- 	((volatile uint16_t*)pDataDMA2)[i + 15];
		sum_OUT2_CPT_CRNT[1] += ((volatile uint16_t*)pDataDMA2)[i+3] 	- 	((volatile uint16_t*)pDataDMA2)[i + 18];
		sum_OUT2_CPT_CRNT[2] += ((volatile uint16_t*)pDataDMA2)[i+6] 	- 	((volatile uint16_t*)pDataDMA2)[i + 21];
		sum_OUT2_CPT_CRNT[3] += ((volatile uint16_t*)pDataDMA2)[i+9] 	- 	((volatile uint16_t*)pDataDMA2)[i + 24];
		sum_OUT2_CPT_CRNT[4] += ((volatile uint16_t*)pDataDMA2)[i+12] 	- 	((volatile uint16_t*)pDataDMA2)[i + 27];

		my_F1F2_P_rez[0] += ((volatile uint16_t*)pDataDMA2)[i] 		+ 	((volatile uint16_t*)pDataDMA2)[i + 15];
		my_F1F2_P_rez[1] += ((volatile uint16_t*)pDataDMA2)[i+3] 	+ 	((volatile uint16_t*)pDataDMA2)[i + 18];
		my_F1F2_P_rez[2] += ((volatile uint16_t*)pDataDMA2)[i+6] 	+ 	((volatile uint16_t*)pDataDMA2)[i + 21];
		my_F1F2_P_rez[3] += ((volatile uint16_t*)pDataDMA2)[i+9] 	+ 	((volatile uint16_t*)pDataDMA2)[i + 24];
		my_F1F2_P_rez[4] += ((volatile uint16_t*)pDataDMA2)[i+12] 	+ 	((volatile uint16_t*)pDataDMA2)[i + 27];
	}

	for(int i = 0; i < 5; i++)
	{
		my_F1F2_P_sum[i] += my_F1F2_P_rez[i];
	}

	if (index_OUT2_CPT_CRNT >= count_OUT2_CPT_CRNT){	// ���� ��� �� 16 ��
		// ���� ��� �� 16 ��
		count_OUT2_CPT_CRNT = index_OUT2_CPT_CRNT;
		for (int i = 0; i < 5; i++){
			// �������� �� 2 ��� ���������� ������� � ����������� ��� ��������
			result_OUT2_CPT_CRNT[i] = (float)(sum_OUT2_CPT_CRNT[i])*2.0f /(float)index_OUT2_CPT_CRNT;
			sum_OUT2_CPT_CRNT[i] = 0;

			F1F2_P_rezult[i] = (float)my_F1F2_P_sum[i] / (float)index_OUT2_CPT_CRNT;
			my_F1F2_P_sum[i] = 0;
		}
		result_OUT2_CPT_CRNT_DOPLER = result_OUT2_CPT_CRNT[4];

		F1F2_P_S = 0;
		for (int i = 0; i < 5; i++)
		{
			F1F2_P_S += F1F2_P_rezult[i];
		}
		F1F2_P_S /= 5;
		for (int i = 0; i < 5; i++)
		{
			F1F2_P_rezult[i] -= F1F2_P_S;
		}
	}
}

static inline void my_ADC1_1(void){
	{
	// ��� ������� ASM
	my_DataADC1_0();		// ����� ���������� my_DataADC1_0() ____ ������
	my_DataADC1_2();		// ����� ���������� my_DataADC1_0()+my_DataADC1_2() ____ ������
	my_OUT1_F1();			// ___ ������
	my_OUT1_F2();			// ___ ������
	my_OUT1_F1F2();			//  ___ ������
	//my_F1F2_P();
	my_OUT1_F2F1();			//  ___ �����, ���������� ����� = ___
	my_OUT1_F1_F2();		//  ___ �����, ���������� ����� = ___
	}

	/*

	//if (index_OUT_0R >= count_OUT_0R){		// 1920/120 = 16

	// ���������� ������ �����������, ���������� ���������
	if(my_ms_num >= 16){
		avrResult_OUT_0R = (float)sum_OUT_0R / (float)index_OUT_0R;
		//resultTemp_CELL = avrResult_OUT_0RN;
		resultTemp_CELL = avrResult_OUT_0R;
		resultTemp_CELL = resultTemp_CELL - levelTemp_CELL;
		flagUpdateCompute_CELL = true;
		sum_OUT_0R = 0;
		}

	//=====================================================================================================
	for(int i = 0; i < 6; i++)
	{
		my_F2F1_sum[i] += my_F2F1_rez[i];
		//my_F2F1_P_sum[i] += my_F2F1_P_rez[i];
	}
	for(int i = 0; i < 5; i++)
	{
		my_F1F2_sum[i] += my_F1F2_rez[i];
		my_F1F2_P_sum[i] += my_F1F2_P_rez[i];
	}

	// ������ 16 ��, ������� 62,5 ��
	//if (index_OUT2_CPT_FREQ >= count_OUT2_CPT_FREQ){
	if(my_ms_num >= 16){
		//count_OUT2_CPT_FREQ = index_OUT2_CPT_FREQ;
		//*
		if(!b_F2F1_rezult)
		{
			b_F2F1_rezult = true;
			for (int i = 0; i < 6; i++){
				F2F1_rezult[i] = F2F1_rezult_1[i] = -(float)my_F2F1_sum[i] / (float)count_OUT2_CPT_FREQ;
				my_F2F1_sum[i] = 0;
			}
			// ���������� ����� ����� ����� � ���� ���������� ����� �����
			value_U2R = value_U2R - value_U2R_D; // +/- 10000 ������ ��������� = +/- 271 ������ ���������
			// ����� +/- 100 ������ ����� = +/- 3690 ������ �����
			flagUpdate_U2R = true;
		}
		else
		{
			b_F2F1_rezult = false;
			for (int i = 0; i < 6; i++){
				F2F1_rezult[i] = F2F1_rezult_2[i] = -(float)my_F2F1_sum[i] / (float)count_OUT2_CPT_FREQ;
				my_F2F1_sum[i] = 0;
				F2F1_rezult_D[i] = F2F1_rezult_2[i] - F2F1_rezult_1[i];
			}
			// ���������� ����� ����� ����� � ���� ���������� ����� �����
			value_U2R = value_U2R + value_U2R_D;
			//resultDOPLER_FREQ = F2F1_rezult_D[0] - F2F1_rezult_D[5];
			//resultDOPLER_FREQ = F2F1_rezult_D[1];
			//resultDOPLER_FREQ = -F2F1_rezult_D[5];
			resultDOPLER_FREQ = F2F1_rezult_D[1];
			flagUpdateCompute_DOPLER_FREQ = true;
			flagUpdate_U2R = true;
		}
		//*/

		/*
		for (int i = 0; i < 6; i++){
			F2F1_rezult[i] = -(float)my_F2F1_sum[i] / (float)index_OUT2_CPT_FREQ;
			//F2F1_P_rezult[i] = -(float)my_F2F1_P_sum[i] / (float)index_OUT2_CPT_FREQ;
			//p_my_F2F1_sum[i] = 0;
			my_F2F1_sum[i] = 0;
			//my_F2F1_P_sum[i] = 0;
		}
		//*/
	/*

		//F2F1_rezult_A = -2.95*F2F1_rezult[4];
		F2F1_rezult_A = F2F1_rezult[4];
		//F2F1_rezult_A = (F2F1_rezult[0]*(-0.37461) + F2F1_rezult[1]*(-0.6976) + F2F1_rezult[2]*(+0.241922) + F2F1_rezult[3]*(+0.529919) + F2F1_rezult[4]*(0.766044))/1.093523;
		F2F1_rezult_A_30 += F2F1_rezult_A;
		//result_OUT2_CPT_FREQ_CPT = F2F1_rezult[1] + 2.95*F2F1_rezult[4];// - F2F1_rezult_X;
		result_OUT2_CPT_FREQ_CPT = F2F1_rezult[1];// - F2F1_rezult_X;
		F2F1_rezult_N_30++;
		if(F2F1_rezult_N_30 == 30)
		{
			F2F1_rezult_A_30 /= 30;
			F2F1_rezult_A_900 += F2F1_rezult_A_30;
			F2F1_rezult_A_30 = 0;
			F2F1_rezult_N_30 = 0;
			F2F1_rezult_N_900++;
			if(F2F1_rezult_N_900 == 30)
			{
				F2F1_rezult_A_900 /= 30;
				F2F1_rezult_X = F2F1_rezult_A_900;
				F2F1_rezult_A_900 = 0;
				F2F1_rezult_N_900 = 0;
			}
		}
	}

	//if (index_OUT2_CPT_CRNT >= count_OUT2_CPT_CRNT){	// ���� ��� �� 16 ��
	if(my_ms_num >= 16){
		// ���� ��� �� 16 ��
		//count_OUT2_CPT_CRNT = index_OUT2_CPT_CRNT;

		// ��������� ������ OUT1
		for (int i = 0; i < 5; i++){
					F1F2_OUT1_rezult[i] = -(float)my_F1F2_OUT1_sum[i] / (float)count_OUT1_CPT_CRNT;
					my_F1F2_OUT1_sum[i] = 0;
				}

		// ��������� ������ OUT2
		for (int i = 0; i < 5; i++){
			F1F2_rezult[i] = -(float)my_F1F2_sum[i] / (float)count_OUT2_CPT_CRNT;
			F1F2_P_rezult[i] = (float)my_F1F2_P_sum[i] / (float)count_OUT2_CPT_CRNT;
			my_F1F2_sum[i] = 0;
			my_F1F2_P_sum[i] = 0;
		}
		F1F2_P_S = 0;
		for (int i = 0; i < 5; i++)
		{
			F1F2_P_S += F1F2_P_rezult[i];
		}
		F1F2_P_S /= 5;
		for (int i = 0; i < 5; i++)
		{
			F1F2_P_rezult[i] -= F1F2_P_S;
		}

		//F1F2_rezult_A = (F1F2_rezult[3]*0.35 + F1F2_rezult[4])/1.35;
		//F1F2_rezult_A = (F1F2_rezult[0]*(-0.37461) + F1F2_rezult[1]*(-0.6976) + F1F2_rezult[2]*(+0.241922) + F1F2_rezult[3]*(+0.529919) + F1F2_rezult[4]*(0.766044))/1.093523;
		F1F2_rezult_A = (F1F2_rezult[2] + F1F2_rezult[3])/2.0;
		F1F2_rezult_A_30 += F1F2_rezult_A;
		//result_OUT2_CPT_CRNT_DOPLER = F1F2_rezult[1] - F1F2_rezult_X;
		//result_OUT2_CPT_CRNT_DOPLER = (F1F2_rezult[0]*0.927184 + F1F2_rezult[1]*0.997564 + F1F2_rezult[2]*0.970296 + F1F2_rezult[3]*0.848048 +  F1F2_rezult[4]*0.642788)/4.385879 - F1F2_rezult_X;


		// 2021_04_08 � ����� ��� ���������, � "������" �� ������� �������
		// ��������������� ����� ����� (��� �������) ����� ��������� ��������� ����������� "������������" ����, ���� ��������� �������� ����������
		result_OUT2_CPT_CRNT_DOPLER = (F1F2_rezult[1] + F1F2_rezult[2])/2.0;// - F1F2_rezult_X;
		F1F2_rezult_N_30++;
		if(F1F2_rezult_N_30 == 30)
		{
			F1F2_rezult_N_30 = 0;
			F1F2_rezult_N_900++;

			F1F2_rezult_A_30 /= 30;
			F1F2_rezult_A_900 += F1F2_rezult_A_30;
			F1F2_rezult_A_30 = 0;

			if(F1F2_rezult_N_900 == 30)
			{
				F1F2_rezult_N_900 = 0;

				F1F2_rezult_A_900 /= 30;
				F1F2_rezult_X = F1F2_rezult_A_900;
				F1F2_rezult_A_900 = 0;
			}
		}
	}
	//*/
}

static inline void my_ADC2_1(void){
	// ��� ������� ASM
	//my_DataADC2_0();		// ����� ���������� my_DataADC2_0() 818 ������
	//my_DataADC2_2();		// ����� ���������� my_DataADC2_0()+my_DataADC2_2() 3404 ������
	my_DataADC2_3();
	index_OUT_1N += 120;
	// ������� �������� ���������� ������������
	if (index_OUT_1N >= count_OUT_DC){
		avrResult_OUT_1N = ((float)(sum_OUT_1N)) / (float)index_OUT_1N;
		//flagUpdateCompute_OUT1N_OPTICS_PWR = true;
		index_OUT_1N = 0;
		sum_OUT_1N = 0;
	}
	// ������������ ������� ��������� �������������
	// START
	DWT->CYCCNT = 0;
	//my_Data_F0 = &my_DMA2_Data_F0[0];
	my_Data_F0 = &my_F0[0];
	my_Data_F1 = &my_DMA2_Data_F1[0];
	my_F1();				//  513 ������
	my_Data_F2 = &my_DMA2_Data_F2[0];
	my_F2();				// 1203 ������
	my_F1F2_rez_A = &my_F1F2_rez[0];
	my_F1F2();				//  707 ������
	my_F1F2_P();
	my_F2F1_rez_A = &my_F2F1_rez[0];
	my_F2F1();		//  694 �����, ���������� ����� = 3054
	my_Data_F1_F2 = &my_DMA2_Data_F1_F2[0];
	my_F1_F2();		//  520 ������, ���������� ����� =
	iT1__ = DWT->CYCCNT;	// �� ����� START, ��� ������ ������� 3779 ������, � �������� - 4443, �� ����������� �� � 1-�� ����

	// ������������ ������� ��������������� �������������
	//*
	//my_Data_F0 = &my_DMA1_Data_F0[0];
	//my_Data_F0 = &my_DMA2_Data_F0[0];
	my_Data_F0 = &my_F0N[0];
	my_Data_F1 = &my_DMA1_Data_F1[0];
	my_F1();				//  513 ������
	my_Data_F2 = &my_DMA1_Data_F2[0];
	my_F2();				// 1203 ������
	my_F1F2_rez_A = &my_F1F2_rez_2[0];
	my_F1F2();				//  707 ������
	my_F2F1_rez_A = &my_F2F1_rez_2[0];
	my_F2F1();		//  694 �����, ���������� ����� = 3054
	my_Data_F1_F2 = &my_DMA1_Data_F1_F2[0];
	my_F1_F2();		//  520 ������, ���������� ����� =
	iT1__ = DWT->CYCCNT;	// �� ����� START, ��� ������ ������� 6745 ������, � �������� - 8265, �� ����������� �� � 1-�� ����
	//*/

	if(itemWork == WORK_HIST){
		Difference();
	}

	//if (index_OUT_0R >= count_OUT_0R){		// 1920/120 = 16

	// ���������� ������ �����������, ���������� ���������
	if(my_ms_num >= 16){
		avrResult_OUT_0R = (float)sum_OUT_0R / (float)index_OUT_0R;
		//resultTemp_CELL = avrResult_OUT_0RN;
		resultTemp_CELL = avrResult_OUT_0R;
		resultTemp_CELL = resultTemp_CELL - levelTemp_CELL;
		flagUpdateCompute_CELL = true;
		sum_OUT_0R = 0;
		}

	//=====================================================================================================
	for(int i = 0; i < 6; i++)
	{
		my_F2F1_sum[i] += my_F2F1_rez[i];
		//my_F2F1_P_sum[i] += my_F2F1_P_rez[i];
		my_F2F1_sum_2[i] += my_F2F1_rez_2[i];
	}
	for(int i = 0; i < 5; i++)
	{
		my_F1F2_sum[i] += my_F1F2_rez[i];
		my_F1F2_P_sum[i] += my_F1F2_P_rez[i];
		my_F1F2_sum_2[i] += my_F1F2_rez_2[i];
	}

	// ������ 16 ��, ������� 62,5 ��
	//if (index_OUT2_CPT_FREQ >= count_OUT2_CPT_FREQ){
	if(my_ms_num >= 16){
		//count_OUT2_CPT_FREQ = index_OUT2_CPT_FREQ;
		//*
		if(!b_F2F1_rezult)
		{
			b_F2F1_rezult = true;
			for (int i = 0; i < 6; i++){
				F2F1_rezult[i] = F2F1_rezult_1[i] = -(float)my_F2F1_sum[i] / (float)count_OUT2_CPT_FREQ;
				my_F2F1_sum[i] = 0;
				F2F1_rezult_2[i] = -(float)my_F2F1_sum_2[i] / (float)count_OUT2_CPT_FREQ;
				my_F2F1_sum_2[i] = 0;
			}
			// ���������� ����� ����� ����� � ���� ���������� ����� �����
			value_U2R = value_U2R - value_U2R_D; // +/- 10000 ������ ��������� = +/- 271 ������ ���������
			// ����� +/- 100 ������ ����� = +/- 3690 ������ �����
			flagUpdate_U2R = true;
		}
		else
		{
			b_F2F1_rezult = false;
			for (int i = 0; i < 6; i++){
				F2F1_rezult[i] = F2F1_rezult_2[i] = -(float)my_F2F1_sum[i] / (float)count_OUT2_CPT_FREQ;
				my_F2F1_sum[i] = 0;
				F2F1_rezult_D[i] = F2F1_rezult_2[i] - F2F1_rezult_1[i];
				F2F1_rezult_2[i] = -(float)my_F2F1_sum_2[i] / (float)count_OUT2_CPT_FREQ;
				my_F2F1_sum_2[i] = 0;
			}
			// ���������� ����� ����� ����� � ���� ���������� ����� �����
			value_U2R = value_U2R + value_U2R_D;
			//resultDOPLER_FREQ = F2F1_rezult_D[0] - F2F1_rezult_D[5];
			//resultDOPLER_FREQ = F2F1_rezult_D[1];
			//resultDOPLER_FREQ = -F2F1_rezult_D[5];
			resultDOPLER_FREQ = F2F1_rezult_D[1];
			flagUpdateCompute_DOPLER_FREQ = true;
			flagUpdate_U2R = true;
		}
		//*/

		/*
		for (int i = 0; i < 6; i++){
			F2F1_rezult[i] = -(float)my_F2F1_sum[i] / (float)index_OUT2_CPT_FREQ;
			//F2F1_P_rezult[i] = -(float)my_F2F1_P_sum[i] / (float)index_OUT2_CPT_FREQ;
			//p_my_F2F1_sum[i] = 0;
			my_F2F1_sum[i] = 0;
			//my_F2F1_P_sum[i] = 0;
		}
		//*/

		//F2F1_rezult_A = -2.95*F2F1_rezult[4];
		F2F1_rezult_A = F2F1_rezult[4];
		//F2F1_rezult_A = (F2F1_rezult[0]*(-0.37461) + F2F1_rezult[1]*(-0.6976) + F2F1_rezult[2]*(+0.241922) + F2F1_rezult[3]*(+0.529919) + F2F1_rezult[4]*(0.766044))/1.093523;
		F2F1_rezult_A_30 += F2F1_rezult_A;
		//result_OUT2_CPT_FREQ_CPT = F2F1_rezult[1] + 2.95*F2F1_rezult[4];// - F2F1_rezult_X;
		result_OUT2_CPT_FREQ_CPT = F2F1_rezult[1];// - F2F1_rezult_X;
		F2F1_rezult_N_30++;
		if(F2F1_rezult_N_30 == 30)
		{
			F2F1_rezult_A_30 /= 30;
			F2F1_rezult_A_900 += F2F1_rezult_A_30;
			F2F1_rezult_A_30 = 0;
			F2F1_rezult_N_30 = 0;
			F2F1_rezult_N_900++;
			if(F2F1_rezult_N_900 == 30)
			{
				F2F1_rezult_A_900 /= 30;
				F2F1_rezult_X = F2F1_rezult_A_900;
				F2F1_rezult_A_900 = 0;
				F2F1_rezult_N_900 = 0;
			}
		}
	}

	//if (index_OUT2_CPT_CRNT >= count_OUT2_CPT_CRNT){	// Один раз за 16 мс
	if(my_ms_num >= 16){
		// ���� ��� �� 16 ��
		//count_OUT2_CPT_CRNT = index_OUT2_CPT_CRNT;

		// ��������� ������ OUT1
		for (int i = 0; i < 5; i++){
					//F1F2_OUT1_rezult[i] = -(float)my_F1F2_OUT1_sum[i] / (float)count_OUT1_CPT_CRNT;
					my_F1F2_OUT1_sum[i] = 0;
				}

		// ��������� ������ OUT2
		for (int i = 0; i < 5; i++){
			F1F2_rezult[i] = -(float)my_F1F2_sum[i] / (float)count_OUT2_CPT_CRNT;
			F1F2_P_rezult[i] = (float)my_F1F2_P_sum[i] / (float)count_OUT2_CPT_CRNT;
			F1F2_rezult_2[i] = -(float)my_F1F2_sum_2[i] / (float)count_OUT2_CPT_CRNT;
			my_F1F2_sum[i] = 0;
			my_F1F2_P_sum[i] = 0;
			my_F1F2_sum_2[i] = 0;
		}
		F1F2_P_S = 0;
		for (int i = 0; i < 5; i++)
		{
			F1F2_P_S += F1F2_P_rezult[i];
		}
		F1F2_P_S /= 5;
		for (int i = 0; i < 5; i++)
		{
			F1F2_P_rezult[i] -= F1F2_P_S;
		}

		//F1F2_rezult_A = (F1F2_rezult[3]*0.35 + F1F2_rezult[4])/1.35;
		//F1F2_rezult_A = (F1F2_rezult[0]*(-0.37461) + F1F2_rezult[1]*(-0.6976) + F1F2_rezult[2]*(+0.241922) + F1F2_rezult[3]*(+0.529919) + F1F2_rezult[4]*(0.766044))/1.093523;
		F1F2_rezult_A = (F1F2_rezult[2] + F1F2_rezult[3])/2.0;
		F1F2_rezult_A_30 += F1F2_rezult_A;
		//result_OUT2_CPT_CRNT_DOPLER = F1F2_rezult[1] - F1F2_rezult_X;
		//result_OUT2_CPT_CRNT_DOPLER = (F1F2_rezult[0]*0.927184 + F1F2_rezult[1]*0.997564 + F1F2_rezult[2]*0.970296 + F1F2_rezult[3]*0.848048 +  F1F2_rezult[4]*0.642788)/4.385879 - F1F2_rezult_X;


		// 2021_04_08 � ����� ��� ���������, � "������" �� ������� �������
		// ��� ������������ ����� ����� (��� �������) ����� ��������� ��������� ����������� "������������" ����, ���� ��������� �������� ����������
		result_OUT2_CPT_CRNT_DOPLER = (F1F2_rezult[1] + F1F2_rezult[2])/2.0;// - F1F2_rezult_X;
		F1F2_rezult_N_30++;
		if(F1F2_rezult_N_30 == 30)
		{
			F1F2_rezult_N_30 = 0;
			F1F2_rezult_N_900++;

			F1F2_rezult_A_30 /= 30;
			F1F2_rezult_A_900 += F1F2_rezult_A_30;
			F1F2_rezult_A_30 = 0;

			if(F1F2_rezult_N_900 == 30)
			{
				F1F2_rezult_N_900 = 0;

				F1F2_rezult_A_900 /= 30;
				F1F2_rezult_X = F1F2_rezult_A_900;
				F1F2_rezult_A_900 = 0;
			}
		}
	}
}

static inline void my_ADC2_2(void){
	// ��� ������� C
	my_DataADC2_1_();		// ����� ���������� my_DataADC2_1_() 6518 ������
	my_DataADC2_2_();		// ����� ���������� my_DataADC2_1_()+my_DataADC2_2_() 17634 ������
	my_F1_();
	my_F2_();
	my_F1F2_();
	my_F2F1_();
	my_F1_F2_();

	if (index_OUT_0R >= count_OUT_0R){
		avrResult_OUT_0R_ = (float)sum_OUT_0R_ / (float)index_OUT_0R;
		avrResult_OUT_2R = (float)sum_OUT_2R_ / (float)index_OUT_0R;
		//resultTemp_CELL = avrResult_OUT_0RN;
		resultTemp_CELL = avrResult_OUT_0R_;
		resultTemp_CELL = resultTemp_CELL - levelTemp_CELL;
		flagUpdateCompute_CELL = true;
		sum_OUT_0R_ = 0;
		sum_OUT_2R_ = 0;
		}
	for(int i = 0; i < 6; i++)
	{
		p_my_F2F1_sum_[i] += p_my_F2F1_rez_[i];
	}
	for(int i = 0; i < 5; i++)
	{
		p_my_F1F2_sum_[i] += p_my_F1F2_rez_[i];
	}
	if (index_OUT2_CPT_FREQ >= count_OUT2_CPT_FREQ){
		count_OUT2_CPT_FREQ = index_OUT2_CPT_FREQ;
		for (int i = 0; i < 6; i++){
			F2F1_rezult_[i] = -(float)my_F2F1_sum_[i] / (float)index_OUT2_CPT_FREQ;
			p_my_F2F1_sum_[i] = 0;
		}
		result_OUT2_CPT_FREQ_CPT = F2F1_rezult_[0];// Kurchanov 2021.01.19
	}

	if (index_OUT2_CPT_CRNT >= count_OUT2_CPT_CRNT){	// ���� ��� �� 16 ��
		// ���� ��� �� 16 ��
		count_OUT2_CPT_CRNT = index_OUT2_CPT_CRNT;
		for (int i = 0; i < 5; i++){
			F1F2_rezult_[i] = -(float)my_F1F2_sum_[i] / (float)index_OUT2_CPT_CRNT;
			p_my_F1F2_sum_[i] = 0;
		}
		result_OUT2_CPT_CRNT_DOPLER = F1F2_rezult_[0];
	}
}

// ��������� ������ � ADC2
static inline void UpdateDataADC2(void){
	// ������������ �������������� ����� DMA2
	iT2__ = DWT->CYCCNT;
	// ������� 2 - ������� �������� ���������� �� �		- 33384 �����,  ������ = 60022
	// ������� 1 - ������� �������� ���������� �� ASM	-  8315 ������, ������ = 60022 (60021 - 60025) (����������� ������ - Ok!)
	// ������� 0 - ��� �������� ���������� �� �			-  8325 ������, ������ = 60022 (60022 - 60027) ��� ����������� ������ !
	// int var_my_ADC2;

	//static int iF0 = 0;	// Kurchanov 27.07.2020
	static int iT1 = 0;
	static int iT2 = 0;
	static int idT = 0;
	

	//pDataDMA2 = (volatile uint16_t*)&my_DMA2_tst_Data[0];

	index_SD2 		+= 120;
	index_OUT_0R	+= 120;
	index_OUT2_CPT_FREQ += 10;
	index_OUT2_CPT_CRNT += 12;

	//my_ms_num++;					// ������� �����������

	switch(var_my_ADC2){
		case 0:
			my_ADC2_0();
			break;
		case 1:
			//my_ADC1_1();
			my_ADC2_1();
			break;
		case 2:
			my_ADC2_2();
			break;
	}

	/*
	if(!b_my_ms_num)
	{
		if(my_ms_num == 16) b_my_ms_num = true;
	}
	//*/

	if (index_OUT_0R >= count_OUT_0R){
		index_OUT_0R = 0;
	}



	
/*
 // ��������� (���� ���� �����������)
	switch(itemMOD_FREQ){
		case 0:
		case 1:
			sum_OUT2_CPT[0]	+= sum_OUT_2R_;
			break;
		case 2:
		case 3:
			sum_OUT2_CPT[1]	+= sum_OUT_2R_;
			break;
	}
//*/


#ifdef my_EQ_test
	b_eq = true;
	//my_EQ_test_1();
	//my_EQ_test_2();
	//my_EQ_test_3();
	//my_EQ_test_4();
	//my_EQ_test_5();
	//my_EQ_test_6();
	//my_EQ_test_7();
#endif

	// ������ ����� ����
	static int i_h   = 0;
	static int i_hh  = 0;	// ������
	static int i_hL  = 0;	// ����������
	static int i_N  = 0;
	static int i_NN = 0;
	static int i_NL = 0;
	static int i_NX = 0;
	static int i_dNX = 0;
	static int i_dNL = 0;
	static int i_Diff_F = 0;
	static int i_Buf[20] = {0, 0, 0, 0, 0,
		                    0, 0, 0, 0, 0,
		                    0, 0, 0, 0, 0,
		                    0, 0, 0, 0, 0};
	static int i_Ind   = 0;
	static int i_P = 0;									
	i_N++;
	if(i_N == 1000) 
	{
		i_N = 0; // ������� ������� �����������
		flagUpdateCompute_FREQ_GNSS = true;	// ���� ��� � �������
	}
	// ������ �������
	if ((statusLoopPID & PID_FLAG_LOOP_FREQ_GNSS) == PID_FLAG_LOOP_FREQ_GNSS){
		if (flagUpdateCompute_FREQ_GNSS == true){
			flagUpdateCompute_FREQ_GNSS = false;
			i_hL = i_h;
			i_h = TIM17->CCR1;
			if(flagStartCompute_FREQ_GNSS == false)
			{
				i_hh = i_h;
				i_hL = i_h;
				flagStartCompute_FREQ_GNSS = true;
			}			
			i_dNX = 0;
			i_Diff_F = i_h - i_hh;	// ������ ������������ 0 � 1,
									// � ������� ����� �������� 0,5
			if(i_Diff_F)			// i_hh + 0.5
			{
				// ������ ������, ��� ���� (���� �� ����������)
				// ������� ������, ��� ����
				i_dNX = 1;
			}
			else
			{
				i_dNX = -1;
			}					

			i_Ind++;
			if(i_Ind >= 20) i_Ind = 0;
			i_P = i_Buf[i_Ind];
			i_Buf[i_Ind] = i_dNX;
			
			i_NX -= i_P;
			i_NX += i_dNX;
			
			i_dNL = 0;
			if(i_h > i_hL)	// i_hh + 0.5
			{
				// ������ ������, ��� ���� (���� �� ����������)
				// ������� ������, ��� ����
				i_dNL = 1;
			}
			if(i_h < i_hL)
			{
				i_dNL = -1;
			}			
			i_NL += i_dNL;
			
			if(i_dNX > 0)
			{
				// ������ ������, ��� ���� (���� �� ����������)
				// ������� ������, ��� ����
				shift_Freq_GNSS_I -= step_Freq_GNSS;
			}
			else
			{
				shift_Freq_GNSS_I += step_Freq_GNSS;
			}
			//
			// ����� �� ������ ������, �� � ���������� !!
			//
			shift_Freq_GNSS = -shift_Freq_GNSS_I*0.5f 
												- ((float)i_dNL)*4.0f 
												- ((float)i_dNX)*0.0f
												- ((float)i_NL)*0.0f
												- ((float)i_NX)*0.0f;
			//flagStartCompute_FREQ_GNSS
			f_MESSAGE_3 = shift_Freq_GNSS;
		}
	}
	// ����� ����� ����
	if (index_OUT2_CPT_FREQ >= count_OUT2_CPT_FREQ){
		index_OUT2_CPT_FREQ = 0;
		result_OUT2_CPT_FREQ_CPT += shift_OUT2_FREQ;
		result_OUT2_CPT_FREQ_CPT += shift_Freq_GNSS;
		result_OUT2_CPT_FREQ_CPT_tmp = result_OUT2_CPT_FREQ_CPT;
		flagUpdateCompute_OUT2_CPT_FREQ = true;
	}

	

	/*
	// ���������� ���������� �������� 1
	if (index_SD2 >= count_SD2){
		index_SD2 = 0;
#ifdef my_ASM_fun
		//avrResult_SD2 = (float)sum_SD2 / (float)index_SD2;
		//sum_SD2 = 0;
#endif
#ifdef my_C_fun
		avrResult_SD2 = (float)sum_SD2_ / (float)index_SD2;		
		sum_SD2_ = 0;
#endif
	}
	//*/

	/*
	// Kurchanov 13.01.2021
#ifdef my_C_fun
	sum_ampl_Data_F0_ += (max_Data_F0_ - min_Data_F0_);
	sum_ampl_Data_F1_ += (max_Data_F1_ - min_Data_F1_);
	sum_ampl_Data_F2_ += (max_Data_F2_ - min_Data_F2_);
	sum_ampl_Data_F1_F2_ += (max_Data_F1_F2_ - min_Data_F1_F2_);

	value_UT1A_aver += value_UT1A;
	value_DTX_aver += value_DTX;
	value_VY_aver += value_VY;
#endif
	//*/
	
	//if (index_OUT2_CPT_CRNT >= count_OUT2_CPT_CRNT){	// ���� ��� �� 16 ��
	if(my_ms_num == 16){
		index_OUT2_CPT_CRNT = 0;
		// ���� ��� �� 16 ��
		result_OUT2_CPT_CRNT_DOPLER += shift_OUT2_DOPLER_CRNT;								// ??
		result_OUT2_CPT_CRNT_DOPLER += delta_DOPLER_DC;										// ??
		result_OUT2_CPT_FREQ_CPT -= result_OUT2_CPT_CRNT_DOPLER*value_mult_To_FREQ;			// !!!!!!!
		result_OUT2_CPT_CRNT_DOPLER_tmp = result_OUT2_CPT_CRNT_DOPLER;

		flag_SCAN_CRNT = true;									// �������� ����� ������������ ��� ���������� � ����������� ������
		flagUpdateCompute_OUT2_DOPLER_CRNT = true;				// ??
		// �������� ������������
		result_OUT2_DOPLER_TEC = result_OUT2_CPT_CRNT_DOPLER;	// ??
		flagUpdateCompute_OUT2_DOPLER_TEC = true;

		//*
		// TOLIK
				if((itemWork == WORK_TEST_ADC_3) && (!b_buf_TEST_ADC_3))
				{
					for(int i = 0; i < 120; i++)
					{
						buf_TEST_ADC_3[numPos + i] = my_DMA2_Data_F0_[i + 55];
					}
					numPos += 120;
					if(numPos == 2400)
					{
						numPos = 0;
						b_buf_TEST_ADC_3 = true;
					}
				}
				//i_MESSAGE_3 = numPos;
				if(b_buf_TEST_ADC_3)
				{
					i_MESSAGE_3 = 2400;
				}
				else
				{
					i_MESSAGE_3 = 0;
				}
		//*/
		/*
		if(itemWork == WORK_TEST_ADC_2)
		{
			b_buf_TEST_ADC_2 = true;
			//i_MESSAGE_3 = 3600;
			if(num_corr_TEST_ADC_2 < 1000){
				corr_1_TEST_ADC_2 +=result_OUT2_CPT_FREQ_CPT_tmp*result_OUT2_CPT_FREQ_CPT_tmp;
				corr_2_TEST_ADC_2 +=result_OUT2_CPT_CRNT_DOPLER_tmp*result_OUT2_CPT_CRNT_DOPLER_tmp;
				corr_12_TEST_ADC_2 +=result_OUT2_CPT_FREQ_CPT_tmp*result_OUT2_CPT_CRNT_DOPLER_tmp;
				num_corr_TEST_ADC_2++;
			}
			else
			{
				if(corr_1_TEST_ADC_2 > 0)
				{
					corr_1_TEST_ADC_2 = sqrt(corr_1_TEST_ADC_2);
					if(corr_2_TEST_ADC_2 > 0)
					{
						corr_2_TEST_ADC_2 = sqrt(corr_2_TEST_ADC_2);
						corr_TEST_ADC_2 = corr_12_TEST_ADC_2/(corr_2_TEST_ADC_2*corr_1_TEST_ADC_2);
					}
					else
					{
						corr_TEST_ADC_2 = 0;
					}
				}
				else
				{
					corr_TEST_ADC_2 = 0;
				}
				corr_1_TEST_ADC_2 = 0;
				corr_2_TEST_ADC_2 = 0;
				corr_12_TEST_ADC_2 = 0;
				num_corr_TEST_ADC_2 = 0;
				i_MESSAGE_3 = (int)(corr_TEST_ADC_2*1000);
			}
		}
		else
		{
			b_buf_TEST_ADC_2 = false;
			//i_MESSAGE_3 = -1;
			corr_1_TEST_ADC_2 = 0;
			corr_2_TEST_ADC_2 = 0;
			corr_12_TEST_ADC_2 = 0;
			num_corr_TEST_ADC_2 = 0;
		}
		//*/
		//my_ms_num = 1;	// ������������� ���� ���������� 1-� ������������
	}

	/*
	// Заготовка
	index_OUT2_CPT++;
	if (index_OUT2_CPT >= count_OUT2_CPT){
		count_OUT2_CPT = index_OUT2_CPT;
		result_OUT2_CPT[0] = (float)(sum_OUT2_CPT[0])/(float)count_OUT2_CPT;
		result_OUT2_CPT[1] = (float)(sum_OUT2_CPT[1])/(float)count_OUT2_CPT;
		result_OUT2_CPT[0] /= 120.0f;
		result_OUT2_CPT[1] /= 120.0f;
		sum_OUT2_CPT[0] = 0;
		sum_OUT2_CPT[1] = 0;
		index_OUT2_CPT = 0;
	}
	//*/
	
	//*
	// Kurchanov 27.07.2020	
	iT3__ = DWT->CYCCNT;
	iT__n = iT3__ - iT2__;
	//i_MESSAGE_3 = idT__;
	//i_MESSAGE_3 = iT__n;
	/*
	iF0 ++;
	if(iF0 >= 2000)
	{
		iF0 = 0;
		b_MESSAGE = true;
	};
	//*/
	//*/
	
	/*
	// Kurchanov 23.11.2020
	tickDelayUpdateTempCell += 1;
	if (tickDelayUpdateTempCell == 1000){
		tickDelayUpdateTempCell = 0;
		// ����������� ����������� ������
		if (flagConnectedTempSensor == true){
			uint8_t addressI2C3 = ADT7410_ADDRESS;
			I2C3_RxBuffer[0] = 0;
			I2C3_RxBuffer[1] = 0;
			if (HAL_I2C_Master_Receive(&hi2c3, addressI2C3<<1, &I2C3_RxBuffer[0], 2, 200) == HAL_OK){
				value_TempCell = ((int)(I2C3_RxBuffer[0] << 8 | I2C3_RxBuffer[1]))/128.0f;
				resultAverage_SENSOR_TempCell = levelValueSensor_TempCell - value_TempCell;
			}		
			flagUpdateTempCell = true;
		}
		
	}
	//*/
}

// Kurchanov 2020_10_23
static inline void funWork_VOID_TEST(){	// ���������� 1000 ��� � �������, ������ ������������
	static int i_Num = 0;
	static int delaySend = 0;
	static bool b_Start = false;
	static uint32_t dataSend[9];
	if ((statusLoopPID & PID_FLAG_LOOP_VOID_TEST ) == PID_FLAG_LOOP_VOID_TEST ){
		if(!b_Start) b_Start = true; // ����� �������
		// ���������� ����� VOID_TEST, ������ ������ ������ �����������
		// ������ ��� itemWork == WORK_NONE
		delaySend++;
		if (delaySend % 100 == 0){
			delaySend = 0;
			// ���������� 10 ��� � �������, ������� 9 ���������� �������� �� 4 �����
			i_Num++;
			dataSend[0] = i_Num;	// ����� ������� ����� ��������� ������ ��������
			dataSend[1] = (int)(avrResult_OUT_3R*1000.0f);
			dataSend[2] = (int)(avrResult_CONTR*1000.0f);
			dataSend[3] = (int)(avrResult_OUT_DC*1000.0f);
			dataSend[4] = (int)(resultTemp_CELL*1000.0f);
			dataSend[5] = value_UT1A*1000;
			dataSend[6] = value_DTX*1000;
			dataSend[7] = value_T5*1000;
			dataSend[8] = 0;	// ��������� ������� � ������� !!
								// ������������ ���� ������� � ���������� ������� �����
			SendPkgData(STREAM_DATA, ((uint8_t*)&dataSend), 9*4);
			}
		}
	else{
		if(b_Start)	// ����� ����������
		{
			b_Start = false;
			i_Num = 0;
			delaySend = 0;
		}
	}
}

static inline void funWork_SCAN_CRNT(){	// ���������� 1000 ��� � �������, ������ ������������
	// ����� ���������� UpdateDataADC2()
	//my_TST++;
	static int delaySend = 0;
	static int delaySend_2 = 0;
	static int dS_1 = 0;
	static int dS_2 = 0;
	static int dS_3 = 0;
	static int dS_4 = 0;
	static int dS_5 = 0;
	static int dS_6 = 0;
	static int dS_7 = 0;
	static int dS_8 = 0;
	static uint32_t dataSend[9];

	if(flag_SCAN_CRNT)	// 1 ��� � 16 ��, 62,5 ���� � �������
	{
		//my_TST++;


		dS_1 += (int)(avrResult_OUT_DC*1000);
		dS_2 += (int)(result_OUT2_CPT_CRNT_DOPLER*1000);
		//dS_3 += (int)(result_OUT2_CPT_FREQ_CPT*1000);
		// value_UT1A
		dS_3 += (int)(value_UT1A*10);
		dS_4 += (int)(avrResult_OUT_1N*1000);
		//dS_5 += (int)(avrResult_OUT_1A*1000);
		dS_5 += (int)((F1F2_rezult_2[1] + F1F2_rezult_2[2])/2.0f*1000);


		switch(var_my_ADC2){
			case 0:
				//*
				dS_4 += (int)(F1F2_P_rezult[0]*10000);
				dS_5 += (int)(F1F2_P_rezult[1]*10000);
				dS_6 += (int)(F1F2_P_rezult[2]*10000);
				dS_7 += (int)(F1F2_P_rezult[3]*10000);
				dS_8 += (int)(F1F2_P_rezult[4]*10000);
				//*/

				/*
				dS_4 += (int)(result_OUT2_CPT_CRNT[0]*1000);
				dS_5 += (int)(result_OUT2_CPT_CRNT[1]*1000);
				dS_6 += (int)(result_OUT2_CPT_CRNT[2]*1000);
				dS_7 += (int)(result_OUT2_CPT_CRNT[3]*1000);
				dS_8 += (int)(result_OUT2_CPT_CRNT[4]*1000);
				//*/
				break;
			case 1:
				/*
				dS_4 += (int)(F1F2_P_rezult[0]*10000);
				dS_5 += (int)(F1F2_P_rezult[1]*10000);
				dS_6 += (int)(F1F2_P_rezult[2]*10000);
				dS_7 += (int)(F1F2_P_rezult[3]*10000);
				dS_8 += (int)(F1F2_P_rezult[4]*10000);
				//*/

				/*
				dS_3 += (int)(F2F1_rezult_D[0]*1000);
				dS_4 += (int)(F2F1_rezult_D[1]*1000);
				dS_5 += (int)(F2F1_rezult_D[2]*1000);
				dS_6 += (int)(F2F1_rezult_D[3]*1000);
				dS_7 += (int)(F2F1_rezult_D[5]*1000);
				dS_8 += 0;//(int)(F2F1_rezult_D[6]*1000);
				/*
				dS_4 += (int)(F2F1_rezult[1]*1000);
				dS_5 += (int)(F2F1_rezult[2]*1000);
				dS_6 += (int)(F2F1_rezult[3]*1000);
				dS_7 += (int)(F2F1_rezult[4]*1000);
				dS_8 += (int)(F2F1_rezult[5]*1000);
				//*/

				//*
				//dS_4 += (int)(result_OUT2_CPT_FREQ_CPT*1000);
				//dS_4 += (int)(F1F2_rezult[0]*1000);
				//dS_5 += (int)(F1F2_rezult[1]*1000);
				dS_6 += (int)(F1F2_rezult[2]*1000);
				dS_7 += (int)(F1F2_rezult[3]*1000);
				dS_8 += (int)(F1F2_rezult[4]*1000);
				//*/
				break;
			case 2:
				dS_7 += (int)(F1F2_rezult_[0]*1000);
				dS_8 += (int)(F1F2_rezult_[1]*1000);
				dS_3 += (int)(F1F2_rezult_[2]*1000);
				dS_4 += (int)(F1F2_rezult_[3]*1000);
				//dS_5 += (int)(F1F2_rezult_[4]*1000);
				/*
				dS_4 += (int)(F1F2_rezult_[0]*1000);
				dS_5 += (int)(F1F2_rezult_[1]*1000);
				dS_6 += (int)(F1F2_rezult_[2]*1000);
				dS_7 += (int)(F1F2_rezult_[3]*1000);
				dS_8 += (int)(F1F2_rezult_[4]*1000);
				//*/
				break;
			}
		flag_SCAN_CRNT = false;

		delaySend++;

		if (delaySend % 6 == 0){			// ����������� 10,42 ��� � �������
			delaySend_2++;					// Kurchanov

			if(delaySend_2  >= value_N_STEP_L){
				delaySend_2 = 0;
				dataSend[0] = value_VY;
				dataSend[1] = dS_1/6/value_N_STEP_L; dS_1 =0;
				dataSend[2] = dS_2/6/value_N_STEP_L; dS_2 =0;
				dataSend[3] = dS_3/6/value_N_STEP_L; dS_3 =0;
				dataSend[4] = dS_4/6/value_N_STEP_L; dS_4 =0;
				dataSend[5] = dS_5/6/value_N_STEP_L; dS_5 =0;
				dataSend[6] = dS_6/6/value_N_STEP_L; dS_6 =0;
				dataSend[7] = dS_7/6/value_N_STEP_L; dS_7 =0;
				dataSend[8] = dS_8/6/value_N_STEP_L; dS_8 =0;

				SendPkgData(STREAM_DATA, ((uint8_t*)&dataSend), 9*4);
				my_TST++;
				value_VY += scanStep_VY;
				if (value_VY > scanMax_VY){
					value_VY = scanMin_VY;
				}
				flagUpdate_VY = true;
			}
		}
	}
	else
	{
		return;
	}

	/*
	delaySend++;

	if (delaySend % 6 == 0){			// ����������� 8 ��� � �������, 125=2*62,5=2/0,016; 125 ��� = 2 �������
		delaySend_2++;					// Kurchanov

		if(delaySend_2  >= value_N_STEP_L){
			delaySend_2 = 0;

			dataSend[0] = value_VY;
			dataSend[1] = dS_1/6/value_N_STEP_L; dS_1 =0;
			dataSend[2] = dS_2/6/value_N_STEP_L; dS_2 =0;
			dataSend[3] = dS_3/6/value_N_STEP_L; dS_3 =0;
			dataSend[4] = dS_4/6/value_N_STEP_L; dS_4 =0;
			dataSend[5] = dS_5/6/value_N_STEP_L; dS_5 =0;
			dataSend[6] = dS_6/6/value_N_STEP_L; dS_6 =0;
			dataSend[7] = dS_7/6/value_N_STEP_L; dS_7 =0;
			dataSend[8] = dS_8/6/value_N_STEP_L; dS_8 =0;

			SendPkgData(STREAM_DATA, ((uint8_t*)&dataSend), 9*4);
			value_VY += scanStep_VY;
			if (value_VY > scanMax_VY){
				value_VY = scanMin_VY;
			}
			flagUpdate_VY = true;
		}
	}
	//*/
}

// 
// ����� �������� ��� funWork_TEST_ADC()
// �������� dataSend[0] - dataSend[8]
// ������ � ����� ������� - ����� �������� �������
// �� ��� ���, ���� �� ������� ���� �������� ������
// 
// ������ ��������� ����������, ����� �������� �� �����
// � ����������� ���
//
// ��������� ����� ������ TEST
//
// ������ �������� ������ � SourceTree 21.08.2020
//

	
static inline void funWork_TEST_ADC(){
	static int delaySend = 0;
	delaySend++;
	if (delaySend % 100 == 0){		// 10 ��� � 1������� �����
		static uint32_t dataSend[6];
		dataSend[0] = delaySend / 100;
		dataSend[1] = (int)(avrResult_OUT_DC*1000);
		dataSend[2] = (int)(result_OUT2_CPT_CRNT_DOPLER*1000);
		// avrResult_SD1 - ����������� �����������
		avrResult_SD1_ /= 1000;
		dataSend[3] = (int)(avrResult_SD1_*1000);
		avrResult_SD1_ = 0;
		//dataSend[3] = (int)(avrResult_CONTR*1000.0f);
		//dataSend[3] = (int)(result_OUT2_CPT_FREQ_CPT*1000);
			//dataSend[4] = (int)(resultTemp_CELL*1000);
		dataSend[4] = value_DTX*1000;
		//dataSend[4] = (int)(resultTemp_D_CELL*1000);
		dataSend[5] = (int)(value_UT1A*1000);
		SendPkgData(STREAM_DATA, ((uint8_t*)&dataSend), 6*4);	
	}
	else
	{
		avrResult_SD1_ += avrResult_SD1;
	}
}

// TOLIK
// dataSend[3] = (int)(result_OUT2_CPT_FREQ_CPT*1000);
// dS_6 += (int)(result_OUT2_CPT_CRNT_DOPLER*1000);
// value_VY
// value_UT1A
static inline void funWork_TEST_ADC_2(){
	static uint32_t dataSend[6];
	static int delaySend = 0;
	//if(b_buf_TEST_ADC_2){
		delaySend++;
		if (delaySend % 100 == 0){
			// value_DTX
			// value_UT1A
			dataSend[0] = delaySend / 100;
			dataSend[1] = (int)(value_UT1A*1000); //(int)(value_RFI*1000); // (avrResult_OUT_DC*1000);
			dataSend[2] = (int)(result_OUT2_CPT_FREQ_CPT*1000); //(int)(value_UT1A*1000);
			dataSend[3] = (int)(value_VY*1000); //(int)(value_DTX*1000); // avrResult_OUT_3R
			dataSend[4] = (int)(result_OUT2_CPT_CRNT_DOPLER*1000); //(int)(avrResult_OUT_3R*1000);
			//dataSend[4] = (int)(resultTemp_CELL*1000);
			dataSend[5] = (int)(avrResult_OUT_DC*1000); //(value_VY*1000);
			SendPkgData(STREAM_DATA, ((uint8_t*)&dataSend), 6*4);
		}
	//}
}

static inline void funWork_TEST_ADC_3(){
	static uint32_t dataSend[9];
	static int delaySend = 0;
	//static int h;
	if(b_buf_TEST_ADC_3){
		//uint16_t * p1 = (uint16_t *)&h;
		//uint16_t * p2 = p1 + 1;
		delaySend++;
		if (delaySend % 100 == 0){
			//*
			dataSend[0] = pkgPos; pkgPos++;
		for(int i = 1; i < 9; i++)
			{
				//*p1 = buf_TEST_ADC_3[numPos]; numPos++;
				//*p2 = buf_TEST_ADC_3[numPos]; numPos++;
				//dataSend[i] = h;
				dataSend[i] = (int)buf_TEST_ADC_3[numPos]; numPos++;
			}
			SendPkgData(STREAM_DATA, ((uint8_t*)&dataSend), 9*4);

			if(numPos == 2400){
				// ����� ��������
				pkgPos = 0;
				numPos = 0;
				b_buf_TEST_ADC_3 = false;
				}
				//*/
			}
		}
}
	
static inline void funWork_SCAN_FREQ(){
	static int delaySend = 0;
	static int delaySend_2 = 0;
	static int dS_1 = 0;
	static int dS_2 = 0;
	static int dS_3 = 0;
	static int dS_4 = 0;
	static int dS_5 = 0;
	static int dS_6 = 0;
	static int dS_7 = 0;
	static int dS_8 = 0;
	static uint32_t dataSend[9];

	if(flag_SCAN_CRNT)	// 1 ��� � 16 ��
	{
		/*
		// my_alarm |= 0x80; 	- ��������� �������
		// my_alarm &= ~(0x80);	- ��������� �������
		if(b_OUT_DC)
		{
			my_alarm |= 0xF0;	// ��������
			b_OUT_DC = false;
		}
		else
		{
			my_alarm &= ~(0xF0);
		}
		i_MESSAGE_2 = my_ms_num;
		i_MESSAGE_3 = index_OUT_DC;
		if(index_OUT_DC != 0)
		{
			my_alarm |= 0x80;	// ��������
			//i_MESSAGE_3 = index_OUT_DC;
		}
		else
		{
			//my_alarm &= ~(0x80);	// ��������
			//i_MESSAGE_3 = index_OUT_DC;
		}
		//*/

		/*			dS_1 += (int)(avrResult_OUT_DC*1000);
		dS_2 += (int)(result_OUT2_CPT_CRNT_DOPLER*1000);//result_OUT2_CPT_CRNT_DOPLER*1000);
		dS_3 += (int)(result_OUT2_CPT_FREQ_CPT*1000);
		//*/

		/*
		dS_7 += (int)(F1F2_rezult[0]*1000);
		dS_8 += (int)(F1F2_rezult[1]*1000);
		dS_3 += (int)(F1F2_rezult[2]*1000);
		dS_4 += (int)(F1F2_rezult[3]*1000);
		dS_5 += (int)(F1F2_rezult[4]*1000);

		dS_6 += (int)(avrResult_OUT_DC*1000);
		dS_1 += (int)(result_OUT2_CPT_CRNT_DOPLER*1000);
		dS_2 += (int)(result_OUT2_CPT_FREQ_CPT*1000);
		//*/

		dS_1 += (int)(avrResult_OUT_DC*1000);
		//dS_1 += (int)(value_VY*1000);

		switch(var_my_ADC2){
			case 0:
				dS_4 += (int)(result_OUT2_CPT_FREQ[0]*1000);
				dS_5 += (int)(result_OUT2_CPT_FREQ[1]*1000);
				dS_6 += (int)(result_OUT2_CPT_FREQ[2]*1000);
				dS_7 += (int)(result_OUT2_CPT_FREQ[3]*1000);
				dS_8 += (int)(result_OUT2_CPT_FREQ[4]*1000);
				break;
			case 1:
				//dS_1 += (int)(F2F1_rezult[0]*1000);
				dS_2 += (int)(F2F1_rezult[1]*1000);
				dS_3 += (int)(F2F1_rezult[2]*1000);
				dS_4 += (int)(F2F1_rezult[3]*1000);
				dS_8 += (int)(F2F1_rezult[4]*1000);
				dS_7 += (int)(F2F1_rezult[5]*1000);
				dS_5 += (int)(result_OUT2_CPT_FREQ_CPT*1000); //(int)(avrResult_OUT_DC*1000);
				dS_6 += (int)(result_OUT2_CPT_CRNT_DOPLER*1000);
				break;
			case 2:
				dS_4 += (int)(F2F1_rezult_[0]*1000);
				dS_5 += (int)(F2F1_rezult_[1]*1000);
				dS_6 += (int)(F2F1_rezult_[2]*1000);
				dS_7 += (int)(F2F1_rezult_[3]*1000);
				dS_8 += (int)(F2F1_rezult_[4]*1000);
				break;
			}
		flag_SCAN_CRNT = false;
	}
	else
	{
		return;
	}

	delaySend++;

	if (delaySend % 6 == 0){			// ����������� 10 ��� � �������
		delaySend_2++;					// Kurchanov

		if(delaySend_2  >= value_N_STEP_L){
			delaySend_2 = 0;

			dataSend[0] = value_UT2A;
			dataSend[1] = dS_1/6/value_N_STEP_L; dS_1 =0;
			dataSend[2] = dS_2/6/value_N_STEP_L; dS_2 =0;
			dataSend[3] = dS_3/6/value_N_STEP_L; dS_3 =0;
			dataSend[4] = dS_4/6/value_N_STEP_L; dS_4 =0;
			dataSend[5] = dS_5/6/value_N_STEP_L; dS_5 =0;
			dataSend[6] = dS_6/6/value_N_STEP_L; dS_6 =0;
			dataSend[7] = dS_7/6/value_N_STEP_L; dS_7 =0;
			dataSend[8] = dS_8/6/value_N_STEP_L; dS_8 =0;

			SendPkgData(STREAM_DATA, ((uint8_t*)&dataSend), 9*4);

			value_UT2A += scanStep_UT2A;
			if (value_UT2A > scanMax_UT2A){
				value_UT2A = scanMin_UT2A;
			}
			flagUpdate_UT2A = true;
		}
	}
}

static inline void Difference(){           // ������� ������  ������� ������ � 1 ��

  maxfreq = 0;
  minfreq = 65535;
  for(int i = 0; i < 120; i++){
	  tmp = my_DMA2_Data_F1_F2[i];             // ����� ��� � ���� �������
	  if(minfreq > tmp)
	  minfreq = tmp;
	  if(maxfreq < tmp)
	  maxfreq = tmp;
  }

  diff[no] = maxfreq - minfreq;      // ��������� m-��������� ������� ������ ������
  no++;

  if( no == 1000) flagHist=true;     // ��� ���������� 1000 ��������� ���������� �������� ����������� (���� �� ���������� = true)
  if( no == 2000)                    // ��� ���������� 2000 ��������� ���� �� ���������� = true, ������������ diff[] ���������� � ������
  {
	  flagHist = true;
	  no = 0;
  }
}

static inline void funWork_HIST(void){     // ������� �������� ����������� �� ���������
  	static uint32_t dataSend[9];
	static int delaySend = 0;
	if(b_buf_HIST){
		delaySend++;
		if (delaySend % 100 == 0){
			dataSend[8] = numPosHist;
			for(int i = 0; i < 8; i++)
			{
				dataSend[i] = rez_cell[numPosHist + i];
			}
			numPosHist += 8;  			// ����� ������
			SendPkgData(STREAM_DATA, ((uint8_t*)&dataSend), 9*4);

			if(numPosHist >= num_cell) {
				numPosHist = 0; 		// ���������� ����� ������
				b_buf_HIST = false; 	//����� ����� �� �������� ������ �� ���������
				}
		}
	}
}


static inline void funWork_TEST_TEMP_CELL(){
	static int delaySend = 0;
	delaySend++;
	if (delaySend % 100 == 0){	

		static uint32_t dataSend[9];
		dataSend[0] = value_UT2A;
		dataSend[1] = (int)(avrResult_OUT_DC*1000);
		dataSend[2] = (int)(result_OUT2_CPT_CRNT_DOPLER*1000);
		dataSend[3] = (int)(result_OUT2_CPT_FREQ_CPT*1000);
		dataSend[4] = (int)(result_OUT2_CPT_FREQ[1]*1000);
		dataSend[5] = (int)(result_OUT2_CPT_FREQ[2]*1000);
		dataSend[6] = (int)(result_OUT2_CPT_FREQ[3]*1000);
		dataSend[7] = (int)(result_OUT2_CPT_FREQ[4]*1000);
		dataSend[8] = (int)(result_OUT2_CPT_FREQ[5]*1000);
		SendPkgData(STREAM_DATA, ((uint8_t*)&dataSend), 9*4);	
	}
}

static inline void funWork_TEST_FACTOR_OUT(){
	
}

// ������������ ������ USART
static inline void UpdateRS232(void){
  // �������� ������ � UART
  uint32_t isrflags = USART3->ISR;
  uint32_t cr1its = USART3->CR1;
  uint32_t cr3its = USART3->CR3;
  // ���� ���� �� �����
  if(((isrflags & USART_ISR_RXNE) == USART_ISR_RXNE)){
  // �������� ���� � USART
	  USART_rx_buffer[USART_rx_wr_index]= (uint8_t)USART3->RDR;
	  // �������� ���� ����� �����
	  USART3->ICR = USART_ISR_RXNE;
	  // ���������� �������� ����
  USART_rx_count++;
  USART_rx_wr_index++;
  // ����� ���������
  if (USART_rx_wr_index == 255) {
	  USART_rx_wr_index=0;
      }
  if (USART_rx_count == 255){
	  USART_rx_count = 0;
	  USART_rx_buffer_overflow = 1;
      }
  }
  
  // ���������� ����� ���������� ������
  if ((isrflags & UART_FLAG_TXE) == UART_FLAG_TXE){
	  if ( USART_tx_buffer_overflow == true ){
		  // ���������� ���� �� �������� ��� ������������
		  USART_tx_count = USART_tx_wr_index + (255 - USART_tx_rd_index);
	  } else {
		  // ���������� ���� �� �������� ��� ���������� ������
		  USART_tx_count = USART_tx_wr_index - USART_tx_rd_index;
	  }
	  // ���� ���� �� ��������
	  if (USART_tx_count > 0){
		  // ���������� ���t
		  USART3->TDR = (uint16_t)USART_tx_buffer[USART_tx_rd_index];
		  // �������� ���� �������� �����
		  USART3->ICR = UART_FLAG_TXE;
		  USART_tx_rd_index++;
		  if (USART_tx_rd_index == 255) {
			  USART_tx_rd_index = 0;
			  USART_tx_buffer_overflow = false;
		  }
		  USART_tx_count--;
		  if (USART_tx_count == 0){
			  // ��������� ���������� �� ��������� ��������
			  USART3->CR1 &= ~USART_CR1_TCIE;
		  }
	  }
  }
  // ������� ���� ������, ���� �� ������ ������� ����
  USART3->ICR = UART_CLEAR_OREF;
}


/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
