VMACHINE = a3k

all: ${VMACHINE}

${VMACHINE}:
	/usr/lib/qt/bin/qmake -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o ./UI/Makefile ./UI/a3k.pro
	cd ./UI && make
	mv ./UI/${VMACHINE} .

clean:
	cd ./UI && make clean

spotless:
	cd ./UI && make distclean
