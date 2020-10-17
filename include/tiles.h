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

//TODO: write a function that modulates the colors in the palette in some way

//these are similiar to the attributes of a sprite. each of the values in these registers packs a bunch of data into its bits
#define REG_BG0CTL *(volatile u16*) 0x4000008
#define REG_BG1CTL *(volatile u16*) 0x400000a
#define REG_BG2CTL *(volatile u16*) 0x400000c
#define REG_BG3CTL *(volatile u16*) 0x400000e

//each of the four backgound layers has two registers to control their movement on the x and y axis
//writing to these will move the corresponding background in the corresponding direction
#define REG_BG0_X *(volatile s16*) 0x4000010
#define REG_BG0_Y *(volatile s16*) 0x4000012
#define REG_BG1_X *(volatile s16*) 0x4000014
#define REG_BG1_Y *(volatile s16*) 0x4000016
#define REG_BG2_X *(volatile s16*) 0x4000018
#define REG_BG2_Y *(volatile s16*) 0x400001a
#define REG_BG3_X *(volatile s16*) 0x400001c
#define REG_BG3_Y *(volatile s16*) 0x400001e

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
//each character block is divided into 8 screen blocks
//these functions return pointers to them
//TODO: verify that these work
static inline volatile u16* char_block(const u64 block) {
    return (volatile unsigned short*) (&REG_VRAM + (block * 0x4000));
}

static inline volatile u16* screen_block(const u64 block) {
	return (volatile u16*) (&REG_VRAM + (block * 0x800));
}

//NOTE: consider using DMA for all of these


//NOTE: the order for loading backgrounds is palette, tiles (tileset, not tilemap), map

//copies the contents of a palette array (typically from a grit header) into palette memory
//TODO: verify this works
static inline void load_palette(u16 new_palette[PALETTE_SIZE]) {
	for(u8 i = 0; i < PALETTE_SIZE; i++)
		(&REG_PALETTE)[i] = new_palette[i];
}

//TODO: verify this works
//NOTE: why do i have to use a 64 bit int?
//NOTE: is this the right way of passing an array?
static inline void load_tiles(const u64 screen_block, const u16 tile_data[], const u16 tile_data_width, const u16 tile_data_height) {
	//declare an int pointer to hold the address of the screen block we want to use
	volatile u16* dest = char_block(screen_block);
	//NOTE: why do i have to declare this at all?
	u16* image = (u16*) tile_data;
	//NOTE: why do i have to divide by 2? (i changed it to a bit shift right by 1 but still why)
	for (int i = 0; i < ((tile_data_width * tile_data_height) >> 1); i++)
		dest[i] = image[i];
}

//TODO: verify this works
static inline void load_map(const u64 char_block, const u16 map_data[], const u16 map_data_width, const u16 map_data_height) {
	//same as before
	volatile u16* dest = screen_block(16);
    for (int i = 0; i < (map_data_width * map_data_height); i++)
        dest[i] = map_data[i];
}

#endif