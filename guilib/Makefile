include make/Makefile.$(OS)

SRCS = src/olsrd_config.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: libs/libguilib.a

libs/libguilib.a: libguilib.a
	mv libguilib.a libs/libguilib.a

libguilib.a: $(OBJS)
	ar rcs libguilib.a $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f libs/libguilib.a
	rm -f $(OBJS)

# Local Variables:
# mode: makefile
# End: