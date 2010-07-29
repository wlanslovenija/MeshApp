include make/Makefile.$(OS)

SRCS = src/olsrd_config.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: libs/libguilib-static.a

libs/libguilib-static.a: libguilib-static.a
	mv libguilib-static.a libs/libguilib-static.a

libguilib-static.a: $(OBJS)
	ar rcs libguilib-static.a $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f libs/libguilib-static.a
	rm -f $(OBJS)

# Local Variables:
# mode: makefile
# End: