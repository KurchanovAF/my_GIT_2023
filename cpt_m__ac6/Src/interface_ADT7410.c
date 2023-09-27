#include "i2c.h"
#include "var.h"
#include "interface_ADT7410.h"

// ����������� ������ ����������� ������ �� I2C
//*
void InitTEMP(void){
	//=======================================================
	uint8_t addressI2C3 = ADT7410_ADDRESS;
	I2C3_TxBuffer[0]	= ADT7410_REG_CONF;
	I2C3_TxBuffer[1]	= ADT7410_RES_16 | ADT7410_CONV_SPS;
	if (HAL_I2C_Master_Transmit(&hi2c3, addressI2C3<<1, &I2C3_TxBuffer[0], 2, 200) != HAL_OK){}
	// �������� ������
	if (HAL_I2C_Master_Receive(&hi2c3, addressI2C3<<1, &I2C3_RxBuffer[0], 2, 200) == HAL_OK){
		value_Temp_D_Cell = ((int)(I2C3_RxBuffer[0] << 8 | I2C3_RxBuffer[1]))/128.0f;
		TempCellIsCorrect = true;
	}
}
//*/

// ��������� �������� �� ���������� ���������� �������� 1 �������
void GetTEMP(void){
	//=======================================================
	uint8_t addressI2C3 = ADT7410_ADDRESS;
	I2C3_RxBuffer[0]	= 0;
	I2C3_RxBuffer[1]	= 0;
	if (HAL_I2C_Master_Receive(&hi2c3, addressI2C3<<1, &I2C3_RxBuffer[0], 2, 200) == HAL_OK){
		value_Temp_D_Cell = ((int)(I2C3_RxBuffer[0] << 8 | I2C3_RxBuffer[1]))/128.0f;
		TempCellIsCorrect = true;
	}
	//value_TempCell = 335577;
}
