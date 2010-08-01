package net.wlanlj.meshapp;

import android.util.Log;

class GuiLibTask {

    public static final String MSG_TAG = "MeshApp -> GuiLibTask ";

    static {
	try {
	    Log.i(MSG_TAG, "Attempting to load GUI Library...");
	    System.loadLibrary("guilib");
	}
	catch (Exception ex) {
	    Log.e(MSG_TAG, "GuiLib failed to load!");
	}
    }

    public static native int init(String path);

    public static native int start();

    public static native int stop();
}
