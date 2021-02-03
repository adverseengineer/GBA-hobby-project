#ifndef DUNGEON_GEN
#define DUNGEON_GEN

//settings that can be tweaked per build
#define WIDTH 16
#define HEIGHT 16
#define NUM_ITER 6
#define QUAD_FREQ 102
#define HORZ_FREQ 102
#define VERT_FREQ 102
#define SEED 69420
//constants that are used to differentiate walls
#define WALL_NORMAL 0
#define WALL_BREAKABLE 1
#define WALL_BROKEN 2
#define WALL_QJOIN 3
#define WALL_HJOIN 4
#define WALL_VJOIN 5
#define WALL_DOOR_UNLOCKED 6
#define WALL_DOOR_LOCKED 7
//used to signify which error happened when debugging
#define ERR1 0xBABE
#define ERR2 0xB00B

void build_dungeon(u32 room_data[], u32 hwall_data[], u32 vwall_data[], const u32 num_iter, const u32 quad_freq, const u32 horz_freq, const u32 vert_freq);
void print_dungeon(const u32 room_data[], const u32 hwall_data[], const u32 vwall_data[]);

#endif
