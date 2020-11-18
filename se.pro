QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += ui/editor.h		\
	   ui/level_view.h

SOURCES += main.cpp 		\
	   ui/editor.cpp 	\
	   ui/level_view.cpp 	\
	   data/level.cpp	\
	   util/sfx_to_pc.cpp

TARGET = se

CONFIG += debug
