#include "level_object.h"

level_object_t::level_object_t(int x, int y, int w, int h, QGraphicsRectItem* parent) 
	: QGraphicsRectItem(x, y, w, h, parent)
{
	const QGraphicsItem::GraphicsItemFlags obj_flags =
			QGraphicsItem::ItemIsMovable |
			QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable;
	setFlags(obj_flags);
}
	
