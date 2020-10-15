/*
This file contains macros and functions needed to get input from the GBA buttons
Nick Sells
10/7/2020
*/

#ifndef KEYS_H
#define KEYS_H

#include "gba_macros.h"

//each button is represented by a single bit
//you can AND any of these into the button register to get the button's state
#define KEY_A		0b1
#define KEY_B		0b10
#define KEY_SELECT	0b100
#define KEY_START	0b1000
#define KEY_RIGHT	0b10000
#define KEY_LEFT	0b100000
#define KEY_UP		0b1000000
#define KEY_DOWN	0b10000000
#define KEY_R		0b100000000
#define KEY_L		0b1000000000

//checks whether a button has been pushed or not
static inline u8 key_pressed(u16 key)
{
	//AND the button register with the button constant we want
	return REG_KEYINPUT & key;
}

//TODO: write a function that only returns true in the frame the button is first pressed or released
//TODO: find a way to implement input sequences; eg. punch in the konami code to enable debug features
//IDEA: keep a list of the last n input states (combinations of buttons, because BTN_REG can hold the state of all of them) and use it to check if a code has been input
//IDEA: use bit shifting to pop old states and push new
#endif