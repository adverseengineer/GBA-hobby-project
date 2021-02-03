#ifndef DUNGEON_GEN
#define DUNGEON_GEN

//settings that can be tweaked per build
#define WIDTH 			16
#define HEIGHT 			16
#define NUM_ITER 		6 	//max recursion depth
#define QUAD_FREQ 		102	//40%
#define HORZ_FREQ 		102
#define VERT_FREQ 		102
#define SEED 			693	//TODO: implement vcount at file select as seed
//constants that are used to differentiate walls
#define WALL_WALL		0x0
#define WALL_DOOR		0x1
#define WALL_QJOIN 		0x2
#define WALL_HJOIN 		0x4
#define WALL_VJOIN 		0x8
#define WALL_ANYJOIN	(WALL_QJOIN | WALL_HJOIN | WALL_VJOIN)
//used to signify which error happened when debugging
#define ERR1 			0xBABE
#define ERR2 			0xB00B

void build_dungeon(u32 room_data[], u32 hwall_data[], u32 vwall_data[], const u32 num_iter, const u32 quad_freq, const u32 horz_freq, const u32 vert_freq);
void print_dungeon(const u32 room_data[], const u32 hwall_data[], const u32 vwall_data[]);

#endif
