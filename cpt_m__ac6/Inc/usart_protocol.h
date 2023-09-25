#ifndef __USARTPROTOCOL_H__
#define __USARTPROTOCOL_H__

#include "stm32l4xx_hal.h"
#include "var.h"


#define BYTE_START 0xAF
#define BYTE_STOP 0xFA

enum IdRs232Cmd{
	NONE = 0,
	GET_UT1A = 1,
	SET_UT1A = 2,
	
	GET_UT2A = 3, 
	SET_UT2A = 4,	
	
	GET_VY = 5,   
	SET_VY = 6,
 	
	GET_U2R = 7,    
	SET_U2R = 8, 
	
	GET_VT1 = 9,    
	SET_VT1 = 10, 
	
	GET_L1 = 11,     
	SET_L1 = 12, 
	
	GET_T5 = 13,     
	SET_T5 = 14,
	
	GET_DTX = 15,        
	SET_DTX = 16,
	
	GET_RFI = 17,
	SET_RFI = 18,
		
	SET_OUT_FACTOR = 19,
	GET_OUT_FACTOR = 20,
		
	SET_REG_FREQ_PLL = 101,
	GET_REG_FREQ_PLL = 102,
	
	SET_ITEM_WORK = 103,
	GET_ITEM_WORK = 104,
	
	SET_LOOP_PID = 105,
	GET_LOOP_PID = 106,
	
	SET_PID_TEC_CTRL = 107,
	GET_PID_TEC_CTRL = 108,
	
	SET_PID_DOPLER_CRNT = 109,
	GET_PID_DOPLER_CRNT = 110,
	
	SET_SHIFT_VCSEL = 111,
	GET_SHIFT_VCSEL = 112,
	
	SET_PID_FREQ = 113,
	GET_PID_FREQ = 114,
	
	SET_SHIFT_FREQ = 115,
	GET_SHIFT_FREQ = 116,
	
	SET_PID_CELL = 117,
	GET_PID_CELL = 118,
	
	SET_PID_DOPLER_TEC = 119,
	GET_PID_DOPLER_TEC = 120,
	
	SET_PID_DC = 121,   // Kurchanov 29.04.2020
  GET_PID_DC = 122,
	
	SET_TC = 123,       // Kurchanov 12.05.2020 код АЦП термостата ячейки
  GET_TC = 124,
	// Kurchanov 06.07.2020 управление фазами синхронных детекторов
  SET_FAZA_L = 125,       // Детектор длины волны
  GET_FAZA_L = 126,
  SET_FAZA_F = 127,       // Детектор частоты
  GET_FAZA_F = 128,
	// Kurchanov 09.07.2020
	SET_STEP_L = 129,       // Шаг сканирования длины волны
	GET_STEP_L = 130,
	// Kurchanov 27.07.2020
  SET_N_STEP_L = 131,       // Прореживание шага сканирования длины волны
  GET_N_STEP_L = 132,
	
	SET_MULT_TO_FREQ = 133,		// Множитель для дискриминатора длины волны при его вычитании
                            // из дискриминатора частоты с целью убрать зависимость частоты
                            // от длины волны в окрестности рабочей точки
	GET_MULT_TO_FREQ = 134,
	
	SET_ALARM_RESET = 135,	// Сброс  признаков недопустимого поведения
	GET_ALARM = 136,		// Чтение признаков недопустимого поведения

	SET_PID_MICROWAVE = 137,
	GET_PID_MICROWAVE = 138,

	SET_PID_DOPLER_FREQ = 139,
	GET_PID_DOPLER_FREQ = 140,

	SET_D_TC = 141,       // Kurchanov 26.08.2021 цифровая температура ячейки
	GET_D_TC = 142,

	STREAM_DATA = 200,
	GET_TEST = 201,
	GET_ID = 202,
	
	GET_MESSAGE = 251
};

// Забираем байт из буфера
int USART_GetByte(void);
// Передаем байт в буфер
void USART_SendByte(uint8_t byte);
// Передаем строку в буфер
void USART_SendString(uint8_t* str, uint8_t count);
int GetCmdID(uint8_t* strCMD, uint16_t* countByte);
void ComputeCmd(int id);
void SendPkgData(int id, uint8_t* data, uint8_t countByte);
void SetOptionPID(int id, uint8_t* cmd, float* Kp, float* Ki, float* Kd);
void GetOptionPID(int id, float* Kp, float* Ki, float* Kd);

float unpackFloat(uint8_t *buf);
uint32_t packFloat(float value);
#endif


