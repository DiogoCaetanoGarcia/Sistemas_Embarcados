# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g -lpthread

# Gather all .c files and corresponding executables
SRCS = $(wildcard *.c)
EXES = $(SRCS:.c=)

# Default rule
all: $(EXES)

# Rule to build each executable
%: %.c
	$(CC) $(CFLAGS) -o $@.out $<

# Clean rule
clean:
	rm -f *.out *.txt

# Phony targets
.PHONY: all clean
