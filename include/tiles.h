/*
This file contains functions and macros needed to manage rendering and translating tile layers
Nick Sells
10/7/2020
*/

#ifndef TILES_H
#define TILES_H

#include "gba_macros.h"

//enable bits for the four background layers and the sprite layer; OR them into REG_DCTRL to use them
#define BG0_ENABLE 0x0100
#define BG1_ENABLE 0x0200
#define BG2_ENABLE 0x0400
#define BG3_ENABLE 0x0800
#define OBJ_ENABLE 0x1000

//pointer to the GBA color palette register
#define REG_PALETTE *(volatile u16*) 0x05000000
//GBA color palettes are always 256 colors
#define PALETTE_SIZE 256

//copies the contents of a palette array (typically from a grit header) into palette memory
//TODO: verify this works
static inline void load_palette(u16 new_palette[PALETTE_SIZE]) {
	for(u8 i = 0; i < PALETTE_SIZE; i++)
		(&REG_PALETTE)[i] = new_palette[i];
}

//these are similiar to the attributes of a sprite. each of the values in these registers packs a bunch of data into its bits
#define bg0_control *(volatile u16*) 0x4000008
#define bg1_control *(volatile u16*) 0x400000a
#define bg2_control *(volatile u16*) 0x400000c
#define bg3_control *(volatile u16*) 0x400000e

//each of the four backgound layers has two registers to control their movement on the x and y axis
//writing to these will move the corresponding background in the corresponding direction
#define bg0_x_scroll *(volatile s16*) 0x4000010
#define bg0_y_scroll *(volatile s16*) 0x4000012
#define bg1_x_scroll *(volatile s16*) 0x4000014
#define bg1_y_scroll *(volatile s16*) 0x4000016
#define bg2_x_scroll *(volatile s16*) 0x4000018
#define bg2_y_scroll *(volatile s16*) 0x400001a
#define bg3_x_scroll *(volatile s16*) 0x400001c
#define bg3_y_scroll *(volatile s16*) 0x400001e

//scroll the specified background the given amounts
static inline void scroll_bg(const u16 background, const s16 x, const s16 y)
{
	//TODO:
}

//sets the backgrounds position to the given coords
static inline void move_bg(int bg, int x, int y)
{
	//TODO:
}

//when using tile modes, the GBA divides the VRAM into 4 character blocks that are used to store the data for each background layer
#define REG_CHBLOCK0 *(volatile s16*) 0x06000000
#define REG_CHBLOCK1 *(volatile s16*) 0x06004000
#define REG_CHBLOCK2 *(volatile s16*) 0x06008000
#define REG_CHBLOCK3 *(volatile s16*) 0x0600c000

//FIXME: why is this function necessary? i got it from the finlayson tutorial
//each char are each divided into 8 screen blocks
static inline volatile u16* screen_block(const u64 block)
{
	return (volatile u16*) (&REG_VRAM + (block * 0x800));
}

#endif