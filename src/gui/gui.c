/*
 * gui.c
 *
 *  Created on: Jun 7, 2015
 *      Author: daniel
 */

#include "gui.h"
#include "../ugfx/gfx.h"

void InitGUI();
void test();

// GUI线程。因为只能在FreeRTOS初始化后，才能进行初始化
void GUITask( void * pvParameters)
{
	(void)pvParameters;

	InitGUI();

	test();
}

void InitGUI()
{
	// 初始化ugfx
	gfxInit();

	// 设置默认对比度（对于OLED就是亮度）
	gdispSetContrast(40);
}

void test()
{
	font_t		font;
	GHandle GW1, GW2, GW3;
	int			i;

	// 测试gfx
	gfxInit();
	//gdispDrawLine(0, 0, 0, 50, 1);
	//gdispFlush();
	//gdispDrawLine(50, 50, 50, 0, 1);
	//gdispFlush();

	font = gdispOpenFont("fixed_5x8");
	gdispDrawString(0, 0, "This is test.", font, 1);
	gdispCloseFont(font);
	gdispFlush();

	font = gdispOpenFont("LargeNumbers");
	gdispDrawString(0, 10, "12:30", font, 1);
	gdispCloseFont(font);
	gdispFlush();

	gdispSetPowerMode(powerOff);
	gdispSetPowerMode(powerOn);

	gdispSetContrast(50);
	gdispSetContrast(0);
	gdispSetContrast(100);
	gdispSetContrast(50);

	vTaskDelay(3000 / portTICK_RATE_MS);

	// test consle
	font = gdispOpenFont("UI2");

	{
	  GWindowInit		wi;

	  wi.show = TRUE;
	  wi.x = 0; wi.y = 0; wi.width = gdispGetWidth(); wi.height = gdispGetHeight();
	  GW1 = gwinConsoleCreate(0, &wi);
	}

	gwinSetFont(GW1, font);
	gwinSetColor(GW1, 1);
	gwinClear(GW1);
	gdispFlush();

	// write console
	i = 0;
	while (TRUE)
	{
	  gwinPrintf(GW1,"Test \033bnumber \033B%d.\r\n", i++);
	  gdispFlush();
	  gfxSleepMilliseconds(1000);
	}
}
