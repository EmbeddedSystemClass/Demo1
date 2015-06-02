/*
 * DS3231.c
 *
 *  Created on: May 20, 2015
 *      Author: Daniel
 */

#include "i2cdevices.h"

/* Register addresses. */
#define DS3231_I2C_ADDR			0x68	// The I2C address of the DS3231 chip. Default is 1101000 (104 decimal)

#define DS3231_TIME_ADDRESS		0x00	// Start of time register addresses, there are 7 in total (0x00 to 0x06)
#define DS3231_TIME_HOURS		0x02	// Start of the Hours register address.
#define DS3231_TIME_ALARM1		0x07	// Start of the alarm 1 addresses, there are 5 in total.
#define DS3231_TIME_ALARM2		0x0B	// Start of the alarm 2 addresses, there are 4 in total.
#define DS3231_SPECIAL_CONTROL	0x0E	// Control register
#define DS3231_SPECIAL_STATUS	0x0F	// Control / Status register
#define DS3231_SPECIAL_AGEOFF	0X10	// Aging offset
#define DS3231_SPECIAL_TMPMSB	0X11	// MSB of temperature
#define DS3231_SPECIAL_TMPLSB	0X12	// LSB of temperature

/* Control bits. */
#define DS3231_BIT_EOSC			128		// Enable oscillalator
#define DS3231_BIT_BBSQW		64		// Battery-Backed Square-Wave Enable
#define DS3231_BIT_CONV			32		// Convert Temperature
#define DS3231_BIT_RS2			16		// Rate Select
#define DS3231_BIT_RS1			8		// Rate Select
#define DS3231_BIT_INTCN		4		// Interrupt Control
#define DS3231_BIT_A2IE			2		// Alarm 2 Interrupt Enable
#define DS3231_BIT_A1IE			1		// Alarm 1 Interrupt Enable
#define DS3231_BIT_SQW_1Hz		0		// Square-wave output frequency mask
#define DS3231_BIT_SQW_1024Hz	8		// Square-wave output frequency mask
#define DS3231_BIT_SQW_4096Hz	16		// Square-wave output frequency mask
#define DS3231_BIT_SQW_8192Hz	24		// Square-wave output frequency mask
#define DS3231_BIT_AM_PM        32		// AM / PM bit.
#define DS3231_BIT_12_24        64		// 12 / 24 hour mode
#define DS3231_BIT_DYDT         64		// Mask for setting DYDT bit to Day of the week.
#define DS3231_BIT_ALARM		128		// Mask used to set the Alarm range bits.

#define SECONDS_PER_DAY 86400L				// Used by DateTime class
#define SECONDS_FROM_1970_TO_2000 946684800	// Used by DateTime class
