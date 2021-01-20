#include <stdio.h>
#include <tonc.h>

int main(void) {

	//enable mode 0 and bg layer 1
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

	//does some kind of initialization.
	tte_init_chr4c_default(0, BG_CBB(0) | BG_SBB(31));

	irq_init(NULL);
	irq_enable(II_VBLANK);

 	int a_presses = 0;
	int b_presses = 0;

	char str_buffer[12];

	while (1) {
		VBlankIntrWait();
		nocash_puts("debug text");

		key_poll();
		if(key_hit(KEY_A))
			a_presses++;
		if(key_hit(KEY_B))
			b_presses++;

		sprintf(str_buffer, "a presses: %3d\n", a_presses);
		tte_set_pos(0, 0);
		tte_write(str_buffer);

		sprintf(str_buffer, "b presses: %3d\n", b_presses);
		tte_set_pos(0, 10);
		tte_write(str_buffer);
	}
}
