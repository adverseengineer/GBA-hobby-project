
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <stdio.h>
#include <stdlib.h>

#include "keys.h"

int main(void) {
	//the vblank interrupt must be enabled for VBlankIntrWait() to work
	//since the default dispatcher handles the bios flags no vblank handler is required
	irqInit();
	irqEnable(IRQ_VBLANK);

	consoleDemoInit();

	while (1) {
		VBlankIntrWait();
		iprintf("\x1b[10;0HA pressed: %u", key_pressed(KEY_A));
	}

	//NOTE: thanks to some assembler magic, all variables are placed where they need to go. anything declared as const or a function gets put in rom (0x8000000) and non-const variables get put in IRAM (0x3000000)
}