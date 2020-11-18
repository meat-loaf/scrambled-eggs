#include "level.h"
#include "../util/sfx_to_pc.h"

#include <iostream>
#include <array>

//TODO split into (static) sub functions for better readability
bool
load_level_data(const char * const rom_data, uint16_t level_num, level& level_data)
{
	bool headered = true;
	//the level data listing consits of two 24 bit pointers:
	//one for header/obj/screen exit data, one for sprite data.
	uint32_t level_data_pointer = sfx_to_pc(0x17F7C3) + (headered == true ? 512 : 0) + level_num * 6;
	//the 65C816 is a little endian processor so they're stored
	//in little endian format.
	uint32_t obj_ptr = sfx_to_pc(
		((static_cast<unsigned char>(rom_data[level_data_pointer+2]) << 16) |
		(static_cast<unsigned char>(rom_data[level_data_pointer+1]) <<  8)  |
		(static_cast<unsigned char>(rom_data[level_data_pointer+0]) <<  0)) &
		0x00FFFFFF);// + (headered == true) ? 512 : 0;
	uint32_t spr_ptr = sfx_to_pc(
		((static_cast<unsigned char>(rom_data[level_data_pointer+5]) << 16) |
		(static_cast<unsigned char>(rom_data[level_data_pointer+4]) <<  8)  |
		(static_cast<unsigned char>(rom_data[level_data_pointer+3]) <<  0)) &
		0x00FFFFFF);// + (headered == true) ? 512 : 0;

	obj_ptr += (headered == true) ? 512 : 0;
	spr_ptr += (headered == true) ? 512 : 0;

	for(int i = 0; i < 10; i++)
	{
		//level_data.header.header_comb[i] = rom_data[obj_ptr+i];
		level_data.header[i] = rom_data[obj_ptr+i];
	}
	obj_ptr += 10;
	//TODO bounds check
	uint32_t obj_table_addr = sfx_to_pc(0x1284EC) + (headered == true ? 512 : 0);
	while(static_cast<uint8_t>(rom_data[obj_ptr]) != 0xFF)
	{
		uint8_t id = rom_data[obj_ptr];
		//four-byte extended objects have '0' in this slot.
		//their actual id is the 4th byte of the object.
		if (id == 0){
			id = rom_data[obj_ptr+3];
			level_data.objects.push_back({
				.type = object_type::four_byte_ext,
				.object = {.four_byte_ext = {
					.ext_marker = id,
					.high_xy = (uint8_t)rom_data[obj_ptr+1],
					.low_xy = (uint8_t)rom_data[obj_ptr+2],
					.id = (uint8_t)rom_data[obj_ptr+3]}
					}
				});
			obj_ptr += 4;
			continue;
		}
		uint8_t table_entry = rom_data[obj_table_addr + id];
		
		switch(table_entry & 0x03)
		{
		//four byte
		case 0:
		case 1:
			level_data.objects.push_back({
				.type = object_type::four_byte_std,
				.object = { .four_byte_std = {
						.id = id,
						.high_xy = (uint8_t)rom_data[obj_ptr+1],
						.low_xy = (uint8_t)rom_data[obj_ptr+2],
						.length_minus_one = rom_data[obj_ptr+3]
						}
					}
				});
			obj_ptr += 4;
		continue;
		//five byte
		default:
			level_data.objects.push_back({
				.type = object_type::five_byte,
				.object = { .five_byte = {
						.id = id,
						.high_xy = (uint8_t)rom_data[obj_ptr+1],
						.low_xy = (uint8_t)rom_data[obj_ptr+2],
						.width_minus_one = rom_data[obj_ptr+3],
						.height_minus_one = rom_data[obj_ptr+4]
					}
				}
			});
			obj_ptr += 5;
		continue;
		}
	}
	//advance past the 'end of object list' marker
	obj_ptr++;
	//TODO bounds check
	//process screen exits
	while(static_cast<uint8_t>(rom_data[obj_ptr]) != 0xFF)
	{
		uint8_t dest = (uint8_t)rom_data[obj_ptr+1];
		switch((dest >= 0xDE && dest <= 0xE9) ? 1 : 0)
		{
		//normal exit
		case 0:
			level_data.exits.push_back({
				.type = exit_type::screen_exit,
				.exit = { .sexit = {
						.target_page = (uint8_t)rom_data[obj_ptr],
						.dest_level = dest,
						.dest_x = (uint8_t)rom_data[obj_ptr+2],
						.dest_y = (uint8_t)rom_data[obj_ptr+3],
						.dest_ent_type = (entrance_type)rom_data[obj_ptr+4]
					}
				}
				
			});
		break;
		//minibattle
		case 1:
			level_data.exits.push_back({
				.type = exit_type::minibattle,
				.exit = { .mexit = {
						.target_page = (uint8_t)rom_data[obj_ptr],
						.dest_minibattle = dest,
						.ret_x = (uint8_t)rom_data[obj_ptr+2],
						.ret_y = (uint8_t)rom_data[obj_ptr+3],
						.ret_level = (uint8_t)rom_data[obj_ptr+4]
					}
				}
				
			});
		break;
		}
		obj_ptr += 5;
		
	}

	//TODO bounds check
	//process sprites
	while(((uint8_t)rom_data[spr_ptr]) != 0xFF && ((uint8_t)rom_data[spr_ptr+1]) != 0xFF)
	{
		level_data.sprites.push_back({
			.id = (uint8_t)rom_data[spr_ptr],
			.y_coord_id_hi = (uint8_t)rom_data[spr_ptr+1],
			.x_coord = (uint8_t)rom_data[spr_ptr+2]
		});
		spr_ptr += 3;
	}
	return true;
}
