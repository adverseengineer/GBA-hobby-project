/*
This file contains all the code necessary to implement V-sync (or something like it) on the GBA
Nick Sells
10/7/2020
*/

#ifndef VBLANK_H
#define VBLANK_H

#include "gba_macros.h"

//the hardware increments this value every time a row of pixels has been pushed to the screen
//the value keeps increasing even during the vblank. it makes it to 227 before it starts over
#define REG_VCOUNT (*(volatile unsigned short*) 0x04000006)

//waits for the the vblank, which is after the screen has been drawn but before the next one starts drawing
static inline void wait_vblank()
{
	while (REG_VCOUNT < SCREEN_HEIGHT);//do nothing
}

#endif