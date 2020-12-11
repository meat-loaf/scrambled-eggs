#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "level_consts.h"

#include <cstdint>
#include <vector>

#define HEADER_BG_COLOR(header_arr)		\
	(((header_arr)[0] & 0xF1) >> 0x3)

#define HEADER_BG1_TILESET(header_arr)		\
	(					\
	(((header_arr)[0] & 0x07) << 0x1) |	\
	(((header_arr)[1] & 0x80) >> 0x7)	\
	)
	

typedef
struct _five_byte_obj
{
	uint8_t id;
	uint8_t high_xy;
	uint8_t low_xy;
	int8_t width_minus_one;
	int8_t height_minus_one;
} five_byte_obj;

typedef
struct _four_byte_obj
{
	uint8_t id;
	uint8_t high_xy;
	uint8_t low_xy;
	int8_t length_minus_one;
} four_byte_obj;

typedef
struct _four_byte_ext_obj
{
	//should always be 00
	uint8_t ext_marker;
	uint8_t high_xy;
	uint8_t low_xy;
	uint8_t id;
	
} four_byte_ext_obj;

enum class object_type : uint8_t
{
	five_byte,
	four_byte_std,
	four_byte_ext
};

typedef
union _single_object
{
	four_byte_obj     four_byte_std;
	five_byte_obj     five_byte;
	four_byte_ext_obj four_byte_ext;
} single_object;

typedef
struct _typed_object
{
	object_type type;
	single_object object;
} typed_object;

enum class entrance_type : uint8_t
{
	nothing = 0x0,
	skiing = 0x1,
	right_from_pipe = 0x2,
	left_from_pipe = 0x3,
	down_from_pipe = 0x4,
	up_from_pipe = 0x5,
	rightwards = 0x6,
	leftwards = 0x7,
	downwards = 0x8,
	high_jump = 0x9,
	moon_unit = 0xA
};

typedef
struct _screen_exit
{
	uint8_t target_page;
	uint8_t dest_level;
	uint8_t dest_x;
	uint8_t dest_y;
	entrance_type dest_ent_type;
} screen_exit;

typedef
struct _minibattle_exit
{
	uint8_t target_page;
	uint8_t dest_minibattle;
	uint8_t ret_x;
	uint8_t ret_y;
	uint8_t ret_level;
} minibattle_exit;

enum class exit_type : uint8_t
{
	screen_exit,
	minibattle
};
typedef
struct _level_exit
{
	exit_type type;
	union {
		screen_exit sexit;
		minibattle_exit mexit;
	} exit;
} level_exit;

typedef
struct _sprite
{
	uint8_t id;
	//high bit of id is in lsb
	uint8_t y_coord_id_hi;
	uint8_t x_coord;
} sprite;

/* 10 byte header looks like this:
typedef
struct header_items {
	uint16_t bg_color:5;
	uint16_t bg1_tileset:4;
	uint16_t bg1_palette:5;
	uint16_t bg2_tileset:5;
	uint16_t bg2_palette:6;
	uint16_t bg3_tileset:6;
	uint16_t bg3_palette:6;
	uint16_t sprite_tileset:7;
	uint16_t sprite_palette:4;
	uint16_t level_mode:5;
	uint16_t anim_tileset:6;
	uint16_t anim_tileset_palette:5;
	uint16_t bg_scroll_rate:5;
	uint16_t music:4;
	uint16_t item_memory:2;
	uint16_t unused:5;
} level_header;
*/

typedef
struct _level {
	uint8_t header[LEVEL_HEADER_SIZE_BYTES];
	std::vector<typed_object> objects;
	std::vector<level_exit> exits;
	std::vector<sprite> sprites;
} level;

bool load_level_data(const char* const rom_data, const uint16_t level_num, level& level_data);

#endif
