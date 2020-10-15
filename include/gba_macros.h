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

//pointer to the screen
#define REG_VRAM (volatile u16*) 0x06000000
//pointer to sprite memory
#define REG_OAM (volatile u16*) 0x07000000
//pointer to the button register
//go ahead and invert it, because it is active-low
#define REG_KEYINPUT ~(*(volatile u16*) 0x04000130)

//helper macro to build 16 bit colors
#define RGB16(r,g,b) ((r)+(g<<5)+(b<<10))

#endif