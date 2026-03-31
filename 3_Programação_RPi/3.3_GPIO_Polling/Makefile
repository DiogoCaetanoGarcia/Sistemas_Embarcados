CC = gcc
CFLAGS = -Wall -Iinclude $(shell pkg-config --cflags libgpiod)
LDFLAGS = $(shell pkg-config --libs libgpiod) -lpthread -lwiringPi

SRC = src/gpiod_lib.c
APPS = $(wildcard exemplos/*.c)

BIN = $(patsubst exemplos/%.c, build/%, $(APPS))

all: $(BIN)

build/%: exemplos/%.c $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf build
