CC=gcc
CFLAGS=-O0 -MMD -fdiagnostics-color=auto -g -nostdlib -m64
LDFLAGS=
SRC=$(wildcard src/*.c)
FILES=$(SRC:src/%=%)
OBJ=$(addprefix build/,$(FILES:.c=.o))
DEP=$(addprefix build/,$(FILES:.c=.d))

prog: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf build

-include $(DEP)
