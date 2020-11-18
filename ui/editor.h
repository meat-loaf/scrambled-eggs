#ifndef _EDITOR_T_H_
#define _EDITOR_T_H_

#include <functional>

#include <QMainWindow>

#include "level_view.h"
#include "../data/level.h"

class editor_t : public QMainWindow {
	Q_OBJECT

public:
	explicit editor_t(
	std::function<void (std::string)> open_callback,
		QWidget* parent = 0);
	void draw_level(level& level_data);

	level_view_t* view;
signals:
public slots:
	void open();
private:
	std::function<void (std::string)> ext_op_cb;
	void initialize();
};

#endif
