CC=gcc
INCLUDE=-Iinclude
LINK=-Llib
CFLAGS=$(INCLUDE) $(LINK) -std=c99 -Wall -Bstatic -lraylib -Wl,-rpath lib

BINARY=yavg
OBJFILES=build/main.o build/voxel.o

all: $(BINARY)

$(BINARY): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o:src/%.c
	$(CC) -c -o $@ $^

clean:
	rm -rf $(BINARY) $(OBJFILES)