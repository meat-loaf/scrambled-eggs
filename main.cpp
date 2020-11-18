#include <QApplication>

#include <fstream>
#include <iostream>
#include <climits>

#include "ui/editor.h"
#include "data/level.h"
#include "util/sfx_to_pc.h"

void setup_editor(std::string);

//static editor_t q(&setup_editor);
static editor_t *q;

void setup_editor(std::string filename)
{
	std::ifstream rom(filename, std::ios::binary | std::ios::ate);
	std::streamsize sz = rom.tellg();
	rom.seekg(0, std::ios::beg);
	char *rom_dat = new char[sz];
	if (rom_dat == nullptr){
		std::cerr << "cant allocate memory\n";
		return;
	}
	rom.read(rom_dat, sz);
	std::cout << "filesize: " << sz << "\n";
	auto name_addr = sfx_to_pc(0xFFC0);

	std::string rom_title;
	bool has_header = (sz & SHRT_MAX) == 512 ? true : false;
	name_addr += has_header ? 512 : 0;
	for (auto i = 0; i < 21; i++)
	{
		rom_title.push_back(rom_dat[name_addr + i]);
	}

	std::cout << "rom title: " << rom_title << std::endl;
	
	level ldat;
	load_level_data(rom_dat, 0, ldat);
	q->draw_level(ldat);
	delete[] rom_dat;

}


int main(int argc, char**argv)
{

	QApplication a(argc, argv);
	editor_t q_m(&setup_editor);
	q = &q_m;

	q->show();
	auto retval = a.exec();

	return retval;
}
