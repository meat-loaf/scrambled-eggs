#include "editor.h"

#include <iostream>
#include <sstream>

#include <QString>
#include <QMenuBar>
#include <QFileDialog>
#include <QMenu>
#include <QMainWindow>
#include <QRegExp>

editor_t::editor_t(QWidget* parent)
	: QMainWindow(parent)
{
	m_view = new level_view_t(this);

	this->resize(800, 600);
	this->setCentralWidget(m_view);

	populate_menu();
	m_error_message_diag = new QErrorMessage(this);
	m_error_message_diag->setModal(true);


}

editor_t::~editor_t()
{
	if (m_rom){
		delete m_rom;
	}
}

void
editor_t::populate_menu()
{
	auto mbar = menuBar();

	auto file_menu = mbar->addMenu("File");

	connect(file_menu->addAction("Open..."), &QAction::triggered, this, &editor_t::open);


	open_lvl_action = file_menu->addAction("Open Level Number...");
	open_lvl_action->setEnabled(false);
	connect(open_lvl_action, &QAction::triggered, this, &editor_t::open_level);
}

void
editor_t::open()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open Yoshi's Island (v1.0) ROM image", ".", "SNES ROM images (*.sfc, *.smc);; All files (*.*)");
	if (!filename.isEmpty()){
		std::string selected_file = filename.toStdString();
		open_lvl_action->setEnabled(true);
		m_rom = new yi_rom_t(selected_file);
		level data;
		load_level_data(m_rom->rom_data(), 0, data);
		draw_level(data);
	}
}

void
editor_t::open_level()
{
	QRegExp rx("^[0-9a-fA-F]{1,2}$");

	bool ok_clicked = false;

	QString input_str_q =
		QInputDialog::getText(this,
			"Open Level Number (in hex)", "Level number (0 - D8)",
			QLineEdit::Normal, "", &ok_clicked);

	if (ok_clicked)
	{

		if (!rx.exactMatch(input_str_q)
			or input_str_q.toUpper() > "D8") {

			m_error_message_diag->showMessage("Bad level number.");
			return;

		}

		std::string input_str = input_str_q.toStdString();

		std::cout << input_str << std::endl;
		std::stringstream ss;
		uint16_t x;
		ss << std::hex << input_str;
		ss >> x;
		level data;
		load_level_data(m_rom->rom_data(), x, data);
		draw_level(data);
	}
}

void
editor_t::draw_level(level& level_data)
{
	m_view->draw_level(level_data);
}
