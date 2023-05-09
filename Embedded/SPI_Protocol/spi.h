/*
 * spi.h
 *
 *  Created on: May 5, 2023
 *      Author: a
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32f1xx_hal.h"
#include <stdlib.h>

void spi_masterInit(GPIO_TypeDef* SPI_PORT, uint16_t SCLK_PIN, uint16_t MOSI_PIN, uint16_t MISO_PIN, uint16_t SS_PIN);
void spi_slaveInit(GPIO_TypeDef* SPI_PORT, uint16_t SCLK_PIN, uint16_t MOSI_PIN, uint16_t MISO_PIN, uint16_t SS_PIN);
void spi_transmitData(uint8_t* data);
uint8_t* spi_slaveReceiveData();
uint8_t* spi_masterReceiveData(uint8_t dataSize);

#endif /* INC_SPI_H_ */
