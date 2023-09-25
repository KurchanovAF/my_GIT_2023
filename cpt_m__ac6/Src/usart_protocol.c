#include "usart_protocol.h"
#include "var.h"



float ConvertToTemp(float value);
void CamputeBufferModulationVCSEL(uint32_t scale, uint32_t shift);
void AD9956_WriteProfile(uint8_t u8ShiftProfile, uint64_t u64Freq, uint16_t u16Phase);
void LMX2486_SetFreq(uint32_t valueN, uint32_t valueFN, uint32_t valueFD);
// Копия текущей командаы
static uint8_t strCommand[256];

///////////////////////////////////////////////////////////
// Приём данных из USART3
///////////////////////////////////////////////////////////
int USART_GetByte(void){
	int data; 
	// Контейнер пустой
	if (USART_rx_count == 0){
		return (-1);
	}
	// Забираем данные из начала буфера
	data = USART_rx_buffer[USART_rx_rd_index];
	USART_rx_rd_index++;
	// Цикличный буфер
	if (USART_rx_rd_index == 255) {
		USART_rx_rd_index = 0; 
	}
	// Уменьшаем счетчик принятых данных (достали из буфера)
	USART_rx_count--;
	return data;
}

// Передача байта
void USART_SendByte(uint8_t byte){
		USART_tx_buffer[USART_tx_wr_index] = byte;
		USART_tx_wr_index++;
		USART_tx_count++;
		if (USART_tx_wr_index == 255){
			USART_tx_wr_index = 0;
			USART_tx_buffer_overflow = true; 
		}
}
void USART_SendString(uint8_t* str, uint8_t count){
	uint8_t i;
	for ( i = 0; i < count; i++){
		USART_SendByte((uint8_t)str[i]);
	}
}

void EraseStr(uint8_t* str, uint16_t length, uint16_t count){
  uint16_t i;
  for (i=0; i < length; i++){
    if(count + i < length){
      str[i] = str[count+i];
      str[count+i] = 0;
    } else {
      str[i] = 0;  
    }
  }
};

float unpackFloat(uint8_t *buf){
	float result = 0.0;
	*((uint8_t*)(&result) + 3) = buf[3];
	*((uint8_t*)(&result) + 2) = buf[2];
	*((uint8_t*)(&result) + 1) = buf[1];
	*((uint8_t*)(&result) + 0) = buf[0];
  return result;
}
uint32_t packFloat(float value){
	uint32_t result = 0;
	result = (*((uint8_t*)(&value) + 0));
	result |= (*((uint8_t*)(&value) + 1))<<8;
	result |= (*((uint8_t*)(&value) + 2))<<16;
	result |= (*((uint8_t*)(&value) + 3))<<24;
  return result;
}
// Binary protocol RS-232
// Start 0xAF
// Command ID
// Count Byte
// Data
// Stop 0xFA
void SendPkgData(int type, uint8_t* data, uint8_t countByte){
	uint8_t i = 0;
	static uint8_t msg[64];
	msg[0] = BYTE_START;
	msg[1] = type;
	msg[2] = countByte;
	// Данные
	for ( i = 0; i < countByte; i++){
		msg[3+i] = (data[i]) & 0xFF;
	}
	// Стоповый байт
	msg[2+countByte+1] = BYTE_STOP;
	USART_SendString((uint8_t*)msg, 4+countByte);	
	// Включаем прерывание по окончанию передачи
	USART3->CR1 |= USART_CR1_TCIE;	
}

// Рекурсивный поиск до первой найденой команды
int GetCmdID(uint8_t* strCMD, uint16_t* countByte){
  // Посылка отсутствует
	static bool flagFindedPkg = false;
  static uint8_t indexStartByte = 0;
  static uint8_t indexStopByte = 0;
  static uint8_t i;
  // Ищем стартовый-стоповый байт
  for ( i = 0; i < (*countByte); i++){
    // Первый найденный стартовый байт
    if (strCMD[i] == BYTE_START){
      indexStartByte = i;
			flagFindedPkg = true;
      break;
    }
  }
	// Не нашли стартовый байт
	if (flagFindedPkg == false){
		// Удаляем все данные
		EraseStr(strCMD, (*countByte), (*countByte));
    (*countByte) = 0;
		return 0;
	}
  // Слишком мало данных
  if (indexStartByte + 4 > (*countByte)){
    // Ждем данные
    return 0;
  }
  static uint16_t countData;
	countData = strCMD[indexStartByte+2];
  // Ошибка размера пакета
  if (countData > 128){
    // Удаляем все включая стартовый байт
      EraseStr(strCMD, (*countByte), indexStartByte + 1);
      (*countByte) -= indexStartByte + 1;
      return GetCmdID(strCMD, countByte);
  }
	 // Слишком мало данных
  if (indexStartByte + 4 + countData  > (*countByte)){
    // Ждем данные
    return 0;
  }
  // Ошибка стопового байта
  if (strCMD[indexStartByte + countData + 3] != BYTE_STOP){
    // Удаляем все включая стартовый байт
    EraseStr(strCMD, (*countByte), indexStartByte + 1);
    (*countByte) -= indexStartByte + 1;
    return GetCmdID(strCMD, countByte);
  }
  indexStopByte = indexStartByte + countData + 3;
  // Посылка нужной длины
  // Определяем ID посылки и данные
  uint8_t ID = strCMD[indexStartByte + 1];
	// Копируем команду
	for ( i = 0; i < (indexStopByte - indexStartByte) + 1; i++){
		strCommand[i] = strCMD[indexStartByte + i];
	}
  // Удаляем все включая стоповый байт
  EraseStr(strCMD, (*countByte), indexStopByte + 1);
  (*countByte) -= indexStopByte + 1;
  return ID;
}

void SetValueFloat(uint8_t id, uint8_t* cmd, float* value){
	static uint32_t dataSend[1];
	(*value) = unpackFloat(&cmd[3]);
	dataSend[0] = packFloat((*value));
	SendPkgData(id, ((uint8_t*)&dataSend), 4);
}
void SetOptionPID(int id, uint8_t* cmd, float* Kp, float* Ki, float* Kd){
	static uint32_t dataSend[3];
	(*Kp) = unpackFloat(&cmd[3]);
	(*Ki) = unpackFloat(&cmd[7]);
	(*Kd) = unpackFloat(&cmd[11]);
	dataSend[0] = packFloat((*Kp));
	dataSend[1] = packFloat((*Ki));
	dataSend[2] = packFloat((*Kd));
	SendPkgData(id, ((uint8_t*)&dataSend), 12);
}
void GetOptionPID(int id, float* Kp, float* Ki, float* Kd){
	static uint32_t dataSend[3];
	dataSend[0] = packFloat((*Kp));
	dataSend[1] = packFloat((*Ki));
	dataSend[2] = packFloat((*Kd));
	SendPkgData(id, ((uint8_t*)&dataSend), 12);
}
//=========================================================
// Выполнение команд
//=========================================================
void ComputeCmd(int id){
	static uint8_t ID;
	ID = (uint8_t)(id&0xFF);
	//На 63 case все ломается
	switch (ID){
		case NONE:
			break;
		// Канал частоты 1
		case GET_UT1A:
			SendPkgData(id, ((uint8_t*)&value_UT1A), 4);
			break;
		case SET_UT1A:
			value_UT1A = (*((int*)(&strCommand[3])));
			fixValue_UT1A = value_UT1A;
			Reset_FREQ_PID();
			flagUpdate_UT1A = true;
			SendPkgData(id, ((uint8_t*)&value_UT1A), 4);
			break;
		// Канал частоты 2
		case GET_UT2A:
			SendPkgData(id, ((uint8_t*)&value_UT2A), 4);
			break;
		case SET_UT2A:
			value_UT2A = (*((int*)(&strCommand[3])));
			flagUpdate_UT2A = true;
			//Reset_FREQ_PID();	// Kurchanov
			SendPkgData(id, ((uint8_t*)&value_UT2A), 4);
			break;
		// Ток лазера грубый
		case SET_VY:
			value_VY = (*((int*)(&strCommand[3])));
			flagUpdate_VY = true;
			fixValue_OUT2_DOPLER_CRNT = value_VY;
			Reset_DOPLER_CRNT_PID();
			Reset_DOPLER_TEC_PID();
			SendPkgData(id, ((uint8_t*)&value_VY), 4);
			break;
		case GET_VY:
			SendPkgData(id, ((uint8_t*)&value_VY), 4);
			break;
		// Ток лазера тонкий
		case SET_U2R:
			value_U2R = (*((int*)(&strCommand[3])));
			flagUpdate_U2R = true;
			SendPkgData(id, ((uint8_t*)&value_U2R), 4);
			break;
		case GET_U2R:
			SendPkgData(id, ((uint8_t*)&value_U2R), 4);
			break;		
		// Опорная температура лазера
		case SET_VT1:
			value_VT1 = (*((int*)(&strCommand[3])));
			flagUpdate_VT1 = true;
			SendPkgData(id, ((uint8_t*)&value_VT1), 4);
			break;
		case GET_VT1:
			SendPkgData(id, ((uint8_t*)&value_VT1), 4);
			break;
		// Ток катушки
		case SET_L1:
			value_L1 = (*((int*)(&strCommand[3])));
			flagUpdate_L1 = true;
			SendPkgData(id, ((uint8_t*)&value_L1), 4);
			break;
		case GET_L1:
			SendPkgData(id, ((uint8_t*)&value_L1), 4);
			break;
		// Мощность нагрева ячейки
		case SET_T5:
			value_T5 = (*((int*)(&strCommand[3])));
			flagUpdate_T5 = true;
			SendPkgData(id, ((uint8_t*)&value_T5), 4);
			break;
		case GET_T5:
			SendPkgData(id, ((uint8_t*)&value_T5), 4);
			break;
		// Мощность нагрева лазера
		case SET_DTX:
			value_DTX = (*((int*)(&strCommand[3])));
			flagUpdate_DTX = true;
			SendPkgData(id, ((uint8_t*)&value_DTX), 4);
			break;
		case GET_DTX:
			SendPkgData(id, ((uint8_t*)&value_DTX), 4);
			break;
		case SET_RFI:
			value_RFI = (*((int*)(&strCommand[3])));
			flagUpdate_RFI = true;
			SendPkgData(id, ((uint8_t*)&value_RFI), 4);
			break;
		case GET_RFI:
			SendPkgData(id, ((uint8_t*)&value_RFI), 4);
			break;
		case SET_OUT_FACTOR:			
			value_OutFactor = (*((int*)(&strCommand[3])));
			flagUpdate_OutFactor = true;
			SendPkgData(id, ((uint8_t*)&value_OutFactor), 4);
			break;
		case GET_OUT_FACTOR:
			SendPkgData(id, ((uint8_t*)&value_OutFactor), 4);
			break;
		// Установка новых значений регистров синтезатора
		case SET_REG_FREQ_PLL:
			LMX_ValueN = (*((int*)(&strCommand[3])));
			LMX_ValueFN = (*((int*)(&strCommand[7])));
			LMX_ValueFD = (*((int*)(&strCommand[11])));
			flagUpdate_LMX2486 = true;
			BufferDataPack[0] = LMX_ValueN;
			BufferDataPack[1] = LMX_ValueFN;
			BufferDataPack[2] = LMX_ValueFD;
			SendPkgData(id, ((uint8_t*)&BufferDataPack[0]), 12);
			break;
		// Отправка текущих значений реистров синтезатора
		case GET_REG_FREQ_PLL:
			BufferDataPack[0] = LMX_ValueN;
			BufferDataPack[1] = LMX_ValueFN;
			BufferDataPack[2] = LMX_ValueFD;
			SendPkgData(id, ((uint8_t*)&BufferDataPack[0]), 12);
			break;	
		case SET_ITEM_WORK:
			itemWork = (*((int*)(&strCommand[3])));
			SendPkgData(id, ((uint8_t*)&itemWork), 4);
			break;
		case GET_ITEM_WORK:
			SendPkgData(id, ((uint8_t*)&itemWork), 4);
			break;
		case GET_TEST:
			SendPkgData(id, ((uint8_t*)&ID_keyTest), 4);
			break;
		case SET_LOOP_PID:
			statusLoopPID = (*((int*)(&strCommand[3])));
			// Kurchanov
			if(statusLoopPID & PID_FLAG_LOOP_FREQ_TK)
			{
				bCompFreqTK = true;
			}
			else
			{
				bCompFreqTK = false;
			}
		    if((statusLoopPID & PID_FLAG_LOOP_DOPLER_TEC) == PID_FLAG_LOOP_DOPLER_TEC){
				statusLoopPID &= ~PID_FLAG_LOOP_DOPLER_CRNT;
				statusLoopPID &= ~PID_FLAG_LOOP_TEC_CTRL;
		    }
		    if ((statusLoopPID & PID_FLAG_LOOP_SENSOR_TEMP_CELL) == PID_FLAG_LOOP_SENSOR_TEMP_CELL){
		    	// При включении цифрового захвата температуры ячейки отключаем аналоговый захват
		    	if ((statusLoopPID & PID_FLAG_LOOP_CELL) == PID_FLAG_LOOP_CELL){
		    		statusLoopPID &= ~PID_FLAG_LOOP_CELL;
		    	}
		    }
			SendPkgData(id, ((uint8_t*)&statusLoopPID), 4);			
			break;
		case GET_LOOP_PID:
			SendPkgData(id, ((uint8_t*)&statusLoopPID), 4);
			break;
	}
	
	switch(ID){
		case SET_PID_TEC_CTRL: 
			SetOptionPID(id, strCommand, &TECCTRL_factorKp, 
										 &TECCTRL_factorKi,
										 &TECCTRL_factorKd);
			break;
		case GET_PID_TEC_CTRL:
			GetOptionPID(id, &TECCTRL_factorKp, 
							 &TECCTRL_factorKi,
							 &TECCTRL_factorKd);
			break;

		case SET_PID_DOPLER_CRNT:
			SetOptionPID(id, strCommand, &DOPLER_CRNT_factorKp, 
										 &DOPLER_CRNT_factorKi,
										 &DOPLER_CRNT_factorKd);
			break;
		case GET_PID_DOPLER_CRNT: 
			GetOptionPID(id, &DOPLER_CRNT_factorKp, 
							 &DOPLER_CRNT_factorKi,
							 &DOPLER_CRNT_factorKd);
			break;
		case SET_PID_DOPLER_TEC:
			SetOptionPID(id, strCommand, &DOPLER_TEC_factorKp, 
										 &DOPLER_TEC_factorKi,
										 &DOPLER_TEC_factorKd);
			break;
		case GET_PID_DOPLER_TEC: 
			GetOptionPID(id, &DOPLER_TEC_factorKp, 
							 &DOPLER_TEC_factorKi,
							 &DOPLER_TEC_factorKd);
			break;
		case SET_PID_FREQ:
			SetOptionPID(id, strCommand, &FREQ_factorKp, 
										 &FREQ_factorKi,
										 &FREQ_factorKd);
			break;
		case GET_PID_FREQ: 
			GetOptionPID(id, &FREQ_factorKp, 
							 &FREQ_factorKi,
							 &FREQ_factorKd);
			break;
		case SET_PID_CELL:
			SetOptionPID(id, strCommand, &CELL_factorKp, 
										 &CELL_factorKi,
										 &CELL_factorKd);
			break;
		case GET_PID_CELL: 
			GetOptionPID(id, &CELL_factorKp, 
							 &CELL_factorKi,
							 &CELL_factorKd);
			break;
		// Kurchanov 07.05.2020
		case SET_PID_DC:
			SetOptionPID(id, strCommand, &OPTICS_PWR_factorKp, 
										 &OPTICS_PWR_factorKi,
										 &OPTICS_PWR_factorKd);
			break;
		case GET_PID_DC:
			GetOptionPID(id, &OPTICS_PWR_factorKp, 
							 &OPTICS_PWR_factorKi,
							 &OPTICS_PWR_factorKd);
			break;
		// Kurchanov 12.05.2020
		case SET_TC:
			value_TC = (*((int*)(&strCommand[3])));
		  levelTemp_CELL = value_TC;
			//Reset_CELL_PID();								// ПЛОХО !! очень медленно восстанавливается
			SendPkgData(id, ((uint8_t*)&value_TC), 4);			
			break;
		case GET_TC:
			value_TC = levelTemp_CELL;
			SendPkgData(id, ((uint8_t*)&value_TC), 4);
			break;

		// Kurchanov 26.08.2021
		case SET_D_TC:
			value_D_TC = (*((float*)(&strCommand[3])));
			levelTemp_D_CELL = value_D_TC;
			//Reset_CELL_PID();								// ПЛОХО !! очень медленно восстанавливается
			SendPkgData(id, ((uint8_t*)&value_D_TC), 4);
			break;
		case GET_D_TC:
			value_D_TC = levelTemp_D_CELL;
			SendPkgData(id, ((uint8_t*)&value_D_TC), 4);
			break;

		// Kurchanov 06.07.2020
		case SET_FAZA_L:
			SetValueFloat(id, strCommand, &value_FAZA_L);
			break;
		case GET_FAZA_L:
			SendPkgData(id, ((uint8_t*)&value_FAZA_L), 4);
			break;
		case SET_FAZA_F:
			SetValueFloat(id, strCommand, &value_FAZA_F);
			break;
		case GET_FAZA_F:
			SendPkgData(id, ((uint8_t*)&value_FAZA_F), 4);
			break;
		// Kurchanov 09.07.2020
		case SET_STEP_L:
			value_STEP_L = (*((int*)(&strCommand[3])));
		  scanStep_VY = value_STEP_L;
		  SendPkgData(id, ((uint8_t*)&value_STEP_L), 4);
			break;
		case GET_STEP_L:
			value_STEP_L = scanStep_VY;
			SendPkgData(id, ((uint8_t*)&value_STEP_L), 4);
			break;
		// Kurchanov 27.07.2020
		case SET_N_STEP_L:
			value_N_STEP_L = (*((int*)(&strCommand[3])));
		  if(value_N_STEP_L < 1) value_N_STEP_L = 1;
		  SendPkgData(id, ((uint8_t*)&value_N_STEP_L), 4);
			break;
		case GET_N_STEP_L:
			SendPkgData(id, ((uint8_t*)&value_N_STEP_L), 4);
			break;
		// Kurchanov 13.11.2020
		case SET_MULT_TO_FREQ:
			SetValueFloat(id, strCommand, &value_mult_To_FREQ);
		  SendPkgData(id, ((uint8_t*)&value_mult_To_FREQ), 4);
			break;
		case GET_MULT_TO_FREQ:
			SendPkgData(id, ((uint8_t*)&value_mult_To_FREQ), 4);
			break;
		
		case SET_SHIFT_VCSEL:
			SetValueFloat(id, strCommand, &shift_OUT2_DOPLER_CRNT);
			SendPkgData(id, ((uint8_t*)&shift_OUT2_DOPLER_CRNT), 4);
			break;
		case GET_SHIFT_VCSEL:
			SendPkgData(id, ((uint8_t*)&shift_OUT2_DOPLER_CRNT), 4);
			break;
		case SET_SHIFT_FREQ:
			if(!b_Start_Shift_Freq) b_Start_Shift_Freq = true; // Kurchanov 29.05.2020
			SetValueFloat(id, strCommand, &shift_OUT2_FREQ);
			SendPkgData(id, ((uint8_t*)&shift_OUT2_FREQ), 4);
			break;
		case GET_SHIFT_FREQ:
			SendPkgData(id, ((uint8_t*)&shift_OUT2_FREQ), 4);
			break;

		case SET_ALARM_RESET:
			my_alarm = 0;
			break;
		case GET_ALARM:
			SendPkgData(id, ((uint8_t*)&my_alarm), 4);
			break;

		case SET_PID_MICROWAVE:
			SetOptionPID(id, strCommand, &MICROWAVE_factorKp,
										 &MICROWAVE_factorKi,
										 &MICROWAVE_factorKd);
			break;
		case GET_PID_MICROWAVE:
			GetOptionPID(id, &MICROWAVE_factorKp,
							 &MICROWAVE_factorKi,
							 &MICROWAVE_factorKd);
			break;
		case SET_PID_DOPLER_FREQ:
			SetOptionPID(id, strCommand, &DOPLER_FREQ_factorKp,
										 &DOPLER_FREQ_factorKi,
										 &DOPLER_FREQ_factorKd);
			break;
		case GET_PID_DOPLER_FREQ:
			GetOptionPID(id, &DOPLER_FREQ_factorKp,
							 &DOPLER_FREQ_factorKi,
							 &DOPLER_FREQ_factorKd);
			break;
	}
}


