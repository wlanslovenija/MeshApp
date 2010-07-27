package net.wlanlj.meshapp;

import android.util.Log;

class GuiLibTask {

    public static final String MSG_TAG = "MeshApp -> GuiLibTask ";

    static {
	try {
	    Log.i(MSG_TAG, "Attempting to load GUI Library...");
	    System.loadLibrary("libguilib");
	}
	catch (Exception ex) {
	    Log.e(MSG_TAG, "GuiLib failed to load!");
	}
    }

    public static native int startOlsrd();

    public static native int stopOlsrd();
}
