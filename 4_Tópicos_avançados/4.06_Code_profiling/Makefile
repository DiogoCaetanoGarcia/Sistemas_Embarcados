SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%.out,$(SRCS))
all: $(PROGS)
%: %.c
	gcc $(CFLAGS) -pg -static -o $@ $< -lm -lpthread
clean:
	rm -f $(PROGS)