include make/Makefile.$(OS)

.PHONY: all guilib clean

all: guilib

guilib: libs/libguilib.a

libs/libguilib.a: libguilib.a
	mv libguilib.a libs/libguilib.a

libguilib.a: src/olsrd_conf.o
	ar -cvq libguilib.a src/olsrd_config.o

src/olsrd_conf.o:
	$(CC) $(CFLAGS) -c src/olsrd_config.c -o src/olsrd_config.o
clean:
	rm -f src/olsrd_config.o libs/libguilib.a