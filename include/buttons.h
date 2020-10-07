/*
This file contains macros and functions needed to get input from the GBA buttons
Nick Sells
10/7/2020
*/

#ifndef BUTTONS
#define BUTTONS

//define a pointer to the button register
volatile unsigned short* buttons = (volatile unsigned short*) 0x04000130;

//define a macro for each of the buttons.
//each button is represented by a single bit
//you can AND any of these into the button register to get those button's states
#define BUTTON_A (1 << 0)
#define BUTTON_B (1 << 1)
#define BUTTON_SELECT (1 << 2)
#define BUTTON_START (1 << 3)
#define BUTTON_RIGHT (1 << 4)
#define BUTTON_LEFT (1 << 5)
#define BUTTON_UP (1 << 6)
#define BUTTON_DOWN (1 << 7)
#define BUTTON_R (1 << 8)
#define BUTTON_L (1 << 9)

//checks whether a button has been pushed or not
unsigned char button_pressed(unsigned short button)
{
	//AND the button register with the button constant we want
	//if this value is zero, it's not pressed
	if (*buttons & button == 0)
		return 1;
	else {
		return 0;
}

#endif