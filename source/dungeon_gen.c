#include <stdio.h>

#include <tonc.h>

#include "dungeon_gen.h"

//getter and setters for the three arrays that make up the dungeon
static inline u32 get_elem(const u32 data[], const u32 x, const u32 y) {
	return data[WIDTH * y + x];
}
static inline void set_elem(u32 data[], const u32 x, const u32 y, const u32 val) {
	data[WIDTH * y + x] = val;
}

//gets the wall value that lies between the room coords given
static inline u32 get_wall_between(const u32 hwall_data[], const u32 vwall_data[], const u32 x1, const u32 y1, const u32 x2, const u32 y2) {
	//sanity check
	//TODO: remove these after the generator works perfectly
	if((x1 == x2) & (y1 == y2)) return ERR1; //points are the same
	if((ABS(x1 - x2) > 1) & (ABS(y1 - y2) > 1)) return ERR2; //points aren't adjacent
	//doors are associated with the room above or to the left of them.
	//therefore, the upper-leftmost room of any adjacent pair will always be the one whose coords are the same as the door
	//if the rooms are horizontally adjacent
	if(y1 == y2)
		return get_elem(hwall_data, min(x1, x2), min(y1, y2));
	else
		return get_elem(vwall_data, min(x1, x2), min(y1, y2));
}
//sets the wall value that lies between the room coords given
static inline void set_wall_between(u32 hwall_data[], u32 vwall_data[], const u32 x1, const u32 y1, const u32 x2, const u32 y2, const u32 val) {
	//sanity check
	//TODO: remove these after the generator works perfectly
	if((x1 == x2) & (y1 == y2)) return; //points are the same
	if((ABS(x1 - x2) > 1) & (ABS(y1 - y2) > 1)) return; //points aren't adjacent
	//doors are associated with the room above or to the left of them.
	//therefore, the upper-leftmost room of any adjacent pair will always be the one whose coords are the same as the door
	//if the rooms are horizontally adjacent
	if(y1 == y2)
		set_elem(hwall_data, min(x1, x2), min(y1, y2), val);
	else
		set_elem(vwall_data, min(x1, x2), min(y1, y2), val);
}

//loops over room_data and finds 2x2 groups of rooms. each group is given a (freq/255)% chance to merge
static inline void make_qrooms(const u32 room_data[], u32 hwall_data[], u32 vwall_data[], u32 freq) {
	//for every cell in room_data
	for(u32 y = 0; y < HEIGHT; y++) {
		for(u32 x = 0; x < WIDTH; x++) {
			//if the rng check passes
			if(qran_range(0, 256) < freq) {
				//if a 2x2 group exists here
				if((get_elem(room_data, x, y) > 0)
				& (get_elem(room_data, x + 1, y) > 0)
				& (get_elem(room_data, x, y + 1) > 0)
				& (get_elem(room_data, x + 1, y + 1) > 0)) {
					//if they are all connected by doors or normal walls
					if(((get_wall_between(hwall_data, vwall_data, x, y, x + 1, y) == WALL_DOOR_UNLOCKED) | (get_wall_between(hwall_data, vwall_data, x, y, x + 1, y) == WALL_NORMAL))
					& ((get_wall_between(hwall_data, vwall_data, x + 1, y, x + 1, y + 1) == WALL_DOOR_UNLOCKED) | (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 1, y + 1) == WALL_NORMAL))
					& ((get_wall_between(hwall_data, vwall_data, x + 1, y + 1, x, y + 1) == WALL_DOOR_UNLOCKED) | (get_wall_between(hwall_data, vwall_data, x + 1, y + 1, x, y + 1) == WALL_NORMAL))
					& ((get_wall_between(hwall_data, vwall_data, x, y + 1, x, y) == WALL_DOOR_UNLOCKED) | (get_wall_between(hwall_data, vwall_data, x, y + 1, x, y) == WALL_NORMAL))) {
						//this huge block of conditions checks every wall connected to the candidate group. if ANY of them are already joined, the group is discarded
						if((get_wall_between(hwall_data, vwall_data, x, y, x, y - 1) != WALL_QJOIN)
						& (get_wall_between(hwall_data, vwall_data, x, y, x, y - 1) != WALL_HJOIN)
	                    & (get_wall_between(hwall_data, vwall_data, x, y, x, y - 1) != WALL_VJOIN)
						& (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 1, y - 1) != WALL_QJOIN)
	                    & (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 1, y - 1) != WALL_HJOIN)
	                    & (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 1, y - 1) != WALL_VJOIN)
						& (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 2, y) != WALL_QJOIN)
						& (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 2, y) != WALL_HJOIN)
	                    & (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 2, y) != WALL_VJOIN)
						& (get_wall_between(hwall_data, vwall_data, x + 1, y + 1, x + 2, y + 1) != WALL_QJOIN)
						& (get_wall_between(hwall_data, vwall_data, x + 1, y + 1, x + 2, y + 1) != WALL_HJOIN)
	                    & (get_wall_between(hwall_data, vwall_data, x + 1, y + 1, x + 2, y + 1) != WALL_VJOIN)
						& (get_wall_between(hwall_data, vwall_data, x + 1, y + 1, x + 1, y + 2) != WALL_QJOIN)
						& (get_wall_between(hwall_data, vwall_data, x + 1, y + 1, x + 1, y + 2) != WALL_HJOIN)
	                    & (get_wall_between(hwall_data, vwall_data, x + 1, y + 1, x + 1, y + 2) != WALL_VJOIN)
						& (get_wall_between(hwall_data, vwall_data, x, y + 1, x, y + 2) != WALL_QJOIN)
	                    & (get_wall_between(hwall_data, vwall_data, x, y + 1, x, y + 2) != WALL_HJOIN)
	                    & (get_wall_between(hwall_data, vwall_data, x, y + 1, x, y + 2) != WALL_VJOIN)
						& (get_wall_between(hwall_data, vwall_data, x, y + 1, x - 1, y + 1) != WALL_QJOIN)
	                    & (get_wall_between(hwall_data, vwall_data, x, y + 1, x - 1, y + 1) != WALL_HJOIN)
	                    & (get_wall_between(hwall_data, vwall_data, x, y + 1, x - 1, y + 1) != WALL_VJOIN)
						& (get_wall_between(hwall_data, vwall_data, x, y, x - 1, y) != WALL_QJOIN)
	                    & (get_wall_between(hwall_data, vwall_data, x, y, x - 1, y) != WALL_HJOIN)
	                    & (get_wall_between(hwall_data, vwall_data, x, y, x - 1, y) != WALL_VJOIN)) {
							//set the walls connecting the group to quad joins
							set_wall_between(hwall_data, vwall_data, x, y, x + 1, y, WALL_QJOIN);
							set_wall_between(hwall_data, vwall_data, x + 1, y, x + 1, y + 1, WALL_QJOIN);
							set_wall_between(hwall_data, vwall_data, x + 1, y + 1, x, y + 1, WALL_QJOIN);
							set_wall_between(hwall_data, vwall_data, x, y + 1, x, y, WALL_QJOIN);
						}
					}
				}
			}
		}
	}
}
//loops over room_data and finds 2x1 groups of rooms. each group is given a (freq/255)% chance to merge
static inline void make_hrooms(const u32 room_data[], u32 hwall_data[], u32 vwall_data[], u32 freq) {
	//for every cell in room_data
	for(u32 y = 0; y < HEIGHT; y++) {
		for(u32 x = 0; x < WIDTH; x++) {
			//if the rng check passes
			if(qran_range(0, 256) < freq) {
				//if a 2x1 group exists here, connected by a door
				if((get_elem(room_data, x, y) > 0)
				& (get_elem(room_data, x + 1, y) > 0)
				& (get_wall_between(hwall_data, vwall_data, x, y, x + 1, y) == WALL_DOOR_UNLOCKED)) {
					//this huge block of conditions checks every wall connected to the candidate group. if ANY of them are already joined, the group is discarded
					if((get_wall_between(hwall_data, vwall_data, x, y, x - 1, y) != WALL_QJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x - 1, y) != WALL_HJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x - 1, y) != WALL_VJOIN)
					& (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 2, y) != WALL_QJOIN)
					& (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 2, y) != WALL_HJOIN)
					& (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 2, y) != WALL_HJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x, y - 1) != WALL_QJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x, y - 1) != WALL_HJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x, y - 1) != WALL_VJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x, y + 1) != WALL_QJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x, y + 1) != WALL_HJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x, y + 1) != WALL_VJOIN)
					& (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 1, y - 1) != WALL_QJOIN)
					& (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 1, y - 1) != WALL_HJOIN)
					& (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 1, y - 1) != WALL_VJOIN)
					& (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 1, y + 1) != WALL_QJOIN)
					& (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 1, y + 1) != WALL_HJOIN)
					& (get_wall_between(hwall_data, vwall_data, x + 1, y, x + 1, y + 1) != WALL_VJOIN)) {
						//change the wall between the pair to a horizontal join
						set_wall_between(hwall_data, vwall_data, x, y, x + 1, y, WALL_HJOIN);
					}
				}
			}
		}
	}
}

//loops over room_data and finds 1x2 groups of rooms. each group is given a (freq/255)% chance to merge
static inline void make_vrooms(const u32 room_data[], u32 hwall_data[], u32 vwall_data[], u32 freq) {
	//for every cell in room_data
	for(u32 y = 0; y < HEIGHT; y++) {
		for(u32 x = 0; x < WIDTH; x++) {
			//if the rng check passes
			if(qran_range(0, 256) < freq) {
				//if a 1x2 group exists here, connected by a door
				if((get_elem(room_data, x, y) > 0)
				& (get_elem(room_data, x, y + 1) > 0)
				& (get_wall_between(hwall_data, vwall_data, x, y, x, y + 1) == WALL_DOOR_UNLOCKED)) {
					//this huge block of conditions checks every wall connected to the candidate group. if ANY of them are already joined, the group is discarded
					if((get_wall_between(hwall_data, vwall_data, x, y, x, y - 1) != WALL_QJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x, y - 1) != WALL_HJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x, y - 1) != WALL_VJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y + 1, x, y + 2) != WALL_QJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y + 1, x, y + 2) != WALL_HJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y + 1, x, y + 2) != WALL_HJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x - 1, y) != WALL_QJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x - 1, y) != WALL_HJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x - 1, y) != WALL_VJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x + 1, y) != WALL_QJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x + 1, y) != WALL_HJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y, x + 1, y) != WALL_VJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y + 1, x - 1, y + 1) != WALL_QJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y + 1, x - 1, y + 1) != WALL_HJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y + 1, x - 1, y + 1) != WALL_VJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y + 1, x + 1, y + 1) != WALL_QJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y + 1, x + 1, y + 1) != WALL_HJOIN)
					& (get_wall_between(hwall_data, vwall_data, x, y + 1, x + 1, y + 1) != WALL_VJOIN)) {
						//change the wall between the pair to a vertical join
						set_wall_between(hwall_data, vwall_data, x, y, x, y + 1, WALL_VJOIN);
					}
				}
			}
		}
	}
}

//uses recursion to generate the initial room values
void place_rooms(u32 room_data[], u32 hwall_data[], u32 vwall_data[], const u32 r_x, const u32 r_y, const u32 num_iter, const u32 cur_iter) {
	//base case: if we are on the last iteration, stop
	if(cur_iter == 1) return;
	//for each adjacent cell to the one whose coords were passed, recurse with it's coords.
	//the chance to actually recurse with the cell decreases gradually to zero, inversely proportional to the number of iterations that have passed
	//if the cell is not already taken (is zero) and the cell passes the rng check
	if(get_elem(room_data, r_x, r_y - 1) == 0) {
		if(qran_range(0, 256) < 255 * cur_iter / num_iter) {
			set_elem(room_data, r_x, r_y - 1, cur_iter - 1);
			set_wall_between(hwall_data, vwall_data, r_x, r_y, r_x, r_y - 1, WALL_DOOR_UNLOCKED);
			place_rooms(room_data, hwall_data, vwall_data, r_x, r_y - 1, num_iter, cur_iter - 1);
		}
	}
	if(get_elem(room_data, r_x + 1, r_y) == 0) {
		if(qran_range(0, 256) < 255 * cur_iter / num_iter) {
			set_elem(room_data, r_x + 1, r_y, cur_iter - 1);
			set_wall_between(hwall_data, vwall_data, r_x, r_y, r_x + 1, r_y, WALL_DOOR_UNLOCKED);
			place_rooms(room_data, hwall_data, vwall_data, r_x + 1, r_y, num_iter, cur_iter - 1);
		}
	}
	if(get_elem(room_data, r_x, r_y + 1) == 0) {
		if(qran_range(0, 256) < 255 * cur_iter / num_iter) {
			set_elem(room_data, r_x, r_y + 1, cur_iter - 1);
			set_wall_between(hwall_data, vwall_data, r_x, r_y, r_x, r_y + 1, WALL_DOOR_UNLOCKED);
			place_rooms(room_data, hwall_data, vwall_data, r_x, r_y + 1, num_iter, cur_iter - 1);
		}
	}
	if(get_elem(room_data, r_x - 1, r_y) == 0) {
		if(qran_range(0, 256) < 255 * cur_iter / num_iter) {
			set_elem(room_data, r_x - 1, r_y, cur_iter - 1);
			set_wall_between(hwall_data, vwall_data, r_x, r_y, r_x - 1, r_y, WALL_DOOR_UNLOCKED);
			place_rooms(room_data, hwall_data, vwall_data, r_x - 1, r_y, num_iter, cur_iter - 1);
		}
	}
}

//calls upon all the other functions to create a dungeon
void build_dungeon(u32 room_data[], u32 hwall_data[], u32 vwall_data[], const u32 num_iter, const u32 quad_freq, const u32 horz_freq, const u32 vert_freq) {
	memset32(room_data, 0, HEIGHT * WIDTH);
	memset32(hwall_data, 0, HEIGHT * WIDTH);
	memset32(vwall_data, 0, HEIGHT * WIDTH);

	set_elem(room_data, (WIDTH >> 1) - 1, (HEIGHT >> 1) - 1, num_iter);
	place_rooms(room_data, hwall_data, vwall_data, (WIDTH >> 1) - 1, (HEIGHT >> 1) - 1, num_iter, num_iter);
	make_qrooms(room_data, hwall_data, vwall_data, quad_freq);
	make_hrooms(room_data, hwall_data, vwall_data, horz_freq);
	make_vrooms(room_data, hwall_data, vwall_data, vert_freq);
}

//temporary debug function
//don't crucify me, this isnt supposed to be efficient
void print_dungeon(const u32 room_data[], const u32 hwall_data[], const u32 vwall_data[]) {
	for(u32 y = 0; y < HEIGHT; y++) {
		for(u32 x = 0; x < WIDTH; x++) {
			char str_buf[4];
			//print rooms
			if(get_elem(room_data, x, y) > 0) {
				sprintf(str_buf, "%d", get_elem(room_data, x, y));
				tte_set_pos(x * 8 * 2, y * 8 * 2);
				tte_write(str_buf);
			}
			//horizontal doors
			if(get_elem(hwall_data, x, y) == WALL_DOOR_UNLOCKED) {
				sprintf(str_buf, "-");
				tte_set_pos(x * 8 * 2 + 8, y * 8 * 2);
				tte_write(str_buf);
			}
			//horizontal quad joins
			else if(get_elem(hwall_data, x, y) == WALL_QJOIN) {
				sprintf(str_buf, "q");
				tte_set_pos(x * 8 * 2 + 8, y * 8 * 2);
				tte_write(str_buf);
			}
			//horizontal joins
			else if(get_elem(hwall_data, x, y) == WALL_HJOIN) {
				sprintf(str_buf, "h");
				tte_set_pos(x * 8 * 2 + 8, y * 8 * 2);
				tte_write(str_buf);
			}

			//vertical doors
			if(get_elem(vwall_data, x, y) == WALL_DOOR_UNLOCKED) {
				sprintf(str_buf, "|");
				tte_set_pos(x * 8 * 2, y * 8 * 2 + 8);
				tte_write(str_buf);
			}
			//vertical quad joins
			else if(get_elem(vwall_data, x, y) == WALL_QJOIN) {
				sprintf(str_buf, "q");
				tte_set_pos(x * 8 * 2, y * 8 * 2 + 8);
				tte_write(str_buf);
			}
			//vertical joins
			else if(get_elem(vwall_data, x, y) == WALL_VJOIN) {
				sprintf(str_buf, "v");
				tte_set_pos(x * 8 * 2, y * 8 * 2 + 8);
				tte_write(str_buf);
			}
		}
	}
}
