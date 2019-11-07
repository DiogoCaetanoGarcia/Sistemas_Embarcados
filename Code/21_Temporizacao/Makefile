SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
all: $(PROGS)
%: %.c
	gcc $(CFLAGS) -o $@ $<
clean:
	rm -f $(PROGS)