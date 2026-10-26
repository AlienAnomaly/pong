CC = gcc
CFLAGS = $(shell pkg-config --cflags sdl3 sdl3-image)
LDFLAGS = $(shell pkg-config --libs sdl3 sdl3-image)

TARGET = pong
SRCS := ${wildcard *.c}
OBJDIR := bin-int
OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

all: ${TARGET}

${TARGET}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${TARGET} ${LDFLAGS}

${OBJDIR}/%.o: %.c | ${OBJDIR}
	${CC} ${CFLAGS} -c $< -o $@

${OBJDIR}:
	mkdir -p ${OBJDIR}

clean:
	rm -rf ${OBJDIR} ${TARGET}

.PHONY: all clean
