.PHONY: all olsrd clean_olsrd guilib clean_guilib meshapp clean_meshapp clean

all: olsrd guilib meshapp

olsrd: android/meshapp/res/raw/olsrd

android/meshapp/res/raw/olsrd: olsr/olsrd/olsrd
	cp olsr/olsrd/olsrd android/meshapp/res/raw/olsrd

olsr/olsrd/olsrd:
	make -C olsr/olsrd

clean_olsrd:
	make -C olsr/olsrd uberclean
	rm -f olsr/olsrd/olsrd olsr/olsrd/olsrd/android/meshapp/res/raw/olsrd

guilib: android/meshapp/libs/libguilib.so

android/meshapp/libs/libguilib.so:
	$(NDK)/ndk-build -C android/meshapp

clean_guilib:
	rm -f android/meshapp/libs/armeabi/libguilib.so

meshapp: MeshApp.apk

MeshApp.apk: android/meshapp/bin/MeshApp-debug.apk
	cp android/meshapp/bin/MeshApp-debug.apk MeshApp.apk

android/meshapp/bin/MeshApp-debug.apk:
	ant debug -buildfile android/meshapp/build.xml

clean_meshapp:
	rm -f MeshApp.apk

clean: clean_olsrd clean_guilib clean_meshapp