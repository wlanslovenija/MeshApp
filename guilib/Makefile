#-------------------#
#  GuiLib Makefile  #
#-------------------#

.PHONY: all libguilib-static clean

#-----------------------#
#  Build GuiLib-Static  #
#-----------------------#

include make/Makefile.$(OS)

libguilib-static: libs/libguilib-static.a

libs/libguilib-static.a: src/guilib.o src/log.o src/config.o
	$(AR) $(ARFLAGS) libs/libguilib-static.a src/guilib.o src/log.o src/config.o

src/guilib.o:
	$(CC) $(CFLAGS) -c src/guilib.c -o src/guilib.o

src/log.o:
	$(CC) $(CFLAGS) -c src/log.c -o src/log.o

src/config.o:
	$(CC) $(CFLAGS) -c src/config.c -o src/config.o

#-----------------------#
#  Clean GuiLib-Static  #
#-----------------------#

clean:
	rm -f libs/libguilib-static.a
	rm -f src/guilib.o
	rm -f src/log.o
	rm -f src/config.o

# Local Variables:
# mode: makefile
# End: