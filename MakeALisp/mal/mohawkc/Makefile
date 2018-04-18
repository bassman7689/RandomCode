CC=gcc
NAME=step3_env
LDFLAGS=-lreadline `pkg-config --libs glib-2.0`
CFLAGS=`pkg-config --cflags glib-2.0`
SOURCES=operators.c env.c ast.c reader.c eval.c printer.c step3_env.c
OBJECTS=${SOURCES:.c=.o}

all : ${NAME}

${NAME} : ${OBJECTS}
	${CC} ${LDFLAGS} $^ -o $@ -g

${OBJECTS}: %.o: %.c
	${CC} -c ${CFLAGS} $< -o $@ -g

.PHONY: clean

clean:
	rm -rf *.o ${NAME} $(NAME).dSYM
