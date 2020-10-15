/*
This file contains macros and functions needed to get input from the GBA buttons
Nick Sells
10/15/2020
*/

#ifndef SPRITES_H
#define SPRITES_H

#include "gba_macros.h"
#include "dma.h"

//the GBA can handle up to 128 sprites at once
#define MAX_SPRITES 128

//each sprite has four 16-bit values which each pack a number of values together
typedef struct {
	u16 attribute0;
	u16 attribute1;
	u16 attribute2;
	u16 attribute3;
} Sprite;
/*====================================================================================================
Attribute 0
	bits 0-7	y coordinate
	bits 8,9	affine
		used for specifying affine transformations
	bits 10,11	effect
		toggles between alpha-blending and masking
	bit 12		mosaic
		toggles the "mosaic effect"
	bit 13		color mode
		0 = 16-color
		1 = 256-color
	bits 14,15	shape
		see below
Attribute 1
	bits 0-7	x coordinate
	bits 9-11	unused
	bit 12		h-flip
		flips the sprite horizontally
	bit 13		v-flip
		flips the sprite vertically
	bits 14,15	size
Attribute 2
	bits 0-9	tile index
		the index of the first tile in the sprite.
		//FIXME: add better information
	bits 10,11	priority
		used for layering. low appears over high. sprites appear over backgrounds of the same priority
	bits 12-15	palette bank
		only used for 16-bit color sprites
Attribute 3
	used internally by the gba to handle affine transformations
======================================================================================================

The dimensions of the sprite are determined by the size and shape properties, as per this table:
			Size
			0		1		2		3
Shape	0	8x8		16x16	32x32	64x64
		1	16x8	32x8	32x16	64x32
		2	8x16	8x32	16x32	32x64 */

//an array to store every sprite
Sprite sprites[MAX_SPRITES];
//an int to remember how many sprites have been set up already
int next_sprite_index = 0;
//this isn't permanent, however. You can only update OAM during VBlank, so we copy this array to OAM using DMA

//an enum of sprite sizes to simplify the lookup
const enum SpriteSize {
	SIZE_8x8, SIZE_16x16, SIZE_32x32, SIZE_64x64,
	SIZE_16x8, SIZE_32x8, SIZE_32x16, SIZE_64x32,
	SIZE_8x16, SIZE_8x32, SIZE_16x32, SIZE_32x64
};

//TODO: decide if i should use finlayson's code or search tonc
//NOTE: it doesn't have to be perfect just yet, it just has to work

//initializes a sprite in the temporary sprite array
static inline Sprite* sprite_init(const u16 x, const u16 y, const enum SpriteSize size, const u16 h_flip, const u16 v_flip, const u16 tile_index, const u16 priority) {
	u16 index = next_sprite_index++;
	u8 size_bits, shape_bits;

	//do the lookup for the size and shape bits
	switch (size) {
		case SIZE_8x8:		size_bits = 0; shape_bits = 0; break;
		case SIZE_16x16:	size_bits = 1; shape_bits = 0; break;
		case SIZE_32x32:	size_bits = 2; shape_bits = 0; break;
		case SIZE_64x64:	size_bits = 3; shape_bits = 0; break;
		case SIZE_16x8: 	size_bits = 0; shape_bits = 1; break;
		case SIZE_32x8: 	size_bits = 1; shape_bits = 1; break;
		case SIZE_32x16:	size_bits = 2; shape_bits = 1; break;
		case SIZE_64x32:	size_bits = 3; shape_bits = 1; break;
		case SIZE_8x16:		size_bits = 0; shape_bits = 2; break;
		case SIZE_8x32:		size_bits = 1; shape_bits = 2; break;
		case SIZE_16x32:	size_bits = 2; shape_bits = 2; break;
		case SIZE_32x64:	size_bits = 3; shape_bits = 2; break;
    }

	u16 h = h_flip ? 1 : 0;
	u16 v = v_flip ? 1 : 0;

	sprites[index].attribute0 = y |
							(0 << 8) |
							(0 << 10) |
							(0 << 12) |
							(1 << 13) |
							(shape_bits << 14);

	sprites[index].attribute1 = x |
							(0 << 9) |
							(h << 12) |
							(v << 13) |
							(size_bits << 14);

	sprites[index].attribute2 = tile_index |
							(priority << 10) |
							(0 << 12);

	return &sprites[index];	
}

//changes a sprite's position
static inline void sprite_position(Sprite* sprite, const u16 x, const u16 y) {
	sprite->attribute0 &= 0xff00;//mask out the y coord in attrib0
	sprite->attribute0 |= (y & 0xff);//trim the y to fit and insert it into attrib0
	sprite->attribute1 &= 0xfe00;
	sprite->attribute1 |= (x & 0x1ff);
}

//moves a sprite
static inline void sprite_move(Sprite* sprite, const s16 dx, const s16 dy) {
	const u16 y = sprite->attribute0 & 0xff;
	const u16 x = sprite->attribute1 & 0x1ff;

	sprite_position(sprite, x + dx, y + dy);
}

//toggles v_flip on the sprite
static inline void sprite_set_v_flip(Sprite* sprite, const u16 v_flip) {
	if(v_flip)
		sprite->attribute1 |= 0x2000;
	else
		sprite->attribute1 &= 0xdfff;
}

//toggles h_flip on the sprite
static inline void sprite_set_h_flip(Sprite* sprite, const u16 h_flip) {
	if(h_flip)
		sprite->attribute1 |= 0x1000;
	else
		sprite->attribute1 &= 0xefff;
}

//changes a sprite's tile offset
static inline void sprite_set_offset(Sprite* sprite, const u16 offset) {
	sprite->attribute2 &= 0xfc00;
	sprite->attribute2 |= (offset & 0x03ff);
}

//copy the temp sprite array to OAM
static inline void sprite_update_all() {
	dma_memcpy16(REG_OAM, (u16*) sprites, MAX_SPRITES * sizeof(Sprite));
}

#endif