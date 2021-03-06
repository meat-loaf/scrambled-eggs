#include "level_view.h"
#include "level_object.h"

#include <iostream>

#include <QGridLayout>
#include <QGraphicsView>
#include <QRectF>
#include <QGraphicsItem>

level_view_t::level_view_t(QWidget *parent)
	: QWidget(parent)
{
	QGridLayout *grid = new QGridLayout(this);
	scene = new QGraphicsScene(this);
	QGraphicsView *g = new QGraphicsView(scene);
	grid->addWidget(g, 0, 0);
	this->setLayout(grid);
}


void
level_view_t::draw_level(level& level_data)
{
	scene->clear();
	//draws a grid for each game screen
	//TODO make toggleable, color differently, figure out how to change opacity
	for (int i = 0; i < 0x80; i++)
	{
		scene->addRect(
			(i & 0x0F)*16*8,
			((i & 0xF0) >> 4)*16*8,
			16*8, 16*8);
	}
	for (const auto obj : level_data.objects)
	{
		uint16_t x, y, w, h;
		switch(obj.type)
		{
			case object_type::four_byte_std:
				x = (obj.object.four_byte_std.high_xy & 0xF0) |
				((obj.object.four_byte_std.low_xy & 0xF0) >> 0x4);
				y = ((obj.object.four_byte_std.high_xy & 0x0F) << 0x4) |
				    (obj.object.four_byte_std.low_xy & 0x0F);
				w = obj.object.four_byte_std.length_minus_one+1;
				h = 1;
			
			break;
			case object_type::four_byte_ext:
			break;
			case object_type::five_byte:
				x = (obj.object.five_byte.high_xy & 0xF0) |
				((obj.object.five_byte.low_xy & 0xF0) >> 0x4);
				y = ((obj.object.five_byte.high_xy & 0x0F) << 0x4) |
				    (obj.object.five_byte.low_xy & 0x0F);
				w = obj.object.five_byte.width_minus_one+1;
				h = obj.object.five_byte.height_minus_one+1;
			break;

		};
		scene->addItem(new level_object_t(y*8, x*8, w*8, h*8));
	}
	return;
}
