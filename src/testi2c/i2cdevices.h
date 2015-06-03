/*
 * i2cdevices.h
 *
 *  Created on: May 20, 2015
 *      Author: Daniel
 */

#ifndef TESTI2C_I2CDEVICES_H_
#define TESTI2C_I2CDEVICES_H_

#include <stdio.h>
#include "stm32f10x.h"
#include "FreeRTOS.h"

#define I2C_SPEED               100000
#define I2C_SLAVE_ADDRESS7      0xA0

#define sEE_I2C                          I2C2
#define sEE_I2C_CLK                      RCC_APB1Periph_I2C2

#define sRTC_I2C						 I2C2

#define sEE_I2C_SCL_PIN                  GPIO_Pin_10                  /* PB.10 */
#define sEE_I2C_SCL_GPIO_PORT            GPIOB                       /* GPIOB */
#define sEE_I2C_SCL_GPIO_CLK             RCC_APB2Periph_GPIOB
#define sEE_I2C_SDA_PIN                  GPIO_Pin_11                  /* PB.11 */
#define sEE_I2C_SDA_GPIO_PORT            GPIOB                       /* GPIOB */
#define sEE_I2C_SDA_GPIO_CLK             RCC_APB2Periph_GPIOB


// RTC DS3231和EEPROM公用一个I2C，不需要另外定义了。

void InitI2C();
BaseType_t I2C_Read(I2C_TypeDef* I2Cx, uint8_t *buf, uint32_t nbyte, uint8_t SlaveAddress);
BaseType_t I2C_Write(I2C_TypeDef* I2Cx, const uint8_t* buf, uint32_t nbyte,	uint8_t SlaveAddress);

BaseType_t InitDS3231();
BaseType_t GetRTC_DS3231();

#endif /* TESTI2C_I2CDEVICES_H_ */
