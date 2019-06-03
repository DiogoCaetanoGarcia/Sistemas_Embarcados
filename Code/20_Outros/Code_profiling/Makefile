SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
all: $(PROGS)
%: %.c
	gcc $(CFLAGS) -pg -static -o $@ $< -lm
clean:
	rm -f $(PROGS)