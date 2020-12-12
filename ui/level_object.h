#ifndef _LEVEL_OBJECT_H_
#define _LEVEL_OBJECT_H_

#include "../data/level.h"

#include <QGraphicsRectItem>

/* TODO this class eventually needs to know about:
	* all the different kinds of objects, to know how to draw itself
		TODO override the paint method
	* the current actual (level) object it is representing, so when this
		is moved by the user, the position can be updated there as well.
*/
class level_object_t : public QGraphicsRectItem {
public:
	explicit level_object_t(int x, int y, int w, int h, QGraphicsRectItem* parent = nullptr);
};

#endif
