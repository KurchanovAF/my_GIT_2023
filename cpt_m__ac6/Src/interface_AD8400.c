#include "interface_AD8400.h"


#define AD8400_nCS_Pin GPIO_PIN_2
#define AD8400_nCS_GPIO_Port GPIOD

// �������� � ������� ����� �� SPI2
void AD8400_SetValue(int value){
	volatile uint8_t rx = 0;
	if (value <= 0){value = 0;}
	if (value >= 255){value = 255;}		
	//value = ((value << 6) & (0xFFC0));
	// ����������� SPI1 ��� �����
	// Disable SPI peripheral
	SPI1->CR1 &= ~SPI_CR1_SPE;
	// ����������� SPI1 ��� �����
	// CPOL = 0
	SPI1->CR1 &= ~SPI_CR1_CPOL;
	// CPHA = 0
	SPI1->CR1 &= ~SPI_CR1_CPHA;	
	// Enable SPI peripheral
	SPI1->CR1 |= SPI_CR1_SPE;
	// ����� �� �������� �� ���������
	static uint8_t data[2];
	data[0] = ((value >> 8) & 0xFF);
	data[1] = ((value >> 0) & 0xFF);
	// ����� ���������� ����
	HAL_GPIO_WritePin(AD8400_nCS_GPIO_Port, AD8400_nCS_Pin, GPIO_PIN_RESET);
	// ���� ����� DR ������������ �� ������
	while (((SPI1->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint16_t *)&SPI1->DR) = value;
	//while (((SPI1->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	//*((__IO uint8_t *)&SPI1->DR) = data[1];
	// ������� ���������� �������� ������
	while (((SPI1->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	// �������� ����������� FIFO
	while (((SPI1->SR) & (SPI_SR_FTLVL)) != 0){};
	while (((SPI1->SR) & (SPI_SR_BSY)) == (SPI_SR_BSY)){}; 
	// ��������� ������
	HAL_GPIO_WritePin(AD8400_nCS_GPIO_Port, AD8400_nCS_Pin, GPIO_PIN_SET);
	SPI1->CR1 &= ~SPI_CR1_SPE;	
	while (((SPI1->SR) & (SPI_SR_FRLVL)) != 0){
		rx = *((__IO uint8_t *)&SPI1->DR);
	};	

}



