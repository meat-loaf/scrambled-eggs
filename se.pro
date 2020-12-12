QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += ui/editor.h		\
	   ui/level_view.h	\
	   ui/level_object.h

SOURCES += main.cpp 		\
	   ui/editor.cpp 	\
	   ui/level_view.cpp 	\
	   ui/level_object.cpp  \
	   data/level.cpp	\
	   data/yi_rom.cpp	\
	   util/sfx_to_pc.cpp

TARGET = se

CONFIG += debug
