CFLAGS = -Wall -Wextra -Werror -ansi -pedantic

all: fpack

debug: CFLAGS += -g
debug: clean all

fpack: fpack.o
	gcc -o fpack fpack.o

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o
