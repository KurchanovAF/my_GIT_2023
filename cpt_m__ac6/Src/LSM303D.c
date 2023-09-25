#include "LSM303D.h"

extern uint8_t LSM303_BufferTx[16];
extern uint8_t LSM303_BufferRx[16];

// Настройка датчика LSM303D
void LSM303D_Initialize(I2C_HandleTypeDef *hi2c){
	
	// LSM303D_REG_CTRL0
  LSM303_BufferTx[0] = LSM303D_FIFO_ENABLED;
  if (HAL_I2C_Mem_Write(hi2c, LSM303D_ADDRESS<<1, LSM303D_REG_CTRL0, 
												I2C_MEMADD_SIZE_8BIT, &LSM303_BufferTx[0], 1, 500) == HAL_OK){};

	// LSM303D_REG_CTRL1
	// Обновляем данные при чтении 
  LSM303_BufferTx[0] = 	LSM303D_READ_UPDATE | 
												LSM303D_ACC_AXIS_ALL_ENABLE |
												LSM303D_ACC_ODR3_125;
  if (HAL_I2C_Mem_Write(hi2c, LSM303D_ADDRESS<<1, LSM303D_REG_CTRL1, 
												I2C_MEMADD_SIZE_8BIT, &LSM303_BufferTx[0], 1, 500) == HAL_OK){};												

	// LSM303D_REG_CTRL5
  LSM303_BufferTx[0] = 	LSM303D_TEMP_ENABLED | 
												LSM303D_MAG_RES_HIGH | 
												LSM303D_MAG_ODR3_125;
  if (HAL_I2C_Mem_Write(hi2c, LSM303D_ADDRESS<<1, LSM303D_REG_CTRL5, 
												I2C_MEMADD_SIZE_8BIT, &LSM303_BufferTx[0], 1, 500) == HAL_OK){};														
		
	// LSM303D_REG_CTRL6
	// Рабочий диапазон магнитометра										
  LSM303_BufferTx[0] = 	LSM303D_MAG_FS_2G;
  if (HAL_I2C_Mem_Write(hi2c, LSM303D_ADDRESS<<1, LSM303D_REG_CTRL6, 
												I2C_MEMADD_SIZE_8BIT, &LSM303_BufferTx[0], 1, 500) == HAL_OK){};															

	// LSM303D_REG_CTRL7									
  LSM303_BufferTx[0] = (0x00);
  if (HAL_I2C_Mem_Write(hi2c, LSM303D_ADDRESS<<1, LSM303D_REG_CTRL7, 
												I2C_MEMADD_SIZE_8BIT, &LSM303_BufferTx[0], 1, 500) == HAL_OK){};
													

}
// Считывание показаний термометра
uint16_t LSM303D_GetTemperature(I2C_HandleTypeDef *hi2c){
	uint8_t memoryAddress = LSM303D_REG_TEMP_OUT_L | LSM303D_ADDR_AUTO_INCREMENT;
	if (HAL_I2C_Mem_Read(hi2c, LSM303D_ADDRESS<<1, memoryAddress, 
												I2C_MEMADD_SIZE_8BIT, &LSM303_BufferRx[0], 2, 500) == HAL_OK){};
  uint16_t result = (LSM303_BufferRx[1]<<8);
  result |=LSM303_BufferRx[0];
  return result;
}
// Считывание показаний акселероmeтра
void LSM303D_GetValueAcc(I2C_HandleTypeDef *hi2c, int *X, int *Y, int *Z){

	uint8_t memoryAddress = LSM303D_REG_OUT_X_L_A | LSM303D_ADDR_AUTO_INCREMENT;
	if (HAL_I2C_Mem_Read(hi2c, LSM303D_ADDRESS<<1, memoryAddress, 
												I2C_MEMADD_SIZE_8BIT, &LSM303_BufferRx[0], 6, 500) == HAL_OK){};
  
  // Собираем данные по Х
  (*X) = (LSM303_BufferRx[1] << 8);
  (*X) |= (LSM303_BufferRx[0]);
  if ((*X) > 32767){
    (*X) -= 65535;
  }
  // Собираем данные по Y
  (*Y) = (int)(LSM303_BufferRx[3] << 8);
  (*Y) |= (int)(LSM303_BufferRx[2]);
  if ((*Y) > 32767){
    (*Y) -= 65535;
  }
  // Собираем данные по Z
  (*Z) = (int)(LSM303_BufferRx[5] << 8);
  (*Z) |= (int)(LSM303_BufferRx[4]);
  if ((*Z) > 32767){
    (*Z) -= 65535;
  }

}
// Считывание показаний магнетометра
void LSM303D_GetValueMag(I2C_HandleTypeDef *hi2c, int *X, int *Y, int *Z){
	uint8_t memoryAddress = LSM303D_REG_OUT_X_L_M | LSM303D_ADDR_AUTO_INCREMENT;
	if (HAL_I2C_Mem_Read(hi2c, LSM303D_ADDRESS<<1, memoryAddress, 
												I2C_MEMADD_SIZE_8BIT, &LSM303_BufferRx[0], 6, 500) == HAL_OK){};
  // Собираем данные по Х
  (*X) = (LSM303_BufferRx[1] << 8);
  (*X) |= (LSM303_BufferRx[0]);
  if ((*X) > 32767){
    (*X) -= 65535;
  }
  // Собираем данные по Y
  (*Y) = (int)(LSM303_BufferRx[3] << 8);
  (*Y) |= (int)(LSM303_BufferRx[2]);
  if ((*Y) > 32767){
    (*Y) -= 65535;
  }
  // Собираем данные по Z
  (*Z) = (int)(LSM303_BufferRx[5] << 8);
  (*Z) |= (int)(LSM303_BufferRx[4]);
  if ((*Z) > 32767){
    (*Z) -= 65535;
  }

}
uint8_t LSM303D_GetID(I2C_HandleTypeDef *hi2c){
	int8_t memoryAddress = LSM303D_REG_WHO_AM_I;
	if (HAL_I2C_Mem_Read(hi2c, LSM303D_ADDRESS<<1, memoryAddress, 
												I2C_MEMADD_SIZE_8BIT, &LSM303_BufferRx[0], 1, 500) == HAL_OK){};
	return LSM303_BufferRx[0];
}

