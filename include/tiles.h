/*
This file contains functions and macros needed to manage rendering and translating tile layers
Nick Sells
10/7/2020
*/

#ifndef TILES
#define TILES

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

//the display control pointer points to the gba graphics register
volatile unsigned long* display_control = (volatile unsigned long*) 0x4000000;
//pointer to the GBA color palette register
volatile unsigned short* bg_palette = (volatile unsigned short*) 0x5000000;
//GBA color palettes are always 256 colors
#define PALETTE_SIZE 256


volatile unsigned short* bg0_control = (volatile unsigned short*) 0x4000008;
volatile unsigned short* bg1_control = (volatile unsigned short*) 0x400000a;
volatile unsigned short* bg2_control = (volatile unsigned short*) 0x400000c;
volatile unsigned short* bg3_control = (volatile unsigned short*) 0x400000e;

/*
There are two registers that control the scrolling of each background layer
Writing to these will move the corresponding background in the corresponding direction
*/
volatile short* bg0_x_scroll = (volatile short*) 0x4000010;
volatile short* bg0_y_scroll = (volatile short*) 0x4000012;
volatile short* bg1_x_scroll = (volatile short*) 0x4000014;
volatile short* bg1_y_scroll = (volatile short*) 0x4000016;
volatile short* bg2_x_scroll = (volatile short*) 0x4000018;
volatile short* bg2_y_scroll = (volatile short*) 0x400001a;
volatile short* bg3_x_scroll = (volatile short*) 0x400001c;
volatile short* bg3_y_scroll = (volatile short*) 0x400001e;

void scroll_bg(int bg, int x, int y)
{
	//TODO:
}

//TODO:
//in all modes besides the bitmap modes, the gba divides the video memory into 4 character blocks, which are each divided into 8 screen blocks
//to help keep these straight, these methods return pointers to the addresses of these blocks
volatile unsigned short* char_block(unsigned long block)
{
	return (volatile unsigned short*) (0x6000000 + (block * 0x4000));
}

volatile unsigned short* screen_block(unsigned long block)
{
	return (volatile unsigned short*) (0x6000000 + (block * 0x800));
}

//TODO:

#endif