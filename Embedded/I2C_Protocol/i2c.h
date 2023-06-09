
#ifndef __I2C_H
#define __I2C_H

#include "main.h"
#include "delay.h"

#define I2C_CLEAR_SDA HAL_GPIO_WritePin(SW_I2C_SDA_GPIO_Port, SW_I2C_SDA_Pin, GPIO_PIN_RESET);
#define I2C_SET_SDA HAL_GPIO_WritePin(SW_I2C_SDA_GPIO_Port, SW_I2C_SDA_Pin, GPIO_PIN_SET);
//#define I2C_READ_SDA {if (HAL_GPIO_ReadPin(SW_I2C_SDA_GPIO_Port, SW_I2C_SDA_Pin)) == GPIO_PIN_SET) return 1; else return 0; return 0;};
#define I2C_CLEAR_SCL HAL_GPIO_WritePin(SW_I2C_SCL_GPIO_Port, SW_I2C_SCL_Pin, GPIO_PIN_RESET);
#define I2C_SET_SCL HAL_GPIO_WritePin(SW_I2C_SCL_GPIO_Port, SW_I2C_SCL_Pin, GPIO_PIN_SET);
#define I2C_DELAY DWT_Delay_us(5); // 5 microsecond delay

//void I2C_bus_init(uint8_t scl_pin, uint8_t sda_pin, uint8_t port);

void I2C_init(void);

void I2C_start_cond(void);

void I2C_stop_cond(void);

void I2C_write_bit(uint8_t b);

uint8_t I2C_read_SDA(void);

// Reading a bit in I2C:
uint8_t I2C_read_bit(void);

uint8_t I2C_write_byte(uint8_t B, uint8_t start, uint8_t stop);

uint8_t I2C_read_byte(uint8_t ack, uint8_t stop);

uint8_t I2C_send_byte(uint8_t address, uint8_t data);

uint8_t I2C_receive_byte(uint8_t address);

uint8_t I2C_send_byte_data(uint8_t address, uint8_t reg, uint8_t data);

uint8_t I2C_receive_byte_data(uint8_t address, uint8_t reg);

uint8_t I2C_transmit(uint8_t address, uint8_t data[], uint8_t size);

uint8_t I2C_receive(uint8_t address, uint8_t reg[], uint8_t *data, uint8_t reg_size, uint8_t size);

#endif /*__STM32_SW_I2C_H */
