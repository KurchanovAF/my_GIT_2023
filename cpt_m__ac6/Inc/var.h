#ifndef __VAR_H
#define __VAR_H

#include <stdbool.h>
#include <stdint.h>

#include "usart_protocol.h"

#include "interface_AD5668.h"
#include "interface_AD8400.h"
#include "interface_LMX2486.h"

#include "interface_ADT7410.h"

#include "pid_tec_ctrl.h"
#include "pid_dopler_crnt.h"
#include "pid_dopler_tec.h"
#include "pid_freq.h"
#include "pid_cell.h"
#include "pid_optics_pwr.h"
#include "pid_MICROWAVE.h"
#include "pid_DOPLER_FREQ.h"

#include "hist.h"

#define my_ASM_fun
#define my_C_fun
//#define my_EQ_test
extern int my_TST;
extern uint32_t  my_TST_U32;

extern uint32_t my_TEST;
extern int my_N_DMA1_1;
extern int my_N_DMA1_2;
extern int my_N_DMA1_3;
extern int my_N_EXTI;

extern int my_Flag_DMA1_1;
extern int my_Flag_DMA1_1_1;
extern int my_Flag_DMA1_1_2;
extern int my_Flag_DMA1_1_3;

extern int my_Flag_DMA1_2;
extern int my_Flag_DMA1_2_1;
extern int my_Flag_DMA1_2_2;
extern int my_Flag_DMA1_2_3;

extern int my_Flag_DMA1_3;
extern int my_Flag_DMA1_3_1;
extern int my_Flag_DMA1_3_2;
extern int my_Flag_DMA1_3_3;

extern int my_N_1;
extern int my_N_2;
extern int my_N_3;
extern int my_N_4;

extern bool bCompFreqTK;			// ����������� ������� �� ����������� �����������
extern bool bCompFreqTK_1;			// ����� �������� �����������, ����������� ���������� ����
extern float avrResult_SD1_start;	// ��������� �������� ���� ������� ����������� ����������������
extern float SD1_d;

extern int var_my_ADC2;
extern bool b_my_ms_num;			// ������� ����������� ������� ����� �� 16 ��из 16 мс
extern int my_ms_num;
extern int my_alarm;
extern int my_Tick;

extern uint32_t num_TIM4;
extern bool     b_TIM4;

// Kurchanov 24.02.2021
extern uint8_t LSM303_BufferTx[16];
extern uint8_t LSM303_BufferRx[16];
// Kurchanov 24.02.2021
extern uint8_t I2C3_RxBuffer[16];
extern uint8_t I2C3_TxBuffer[16];
// Kurchanov 24.02.2021
extern uint16_t my_LSM303D_Temperature;

// Kurchanov 05.03.2021
extern float F2F1_rezult_X;
extern float F2F1_rezult_A;
extern float F2F1_rezult_A_30;		//   3 �������
extern float F2F1_rezult_A_900;		//  90 ������
extern int   F2F1_rezult_N_30;
extern int   F2F1_rezult_N_900;

// Kurchanov 09.03.2021
extern float F1F2_rezult_X;
extern float F1F2_rezult_A;
extern float F1F2_rezult_A_30;		//   3 �������
extern float F1F2_rezult_A_900;		//  90 ������
extern int   F1F2_rezult_N_30;
extern int   F1F2_rezult_N_900;

enum IdWorkType{
	WORK_NONE = 0,
	WORK_SCAN_CRNT = 1,
	WORK_TEST_ADC = 2,
	WORK_SCAN_FREQ = 3,
	WORK_TEST_ADC_2 = 4,
	WORK_TEST_ADC_3 = 5,
	WORK_HIST = 6
	// TOLIK
	/*
	WORK_TEST_FACTOR_OUT = 4,
	WORK_TEST_TEMP_CELL = 5
	//*/
};

extern int ID_keyTest;
extern int itemWork;

extern int value_UT1A;
extern int value_UT1A_aver;
extern float value_UT1A_rez;
extern int value_UT2A;
extern int value_VY;
extern int value_VY_aver;
extern float value_VY_rez;
extern int value_U2R;
extern int value_U2R_D;
extern int value_VT1;
extern int value_L1;
extern int value_T5;
extern int value__T5;
extern int value_DTX;
extern int value_DTX_aver;
extern float value_DTX_rez;
extern int value_RFI;
extern int value_OutFactor;

extern bool flagUpdate_UT1A;
extern bool flagUpdate_UT2A;
extern bool flagUpdate_VY;
extern bool flagUpdate_U2R;
extern bool flagUpdate_VT1;
extern bool flagUpdate_L1;
extern bool flagUpdate_T5;
extern bool flagUpdate_DTX;
extern bool flagUpdate_RFI;
extern bool flagUpdate_OutFactor;
extern bool flagUpdate_LMX2486;
extern uint8_t I2C3_RxBuffer[16];
extern uint8_t I2C3_TxBuffer[16];

extern bool flagConnectedTempSensor;
extern uint32_t ticsDelayUpdateTempCell;

extern int fixValue_TEC_CTRL;
extern int fixValue_MICROWAVE;
extern int fixValue_DOPLER_FREQ;
extern int fixValue_VY;
extern int fixValue_T5;
extern int fixValue_U2R;
extern int fixValue_UT1A;

extern int scanStep_UT2A;
extern int scanMin_UT2A;
extern int scanMax_UT2A;

extern int scanStep_VY;
extern int scanMin_VY;
extern int scanMax_VY;

// 3В 417В xxx xxx
extern int LMX_ValueN;
extern int LMX_ValueFN;
extern int LMX_ValueFD;
extern int LMX_ValueINT;
extern float LMX_ShiftFreq;
extern int LMX_DataValueFN[256];
extern int LMX_DataValueFD[256];
extern int itemOptionLMX;

#define PID_FLAG_LOOP_TEC_CTRL (0x01)
#define PID_FLAG_LOOP_DOPLER_CRNT (0x02)
#define PID_FLAG_LOOP_FREQ (0x04)

// ���������� ������ ����������� ������
#define PID_FLAG_LOOP_CELL (0x08)
extern bool b_PID_FLAG_LOOP_CELL;	// false - ������ �����, true - ��� ��������

// ������ ������� ������������ ������
#define PID_FLAG_LOOP_DOPLER_TEC (0x10)

// ������ ������� DC �������������
#define PID_FLAG_LOOP_OPTICS_PWR (0x20)

// �������� ������ ����������� ������
#define PID_FLAG_LOOP_SENSOR_TEMP_CELL (0x40)
extern bool b_PID_FLAG_LOOP_SENSOR_TEMP_CELL;	// false - ������ �����, true - ��� ��������

// �������� �� �������
#define PID_FLAG_LOOP_FREQ_GNSS (0x80)
#define PID_FLAG_LOOP_VOID_TEST (0x100)
#define PID_FLAG_LOOP_MICROWAVE (0x200)
#define PID_FLAG_LOOP_DOPLER_FREQ (0x400)
#define PID_FLAG_LOOP_FREQ_TK	(0x800)

extern int statusLoopPID;

extern bool flagUpdateCompute_TEC_CTRL;
extern bool flagUpdateCompute_MICROWAVE;
extern bool flagProcess_MICROWAVE;
extern bool flagUpdateCompute_DOPLER_FREQ;
extern bool flagProcess_DOPLER_FREQ;
extern bool flagUpdateCompute_OUT2_DOPLER_CRNT;
extern bool flag_SCAN_CRNT;						// Kurchanov 10.03.2021
extern bool flagUpdateCompute_OUT2_DOPLER_TEC;
extern bool flagUpdateCompute_OUT1_OPTICS_PWR;
extern bool flagProcess_OUT1_OPTICS_PWR;
extern bool flagUpdateCompute_CELL;
extern bool flagUpdateTempCell;

extern float result_OUT2_DOPLER_CRNT;
extern float result_OUT2_DOPLER_TEC;
extern float result_OUT1_OPTICS_PWR;
extern float delta_DOPLER_DC;

extern int fixValue_OUT2_DOPLER_CRNT;
extern int fixValue_OUT2_DOPLER_TEC;

extern float resultTec;						// ��������
extern float resultMICROWAVE;
extern float resultDOPLER_FREQ;
extern float resultTemp_CELL;
extern float resultTemp_D_CELL;
extern float levelTemp_CELL;
extern float levelTemp_D_CELL;
extern float level_CONTR;
// ����������� ����������� ������
extern float levelValueSensor_TempCell;

extern int value_TC;
extern float value_D_TC;
extern float value_FAZA_L;
extern float value_FAZA_F;
extern int value_STEP_L;
extern int value_N_STEP_L;
extern float value_mult_To_FREQ;
extern int i_MESSAGE_1;
extern int i_MESSAGE_2;
extern int i_MESSAGE_3;
extern float f_MESSAGE_2;
extern float f_MESSAGE_3;
extern bool b_MESSAGE;
extern bool b_eq;
extern int volatile my_dat__1;
extern int volatile my_dat__2;

extern int iF0;
extern int iT1__;
extern int iT2__;
extern int iT3__;
extern int iT4__;
extern int iT__n;
extern uint32_t my_dat_1;
extern uint32_t my_dat_2;

// �������� �������
extern float sigmaPID_CTRL;
extern int countLoopPID_TEC_CTRL;
extern int timeLoopPID_TEC_CTRL;
extern bool isLoopPID_TEC_CTRL;

extern int timeLoopPID_MICROWAVE;
extern bool isLoopPID_MICROWAVE;

// 120 �������� � ������ ������ ��������� �� ������ 1 ��
#define ADC_SAMPLES_HALF_SIZE 120
// ���������� 16-������ �������� uint16_t, ����� DMA1_1, Medium
// Vref (24.5 cycles), ch7 (24.5 cycles), Vref (24.5 cycles), ch7 (24.5 cycles)
// ch7 = CONT ���������� ����������� ������ �� �������� �������� ��� ��� �����
#define ADC1_SH_HALF_SIZE 480
// ���������� 16-������ �������� uint16_t, ����� DMA1_2, Very High
// ch13 (24.5 cycles), ch6 (24.5 cycles), ch13 (24.5 cycles), ch5 (24.5 cycles)
// ch13 = OUT0 (��������), ch6 = OUT2, ch5 = OUT1
#define ADC2_SH_HALF_SIZE 480
// ���������� 16-������ �������� uint16_t, ����� DMA1_3, High
// TS (24.5 cycles), ch3 (24.5 cycles), TS (24.5 cycles), ch4 (24.5 cycles)
// ch3 = OUT2N, ch4 = OUT1N, TS = ������ ����������� �����������
#define ADC3_SH_HALF_SIZE 480

extern uint16_t DMA1_1_Data[2*ADC1_SH_HALF_SIZE];
extern uint16_t DMA1_2_Data[2*ADC2_SH_HALF_SIZE];
extern uint16_t DMA1_3_Data[2*ADC3_SH_HALF_SIZE];

extern uint16_t my_ADC1_Data[ADC1_SH_HALF_SIZE] __attribute__((aligned));
extern uint16_t my_ADC2_Data[ADC2_SH_HALF_SIZE] __attribute__((aligned));
extern uint16_t my_ADC3_Data[ADC3_SH_HALF_SIZE] __attribute__((aligned));

extern uint16_t my_F0[ADC2_SH_HALF_SIZE + 56] __attribute__((aligned));
extern uint16_t my_F0N[ADC2_SH_HALF_SIZE + 56] __attribute__((aligned));
//==========================================

#define ADC_ARRAY_DMA12_HALF_SIZE 120
#define ADC_ARRAY_DMA1_HALF_SIZE 480
#define ADC_ARRAY_DMA2_HALF_SIZE 480

#define COUNT_DATA_HALF_SIZE_OUT_1R 120
#define COUNT_DATA_HALF_SIZE_CONTR 120
#define COUNT_DATA_HALF_SIZE_SD1 120
#define COUNT_DATA_HALF_SIZE_OUT_3R 120

#define COUNT_DATA_HALF_SIZE_OUT_2R 120
#define COUNT_DATA_HALF_SIZE_OUT_0R 120
#define COUNT_DATA_HALF_SIZE_SD2 120

extern uint16_t DMA1_Data[2*ADC_ARRAY_DMA1_HALF_SIZE];
extern uint16_t DMA2_Data[2*ADC_ARRAY_DMA2_HALF_SIZE];

extern volatile uint16_t* volatile pDataDMA1;
extern volatile uint16_t* volatile pDataDMA2;
extern volatile uint16_t* volatile pDataDMA1_1;
extern volatile uint16_t* volatile pDataDMA1_2;
extern volatile uint16_t* volatile pDataDMA1_3;
extern volatile uint16_t* volatile pDataDMA;
extern volatile uint16_t* volatile pDataADC;
//extern volatile uint16_t* pDataDMA2;

// Kurchanov 23.11.2020
//=========================================================
// ������ �����������
//=========================================================
extern float value_TempCell;
extern float value_Temp_D_Cell;
extern bool TempCellIsCorrect;
extern int tickDelayUpdateTempCell;
extern float resultAverage_SENSOR_TempCell;

// Kurchanov 16.04.2021
// ���� �������� ��������� �������� �����
extern uint16_t  my_DMA2_tst_Data[ADC_ARRAY_DMA2_HALF_SIZE]   __attribute__((aligned));

// Kurchanov 10.08.2020
#ifdef my_ASM_fun
extern uint16_t my_DMA2_Data[ADC_ARRAY_DMA2_HALF_SIZE];
//===============================================================
extern uint16_t my_DMA2_Data_F0[ADC_ARRAY_DMA12_HALF_SIZE + 56];
extern uint16_t my_DMA2_Data_F1[ADC_ARRAY_DMA12_HALF_SIZE];
extern uint16_t my_DMA2_Data_F2[ADC_ARRAY_DMA12_HALF_SIZE + 30];
extern uint16_t my_DMA2_Data_F1_F2[ADC_ARRAY_DMA12_HALF_SIZE];
//===============================================================
extern uint16_t my_DMA1_Data[ADC_ARRAY_DMA1_HALF_SIZE];
//===============================================================
extern uint16_t my_DMA1_Data_F0[ADC_ARRAY_DMA12_HALF_SIZE + 56];
extern uint16_t my_DMA1_Data_F1[ADC_ARRAY_DMA12_HALF_SIZE];
extern uint16_t my_DMA1_Data_F2[ADC_ARRAY_DMA12_HALF_SIZE + 30];
extern uint16_t my_DMA1_Data_F1_F2[ADC_ARRAY_DMA12_HALF_SIZE];
//===============================================================
extern uint16_t * my_Data_F0;
extern uint16_t * my_Data_F1;
extern uint16_t * my_Data_F2;
extern uint16_t * my_Data_F1_F2;
//===============================================================

//===============================================================
extern int32_t my_F2F1_rez[6];
extern int32_t my_F2F1_rez_2[6];
extern int32_t * my_F2F1_rez_A;
extern int32_t my_F2F1_P_rez[6];
extern int32_t my_F1F2_rez[5];
extern int32_t my_F1F2_rez_2[5];
extern int32_t * my_F1F2_rez_A;
extern int32_t my_F1F2_P_rez[5];
extern float F1F2_rezult[5];
extern float F1F2_rezult_2[5];
extern float F1F2_OUT1_rezult[5];
extern float F1F2_P_rezult[5];
extern float F1F2_P_S;
extern float F2F1_rezult[6];
extern float F2F1_rezult_2[6];
extern bool b_F2F1_rezult;
extern float F2F1_rezult_1[6];
extern float F2F1_rezult_2[6];
extern float F2F1_rezult_D[6];
extern float F2F1_P_rezult[6];
extern int32_t my_F2F1_sum[6];
extern int32_t my_F2F1_sum_2[6];
extern int32_t my_F2F1_P_sum[6];
extern int32_t my_F1F2_sum[5];
extern int32_t my_F1F2_sum_2[5];
extern int32_t my_F1F2_OUT1_sum[5];
extern int32_t my_F1F2_P_sum[5];
extern int32_t my_F0_sum;

extern uint16_t* p_my_DMA2_Data;
extern uint16_t* p_my_DMA2_Data_F0;
extern uint16_t* p_my_DMA2_Data_F1;
extern uint16_t* p_my_DMA2_Data_F2;
extern uint16_t* p_my_DMA2_Data_F1_F2;
extern int32_t* p_my_F2F1_rez;
extern int32_t* p_my_F1F2_rez;
extern int32_t* p_my_F2F1_sum;
extern int32_t* p_my_F1F2_sum;
extern int32_t* p_my_F1F2_OUT1_sum;
#endif

extern uint16_t buf_TEST_ADC_3[2400];
extern bool b_buf_TEST_ADC_3;
extern bool b_buf_TEST_ADC_2;
extern float corr_1_TEST_ADC_2;
extern float corr_2_TEST_ADC_2;
extern float corr_12_TEST_ADC_2;
extern float corr_TEST_ADC_2;
extern int num_corr_TEST_ADC_2;
extern int pkgPos;		// ����� ������� �� 16 ��������
extern int numPos;		// ����� ������� � ������� ������
extern float result_OUT2_CPT_FREQ_CPT_tmp;
extern float result_OUT2_CPT_CRNT_DOPLER_tmp;

// Kurchanov 19.10.2020
#ifdef my_C_fun
extern uint16_t my_DMA2_Data_[ADC_ARRAY_DMA2_HALF_SIZE];
extern uint16_t my_DMA2_Data_F0_[ADC_ARRAY_DMA12_HALF_SIZE + 56];
extern uint16_t my_DMA2_Data_F1_[ADC_ARRAY_DMA12_HALF_SIZE];
extern uint16_t my_DMA2_Data_F2_[ADC_ARRAY_DMA12_HALF_SIZE + 30];
extern uint16_t my_DMA2_Data_F1_F2_[ADC_ARRAY_DMA12_HALF_SIZE];




extern int32_t my_F2F1_rez_[6];
extern int32_t my_F1F2_rez_[5];
// Kurchanov 13.01.2021
extern uint16_t max_Data_F0_;
extern uint16_t min_Data_F0_;
extern uint16_t max_Data_F1_;
extern uint16_t min_Data_F1_;
extern uint16_t max_Data_F2_;
extern uint16_t min_Data_F2_;
extern uint16_t max_Data_F1_F2_;
extern uint16_t min_Data_F1_F2_;
extern int32_t  sum_ampl_Data_F0_;
extern int32_t  sum_ampl_Data_F1_;
extern int32_t  sum_ampl_Data_F2_;
extern int32_t  sum_ampl_Data_F1_F2_;
extern float  rez_ampl_Data_F0_;
extern float  rez_ampl_Data_F1_;
extern float  rez_ampl_Data_F2_;
extern float  rez_ampl_Data_F1_F2_;

extern float F1F2_rezult_[5];
extern float F2F1_rezult_[6];
extern int32_t my_F2F1_sum_[6];
extern int32_t my_F1F2_sum_[5];
extern int32_t my_F0_sum_;


extern uint16_t* p_my_DMA2_Data_;
extern uint16_t* p_my_DMA2_Data_F0_;
extern uint16_t* p_my_DMA2_Data_F1_;
extern uint16_t* p_my_DMA2_Data_F2_;
extern uint16_t* p_my_DMA2_Data_F1_F2_;
extern int32_t* p_my_F2F1_rez_;
extern int32_t* p_my_F1F2_rez_;
extern int32_t* p_my_F2F1_sum_;
extern int32_t* p_my_F1F2_sum_;
#endif

extern uint8_t itemPartResultDMA1_ADC1;
extern uint8_t itemPartResultDMA1_ADC2;
extern uint8_t itemPartResultDMA1_ADC3;

extern int resultData_OUT_1R[2*COUNT_DATA_HALF_SIZE_OUT_1R];
extern int resultData_CONTR[2*COUNT_DATA_HALF_SIZE_CONTR];
extern int resultData_SD1[2*COUNT_DATA_HALF_SIZE_SD1];
extern int resultData_OUT_3R[2*COUNT_DATA_HALF_SIZE_OUT_3R];

extern int resultData_OUT_2R[2*COUNT_DATA_HALF_SIZE_OUT_2R];
extern int resultData_OUT_0R[2*COUNT_DATA_HALF_SIZE_OUT_0R];
extern int resultData_SD2[2*COUNT_DATA_HALF_SIZE_SD2];

extern int itemMOD_CRNT;
extern int itemMOD_FREQ;
extern int MOD_CRNT_width;

extern int sum_CONT1;
extern int sum_CONT2;
extern int sum_CONT;
extern int abs_diff_CONT;

extern int sum_OUT_DC;
extern int sum_CONTR;
extern int sum_SD1;
extern int sum_OUT_3R;

extern int sum_OUT_1;
extern int sum_OUT_1N;

extern int sum_TS;

#ifdef my_ASM_fun
extern int sum_OUT_2R;
extern int sum_OUT_0R;
extern int sum_OUT_1A;

extern int sum_SD2;
#endif

#ifdef my_C_fun
extern int sum_OUT_2R_;
extern int sum_OUT_0R_;
extern int sum_SD2_;
#endif

extern int sum_OUT_2RN;
extern int sum_OUT_0RN;

extern int rez_OUT_2R;

extern int * p_sum_OUT_DC;
extern int * p_sum_OUT_1R;
extern int * p_sum_CONTR;
extern int * p_sum_SD1;
extern int * p_sum_OUT_3R;
#ifdef my_ASM_fun
extern int * p_sum_OUT_2R;
extern int * p_sum_OUT_0R;
extern int * p_sum_SD2;
#endif

extern int * p_rez_OUT_2R;

extern float fix_avrResult_OUT_DC;
extern float avrResult_OUT_DC;
extern float avrResult_OUT_1N;
extern float avrResult_OUT_1A;

extern float avrResult_OUT_1R;
extern float avrResult_CONTR;
extern float avrResult_SD1;
extern float avrResult_SD1_;
extern float avrResult_OUT_3R;
extern float startResult_OUT_3R;
extern float avrResult_OUT_2R;
extern float avrResult_OUT_0R;
extern float avrResult_OUT_0R_;
extern float avrResult_SD2;

extern float avrResult_OUT2_DC;
extern float avrResult_OUT_0RN;

extern int count_OUT_DC;
extern int count_OUT_1R;
extern int count_CONTR;
extern int count_SD1;
extern int count_OUT_3R;
extern int count_OUT_2R;
extern int count_OUT_0R;
extern int count_SD2;

extern int index_OUT_DC;
extern int index_OUT_1N;
//extern bool b_OUT_DC;
//extern int index_OUT_1R;
extern int index_CONTR;
extern int index_SD1;
extern int index_OUT_3R;
extern int index_OUT_2R;
//extern int index_OUT_2RN;
extern int index_OUT_0R;
extern int index_SD2;

//extern float result_OUT2_CPT[2];

//extern int sum_OUT2_CPT[2];
//extern int index_OUT2_CPT;
//extern int count_OUT2_CPT;
extern bool flagUpdateCompute_OUT2_CPT;
extern int fixValue_OUT2_CPT;

extern bool flagUpdateCompute_OUT2_DOPLER_CRNT;
extern float shift_OUT2_DOPLER_CRNT;

extern int sum_OUT1_DOPLER_CRNT[2];
extern int count_OUT1_DOPLER_CRNT;
extern bool flagUpdateCompute_OUT1_DOPLER_CRNT;
extern float result_OUT1_DOPLER_CRNT;
extern int fixValue_OUT1_DOPLER_CRNT;

//extern int sum_CPT_FREQ;
//extern int index_CPT_FREQ;
//extern int count_CPT_FREQ;
//extern bool flagUpdateCompute_CPT_FREQ;
//extern float result_CPT_FREQ;
//extern int fixValue_CPT_FREQ;

extern int sum_OUT1_CPT_CRNT[5];
extern int sum_OUT2_CPT_CRNT[5];
extern int sum_OUT1_CRNT_2[5];
extern int sum_OUT2_CRNT_2[5];
extern int index_OUT1_CPT_CRNT;
extern int index_OUT2_CPT_CRNT;
extern int count_OUT1_CPT_CRNT;	// �� ������������
extern int count_OUT2_CPT_CRNT;
extern bool flagUpdateCompute_OUT2_CPT_CRNT;
extern float result_OUT1_CPT_CRNT[5];
extern float result_OUT1_CRNT_2[5];
extern float result_OUT1_CPT_CRNT_DOPLER;
extern float result_OUT2_CPT_CRNT[5];
extern float result_OUT2_CRNT_2[5];
extern float result_OUT2_CPT_CRNT_DOPLER;

extern int sum_OUT2_CPT_FREQ[6];
extern int index_OUT2_CPT_FREQ;
extern int count_OUT2_CPT_FREQ;
extern bool flagUpdateCompute_OUT2_CPT_FREQ;
extern bool flagUpdateCompute_FREQ_GNSS;
extern bool flagStartCompute_FREQ_GNSS;
extern float result_OUT2_CPT_FREQ[6];
extern float result_OUT2_CPT_FREQ_CPT;
// Kurchanov
extern float result_OUT2_CPT_FREQ_CPT_0;
extern float result_OUT2_CPT_FREQ_CPT_1;
extern float result_OUT2_CPT_FREQ_CPT_2;
extern float result_OUT2_CPT_FREQ_CPT_3;
extern float result_OUT2_CPT_FREQ_CPT_4;
extern float result_OUT2_CPT_FREQ_CPT_5;

extern float shift_OUT2_FREQ;
// Kurchanov 29.05.2020
extern bool b_Start_Shift_Freq;
extern float shift_Lin_Freq;
extern float shift_Freq_GNSS;
extern float shift_Freq_GNSS_I;
extern float step_Freq_GNSS;

extern int sum_OUT1_CPT_FREQ[6];
extern int index_OUT1_CPT_FREQ;
extern int count_OUT1_CPT_FREQ;
extern bool flagUpdateCompute_OUT1_CPT_FREQ;
extern float result_OUT1_CPT_FREQ[6];

extern int DEBUG_maxDWT1;
extern int DEBUG_maxDWT2;
extern int DEBUG_maxDWT3;

extern int DEBUG_item_VY;
extern int DEBUG_item_DTX;
extern int DEBUG_item_RFI;
extern int DEBUG_item_VT1;
//=========================================================
// UART
//=========================================================
#define UART_COUNT_TX (255)
// ������ ��� ��������
extern uint8_t 							UART_TxBuffer[255];
extern volatile uint8_t   	USART_tx_buffer[255];
extern volatile uint16_t   	USART_tx_count; // ���������� ������ �� ��������
extern volatile uint16_t   	USART_tx_wr_index; //
extern volatile uint16_t   	USART_tx_rd_index; //
extern volatile bool				USART_tx_buffer_overflow; // ���� ������������ ������
// �������� ������ � ��������
extern char  								UART_RxBuffer[255];
extern volatile uint8_t   	USART_rx_buffer[255];
extern volatile uint16_t   	USART_rx_count; // ���������� ������ � �������� ������
extern volatile uint16_t   	USART_rx_wr_index; // ������ ������ ������ (���� ������ ������ )
extern volatile uint16_t   	USART_rx_rd_index; // ������ ������ ������ (������ ������ ������)
extern volatile bool    	USART_rx_buffer_overflow; // ���� ������������ ������

extern uint8_t BufferMsg[256];
extern uint16_t lengthBufferCmd;
extern int byteUSART;
extern int cmdID;
extern int BufferDataPack[4];

extern float TECCTRL_factorKp;
extern float TECCTRL_factorKi;
extern float TECCTRL_factorKd;

extern float MICROWAVE_factorKp;
extern float MICROWAVE_factorKi;
extern float MICROWAVE_factorKd;

extern float DOPLER_FREQ_factorKp;
extern float DOPLER_FREQ_factorKi;
extern float DOPLER_FREQ_factorKd;

//extern float my_delta;
//extern float my_deltaPID;
//extern int my_INT;
//extern float my_FLT;
//extern float my_FLT_;

extern float DOPLER_CRNT_factorKp;
extern float DOPLER_CRNT_factorKi;
extern float DOPLER_CRNT_factorKd;

extern float DOPLER_TEC_factorKp;
extern float DOPLER_TEC_factorKi;
extern float DOPLER_TEC_factorKd;

extern float FREQ_factorKp;
extern float FREQ_factorKi;
extern float FREQ_factorKd;

extern float CELL_factorKp;
extern float CELL_factorKi;
extern float CELL_factorKd;

extern float OPTICS_PWR_factorKp;
extern float OPTICS_PWR_factorKi;
extern float OPTICS_PWR_factorKd;


#endif
