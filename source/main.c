
#include <tonc.h>
#include "dungeon_gen.h"

int main(void) {

	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

	tte_init_chr4c_default(0, BG_CBB(0) | BG_SBB(31));
	tte_set_font(&sys8Font);

	sqran(SEED);

	u32 room_data[HEIGHT * WIDTH];
	u32 hwall_data[HEIGHT * WIDTH];
	u32 vwall_data[HEIGHT * WIDTH];

	build_dungeon(room_data, hwall_data, vwall_data, NUM_ITER, QUAD_FREQ, HORZ_FREQ, VERT_FREQ);
	print_dungeon(room_data, hwall_data, vwall_data);
	tte_set_pos(0, 0);

	char str_buf[128];
	sprintf(str_buf, "%s", " ");
	tte_write(str_buf);

	while (1) {
		vid_vsync();
	}
}
