#include <stdint.h>

#define WIDTH 240
#define HEIGHT 160
#define RGB16(r,g,b) ((r)+(g<<5)+(b<<10))

uint16_t *screen = (void*)0x6000000;

#define FRAME_SEL_BIT		0x10
#define BG2_ENABLE			0x400

int main(void) {
	static volatile uint16_t * const reg_disp_ctl = (void*)0x4000000;

	*reg_disp_ctl = 3 | BG2_ENABLE;
	*reg_disp_ctl &= ~FRAME_SEL_BIT;

	for(uint16_t i = 0; i < WIDTH * HEIGHT; i++)
		screen[i] = 31;

	for(;;);
	return 0;
}
