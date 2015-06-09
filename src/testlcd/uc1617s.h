/*
 * u1617s.h
 *
 *  Created on: Apr 23, 2015
 *      Author: Daniel
 */

#ifndef TESTLCD_UC1617S_H_
#define TESTLCD_UC1617S_H_

#include "stm32f10x.h"

#define sLCD_SPI						SPI2
#define sLCD_SPI_CLK					RCC_APB1Periph_SPI2

#define sLCD_SPI_SCK_PIN				GPIO_Pin_13					/* PB.13 */
#define sLCD_SPI_SCK_GPIO_PORT			GPIOB                       /* GPIOB */
#define sLCD_SPI_SCK_GPIO_CLK			RCC_APB2Periph_GPIOB

#define sLCD_CD_PIN						GPIO_Pin_14					/* PB.14 */
#define sLCD_CD_GPIO_PORT				GPIOB                       /* GPIOB */
#define sLCD_CD_GPIO_CLK				RCC_APB2Periph_GPIOB

#define sLCD_SPI_MOSI_PIN				GPIO_Pin_15					/* PB.15 */
#define sLCD_SPI_MOSI_GPIO_PORT			GPIOB                       /* GPIOB */
#define sLCD_SPI_MOSI_GPIO_CLK			RCC_APB2Periph_GPIOB

#define sLCD_CS_PIN						GPIO_Pin_12                  /* PB.12 */
#define sLCD_CS_GPIO_PORT				GPIOB                      /* GPIOB */
#define sLCD_CS_GPIO_CLK				RCC_APB2Periph_GPIOB

// LCD Backlight(Use PWM output pin)
//#define sLCD_LED_PIN					GPIO_Pin_
//#define sLCD_LED_GPIO_PORT				GPIO
//#define sLCD_LED_GPIO_CLK				RCC_APB2Periph_GPIO

/**
  * @brief  LCD controller U1617s supported commands
  */
#define sLCD_CMD_WRITE          0x02  /*!< Write to Memory instruction */
#define sLCD_CMD_WRSR           0x01  /*!< Write Status Register instruction */
#define sLCD_CMD_WREN           0x06  /*!< Write enable instruction */
#define sLCD_CMD_READ           0x03  /*!< Read from Memory instruction */
#define sLCD_CMD_RDSR           0x05  /*!< Read Status Register instruction  */
#define sLCD_CMD_RDID           0x9F  /*!< Read identification */
#define sLCD_CMD_SE             0xD8  /*!< Sector Erase instruction */
#define sLCD_CMD_BE             0xC7  /*!< Bulk Erase instruction */

#define sLCD_UC1617s_ID          0x202017

/**
  * @brief  Select sLCD: Chip Select pin low
  */
#define sLCD_CS_LOW()       GPIO_ResetBits(sLCD_CS_GPIO_PORT, sLCD_CS_PIN)
/**
  * @brief  Deselect sLCD: Chip Select pin high
  */
#define sLCD_CS_HIGH()      GPIO_SetBits(sLCD_CS_GPIO_PORT, sLCD_CS_PIN)

#define sLCD_CD_COMMAND()	GPIO_ResetBits(sLCD_CD_GPIO_PORT, sLCD_CD_PIN)		// Command
#define sLCD_CD_DATA()		GPIO_SetBits(sLCD_CD_GPIO_PORT, sLCD_CD_PIN)		// Data

void InitUC1617s(void);

#endif /* TESTLCD_UC1617S_H_ */
