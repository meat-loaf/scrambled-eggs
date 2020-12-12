#include "yi_rom.h"

#include <climits>

yi_rom_t::yi_rom_t(const std::string& filename)
	: m_filename(filename)
{
	std::ifstream rom(filename, std::ios::binary | std::ios::ate);
	m_rom_sz = rom.tellg();

	rom.seekg(0, std::ios::beg);

	m_rom_data = new char[m_rom_sz];

	rom.read(m_rom_data, m_rom_sz);
	//auto name_addr = sfx_to_pc(0xFFC0);

	m_has_header = (m_rom_sz & SHRT_MAX) == 512 ? true : false;
}

yi_rom_t::~yi_rom_t()
{
	if (m_rom_data){
		delete[] m_rom_data;
	}
}

const char *
yi_rom_t::rom_data() const {
	return m_rom_data;
}
