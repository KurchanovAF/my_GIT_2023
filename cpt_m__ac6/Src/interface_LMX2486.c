#include "interface_LMX2486.h"

#define LMX_nCS_Pin GPIO_PIN_4
#define LMX_nCS_GPIO_Port GPIOA

// Запись данных в LMX2486 по SPI2
void LMX2486_SendData(uint32_t sendData){
	volatile uint8_t rx = 0;
	// Настраиваем SPI2 для работы с синтезатором
	// Disable SPI peripheral
	SPI3->CR1 &= ~SPI_CR1_SPE;
	// Настраиваем SPI2 для работы с ЦАПом
	// CPOL = 0
	SPI3->CR1 &= ~SPI_CR1_CPOL;
	// CPHA = 0
	SPI3->CR1 &= ~SPI_CR1_CPHA;
	// Enable SPI peripheral
	SPI3->CR1 |= SPI_CR1_SPE;
	// Выбор микросхемы синтезатора
	HAL_GPIO_WritePin(LMX_nCS_GPIO_Port, LMX_nCS_Pin, GPIO_PIN_RESET);		// сигнал LE, ПЕРЕДАЧА СЛОВА ДЛИНОЙ 24 БИТ
	// Ждем когда DR осовободится на запись
	while (((SPI3->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI3->DR) = ((sendData >> 16) & 0xFF);					// младщий байт старшего полуслова
	while (((SPI3->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI3->DR) = ((sendData >> 8) & 0xFF);				// старший байт младшего полуслова
	while (((SPI3->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI3->DR) = ((sendData >> 0) & 0xFF);				// младший байт младшего полуслова
	// Ожидаем завершение передачи данных
	while (((SPI3->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	// Ожидание опустошения FIFO
	while (((SPI3->SR) & (SPI_SR_FTLVL)) != 0){};
	while (((SPI3->SR) & (SPI_SR_BSY)) == (SPI_SR_BSY)){};
	// Фиксируем данные
	HAL_GPIO_WritePin(LMX_nCS_GPIO_Port, LMX_nCS_Pin, GPIO_PIN_SET);		// данные из сдвигового регистра сохранены в нужном регистре
	SPI3->CR1 &= ~SPI_CR1_SPE;	
	while (((SPI3->SR) & (SPI_SR_FRLVL)) != 0){
		rx = *((__IO uint8_t *)&SPI3->DR);
	};
}



// Инициализация микросхемы синтезатора
void LMX2486_Init(void){
		// Целое
	int valueC = (int)(LMX_ValueN / 32);							// 459/32 = 14
	int valueB = (int)((LMX_ValueN - valueC * 32) / 4);				// 11/4 = 2
	int valueA = (int)(LMX_ValueN - valueC * 32 - valueB * 4);		// = 3
	
	uint32_t RF_N_Reg0 =	LMX2486_R0_RF_C(valueC) |				// ((0xE0 << 5) | (0x02 << 2) | 0x03) << 13
							LMX2486_R0_RF_B(valueB) |
							LMX2486_R0_RF_A(valueA);
	// RF_N(1708) C(53) B(3) A(0)	
	// Числитель
	uint32_t RF_FN =  LMX_ValueFN;									// 2064823
	uint32_t RF_FN_Reg5 = (((RF_FN >> 12) & 0x03FF) << 4);			// 1008 << 4
	uint32_t RF_FN_Reg0 = ((RF_FN & 0x0FFF) << 1);					//  439 << 1
	// Знаменатель
	uint32_t RF_FD = LMX_ValueFD;									// 3261007
	uint32_t RF_FD_Reg5 = (((RF_FD >> 12) & 0x03FF) << 14);
	uint32_t RF_FD_Reg1 = ((RF_FD & 0xFFF) << 4); 					// 0xE00
	//=======================================================
	// REG 5
	//=======================================================
	uint32_t lmx2486Reg5 = 	LMX2486_REG_R5 | 						// 0x0B - ВЕРНО
								RF_FN_Reg5 | 						//
								RF_FD_Reg5;							//
	//=======================================================
	// REG 1
	//=======================================================
	// RF_R(5) RF_P(32)
	uint32_t lmx2486Reg1 = LMX2486_REG_R1 | 						// 0x03
					   LMX2486_R1_RF_R(1) | 						// 0x3F << 16, RF_R = 1 (ЗНАЧЕНИЕ ДЕЛИТЕЛЯ)
						  LMX2486_R1_RF_P | 						// 0x400000 = 0x1 << 22 = RF_P бит 22 установлен (32/33/36/37 Prescaler для работы до 6 ГГц), бит 23 (RF_PD -- RF Power Down Control Bit) не определен !!
						       RF_FD_Reg1;							// установка бита 23 в 1 переводит в 3-е состояние выход Charge Pump (ВАЖНО !!)
	//=======================================================
	// REG 2
	//=======================================================
	// Отключаем IF PLL
	uint32_t lmx2486Reg2 = LMX2486_REG_R2 | 						// 0x05 - ВЕРНО						IF_N - не задан
						 LMX2486_R2_IF_PD;							// 0x800000 = 0x1 << 23, IF_PD установлен ( IF_PD -- IF Power Down Bit)
	//=======================================================
	// REG 3
	//=======================================================
	// 9  	10X 	950 	uA
	uint32_t lmx2486Reg3 = LMX2486_REG_R3 | 						// 0x07								IF_R - не задан
				  LMX2486_R3_ACCESS_0_SET |							// 0x100000 = 0x1 << 20
			 	  LMX2486_R3_ACCESS_1_SET | 						// 0x200000 = 0x1 << 21 ==> 0x03 включен доступ к регистру R5 ==> РАСШИРЕНИЕ режима 12 бит до режима 22 бит													   !!!! XXXX
												 //LMX2486_R3_RF_CPG(9);				// Kurchanov 9 ==> 950 mkA	// OLD
					// LMX2486_R3_RF_CPG(5);				// Kurchanov 5 ==> 570 mkA	// Rb
												 //LMX2486_R3_RF_CPG(4);				// Kurchanov 4 ==> 475 mkA
												 //LMX2486_R3_RF_CPG(3);				// Kurchanov 3 ==> 380 mkA
												 //LMX2486_R3_RF_CPG(2);				// Kurchanov 2 ==> 285 mkA
				    LMX2486_R3_RF_CPG(1);				// Kurchanov 1 ==> 190 mkA	// Cs
												 //LMX2486_R3_RF_CPG(0);				// Kurchanov 0 ==> 95 mkA
	//=======================================================
	// REG 4
	//=======================================================	
	uint32_t lmx2486Reg4 = 	LMX2486_REG_R4 | LMX2486_R4_R4 |		// 0x09 | 0x200000 бит 21
							  	 LMX2486_R4_RF_CP_POSITIVE |		// 0x000200 бит  9
									 LMX2486_R4_OSC_OUT_ON |		// 0x000800 бит 11			бит 23 не установлен (Oscillator Doubler) (ВАЖНО !! попробовать включить)
									 LMX2486_R4_FM_MODE_2X |		// 0x008000	бит 15			биты 4 - 7 MUX не установлены ==>  Disabled
									   LMX2486_R4_DITH_OFF |		// 0x0						биты 16 и 17 не установлены Dithering Mode Used ==>  Disabled																	   !!!! XXXX
										LMX2486_R4_MUX_OFF;			// 0x0						IF_CPP = бит 10?,  IF_P = бит 8?, FM(биты 14 и 15) = бит 14? 0x02 ==>   Fractional PLL mode with a 2nd order delta-sigma modulator !!!! XXXX
	//=======================================================
	// REG 6
	//=======================================================
	// RF Time Out Counter and Control for FLoutRF Pin, RF PLL Fastlock Charge Pump Current,  RF Cycle Slip Reduction


	//=======================================================
	// REG 7
	//=======================================================
	// RF Digital Lock Detect Divide By 4,  IF PLL Counter Reset (ВАЖНО !!), RF PLL Counter Reset,  RF Charge Pump Tri-State (ВАЖНО !!),  IF Charge Pump Tri-State (ВАЖНО !!)



	//=======================================================
	// REG 0
	//=======================================================	
	uint32_t lmx2486Reg0 = 	LMX2486_REG_R0 | 						// 0x00
								 RF_N_Reg0 |
								RF_FN_Reg0;
	// Передаем данные в микросхему R0 регистр заполняем последним								Регистры 6 и 7 - почему не используются ???
	LMX2486_SendData(lmx2486Reg3);
	LMX2486_SendData(lmx2486Reg5);
	LMX2486_SendData(lmx2486Reg1);
	LMX2486_SendData(lmx2486Reg2);
	LMX2486_SendData(lmx2486Reg4);
	LMX2486_SendData(lmx2486Reg0);
}

void LMX2486_SetFreq(uint32_t valueN, uint32_t valueFN, uint32_t valueFD){
	// Целое
	int valueC = (int)(valueN / 32);
	int valueB = (int)((valueN - valueC * 32) / 4);
	int valueA = (int)(valueN - valueC * 32 - valueB * 4);
	
	uint32_t RF_N_Reg0 =	LMX2486_R0_RF_C(valueC) |
												LMX2486_R0_RF_B(valueB) |
												LMX2486_R0_RF_A(valueA);
	// Числитель
	uint32_t RF_FN = valueFN;
	uint32_t RF_FN_Reg5 = (((RF_FN >> 12) & 0x03FF) << 4);
	uint32_t RF_FN_Reg0 = ((RF_FN & 0x0FFF) << 1);
	// Знаменатель
	uint32_t RF_FD = valueFD;
	uint32_t RF_FD_Reg5 = (((RF_FD >> 12) & 0x03FF) << 14);
	uint32_t RF_FD_Reg1 = ((RF_FD & 0xFFF) << 4); // 0xE00
	uint32_t lmx2486Reg5 = 	LMX2486_REG_R5 | 
													RF_FN_Reg5 | 
													RF_FD_Reg5;	
	uint32_t lmx2486Reg1 = LMX2486_REG_R1 | 
												 LMX2486_R1_RF_R(1) | 
												 LMX2486_R1_RF_P | 
												 RF_FD_Reg1;													
	uint32_t lmx2486Reg0 = 	LMX2486_REG_R0 | 
													RF_N_Reg0 |
													RF_FN_Reg0;
	LMX2486_SendData(lmx2486Reg5);
	LMX2486_SendData(lmx2486Reg1);
	LMX2486_SendData(lmx2486Reg0);
	
}


void CamputeOptionSetValueLMX(int value){
	double dblValue = (double)(value)/2926.25;
	double delta = dblValue;
	double centreFreq = 3417341307.00619 + (double)LMX_ShiftFreq;
	double realValue = centreFreq + delta;
	CamputeOptionLMX(realValue, 341.0, &LMX_ValueFN, &LMX_ValueFD);
	flagUpdate_LMX2486 = true;
}

void CamputeOptionAddValueLMX(int value){
	double dblValue = (double)(LMX_ValueINT + value)/2926.25;
	LMX_ValueINT += value;
	double delta = dblValue;
	double centreFreq = 3417341307.00619 + (double)LMX_ShiftFreq;
	double realValue = centreFreq + delta;
	CamputeOptionLMX(realValue, 341.0, &LMX_ValueFN, &LMX_ValueFD);
	flagUpdate_LMX2486 = true;
}

void CamputeOptionDataLMX(int value){
	double dblValue = (double)(value)/2926.25;
	LMX_ValueINT = value;
	double delta = dblValue;
	double centreFreq = 3417341307.00619 + (double)LMX_ShiftFreq;
	double realValue = centreFreq + delta;
	for (int i = 0; i < 256; i++){
		delta	= (double)(i - 128)*0.005;
		realValue = centreFreq + delta;
		CamputeOptionLMX(realValue, 341.0, &LMX_DataValueFN[i], &LMX_DataValueFD[i]);
	}
}

void CamputeOptionLMX(double real_value, double valueN, int* valueFN, int* valueFD){
	real_value = (real_value - valueN * 10000000.0) / 10000000.0;
	double x;
	long long maxden = 4194303L; //0x3FFFFF;
	long long ai, FN1, FD1;
	long long m[2][2];
	x = real_value;
	
	/// initialize matrix
	m[0][0] = 1L;
	m[1][1] = 1L;
	m[0][1] = 0L;
	m[1][0] = 0L;
	
	/// loop finding terms until denom gets too big
	while (m[1][0] *  ( ai = (long long)x ) + m[1][1] <= maxden) {
			long long t;
			t = m[0][0] * ai + m[0][1];
			m[0][1] = m[0][0];
			m[0][0] = t;
			t = m[1][0] * ai + m[1][1];
			m[1][1] = m[1][0];
			m[1][0] = t;
			if (x == (double)ai) { break; }   /// AF: division by zero
			x = 1/(x - (double) ai);
			if (x > (double)0x7FFFFFFF) { break; } /// AF: representation failure
	}
	
	/// now remaining x is between 0 and 1/ai */
	/// approx as either 0 or 1/m where m is max that will fit in maxden */
	/// first try zero */
	///
	if(m[1][0]>0 && m[0][0]>0)
	{
			FN1 = m[0][0];
			FD1 = m[1][0];
	}else{
			ai = (maxden - m[1][1]) / m[1][0];
			m[0][0] = m[0][0] * ai + m[0][1];
			m[1][0] = m[1][0] * ai + m[1][1];
	
			FN1 = m[0][0];
			FD1 = m[1][0];
	}
	double reg1Res = FN1 / FD1;
	(*valueFN) = (int)(FN1 - reg1Res * FD1);
	if (valueFN < 0) {
			valueFN = 0;
	}
	(*valueFD) = FD1;
}	

