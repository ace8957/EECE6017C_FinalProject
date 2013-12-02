CC=clang
CFLAGS=-Wall -Wextra -Wno-unused-parameter -Wno-unused-value -g3
INC=
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  LIBS=-lGL -lglut
endif
ifeq ($(UNAME_S),Darwin)
  LIBS=-framework OpenGL -framework GLUT
endif

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
