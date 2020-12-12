#include <QApplication>

#include <fstream>
#include <iostream>
#include <climits>

#include "ui/editor.h"

//	level ldat;
//	load_level_data(rom_dat, 0, ldat);
//	q->draw_level(ldat);


int main(int argc, char**argv)
{

	QApplication a(argc, argv);
	editor_t ed;
	ed.show();

	return a.exec();
}
