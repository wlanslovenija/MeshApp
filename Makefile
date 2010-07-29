.PHONY: all clean

all: olsrd guilib meshapp

clean: clean_olsrd clean_guilib clean_meshapp

##
# OLSRD
##

.PHONY: olsrd clean_olsrd

olsrd: android/meshapp/assets/bin/olsrd

android/meshapp/assets/bin/olsrd: olsr/olsrd/olsrd
	cp olsr/olsrd/olsrd android/meshapp/assets/bin/olsrd

olsr/olsrd/olsrd:
	make -C olsr/olsrd

clean_olsrd:
	make -C olsr/olsrd uberclean
	rm -f olsr/olsrd/olsrd android/meshapp/assets/bin/olsrd

##
# GUIlib - Common
##

.PHONY: guilib clean_guilib

guilib: guilib_static guilib_shared

clean_guilib: clean_guilib_static clean_guilib_shared


##
# GUIlib - Static
##

.PHONY: guilib_static clean_guilib_static

guilib_static: android/meshapp/obj/local/armeabi/libguilib-static.a

android/meshapp/obj/local/armeabi/libguilib-static.a: guilib/libs/libguilib-static.a
	cp guilib/libs/libguilib-static.a android/meshapp/obj/local/armeabi/libguilib-static.a

guilib/libs/libguilib-static.a: 
	make -C guilib all

clean_guilib_static:
	make -C guilib clean
	rm -f android/meshapp/obj/local/armeabi/libguilib-static.a

##
# GUIlib - Shared
##

.PHONY: guilib_shared clean_guilib_shared

guilib_shared: android/meshapp/obj/local/armeabi/libguilib.so

android/meshapp/obj/local/armeabi/libguilib.so:
	$(NDK)/ndk-build V=1 -C android/meshapp

clean_guilib_shared:
	rm -f android/meshapp/obj/local/armeabi/libguilib.so

##
# MeshApp
##

meshapp: MeshApp.apk

MeshApp.apk: android/meshapp/bin/MeshApp-debug.apk
	cp android/meshapp/bin/MeshApp-debug.apk MeshApp.apk

android/meshapp/bin/MeshApp-debug.apk:
	ant debug -buildfile android/meshapp/build.xml

clean_meshapp:
	ant clean -buildfile android/meshapp/build.xml
	rm -f MeshApp.apk

# Local Variables:
# mode: makefile
# End: