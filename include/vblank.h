/*
This file contains all the code necessary to implement V-sync (or something like it) on the GBA
Nick Sells
10/7/2020
*/

#ifndef VBLANK
#define VBLANK

#include "gba_macros.h"

//define a pointer for the scanline counter
//the hardware updates the vale at this address every time a row of pixels has been pushed to the screen
volatile unsigned short* scanline_counter = (volatile unsigned short*) 0x4000006;

//waits for the the vblank, which is when the screen has finished updating for this frame
void wait_vblank()
{
	while (*scanline_counter < HEIGHT) {}
}

#endif