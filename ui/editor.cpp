#include "editor.h"

#include <iostream>
#include <sstream>

#include <QString>
#include <QMenuBar>
#include <QFileDialog>
#include <QMenu>
#include <QMainWindow>

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
	bool ok = false;
	//TODO limit number of input characters to a sane amount, if possible
	std::string value =
		QInputDialog::getText(this,
			"Open Level Number (in hex)", "Level number (0 - D8)",
			QLineEdit::Normal, "", &ok).toStdString();
	
	if (ok)
	{
		std::cout << value << std::endl;
		//TODO better way to do this (use QValidator)?
		for (auto i : value)
		{
			if (i >= '0' || i <= '9')
				continue;
			if (i >= 'A' || i <= 'F')
				continue;
			if (i >= 'a' || i <= 'f')
			{
				m_error_message_diag->showMessage("Bad level number.");
				return;
			}
		}
		std::stringstream ss;
		uint16_t x;
		ss << std::hex << value;
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
