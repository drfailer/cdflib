CC=gcc
CFLAGS=-O0 -MMD -fdiagnostics-color=auto -g -nostdlib -m64
LDFLAGS=
SRC=$(wildcard *.c)
OBJ=$(addprefix build/,$(SRC:.c=.o))
DEP=$(addprefix build/,$(SRC:.c=.d))

prog: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

build/%.o: %.c
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf build

-include $(DEP)
