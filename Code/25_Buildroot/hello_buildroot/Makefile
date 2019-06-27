OBJS=hello_buildroot.o

all:	hello_buildroot

hello_buildroot:	$(OBJS)
	$(CC) $(LDFLAGS) -o hello_buildroot $(OBJS)

$(OBJS): %.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<
