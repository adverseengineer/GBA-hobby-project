/*
This file contains macros that are needed across all files
Nick Sells
10/7/2020
*/

#ifndef GBA_MACROS_H
#define GBA_MACROS_H

#include <stdint.h>

//shorthand defines for the std ints
#define s8 int8_t
#define s16 int16_t
#define s32 int32_t
#define s64 int64_t
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

//the resolution of the GBA screen
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

//The GBA has 6 video modes, 3 for tiles and 3 for bitmaps
#define MODE0 0 //four tile layers, but none of them can be rotated or scaled
#define MODE1 1 //three tile layers, but only one of them can be rotated and scaled
#define MODE2 2 //only two tile layers, but both can be rotated and scaled
#define MODE3 3 //regular bitmap. any pixel can be given any color
#define MODE4 4 //same as mode 3, but lower resolution in exchange for page flipping
#define MODE5 5 //same as the SNES mode 7. pseudo-3d by scaling and shearing a bitmap

//pointer to the display control register
#define REG_DCTRL *(volatile u16*) 0x04000000
//pointer to the button register (inverted, because it is active-low)
#define REG_KEYINPUT ~(*(volatile u16*) 0x04000130)
//pointer to the screen
#define REG_VRAM *(volatile u16*) 0x06000000
//pointer to sprite memory
#define REG_OAM *(volatile u16*) 0x07000000

//helper macro to build 16 bit colors
#define RGB16(r,g,b) ((r)+(g<<5)+(b<<10))

//TODO: write a function that reaches into memory of an aleady running game and tells you what video mode is being used

#endif