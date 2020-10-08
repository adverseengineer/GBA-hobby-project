/*
This file contains functions and macros needed to manage rendering and translating tile layers
Nick Sells
10/7/2020
*/

#ifndef TILES_H
#define TILES_H

#include "gba_macros.h"

/*
The GBA has three tile modes.
Mode 0:	four tile layers, but none of them can be rotated or scaled
Mode 1: three tile layers, but only one of them can be rotated and scaled
Mode 2:	only two tile layers, but both can be rotated and scaled
*/
#define MODE0 0x00
#define MODE1 0x01
#define MODE2 0x02

/*
These are the enable bits for the four background layers
To use them to enable a background, you OR them into the display_control register
*/
#define BG0_ENABLE 0x100
#define BG1_ENABLE 0x200
#define BG2_ENABLE 0x400
#define BG3_ENABLE 0x800

//define a pointer to the GBA graphics control register
#define DCTRL_REG (*(volatile unsigned long*) 0x4000000);
//pointer to the GBA color palette register
volatile unsigned short* bg_palette = (volatile unsigned short*) 0x5000000;
//GBA color palettes are always 256 colors
#define PALETTE_SIZE 256


#define bg0_control (*(volatile unsigned short*) 0x4000008)
#define bg1_control (*(volatile unsigned short*) 0x400000a)
#define bg2_control (*(volatile unsigned short*) 0x400000c)
#define bg3_control (*(volatile unsigned short*) 0x400000e)

//each of the four backgound layers has two registers to control their movement on the x and y axis
//writing to these will move the corresponding background in the corresponding direction
#define bg0_x_scroll (*(volatile short*) 0x4000010)
#define bg0_y_scroll (*(volatile short*) 0x4000012)
#define bg1_x_scroll (*(volatile short*) 0x4000014)
#define bg1_y_scroll (*(volatile short*) 0x4000016)
#define bg2_x_scroll (*(volatile short*) 0x4000018)
#define bg2_y_scroll (*(volatile short*) 0x400001a)
#define bg3_x_scroll (*(volatile short*) 0x400001c)
#define bg3_y_scroll (*(volatile short*) 0x400001e)

//scroll the specified background the given amounts
static inline void scroll_bg(int bg, int x, int y)
{
	//TODO:
}

//sets the backgrounds position to the given coords
static inline void move_bg(int bg, int x, int y)
{
	//TODO:
}

//TODO: why do i need this?
//FIXME: give this a better name
//when using tile modes, the GBA divides the VRAM into 4 blocks that are used to store the data for each background layer
//to help keep these straight, these methods return pointers to the addresses of these blocks
static inline volatile unsigned short* getBgBlockPtr(unsigned long block)
{
	return (volatile unsigned short*) (0x6000000 + (block * 0x4000));
}

//FIXME: why is this function necessary? i got it from the finlayson tutorial
//each char are each divided into 8 screen blocks
static inline volatile unsigned short* screen_block(unsigned long block)
{
	return (volatile unsigned short*) (0x6000000 + (block * 0x800));
}

//TODO:

#endif