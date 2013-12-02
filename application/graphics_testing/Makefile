CC=clang
CFLAGS=-Wall -Wextra -Wno-unused-parameter -Wno-unused-value -g3
INC=
LIBS=-lGL -lglut

OBJS=\
	graphics.o \
	ui.o \
	keyboard.o \
	main.o

TARGET=testUI

default: ${OBJS}
	@echo Linking into ${TARGET}
	@echo
	${CC} ${CFLAGS} -o ${TARGET} ${OBJS} ${INC} ${LIBS}
	@echo
	@echo All Done!

%.o: %.c
	@echo Compiling $@
	@echo
	${CC} -c ${CFLAGS} -o $@ $< ${INC}
	@echo

clean:
	rm -rf ${OBJS} ${TARGET}
