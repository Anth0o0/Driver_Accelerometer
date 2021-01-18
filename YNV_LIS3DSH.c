/*
 * YNV_LIS3DSH.c
 *
 *  Created on: Jan 12, 2021
 *      Author: raffe
 */

#include "YNV_LIS3DSH.h"

																							// to define who is the master, slave
LIS3DSH_Status_t LIS3DSH_Write_Reg(SPI_HandleTypeDef *AxeSPI,uint8_t reg_addr,uint8_t *dataW,uint8_t size)		// write on the registers
{
    dataW[0]=reg_addr;																							// we place the value we want to write in the register in the dataW[0]
    if(HAL_SPI_Transmit(AxeSPI, dataW, size, 10) == HAL_OK)														// if the data is transmit return OK else return error
    {
        return LIS3DSH_OK;
    }
    return LIS3DSH_ERROR;
}

LIS3DSH_Status_t LIS3DSH_Read_Reg(SPI_HandleTypeDef *AxeSPI,uint8_t reg_addr,uint8_t *dataR,uint8_t size)		// read the registers
{
	dataR[0] = reg_addr | 0x80;																					// bit at 1 to read
	if (HAL_SPI_Transmit(AxeSPI, &reg_addr, size, 10)==HAL_OK)													// if the data is received return OK else return error
    {
        if(HAL_SPI_Transmit(AxeSPI, dataR, size, 10) == HAL_OK)
        {
            return LIS3DSH_OK;
        }
    }
    return LIS3DSH_ERROR;
}

/* config of register CTRL_REG4 */

LIS3DSH_Status_t LIS3DSH_Init(SPI_HandleTypeDef *AxeSPI, LIS3DSH_init_t *AxeInitDef)
{
    uint8_t SPIData[1] = {0x00};																				// initialization of an array named SPIData
    uint8_t SPICheckData[1] = {0x00};																			// initialization of an array named SPICheckData

/* Data register config */
    SPIData[1] |= (AxeInitDef->Axis_X & 0x01);
    SPIData[1] |= (AxeInitDef->Axis_Y & 0x02);
    SPIData[1] |= (AxeInitDef->Axis_Z & 0x04);
    SPIData[1] |= (AxeInitDef->DataUpdateEnable & 0x00);
    SPIData[1] |= (AxeInitDef->OutputDataRate & 0x10);

    if(LIS3DSH_Write_Reg(AxeSPI,LIS3DSH_CTRL_REG4,SPIData,2) == LIS3DSH_OK)										// if the transmission is done correctly we put an OK else return error
    {
        if (LIS3DSH_Read_Reg(AxeSPI,LIS3DSH_CTRL_REG4,SPICheckData,1) == LIS3DSH_OK)							// if the reception is done correctly we put an OK else return error
        {
            if(SPICheckData[0] == SPIData[1])																	// if the answer of data (in SPICheckData) is the same as the data transmit return OK else  return error
            {
                return LIS3DSH_OK;
            }
        }
    }
    return LIS3DSH_ERROR;
}

