SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%.out,$(SRCS))
all: $(PROGS)
%: %.c
	gcc $(CFLAGS) -o $@ $< `pkg-config --cflags --libs gtk+-2.0`
clean:
	rm -f $(PROGS)