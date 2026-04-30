# NOTE: As programmers who now supposedly know what we are doing, we have
#       earned the right to drop the -Werror flag and switch to the latest
#       supported C standard with all the extra features.
CFLAGS = -Wall -Wextra -std=gnu11 -pedantic

all: fpack pack

debug: CFLAGS += -g
debug: clean all

fpack: fpack.o
	gcc -o fpack fpack.o

pack: pack.o
	gcc -o pack pack.o

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o
