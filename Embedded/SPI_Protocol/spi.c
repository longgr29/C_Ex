/*
 * spi.c
 *
 *  Created on: May 5, 2023
 *      Author: Long
 */
#include "spi.h"

/*T_ON: time of high pulse (ms)
T_OFF: time of low pulse (ms)*/
#define T_ON 10
#define T_OFF 10

//isMaster: 1 = master, 2 = slave
static uint8_t isMaster = 0;
static GPIO_TypeDef* spiPort;
static uint16_t sclkPin;
static uint16_t mosiPin;
static uint16_t misoPin;
static uint16_t ssPin;

static void spi_transmitByte(uint8_t byte);
static uint8_t spi_receiveByte();

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();


  if (isMaster) {
	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(spiPort, ssPin, 1);
	  HAL_GPIO_WritePin(spiPort, sclkPin|mosiPin, 0);

	  /*Configure input pin: MISO_PIN */
	  GPIO_InitStruct.Pin = misoPin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(spiPort, &GPIO_InitStruct);

	  /*Configure output pin: SCLK_PIN, SS_PIN, MOSI_PIN */
	  GPIO_InitStruct.Pin = sclkPin|mosiPin|ssPin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(spiPort, &GPIO_InitStruct);
  } else {
	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(spiPort, misoPin, 0);

	  /*Configure input pin: SCLK_PIN, SS_PIN, MOSI_PIN */
	  GPIO_InitStruct.Pin = sclkPin|mosiPin|ssPin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(spiPort, &GPIO_InitStruct);

	  /*Configure output pin: MISO_PIN */
	  GPIO_InitStruct.Pin = misoPin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(spiPort, &GPIO_InitStruct);
  }
}

/**
  * @brief Spi Initialization Function For Master MCU
  * @param  SPI_PORT: where GPIOA, GPIOB, etc. to select the GPIO peripheral
  * @param  SCLK_PIN: Specifies the SCLK pins.
  * @param  MOSI_PIN: Specifies the MOSI pins.
  * @param  MISO_PIN: Specifies the MISO pins.
  * @param  SS_PIN: Specifies the SCLK pins.
  * @retval None
  */
void spi_masterInit(GPIO_TypeDef* SPI_PORT, uint16_t SCLK_PIN, uint16_t MOSI_PIN, uint16_t MISO_PIN, uint16_t SS_PIN){
	isMaster = 1;
	spiPort = SPI_PORT;
	sclkPin = SCLK_PIN;
	mosiPin = MOSI_PIN;
	misoPin = MISO_PIN;
	ssPin = SS_PIN;
	MX_GPIO_Init();
}

/**
  * @brief Spi Initialization Function For Slave MCU
  * @param  SPI_PORT: where GPIOA, GPIOB, etc. to select the GPIO peripheral
  * @param  SCLK_PIN: Specifies the SCLK pins.
  * @param  MOSI_PIN: Specifies the MOSI pins.
  * @param  MISO_PIN: Specifies the MISO pins.
  * @param  SS_PIN: Specifies the SCLK pins.
  * @retval None
  */
void spi_slaveInit(GPIO_TypeDef* SPI_PORT, uint16_t SCLK_PIN, uint16_t MOSI_PIN, uint16_t MISO_PIN, uint16_t SS_PIN){
	isMaster = 0;
	spiPort = SPI_PORT;
	sclkPin = SCLK_PIN;
	mosiPin = MOSI_PIN;
	misoPin = MISO_PIN;
	ssPin = SS_PIN;
	MX_GPIO_Init();
}

/**
  * @brief 	Transmit A Byte
  * @param  byte: The byte which is transmitted
  * @retval None
  */
static void spi_transmitByte(uint8_t byte){
	for(uint8_t i = 0; i < 8; i++){
		//transmit from 2^0 bit to 2^7 bit
		HAL_GPIO_WritePin(spiPort, mosiPin, (byte >> i) & 1);
		HAL_Delay(T_OFF);
		HAL_GPIO_WritePin(spiPort, sclkPin, 1);
		HAL_Delay(T_ON);
		HAL_GPIO_WritePin(spiPort, sclkPin, 0);
	}
}

/**
  * @brief 	Transmit A String
  * @param  data: The string which is transmitted
  * @retval None
  */
void spi_transmitData(uint8_t* data){
	unsigned int dataSize = 0;

	while (data[dataSize] != '\0'){
		dataSize++;
	}

	if(isMaster){
		HAL_GPIO_WritePin(spiPort, ssPin|sclkPin, 0);
		for(unsigned int i = 0; i < dataSize; i++){
			spi_transmitByte(*(data + i));
		}
		HAL_GPIO_WritePin(spiPort, ssPin, 1);
	}
}

/**
  * @brief 	Receive A String
  * @param  None
  * @retval A String Which is Transmitted
  */
uint8_t* spi_receiveData(){

	unsigned int dataSize = 1;
	uint8_t* data = (uint8_t*) malloc(1 * sizeof(uint8_t));

	if (!isMaster){
		while (!HAL_GPIO_ReadPin(spiPort, ssPin)){
			*(data + dataSize - 1) = spi_receiveByte();
			data = (uint8_t*) realloc(data, ++dataSize * sizeof(uint8_t));
		}
		uint8_t* rxData = data;
		free(data);
		return rxData;
	}
}

/**
  * @brief 	Receive A Byte
  * @param  None
  * @retval A Byte Which is Transmitted
  */
static uint8_t spi_receiveByte(){
	uint8_t data = 0;
	uint8_t powerOf2 = 1;

	for (uint8_t i = 0; i < 8; i++){

		while(!HAL_GPIO_ReadPin(spiPort, sclkPin)){
			if(HAL_GPIO_ReadPin(spiPort, ssPin)){
				return ' ';
			}
		}
		data += powerOf2 * HAL_GPIO_ReadPin(spiPort, mosiPin);
		powerOf2 *= 2;
		while(HAL_GPIO_ReadPin(spiPort, sclkPin));

	}
	return data;
}
