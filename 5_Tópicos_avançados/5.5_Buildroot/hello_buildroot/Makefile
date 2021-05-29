OBJS=hello_buildroot.o

all:	hello_buildroot.out

hello_buildroot.out:	$(OBJS)
	$(CC) $(LDFLAGS) -o hello_buildroot.out $(OBJS)

$(OBJS): %.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<
