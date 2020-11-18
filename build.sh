if [ ! -f ./Makefile -o ./Makefile -nt se.pro ]; then
	qmake se.pro -o Makefile
fi

make $@
