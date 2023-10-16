CC=gcc
INCLUDE=-Iinclude
LINK=-Llib
CFLAGS=$(INCLUDE) $(LINK) -std=c99 -Wall -lraylib -Wl,-rpath lib -o2

BINARY=yavg
OBJFILES=build/main.o build/voxel.o build/textures.o

all: $(BINARY)

$(BINARY): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o:src/%.c
	$(CC) -c -o $@ $^

clean:
	rm -rf $(OBJFILES)