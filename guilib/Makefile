#-------------------#
#  GuiLib Makefile  #
#-------------------#

.PHONY: all libguilib-static clean

#-----------------------#
#  Build GuiLib-Static  #
#-----------------------#

include make/Makefile.$(OS)

libguilib-static: libs/libguilib-static.a

libs/libguilib-static.a: src/olsrd_config.o
	$(AR) $(ARFLAGS) libs/libguilib-static.a src/olsrd_config.o

src/olsrd_config.o:
	$(CC) $(CFLAGS) -c src/olsrd_config.c -o src/olsrd_config.o

#-----------------------#
#  Clean GuiLib-Static  #
#-----------------------#

clean:
	rm -f libs/libguilib-static.a
	rm -f src/olsrd_config.o

# Local Variables:
# mode: makefile
# End: