#include "interface_AD8400.h"


#define AD8400_nCS_Pin GPIO_PIN_2
#define AD8400_nCS_GPIO_Port GPIOD

// Работаем с внешним ЦАПом по SPI2
void AD8400_SetValue(int value){
	volatile uint8_t rx = 0;
	if (value <= 0){value = 0;}
	if (value >= 255){value = 255;}		
	//value = ((value << 6) & (0xFFC0));
	// Настраиваем SPI1 для работ
	// Disable SPI peripheral
	SPI1->CR1 &= ~SPI_CR1_SPE;
	// Настраиваем SPI1 для работ
	// CPOL = 0
	SPI1->CR1 &= ~SPI_CR1_CPOL;
	// CPHA = 0
	SPI1->CR1 &= ~SPI_CR1_CPHA;	
	// Enable SPI peripheral
	SPI1->CR1 |= SPI_CR1_SPE;
	// Сброс на значения по умолчанию
	static uint8_t data[2];
	data[0] = ((value >> 8) & 0xFF);
	data[1] = ((value >> 0) & 0xFF);
	// Выбор микросхемы ЦАПа 
	HAL_GPIO_WritePin(AD8400_nCS_GPIO_Port, AD8400_nCS_Pin, GPIO_PIN_RESET);
	// Ждем когда DR осовободится на запись
  while (((SPI1->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
  *((__IO uint16_t *)&SPI1->DR) = value;
	//while (((SPI1->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	//*((__IO uint8_t *)&SPI1->DR) = data[1];
	// Ожидаем завершение передачи данных
	while (((SPI1->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	// Ожидание опустошения FIFO
	while (((SPI1->SR) & (SPI_SR_FTLVL)) != 0){};
	while (((SPI1->SR) & (SPI_SR_BSY)) == (SPI_SR_BSY)){}; 
	// Фиксируем данные
	HAL_GPIO_WritePin(AD8400_nCS_GPIO_Port, AD8400_nCS_Pin, GPIO_PIN_SET);
	SPI1->CR1 &= ~SPI_CR1_SPE;	
	while (((SPI1->SR) & (SPI_SR_FRLVL)) != 0){
		rx = *((__IO uint8_t *)&SPI1->DR);
	};	

}



