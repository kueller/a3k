SOURCE = split.c instructions.c variables.c interpret.c fileread.c assemble.c kasm.c
BINARY = kasm
CC     = gcc
CFLAGS = -Wall -v
OBJ    = ${SRC:.c=.o}

all: ${BINARY}

${BINARY}:
	${CC} ${CFLAGS} ${SOURCE} -o ${BINARY}
	chmod +x ${BINARY}




