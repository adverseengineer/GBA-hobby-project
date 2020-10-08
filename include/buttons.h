/*
This file contains macros and functions needed to get input from the GBA buttons
Nick Sells
10/7/2020
*/

#ifndef BUTTONS
#define BUTTONS

//define a pointer to the button register
#define BTN_REG (*(volatile unsigned short*) 0x04000130)

//each button is represented by a single bit
//you can AND any of these into the button register to get the button's state
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
static inline unsigned char button_pressed(unsigned short button)
{
	//AND the button register with the button constant we want
	//if the bit is 0, the button is pressed, so negate the AND
	return ~(BTN_REG & button);
}

//TODO: write a function that only returns true in the frame the button is first pressed or released
//TODO: find a way to implement input sequences; eg. punch in the konami code to enable debug features

#endif