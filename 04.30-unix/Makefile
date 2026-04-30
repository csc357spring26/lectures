# NOTE: Now that we are experienced C programmers who supposedly know what we
#       are doing, we still want to see warnings, but we have earned the right
#       to stop treating warnings as errors and to switch to the latest
#       supported version of the C standard.
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
