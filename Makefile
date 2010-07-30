#----------------------------------#
#  Top-Level Makefile for MeshApp  #
#----------------------------------#

.PHONY: all olsrd guilib meshapp

all: olsrd guilib meshapp

#----------------#
#  OLSRD Binary  #
#----------------#

olsrd: android/meshapp/assets/bin/olsrd

android/meshapp/assets/bin/olsrd: olsr/olsrd/olsrd
	cp olsr/olsrd/olsrd android/meshapp/assets/bin/olsrd

olsr/olsrd/olsrd:
	make -C olsr/olsrd

#------------------------------#
#  Shared Android GUI Library  #
#------------------------------#

guilib: android/meshapp/obj/local/armeabi/libguilib.so

android/meshapp/obj/local/armeabi/libguilib.so: guilib-static
	$(NDK)/ndk-build V=1 -C android/meshapp

#------------------------------#
#  Static Android GUI Library  #
#------------------------------#

.PHONY: guilib_static clean_guilib_static

guilib-static: android/meshapp/obj/local/armeabi/libguilib-static.a

android/meshapp/obj/local/armeabi/libguilib-static.a: guilib/libs/libguilib-static.a
	cp guilib/libs/libguilib-static.a android/meshapp/obj/local/armeabi/libguilib-static.a

guilib/libs/libguilib-static.a: 
	make -C guilib

#---------------#
#  MeshApp.apk  #
#---------------#

meshapp: MeshApp.apk

MeshApp.apk: android/meshapp/bin/MeshApp-debug.apk
	cp android/meshapp/bin/MeshApp-debug.apk MeshApp.apk

android/meshapp/bin/MeshApp-debug.apk: guilib
	ant debug -buildfile android/meshapp/build.xml

#---------#
#  Clean  #
#---------#

clean: clean_guilib clean_meshapp

uberclean: clean_olsrd clean_guilib clean_meshapp

clean_olsrd:
	make -C olsr/olsrd uberclean
	rm -f olsr/olsrd/olsrd android/meshapp/assets/bin/olsrd

clean_guilib:
	make -C guilib clean
	rm -f android/meshapp/obj/local/armeabi/objs/libguilib.so
	rm -f android/meshapp/obj/local/armeabi/objs/libguilib-static.a
	rm -f android/meshapp/obj/local/armeabi/objs/guilib/net_wlanlj_meshapp_GuiLibTask.o
	rm -f android/meshapp/obj/local/armeabi/objs/guilib/net_wlanlj_meshapp_GuiLibTask.o.d

clean_meshapp:
	ant clean -buildfile android/meshapp/build.xml
	rm -f MeshApp.apk

# Local Variables:
# mode: makefile
# End: