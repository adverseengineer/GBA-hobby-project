
#include <tonc.h>
#include "dungeon_gen.h"

int main(void) {

	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

	tte_init_chr4c_default(0, BG_CBB(0) | BG_SBB(31));
	tte_set_font(&sys8Font);

	irq_init(NULL);
	irq_enable(II_VBLANK);

	sqran(SEED);

	u32 room_data[HEIGHT * WIDTH];
	u32 hwall_data[HEIGHT * WIDTH];
	u32 vwall_data[HEIGHT * WIDTH];

	char sb[64];
	sprintf(sb, "addr of fn: %p", print_dungeon);
	tte_write(sb);

	build_dungeon(room_data, hwall_data, vwall_data, NUM_ITER, QUAD_FREQ, HORZ_FREQ, VERT_FREQ);
	print_dungeon(room_data, hwall_data, vwall_data);

	while (1) {
		VBlankIntrWait();
		key_poll();
		if(key_hit(KEY_A)) {
			tte_erase_screen();
			build_dungeon(room_data, hwall_data, vwall_data, NUM_ITER, QUAD_FREQ, HORZ_FREQ, VERT_FREQ);
			print_dungeon(room_data, hwall_data, vwall_data);
		}
	}
}
