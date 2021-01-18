/*
 * YNV_LIS3DSH.h
 *
 *  Created on: Jan 12, 2021
 *      Author: raffe
 */

#ifndef INC_YNV_LIS3DSH_H_
#define INC_YNV_LIS3DSH_H_

#include "stm32f4xx_hal.h"

/* Register Address Define */
#define LIS3DSH_CTRL_REG3				0x23				// Interruptions
#define LIS3DSH_CTRL_REG4 				0x20 				// configure axes X and Y
#define LIS3DSH_CTRL_REG5				0x24				// configure anti-aliasing filter at 800Hz; full-scale at+- 2g; self-test disabled; SPI with 4 wire interface
#define LIS3DSH_OUT_X 					0x28				// X_axis output
#define LIS3DSH_OUT_Y 					0x2A				// Y_axis output
#define LIS3DSH_OUT_Z					0x2C				// Z_axis output
#define LIS3DSH_Status					0x27				// define status


/* Configuration Parameters define */

// About register LIS3DSH_CTRL_REG4 //
#define LIS3DSH_ODR_DISABLED		((uint8_t)0x00)			// Output Data Register disabled
#define LIS3DSH_ODR_3_125_HZ		((uint8_t)0x10)			// Output Data Register at 3.125Hz
#define LIS3DSH_ODR_6_25_HZ			((uint8_t)0x20)			// Output Data Register at 6.25Hz
#define LIS3DSH_ODR_12_5_HZ			((uint8_t)0x30)			// Output Data Register at 12.5Hz
#define LIS3DSH_ODR_25_HZ			((uint8_t)0x40)			// Output Data Register at 25Hz
#define LIS3DSH_ODR_50_HZ			((uint8_t)0x50)			// Output Data Register at 50Hz
#define LIS3DSH_ODR_100_HZ			((uint8_t)0x60)			// Output Data Register at 100Hz
#define LIS3DSH_ODR_400_HZ			((uint8_t)0x70)			// Output Data Register at 400Hz
#define LIS3DSH_ODR_800_HZ			((uint8_t)0x80)			// Output Data Register at 800Hz
#define LIS3DSH_ODR_1600_HZ			((uint8_t)0x90)			// Output Data Register at 1600Hz

#define LIS3DSH_BDU_CONTINUOUS		((uint8_t)0x00)			// Block Data Update Enable is with continuous update
#define LIS3DSH_BDU_NOT_UPDATED		((uint8_t)0x08)			// output registers not updated until MSB and LSB have been read

#define LIS3DSH_ZEN_DISABLED		((uint8_t)0x00)			// z_axe disabled
#define LIS3DSH_ZEN_ENABLED			((uint8_t)0x04)			// z_axe enabled

#define LIS3DSH_YEN_DISABLED		((uint8_t)0x00)			// y_axe disabled
#define LIS3DSH_YEN_ENABLED			((uint8_t)0x02)			// y_axe enabled

#define LIS3DSH_XEN_DISABLED		((uint8_t)0x00)			// x_axe disabled
#define LIS3DSH_XEN_ENABLED			((uint8_t)0x01)			// x_axe enabled

// About register LIS3DSH_CTRL_REG5
#define LIS3DSH_BW2_800_HZ 			((uint8_t)0x00)			//Anti-aliasing filter bandwidth at 800Hz
#define LIS3DSH_BW2_200_HZ 			((uint8_t)0x40)			//Anti-aliasing filter bandwidth at 200Hz
#define LIS3DSH_BW2_400_HZ 			((uint8_t)0x80)			//Anti-aliasing filter bandwidth at 400Hz
#define LIS3DSH_BW_50_HZ 			((uint8_t)0x90)			//Anti-aliasing filter bandwidth at 50Hz

#define LIS3DSH_FSCALE_2g			((uint8_t)0x00)			// Full scale selection with maximum 2g
#define LIS3DSH_FSCALE_4g			((uint8_t)0x08)			// Full scale selection with maximum 4g
#define LIS3DSH_FSCALE_6g			((uint8_t)0x10)			// Full scale selection with maximum 6g
#define LIS3DSH_FSCALE_8g			((uint8_t)0x18)			// Full scale selection with maximum 8g
#define LIS3DSH_FSCALE_16g			((uint8_t)0x20)			// Full scale selection with maximum 16g


/* Init struct */
typedef struct												// name the functions
{
	uint8_t Axis_X;
	uint8_t Axis_Y;
	uint8_t Axis_Z;
	uint8_t OutputDataRate;
	uint8_t CTRL_Reg5;
	uint8_t DataUpdateEnable;
	uint8_t BandWidth;
	uint8_t FScale;
}LIS3DSH_init_t;


/* Status enum */
typedef enum
{
	LIS3DSH_OK,
	LIS3DSH_ERROR,
}LIS3DSH_Status_t;

/* Write Function */
LIS3DSH_Status_t LIS3DSH_Write_Reg(SPI_HandleTypeDef *AxeSPI,
									uint8_t reg_addr,
									uint8_t * dataW,
									uint8_t size);

/* Read Funtion */
LIS3DSH_Status_t LIS3DSH_Read_Reg(SPI_HandleTypeDef *AxeSPI,
									uint8_t reg_addr,
									uint8_t * dataR,
									uint8_t size);

/* Init function */
LIS3DSH_Status_t LIS3DSH_Init(SPI_HandleTypeDef *AxeSPI,
									LIS3DSH_init_t *AxeInitDef);

/* Get Position */
LIS3DSH_Status_t LIS3DSH_Get_Pos(SPI_HandleTypeDef *AxeSPI,
									uint16_t *AxeGetPosition);

#endif /* INC_YNV_LIS3DSH_H_ */
