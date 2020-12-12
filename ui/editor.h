#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "level_view.h"
#include "../data/level.h"
#include "../data/yi_rom.h"

#include <functional>

#include <QMainWindow>
#include <QAction>
#include <QInputDialog>
#include <QDialog>
#include <QErrorMessage>

class editor_t : public QMainWindow {
	Q_OBJECT

public:
	explicit editor_t(QWidget* parent = 0);
	virtual ~editor_t();

signals:
public slots:
	void open();
	void open_level();
private:
	void initialize();
	void populate_menu();
	void draw_level(level& level_data);

	yi_rom_t* m_rom;
	level_view_t* m_view;

	QAction* open_lvl_action;
	QErrorMessage* m_error_message_diag;

};

#endif
