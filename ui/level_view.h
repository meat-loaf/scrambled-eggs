#ifndef _LEVEL_VIEW_T_H_
#define _LEVEL_VIEW_T_H_

#include <QWidget>
#include <QGraphicsScene>

#include "../data/level.h"

class level_view_t : public QWidget {
	Q_OBJECT

public:
	explicit level_view_t(QWidget* parent = 0);
	void draw_level(level& level_data);
signals:
public slots:
private:
	QGraphicsScene *scene;

};

#endif
