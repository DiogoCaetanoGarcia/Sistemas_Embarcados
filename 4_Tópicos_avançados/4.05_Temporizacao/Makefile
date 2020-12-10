SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%.out,$(SRCS))
all: $(PROGS)
%: %.c
	gcc $(CFLAGS) -o $@ $<
clean:
	rm -f $(PROGS)