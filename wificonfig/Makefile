#-----------------------#
#  WifiConfig Makefile  #
#-----------------------#

include make/Makefile.$(OS)

objects := $(patsubst src/%.c,src/%.o,$(wildcard src/*.c))

LDFLAGS += -Wl,-export-dynamic
LDFLAGS += -Wl,-rpath,/usr/lib
LDFLAGS += -Wl,-warn-common

.PHONY: all wifi_config clean

all: wificonfig

wificonfig: $(objects)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS) 

clean:
	rm -f src/*.o
	rm -f wificonfig