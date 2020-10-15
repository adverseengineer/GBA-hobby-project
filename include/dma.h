/*
This file contains functions and macros needed to use DMA on the GBA
Nick Sells
10/7/2020
*/

#ifndef DMA_H
#define DMA_H

#include "gba_macros.h"

//TODO: clean up this whole file

//dma enable flag
#define DMA_ENABLE 0x80000000

//dma transfer size flags
#define DMA_16 0x00000000
#define DMA_32 0x04000000

//pointers to the dma registers
#define dma_source (*(volatile unsigned int*) 0x40000D4)
#define dma_destination (*(volatile unsigned int*) 0x40000D8)
#define dma_count (*(volatile unsigned int*) 0x40000DC)

/* copy data using DMA */
static inline void dma_memcpy16(volatile u16* dest, volatile u16* source, const u32 amount)
{
	dma_source = (unsigned int) source;
    dma_destination = (unsigned int) dest;
    dma_count = amount | DMA_16 | DMA_ENABLE;
}

//TODO: finish this file

#endif