#include "interface_AD5668.h"


#define DAC_nCS_Pin GPIO_PIN_12
#define DAC_nCS_GPIO_Port GPIOB


void AD5668_Init(void){
	// �����
	AD5668_Reset();

	volatile uint8_t rx = 0;
	// ����������� SPI2 ��� ������ � �����
	// Disable SPI peripheral
	SPI2->CR1 &= ~SPI_CR1_SPE;
	// ����������� SPI2 ��� ������ � �����
	// CPOL = 1
	SPI2->CR1 |= SPI_CR1_CPOL;
	// CPHA = 0
	SPI2->CR1 &= ~SPI_CR1_CPHA;	
	// Enable SPI peripheral
	SPI2->CR1 |= SPI_CR1_SPE;
	// ����� �� �������� �� ���������
		
	uint32_t sendData = AD5668_REF | AD5668_REF_OFF;
	static uint8_t data[4];
	data[0] = ((sendData >> 24) & 0xFF);
	data[1] = ((sendData >> 16) & 0xFF);
	data[2] = ((sendData >> 8) & 0xFF);
	data[3] = ((sendData >> 0) & 0xFF);
	// ����� ���������� ����
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_RESET);
	// ���� ����� DR ������������ �� ������
	 while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	 *((__IO uint8_t *)&SPI2->DR) = data[0];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[1];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	 *((__IO uint8_t *)&SPI2->DR) = data[2];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[3];
	// ������� ���������� �������� ������
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	// �������� ����������� FIFO
	while (((SPI2->SR) & (SPI_SR_FTLVL)) != 0){};
	while (((SPI2->SR) & (SPI_SR_BSY)) == (SPI_SR_BSY)){}; 
	// ��������� ������
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_SET);
	SPI2->CR1 &= ~SPI_CR1_SPE;	
	while (((SPI2->SR) & (SPI_SR_FRLVL)) != 0){
		rx = *((__IO uint8_t *)&SPI2->DR);
	};	
	
}
// �������� � ������� ����� �� SPI2
void AD5668_SetValue(uint32_t chanel, int value){
	volatile uint8_t rx = 0;
	if (value <= 0){value = 0;}
	if (value >= 65535){value = 65535;}		
	
	// Disable SPI peripheral
	SPI2->CR1 &= ~SPI_CR1_SPE;
	// ����������� SPI2 ��� ������ � �����
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
	// ����� ���������� ����
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_RESET);
	// ���� ����� DR ������������ �� ������
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[0];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[1];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[2];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[3];
	// ������� ���������� �������� ������
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	// �������� ����������� FIFO
	while (((SPI2->SR) & (SPI_SR_FTLVL)) != 0){};
	while (((SPI2->SR) & (SPI_SR_BSY)) == (SPI_SR_BSY)){}; 
	// ��������� ������
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_SET);	
	SPI2->CR1 &= ~SPI_CR1_SPE;	
	while (((SPI2->SR) & (SPI_SR_FRLVL)) != 0){
		rx = *((__IO uint8_t *)&SPI2->DR);
	};

}


// �������� � ������� ����� �� SPI2
void AD5668_WriteValue(uint32_t chanel, int value){
	volatile uint8_t rx = 0;
	if (value < 0){value = 0;}
	//value &= 0xFFFF;
	if (value >= 65535){value = 65535;}
	
	// Disable SPI peripheral
	SPI2->CR1 &= ~SPI_CR1_SPE;
	// ����������� SPI2 ��� ������ � �����
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
	// ����� ���������� ����
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_RESET);
	// ���� ����� DR ������������ �� ������
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[0];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[1];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[2];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[3];
	// ������� ���������� �������� ������
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	// �������� ����������� FIFO
	while (((SPI2->SR) & (SPI_SR_FTLVL)) != 0){};
	while (((SPI2->SR) & (SPI_SR_BSY)) == (SPI_SR_BSY)){}; 
	// ��������� ������
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_SET);	
	SPI2->CR1 &= ~SPI_CR1_SPE;	
	while (((SPI2->SR) & (SPI_SR_FRLVL)) != 0){
		rx = *((__IO uint8_t *)&SPI2->DR);
	};
}

// ����� �������� ��������� �����������
void AD5668_Reset(void){
	volatile uint8_t rx = 0;
	// ����������� SPI2 ��� ������ � �����
	// Disable SPI peripheral
	SPI2->CR1 &= ~SPI_CR1_SPE;
	// ����������� SPI2 ��� ������ � �����
	// CPOL = 1
	SPI2->CR1 |= SPI_CR1_CPOL;
	// CPHA = 0
	SPI2->CR1 &= ~SPI_CR1_CPHA;
	// Enable SPI peripheral
	SPI2->CR1 |= SPI_CR1_SPE;
	// ����� �� �������� �� ���������
	uint32_t sendData = AD5668_RESET;
	static uint8_t data[4];
	data[0] = ((sendData >> 24) & 0xFF);
	data[1] = ((sendData >> 16) & 0xFF);
	data[2] = ((sendData >> 8) & 0xFF);
	data[3] = ((sendData >> 0) & 0xFF);
	// ����� ���������� ����
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_RESET);
	// ���� ����� DR ������������ �� ������
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[0];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[1];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[2];
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	*((__IO uint8_t *)&SPI2->DR) = data[3];
	// ������� ���������� �������� ������
	while (((SPI2->SR) & (SPI_SR_TXE)) != (SPI_SR_TXE)){};
	// �������� ����������� FIFO
	while (((SPI2->SR) & (SPI_SR_FTLVL)) != 0){};
	while (((SPI2->SR) & (SPI_SR_BSY)) == (SPI_SR_BSY)){}; 
	// ��������� ������
	HAL_GPIO_WritePin(DAC_nCS_GPIO_Port, DAC_nCS_Pin, GPIO_PIN_SET);	
	SPI2->CR1 &= ~SPI_CR1_SPE;	
	while (((SPI2->SR) & (SPI_SR_FRLVL)) != 0){
		rx = *((__IO uint8_t *)&SPI2->DR);
	};
}

