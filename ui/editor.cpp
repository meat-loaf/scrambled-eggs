
#include <iostream>

#include <QString>
#include <QToolBar>
#include <QFileDialog>
#include <QMainWindow>

#include "editor.h"

editor_t::editor_t(std::function<void(std::string)> open_callback,
QWidget* parent)
	: QMainWindow(parent)
	, ext_op_cb(open_callback)
{
	QToolBar *toolbar = new QToolBar(this);
	this->view = new level_view_t(this);
	auto act = toolbar->addAction("File");
	connect(act, &QAction::triggered, this, &editor_t::open);
	this->resize(800, 600);
	this->addToolBar(toolbar);
	this->setCentralWidget(view);
}

void
editor_t::open()
{
	std::cout << "open called" << std::endl;
	QString filename = QFileDialog::getOpenFileName(this, "Open Yoshi's Island (v1.0) ROM image", ".", "SNES ROM images (*.sfc, *.smc);; All files (*.*)");
	if (!filename.isEmpty()){
		std::string selected_file = filename.toStdString();
		ext_op_cb(selected_file);
	}
}

void
editor_t::draw_level(level& level_data)
{
	view->draw_level(level_data);
}
