CC=gcc
CFLAGS=
LDFLAGS=-lncurses -macosx_version_min 10.12 -lc -arch x86_64
BUILDDIR=./build
SOURCEDIR=./src
OBJS=${BUILDDIR}/main.o
SRCS=${SOURCEDIR}/main.c
APPNAME=gap_buffer_test

all: ${BUILDDIR} ${OBJS}
	ld -o ${BUILDDIR}/${APPNAME} ${OBJS} ${LDFLAGS}

run: 
	./build/${APPNAME}

${BUILDDIR}/%.o: ${SOURCEDIR}/%.c
	${CC} ${CFLAGS} -c $< -o $@

${BUILDDIR}:
	mkdir -p build

.PHONY: clean

clean:
	rm -rf build
