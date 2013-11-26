CC=gcc
VERSION=-g3
CFLAGS=-Wall -Wextra -Werror

OBJS=\
    graphics.o \
    ui.o \
    test_dispMenu.o

default: ${OBJS}
	@echo Linking ...
	${CC} ${VERSION} ${CFLAGS} -o dispMenu.test ${OBJS}
	@echo Done!

%.o: %.cpp
	${CC} ${VERSION} ${CFLAGS} -c -o $@ $<

clean:
	rm -rf ${OBJS}
