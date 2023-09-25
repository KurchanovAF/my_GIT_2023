// =========================================================
// Filename:       lsm303d.h
// Revised:        $Date: 2017-09-29 $
// Revision:       $Revision: DOC ID 023312 Rev 1$
// Description:    This file contains the interface to the LSM303D.
//=========================================================
#ifndef __LSM303D_H
#define __LSM303D_H

#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_i2c.h"
//=========================================================
// CONSTANTS
//=========================================================
#define LSM303D_WHO_AM_I                (0x49) /* ?onstant 0x49 */
#define LSM303D_ADDRESS                 (0x1E) /* Address device */


/* Sensitivity */
#define SENSITIVITY_ACC_2G      (16384) /* 60ug/LSB  */
#define SENSITIVITY_ACC_4G      (8192)  /* 120ug/LSB */
#define SENSITIVITY_ACC_8G      (4096)  /* 240ug/LSB */
#define SENSITIVITY_ACC_16G     (2048)  /* 480ug/LSB */
/*---------------------------------------------------------*/
/* CTRL0 (0x1F) */
/*---------------------------------------------------------*/
#define LSM303D_REBOOT          (0x80)  /* Reboot memory content */

#define LSM303D_FIFO_ENABLED    (0x40)

/*---------------------------------------------------------*/
/* CTRL1 (0x20) */
/*---------------------------------------------------------*/
#define LSM303D_ACC_ODR_OFF     (0x00)  /* Power down */
#define LSM303D_ACC_ODR3_125    (0x10)  /* 3.25Hz output data rate */
#define LSM303D_ACC_ODR6_25     (0x20)  /* 6.25Hz output data rate */
#define LSM303D_ACC_ODR12_5     (0x30)  /* 12.5Hz output data rate */
#define LSM303D_ACC_ODR25       (0x40)  /* 25Hz output data rate */
#define LSM303D_ACC_ODR50       (0x50)  /* 50Hz output data rate */
#define LSM303D_ACC_ODR100      (0x60)  /* 100Hz output data rate */
#define LSM303D_ACC_ODR200      (0x70)  /* 200Hz output data rate */
#define LSM303D_ACC_ODR400      (0x80)  /* 400Hz output data rate */
#define LSM303D_ACC_ODR800      (0x90)  /* 800Hz output data rate */
#define LSM303D_ACC_ODR1600     (0xA0)  /* 1600Hz output data rate */

#define LSM303D_AUTO_UPDATE     (0x00)  /* Continuous update */
#define LSM303D_READ_UPDATE     (0x08)  /* Update have been read */

#define LSM303D_ACC_AXIS_X_ENABLE       (0x01)  /* Enable X acceleration */
#define LSM303D_ACC_AXIS_Y_ENABLE       (0x02)  /* Enable Y acceleration */
#define LSM303D_ACC_AXIS_Z_ENABLE       (0x04)  /* Enable Z acceleration */
#define LSM303D_ACC_AXIS_ALL_ENABLE     (0x07)  /* Enable X,Y,Z acceleration */

/*---------------------------------------------------------*/
/* CTRL2 (0x21) */
/*---------------------------------------------------------*/
/* Accelerometer Anti-alias filter */
#define LSM303D_ACC_FILTER_773  (0x00)  /*  Bandwidth 773 Hz */
#define LSM303D_ACC_FILTER_362  (0x40)  /*  Bandwidth 362 Hz */
#define LSM303D_ACC_FILTER_194  (0x80)  /*  Bandwidth 194 Hz */
#define LSM303D_ACC_FILTER_50   (0xC0)  /*  Bandwidth 50 Hz */

/* Accelerometer Sensor Full Scale */
#define LSM303D_ACC_FS_2G       (0x00)  /* Full scale 2g */
#define LSM303D_ACC_FS_4G       (0x08)  /* Full scale 4g */
#define LSM303D_ACC_FS_6G       (0x10)  /* Full scale 6g */
#define LSM303D_ACC_FS_8G       (0x18)  /* Full scale 8g */
#define LSM303D_ACC_FS_16G      (0x20)  /* Full scale 16g */

/* SPI Serial Interface mode selection */
#define LSM303D_SPI_4WIRE       (0x00)
#define LSM303D_SPI_3WIRE       (0x01)

/*---------------------------------------------------------*/
/* CTRL3 (0x22) */
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/* CTRL4 (0x23) */
/*---------------------------------------------------------*/

/*---------------------------------------------------------*/
/* CTRL5 (0x24) */
/*---------------------------------------------------------*/
#define LSM303D_TEMP_DISABLED   (0x00)
#define LSM303D_TEMP_ENABLED    (0x80)

/* Magnetic resolution selection */
#define LSM303D_MAG_RES_LOW     (0x00)
#define LSM303D_MAG_RES_HIGH    (0x60)
/* Magnetic data rate configuration */
#define LSM303D_MAG_ODR3_125    (0x00) /* 3.125 Hz */
#define LSM303D_MAG_ODR6_25     (0x04) /* 6.25 Hz */
#define LSM303D_MAG_ODR12_5     (0x08) /* 12.5 Hz */
#define LSM303D_MAG_ODR25       (0x0C) /* 25 Hz */
#define LSM303D_MAG_ODR50       (0x10) /* 50 Hz */
#define LSM303D_MAG_ODR100      (0x1C) /* 100 Hz */
/* Latch interrupt request on INT1_SRC register */
#define LSM303D_LIR1_DISABLED   (0x00) /* Interrupt request not latched */
#define LSM303D_LIR1_ENABLED    (0x01) /* Interrupt request latched */
/* Latch interrupt request on INT2_SRC register */
#define LSM303D_LIR2_DISABLED   (0x00) /* Interrupt request not latched */
#define LSM303D_LIR2_ENABLED    (0x02) /* Interrupt request latched */

/*---------------------------------------------------------*/
/* CTRL6 (0x25) */
/*---------------------------------------------------------*/
#define LSM303D_MAG_FS_2G       (0x00) /* 2 gauss */
#define LSM303D_MAG_FS_4G       (0x20) /* 4 gauss */
#define LSM303D_MAG_FS_8G       (0x40) /* 8 gauss */
#define LSM303D_MAG_FS_12G      (0x60) /* 12 gauss */

/*---------------------------------------------------------*/
/* CTRL7 (0x26) */
/*---------------------------------------------------------*/
#define LSM303D_AHPM_NORMAL_XYZ (0x00)
#define LSM303D_AHPM_REF        (0x40)
#define LSM303D_AHPM_NORMAL     (0x80)
#define LSM303D_AHPM_AUTO       (0xC0)

#define LSM303D_AFDS_OFF        (0x00)
#define LSM303D_AFDS_FIFO       (0x20)

#define LSM303D_T_ONLY_RM       (0x10)

#define LSM303D_LOW_POWER_MODE  (0x04)

#define LSM303_SCAN_MODE        (0x00)
#define LSM303_SINGLE_MODE      (0x01)
#define LSM303_DOWN_MODE        (0x02)
#define LSM303_DOWN_MODE_2      (0x03)
/*---------------------------------------------------------*/
/* STATUS_A (0x27) */
/*---------------------------------------------------------*/
#define LSM303D_STATUS_XADA     (0x01) /* Acceleration X data new value */

#define LSM303D_STATUS_YADA     (0x02) /* Acceleration Y data new value */

#define LSM303D_STATUS_ZADA     (0x04) /* Acceleration Z data new value */

#define LSM303D_STATUS_ZYXADA   (0x08) /* Acceleration X,Y,Z new value */

#define LSM303D_STATUS_XAOR     (0x10) /* Acceleration X data overrun */

#define LSM303D_STATUS_YAOR     (0x20) /* Acceleration Y data overrun */

#define LSM303D_STATUS_ZAOR     (0x40) /* Acceleration Z data overrun */

#define LSM303D_STATUS_ZYXOR    (0x80) /* Acceleration X,Y,Z data overrun */

/*---------------------------------------------------------*/
/* OUT_X_L_A - OUT_X_H_A(0x28-0x029) */
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/* OUT_Y_L_A - OUT_Y_H_A (0x2A-0x02B) */
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/* OUT_Z_L_A - OUT_Z_H_A (0x2C-0x02D) */
/*---------------------------------------------------------*/

/*---------------------------------------------------------*/
/* FIFO_CTRL (0x2E) */
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/* FIFO_SRC (0x2F) */
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/* IG_CFG1 (0x30) */
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/* IG_SRC1 (0x31) */
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/* IG_THS1 (32h) */
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/* IG_DUR1 (33h) */
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/* IG_CFG2 (34h) */
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/* IG_SRC2 (35h) */
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/* IG_THS2 (36h) */
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/* IG_DUR2 (37h) */
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/* CLICK_CFG (38h) */
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/* CLICK_SRC (39h) */
/*---------------------------------------------------------*/
#define LSM303D_SUCCESS                  0
#define LSM303D_ERR_I2C                 -1
#define LSM303D_ERR_STATUS              -3
#define LSM303D_ERR_SETUP_FAILURE       -4
#define LSM303D_ERR_GETGSENSORDATA      -5
#define LSM303D_ERR_IDENTIFICATION      -6

/*---------------------------------------------------------*/
/* REGISTER ADDRESS MAP */
/*---------------------------------------------------------*/
#define LSM303D_ADDR_AUTO_INCREMENT     (0x80) /* Autoincrement address*/

#define LSM303D_REG_TEMP_OUT_L          (0x05) /* Temperature bits 7-0 */
#define LSM303D_REG_TEMP_OUT_H          (0x06) /* Temperature bits 11-8 */
  
#define LSM303D_REG_STATUS_M            (0x07) /* Magnetic status register */
  
#define LSM303D_REG_OUT_X_L_M           (0x08) /* Magnetic X-axis MSB */
#define LSM303D_REG_OUT_X_H_M           (0x09) /* Magnetic X-axis LSB */
#define LSM303D_REG_OUT_Y_L_M           (0x0A) /* Magnetic Y-axis MSB */
#define LSM303D_REG_OUT_Y_H_M           (0x0B) /* Magnetic Y-axis LSB */
#define LSM303D_REG_OUT_Z_L_M           (0x0C) /* Magnetic Z-axis MSB */
#define LSM303D_REG_OUT_Z_H_M           (0x0D) /* Magnetic Z-axis LSB */
  
#define LSM303D_REG_WHO_AM_I            (0x0F) /* ID register, constant 0x49 */
  
#define LSM303D_REG_CTRL_M	        		(0x12) /* Magnetic control register */
#define LSM303D_REG_INT_SRC_M           (0x13)
#define LSM303D_REG_THS_L_M	        		(0x14)
#define LSM303D_REG_THS_H_M	        		(0x15)
  
#define LSM303D_REG_OFFSET_X_L_M        (0x16)
#define LSM303D_REG_OFFSET_X_H_M        (0x17)
#define LSM303D_REG_OFFSET_Y_L_M        (0x18)
#define LSM303D_REG_OFFSET_Y_H_M        (0x19)
#define LSM303D_REG_OFFSET_Z_L_M        (0x1A)
#define LSM303D_REG_OFFSET_Z_H_M        (0x1B)
  
#define LSM303D_REG_REFERENCE_X         (0x1C)
#define LSM303D_REG_REFERENCE_Y         (0x1D)
#define LSM303D_REG_REFERENCE_Z         (0x1E)
  
#define LSM303D_REG_CTRL0               (0x1F)
#define LSM303D_REG_CTRL1               (0x20)
#define LSM303D_REG_CTRL2               (0x21)
#define LSM303D_REG_CTRL3               (0x22)
#define LSM303D_REG_CTRL4               (0x23)
#define LSM303D_REG_CTRL5               (0x24)
#define LSM303D_REG_CTRL6               (0x25)
#define LSM303D_REG_CTRL7               (0x26)
  
#define LSM303D_REG_STATUS_A            (0x27)
  
#define LSM303D_REG_OUT_X_L_A           (0x28)
#define LSM303D_REG_OUT_X_H_A           (0x29)
#define LSM303D_REG_OUT_Y_L_A           (0x2A)
#define LSM303D_REG_OUT_Y_H_A           (0x2B)
#define LSM303D_REG_OUT_Z_L_A           (0x2C)
#define LSM303D_REG_OUT_Z_H_A           (0x2D)
  
#define LSM303D_REG_FIFO_CTRL           (0x2E)
#define LSM303D_REG_FIFO_SRC0           (0x2F)
  
#define LSM303D_REG_IG_CFG1             (0x30)
#define LSM303D_REG_IG_SRC1             (0x31)
#define LSM303D_REG_IG_THS1             (0x32)
#define LSM303D_REG_IG_DUR1             (0x33)
#define LSM303D_REG_IG_CFG2             (0x34)
#define LSM303D_REG_IG_SRC2             (0x35)
#define LSM303D_REG_IG_THS2             (0x36)
#define LSM303D_REG_IG_DUR2             (0x37)
  
#define LSM303D_REG_CLICK_CFG           (0x38)
#define LSM303D_REG_CLICK_SRC           (0x39)
#define LSM303D_REG_CLICK_THS           (0x3A)
  
#define LSM303D_REG_TIME_LIMIT	        (0x3B)
#define LSM303D_REG_TIME_LATENCY        (0x3C)
#define LSM303D_REG_TIME_WINDOW	        (0x3D)
  
#define LSM303D_REG_ACT_THS             (0x3E)
#define LSM303D_REG_ACT_DUR             (0x3F)
/*---------------------------------------------------------*/

typedef struct {
  uint16_t x;
  uint16_t y;
  uint16_t z;
} acc_data_t;

typedef struct {
  uint16_t x;
  uint16_t y;
  uint16_t z;
} mag_data_t;


//=========================================================
// FUNCTIONS - API
//=========================================================
void LSM303D_Initialize(I2C_HandleTypeDef *hi2c);
void LSM303D_GetValueAcc(I2C_HandleTypeDef *hi2c, int *X, int *Y, int *Z);
void LSM303D_GetValueMag(I2C_HandleTypeDef *hi2c, int *X, int *Y, int *Z);
uint16_t LSM303D_GetTemperature(I2C_HandleTypeDef *hi2c);
uint8_t LSM303D_GetID(I2C_HandleTypeDef *hi2c);

#endif

