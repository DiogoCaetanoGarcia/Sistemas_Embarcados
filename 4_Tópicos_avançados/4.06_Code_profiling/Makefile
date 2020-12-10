SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
all: $(PROGS)
%: %.c
	gcc $(CFLAGS) -pg -static -o $@ $< -lm -lpthread
clean:
	rm -f $(PROGS)