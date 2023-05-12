#include "main.h"
#include "delay.h"
#include "i2c.h"

//void I2C_bus_init(uint8_t scl_pin, uint8_t sda_pin, uint8_t port){
//	  /*Configure GPIO pins : SW_I2C_SCL_Pin SW_I2C_SDA_Pin */
//	  GPIO_InitStruct.Pin = SW_I2C_SCL_Pin|SW_I2C_SDA_Pin;
//	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
//	  GPIO_InitStruct.Pull = GPIO_PULLUP;
//	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//}

#define true 1
#define false 0

/**
  * @brief i2c Initialization Function
  * @param  None
  * @retval None
  */
void I2C_init(void)
{
    I2C_SET_SDA;
    I2C_SET_SCL;
}

/**
  * @brief  start condition
  * @param  None
  * @retval None
  */
void I2C_start_cond(void)
{
    I2C_SET_SCL
    I2C_SET_SDA
    I2C_DELAY
    I2C_CLEAR_SDA
    I2C_DELAY
    I2C_CLEAR_SCL
    I2C_DELAY
}

/**
  * @brief  stop condition
  * @param  None
  * @retval None
  */
void I2C_stop_cond(void)
{
    I2C_CLEAR_SDA
    I2C_DELAY
    I2C_SET_SCL
    I2C_DELAY
    I2C_SET_SDA
    I2C_DELAY
}

/**
  * @brief  write a single bit
  * @param  b: received bit
  * @retval None
  */
void I2C_write_bit(uint8_t b)
{
    if (b > 0)
        I2C_SET_SDA
    else
        I2C_CLEAR_SDA

    I2C_DELAY
    I2C_SET_SCL
    I2C_DELAY
    I2C_CLEAR_SCL
}

/**
  * @brief  read SDA line
  * @param  None
  * @retval status
  */
uint8_t I2C_read_SDA(void)
{
    if (HAL_GPIO_ReadPin(SW_I2C_SDA_GPIO_Port, SW_I2C_SDA_Pin) == GPIO_PIN_SET)
        return 1;
    else
        return 0;
    return 0;
}

/**
  * @brief  Reading a bit in I2C
  * @param  None
  * @retval a bit
  */
uint8_t I2C_read_bit(void)
{
    uint8_t b;

    I2C_SET_SDA
    I2C_DELAY
    I2C_SET_SCL
    I2C_DELAY

    b = I2C_read_SDA();

    I2C_CLEAR_SCL

    return b;
}

/**
  * @brief  Writing a byte in I2C
  * @param  B : a byte
  * @param  start : (1 or 0) add start condition
  * @param  stop : (1 or 0) add stop condition
  * @retval ack bit
  */
uint8_t I2C_write_byte(uint8_t B,
                     uint8_t start,
                     uint8_t stop)
{
    uint8_t ack = 0;

    if (start)
        I2C_start_cond();

    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        I2C_write_bit(B & 0x80); // write the most-significant bit
        B <<= 1;
    }

    ack = I2C_read_bit();

    if (stop)
        I2C_stop_cond();

    return !ack; //0-ack, 1-nack
}

/**
  * @brief  Reading a byte with I2C
  * @param  ack : 1 or 0
  * @param  stop : (1 or 0) add stop condition
  * @retval a byte
  */
uint8_t I2C_read_byte(uint8_t ack, uint8_t stop)
{
    uint8_t B = 0;

    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        B <<= 1;
        B |= I2C_read_bit();
    }

    if (ack)
        I2C_write_bit(0);
    else
        I2C_write_bit(1);

    if (stop)
        I2C_stop_cond();

    return B;
}

/**
  * @brief  Sending a byte with I2C
  * @param  address : address of slave mcu
  * @param  data : received data
  * @retval ack bit
  */
uint8_t I2C_send_byte(uint8_t address,
                    uint8_t data)
{
    //    if( I2C_write_byte( address << 1, true, false ) )   // start, send address, write
    if (I2C_write_byte(address, true, false)) // start, send address, write
    {
        // send data, stop
        if (I2C_write_byte(data, false, true))
            return true;
    }

    I2C_stop_cond(); // make sure to impose a stop if NAK'd
    return false;
}

/**
  * @brief  Receiving a byte with a I2C
  * @param  address : address of slave mcu
  * @retval a byte
  */
uint8_t I2C_receive_byte(uint8_t address)
{
    if (I2C_write_byte((address << 1) | 0x01, true, false)) // start, send address, read
    {
        return I2C_read_byte(false, true);
    }

    return 0; // return zero if NAK'd
}

/**
  * @brief  Sending a byte of data with I2C
  * @param  address : address of slave mcu
  * @param  reg : register
  * @param  data : received data
  * @retval status
  */
uint8_t I2C_send_byte_data(uint8_t address,
                         uint8_t reg,
                         uint8_t data)
{
    //    if( I2C_write_byte( address << 1, true, false ) )   // start, send address, write
    if (I2C_write_byte(address, true, false))
    {
        if (I2C_write_byte(reg, false, false)) // send desired register
        {
            if (I2C_write_byte(data, false, true))
                return true; // send data, stop
        }
    }

    I2C_stop_cond();
    return false;
}

/**
  * @brief  Receiving a byte of data with I2C
  * @param  address : address of slave mcu
  * @param  reg : register
  * @retval a byte
  */
uint8_t I2C_receive_byte_data(uint8_t address,
                              uint8_t reg)
{
    //if( I2C_write_byte( address << 1, true, false ) )   // start, send address, write
    if (I2C_write_byte(address, true, false))
    {
        if (I2C_write_byte(reg, false, false)) // send desired register
        {
            if (I2C_write_byte((address << 1) | 0x01, true, false)) // start again, send address, read
            {
                return I2C_read_byte(false, true); // read data
            }
        }
    }

    I2C_stop_cond();
    return 0; // return zero if NACKed
}

/**
  * @brief  Sending data with I2C
  * @param  address : address of slave mcu
  * @param  data : received data
  * @param  size : data size
  * @retval state
  */
uint8_t I2C_transmit(uint8_t address, uint8_t data[], uint8_t size)
{
    if (I2C_write_byte(address, true, false)) // first byte
    {
        for (int i = 0; i < size; i++)
        {
            if (i == size - 1)
            {
                if (I2C_write_byte(data[i], false, true))
                    return true;
            }
            else
            {
                if (!I2C_write_byte(data[i], false, false))
                    break; //last byte
            }
        }
    }

    I2C_stop_cond();
    return false;
}

/**
  * @brief  Receiving a byte of data with I2C
  * @param  address : address of slave mcu
  * @param  reg : register
  * @param  data : received data variable
  * @param  reg_size : register size
  * @param  size : data size
  * @retval state
  */
uint8_t I2C_receive(uint8_t address, uint8_t reg[], uint8_t *data, uint8_t reg_size, uint8_t size)
{
    if (I2C_write_byte(address, true, false))
    {
        for (int i = 0; i < reg_size; i++)
        {
            if (!I2C_write_byte(reg[i], false, false))
                break;
        }
        if (I2C_write_byte(address | 0x01, true, false)) // start again, send address, read (LSB signifies R or W)
        {
            for (int j = 0; j < size; j++)
            {
                *data++ = I2C_read_byte(false, false); // read data
            }
            I2C_stop_cond();
            return true;
        }
    }
    I2C_stop_cond();
    return false;
}
