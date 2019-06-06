SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
all: $(PROGS)
%: %.c
	gcc $(CFLAGS) -o $@ $< `pkg-config --cflags --libs gtk+-3.0`
clean:
	rm -f $(PROGS)