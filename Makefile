ASSEMBLER = kasm
VMACHINE  = a3k

all: ${ASSEMBLER} ${VMACHINE}

${ASSEMBLER}:
	cd ./${ASSEMBLER}-src && make
	mv ./${ASSEMBLER}-src/${ASSEMBLER} ./

${VMACHINE}:
	cd ./${VMACHINE}-src && make
	mv ./${VMACHINE}-src/${VMACHINE} ./

install: all
	cp ${ASSEMBLER} /usr/bin
	cp ${VMACHINE} /usr/bin
	cp ./${VMACHINE}-src/${VMACHINE}.desktop /usr/share/applications

uninstall:
	rm -f /usr/bin/${ASSEMBLER}
	rm -f /usr/bin/${VMACHINE}
	rm -f /usr/share/applications/${VMACHINE}.desktop

clean:
	cd ./a3k-src && make clean

spotless: clean
	rm -f ${ASSEMBLER}
	rm -f ${VMACHINE}
