/*
 * uc1617s.c
 *
 *  Created on: Apr 23, 2015
 *      Author: Daniel
 */

#include "uc1617s.h"
#include "FreeRTOS.h"
#include "task.h"

void sLCD_SendByte(uint8_t byte);

void InitUC1617s(void)
{
	// 初始化SPI使用的管脚和时钟，以及额外的GPIO
	// 使用SPI2
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	/*!< sLCD_SPI_CS_GPIO, sLCD_SPI_MOSI_GPIO, sLCD_SPI_MISO_GPIO
	 and sLCD_SPI_SCK_GPIO Periph clock enable */
	RCC_APB2PeriphClockCmd(
			sLCD_CS_GPIO_CLK | sLCD_SPI_MOSI_GPIO_CLK | sLCD_CD_GPIO_CLK |
			sLCD_SPI_SCK_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

	/*!< sLCD_SPI Periph clock enable */
	RCC_APB1PeriphClockCmd(sLCD_SPI_CLK, ENABLE);

	/*!< Configure sLCD_SPI pins: SCK */
	GPIO_InitStructure.GPIO_Pin = sLCD_SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(sLCD_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure sLCD_SPI pins: MOSI */
	GPIO_InitStructure.GPIO_Pin = sLCD_SPI_MOSI_PIN;
	GPIO_Init(sLCD_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure sLCD_SPI pins: CD */
	GPIO_InitStructure.GPIO_Pin = sLCD_CD_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(sLCD_CD_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure sLCD_CS_PIN pin: sLCD Card CS pin */
	GPIO_InitStructure.GPIO_Pin = sLCD_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(sLCD_CS_GPIO_PORT, &GPIO_InitStructure);

	/*!< Deselect the LCD: Chip Select high */
	sLCD_CS_HIGH();

	/*!< SPI configuration */
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
#else
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
#endif

	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(sLCD_SPI, &SPI_InitStructure);

	/*!< Enable the sLCD_SPI  */
	SPI_Cmd(sLCD_SPI, ENABLE);

	// 初始化LCD控制器
	sLCD_CS_LOW();
	sLCD_CD_COMMAND();

	// 软件Reset
	sLCD_SendByte(0xE2);
	// 延迟等待复位成功
	// vTaskDelay(10 / portTICK_RATE_MS);
	//
	sLCD_SendByte(0x27);
	sLCD_SendByte(0x2b);
	sLCD_SendByte(0x2f);
	sLCD_SendByte(0xeb);
	sLCD_SendByte(0x81);
	sLCD_SendByte(0x36);
	sLCD_SendByte(0xa9);
	sLCD_SendByte(0xc8);
	sLCD_SendByte(0x04);
	sLCD_SendByte(0x89);
	sLCD_SendByte(0xc4);
	sLCD_SendByte(0xf1);
	sLCD_SendByte(0x7f);
	//sLCD_SendByte(0xd3);
	//sLCD_SendByte(0xd7);
	sLCD_SendByte(0xaf);	// Enable display

	sLCD_SendByte(0xA5);	// Test:All pixel on.
}

/**
  * @brief  Sends a byte through the SPI interface and return the byte received
  *         from the SPI bus.
  * @param  byte: byte to send.
  */
void sLCD_SendByte(uint8_t byte)
{
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(sLCD_SPI, SPI_I2S_FLAG_TXE) == RESET)
		;

	/*!< Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(sLCD_SPI, byte);

//	/*!< Wait to receive a byte */
//	while (SPI_I2S_GetFlagStatus(sLCD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
//		;
}
