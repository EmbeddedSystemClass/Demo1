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
}
