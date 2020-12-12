if [ ! -f ./Makefile -o ./Makefile -nt se.pro ]; then
  mkdir -p build
  cd build && qmake ../se.pro -o Makefile
fi

make $@
