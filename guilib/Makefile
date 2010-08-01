#-------------------#
#  GuiLib Makefile  #
#-------------------#

.PHONY: all libguilib-static clean

#-----------------------#
#  Build GuiLib-Static  #
#-----------------------#

include make/Makefile.$(OS)

libguilib-static: libs/libguilib-static.a

libs/libguilib-static.a: src/guilib.o
	$(AR) $(ARFLAGS) libs/libguilib-static.a src/guilib.o

src/guilib.o:
	$(CC) $(CFLAGS) -c src/guilib.c -o src/guilib.o

#-----------------------#
#  Clean GuiLib-Static  #
#-----------------------#

clean:
	rm -f libs/libguilib-static.a
	rm -f src/guilib.o

# Local Variables:
# mode: makefile
# End: