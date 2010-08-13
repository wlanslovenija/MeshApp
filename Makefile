#----------------------------------#
#  Top-Level Makefile for MeshApp  #
#----------------------------------#

.PHONY: all olsrd guilib-static guilib meshapp olsrd_txtinfo wifi_config

all: olsrd wifi_config guilib meshapp

#--------#
#  OLSR  #
#--------#

olsrd: android/meshapp/assets/bin/olsrd

android/meshapp/assets/bin/olsrd: olsr/olsrd/olsrd
	cp olsr/olsrd/olsrd android/meshapp/assets/bin/olsrd

olsr/olsrd/olsrd:
	make -C olsr/olsrd

#----------------#
#  OLSR Plugins  #
#----------------#

olsrd_txtinfo: android/meshapp/assets/lib/olsrd_txtinfo.so.0.1

android/meshapp/assets/lib/olsrd_txtinfo.so.0.1: olsr/olsrd/lib/txtinfo/olsrd_txtinfo.so.0.1
	cp olsr/olsrd/lib/txtinfo/olsrd_txtinfo.so.0.1 android/meshapp/assets/lib/olsrd_txtinfo.so.0.1

olsr/olsrd/lib/txtinfo/olsrd_txtinfo.so.0.1:
	make -C olsr/olsrd/lib/txtinfo

#--------------#
#  WifiConfig  #
#--------------#

wifi_config: android/meshapp/assets/bin/wificonfig

android/meshapp/assets/bin/wificonfig: wificonfig/wificonfig
	cp wificonfig/wificonfig android/meshapp/assets/bin/wificonfig

wificonfig/wificonfig:
	make -C wificonfig

#------------------------------#
#  Shared Android GUI Library  #
#------------------------------#

guilib: android/meshapp/obj/local/armeabi/libguilib.so

android/meshapp/obj/local/armeabi/libguilib.so: guilib-static
	$(NDK)/ndk-build V=1 -C android/meshapp

#------------------------------#
#  Static Android GUI Library  #
#------------------------------#

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

.PHONY: clean_guilib clean_wificonfig clean_meshapp clean_wificonfig

clean: clean_guilib clean_wificonfig clean_meshapp

uberclean: clean_olsrd clean_wificonfig clean_guilib clean_meshapp

clean_olsrd:
	make -C olsr/olsrd uberclean
	rm -f olsr/olsrd/olsrd 
	rm -f android/meshapp/assets/bin/olsrd
	rm -f android/meshapp/assets/lib/olsrd_txtinfo.so.0.1

clean_guilib:
	make -C guilib clean
	rm -f android/meshapp/obj/local/armeabi/libguilib.so
	rm -f android/meshapp/obj/local/armeabi/libguilib-static.a
	rm -f android/meshapp/obj/local/armeabi/objs/guilib/net_wlanlj_meshapp_GuiLibTask.o
	rm -f android/meshapp/obj/local/armeabi/objs/guilib/net_wlanlj_meshapp_GuiLibTask.o.d

clean_wificonfig:
	make -C wificonfig clean
	rm -f wificonfig/wificonfig
	rm -f wificonfig/src/wificonfig
	rm -f android/meshapp/assets/bin/wificonfig

clean_meshapp:
	ant clean -buildfile android/meshapp/build.xml
	rm -f MeshApp.apk

# Local Variables:
# mode: makefile
# End: