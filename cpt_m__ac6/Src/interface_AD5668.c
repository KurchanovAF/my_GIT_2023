#include "interface_AD5668.h"


#define DAC_nCS_Pin GPIO_PIN_12
#define DAC_nCS_GPIO_Port GPIOB


void AD5668_Init(void){
	// Сброс
	AD5668_Reset();
	
	volatile uint8_t rx = 0;
	// Настраиваем SPI2 для работы с ЦАПом
	// Disable SPI peripheral
	SPI2->CR1 &= ~SPI_CR1_SPE;
	// Настраиваем SPI2 для работы с ЦАПом
	// CPOL = 1
	SPI2->CR1 |= SPI_CR1_CPOL;
	// CPHA = 0
	SPI2->CR1 &= ~SPI_CR1_CPHA;	
	// Enable SPI peripheral
	SPI2->CR1 |= SPI_CR1_SPE;
	// Сброс на значения по умолчанию
		
	uint32_t sendData = AD5668_REF | AD5668_REF_OFF;
	static uint8_t data[4];
	data[0] = ((sendData >> 24) & 0xFF);
	data[1] = ((sendData >> 16) & 0xFF);
	data[2] = ((sendData >> 8) & 0xFF);
	data[3] = ((sendData >> 0) & 0xFF);
	// Выбор микросхемы ЦАПа
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_RESET);
	// Ждем когда DR осовободится на запись
  while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
  *((__IO uint8_t *)&SPI2->DR) = data[0];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[1];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
  *((__IO uint8_t *)&SPI2->DR) = data[2];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[3];
	// Ожидаем завершение передачи данных
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	// Ожидание опустошения FIFO
	while (((SPI2->SR) & (SPI_SR_FTLVL)) != 0){};
	while (((SPI2->SR) & (SPI_SR_BSY)) == (SPI_SR_BSY)){}; 
	// Фиксируем данные
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_SET);
	SPI2->CR1 &= ~SPI_CR1_SPE;	
	while (((SPI2->SR) & (SPI_SR_FRLVL)) != 0){
		rx = *((__IO uint8_t *)&SPI2->DR);
	};	
	
}
// Работаем с внешним ЦАПом по SPI2
void AD5668_SetValue(uint32_t chanel, int value){
	volatile uint8_t rx = 0;
	if (value <= 0){value = 0;}
	if (value >= 65535){value = 65535;}		
	
	// Disable SPI peripheral
	SPI2->CR1 &= ~SPI_CR1_SPE;
	// Настраиваем SPI2 для работы с ЦАПом
	// CPOL = 1
	SPI2->CR1 |= SPI_CR1_CPOL;
	// CPHA = 0
	SPI2->CR1 &= ~SPI_CR1_CPHA;	
	// Enable SPI peripheral
	SPI2->CR1 |= SPI_CR1_SPE;
 
	uint32_t sendData = AD5668_WRITE_AND_UPDATE_N | chanel | AD5668_VALUE(value);
	static uint8_t data[4];
	data[0] = ((sendData >> 24) & 0xFF);
	data[1] = ((sendData >> 16) & 0xFF);
	data[2] = ((sendData >> 8) & 0xFF);
	data[3] = ((sendData >> 0) & 0xFF);	
	// Выбор микросхемы ЦАПа
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_RESET);
	// Ждем когда DR осовободится на запись
  while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
  *((__IO uint8_t *)&SPI2->DR) = data[0];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[1];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
  *((__IO uint8_t *)&SPI2->DR) = data[2];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[3];
	// Ожидаем завершение передачи данных
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	// Ожидание опустошения FIFO
	while (((SPI2->SR) & (SPI_SR_FTLVL)) != 0){};
	while (((SPI2->SR) & (SPI_SR_BSY)) == (SPI_SR_BSY)){}; 
	// Фиксируем данные
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_SET);	
	SPI2->CR1 &= ~SPI_CR1_SPE;	
	while (((SPI2->SR) & (SPI_SR_FRLVL)) != 0){
		rx = *((__IO uint8_t *)&SPI2->DR);
	};

}


// Работаем с внешним ЦАПом по SPI2
void AD5668_WriteValue(uint32_t chanel, int value){
	volatile uint8_t rx = 0;
	if (value < 0){value = 0;}
	//value &= 0xFFFF;
	if (value >= 65535){value = 65535;}
	
	// Disable SPI peripheral
	SPI2->CR1 &= ~SPI_CR1_SPE;
	// Настраиваем SPI2 для работы с ЦАПом
	// CPOL = 1
	SPI2->CR1 |= SPI_CR1_CPOL;
	// CPHA = 0
	SPI2->CR1 &= ~SPI_CR1_CPHA;	
	// Enable SPI peripheral
	SPI2->CR1 |= SPI_CR1_SPE;
 
	uint32_t sendData = AD5668_WRITE_N | chanel | AD5668_VALUE(value);
	static uint8_t data[4];
	data[0] = ((sendData >> 24) & 0xFF);
	data[1] = ((sendData >> 16) & 0xFF);
	data[2] = ((sendData >> 8) & 0xFF);
	data[3] = ((sendData >> 0) & 0xFF);	
	// Выбор микросхемы ЦАПа
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_RESET);
	// Ждем когда DR осовободится на запись
  while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
  *((__IO uint8_t *)&SPI2->DR) = data[0];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[1];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
  *((__IO uint8_t *)&SPI2->DR) = data[2];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[3];
	// Ожидаем завершение передачи данных
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	// Ожидание опустошения FIFO
	while (((SPI2->SR) & (SPI_SR_FTLVL)) != 0){};
	while (((SPI2->SR) & (SPI_SR_BSY)) == (SPI_SR_BSY)){}; 
	// Фиксируем данные
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_SET);	
	SPI2->CR1 &= ~SPI_CR1_SPE;	
	while (((SPI2->SR) & (SPI_SR_FRLVL)) != 0){
		rx = *((__IO uint8_t *)&SPI2->DR);
	};
}

// Сброс значений микросхем поумолчанию
void AD5668_Reset(void){
	volatile uint8_t rx = 0;
	// Настраиваем SPI2 для работы с ЦАПом
	// Disable SPI peripheral
	SPI2->CR1 &= ~SPI_CR1_SPE;
	// Настраиваем SPI2 для работы с ЦАПом
	// CPOL = 1
	SPI2->CR1 |= SPI_CR1_CPOL;
	// CPHA = 0
	SPI2->CR1 &= ~SPI_CR1_CPHA;	
	// Enable SPI peripheral
	SPI2->CR1 |= SPI_CR1_SPE;
	// Сброс на значения по умолчанию
	uint32_t sendData = AD5668_RESET;
	static uint8_t data[4];
	data[0] = ((sendData >> 24) & 0xFF);
	data[1] = ((sendData >> 16) & 0xFF);
	data[2] = ((sendData >> 8) & 0xFF);
	data[3] = ((sendData >> 0) & 0xFF);
	// Выбор микросхемы ЦАПа
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_RESET);
	// Ждем когда DR осовободится на запись
  while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
  *((__IO uint8_t *)&SPI2->DR) = data[0];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[1];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
  *((__IO uint8_t *)&SPI2->DR) = data[2];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[3];
	// Ожидаем завершение передачи данных
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	// Ожидание опустошения FIFO
	while (((SPI2->SR) & (SPI_SR_FTLVL)) != 0){};
	while (((SPI2->SR) & (SPI_SR_BSY)) == (SPI_SR_BSY)){}; 
	// Фиксируем данные
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_SET);	
	SPI2->CR1 &= ~SPI_CR1_SPE;	
	while (((SPI2->SR) & (SPI_SR_FRLVL)) != 0){
		rx = *((__IO uint8_t *)&SPI2->DR);
	};
}

