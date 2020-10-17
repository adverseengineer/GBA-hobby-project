/*
This file contains reusable functions, mostly for debugging
Nick Sells
10/7/2020
*/

#ifndef UTIL_H
#define UTIL_H

//TODO: find a way to make this not even try to execute unless the hardware is in the right mode
//TODO: find a way to make this work with control chars like \n \t like iprintf does
//NOTE: bonus points if you make \a work too
//copied from finlayson
/* function to set text on the screen at a given location */
void set_text(char* str, int row, int col) {
    /* find the index in the texmap to draw to */
    int index = row * 32 + col;

    /* the first 32 characters are missing from the map (controls etc.) */
    int offset = 32;

    /* pointer to text map */
    volatile unsigned short* ptr = 0;//screen_block(24);
	//^^^^ i had to comment that last bit out until i can find a way to guarantee that a font will always be stored in screen block 24

    /* for each character */
    while (*str) {
        /* place this character in the map */
        ptr[index] = *str - offset;

        /* move onto the next character */
        index++;
        str++;
    }
}

#endif