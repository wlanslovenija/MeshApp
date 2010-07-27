
package net.wlanlj.meshapp;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Properties;

import android.app.Application;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.res.AssetFileDescriptor;
import android.content.res.Resources;
import android.content.res.AssetManager;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;


public class MeshApplication extends Application {

    public static final String MSG_TAG = "MeshApp -> MeshApplication";

    public void onCreate() {
	Log.d(MSG_TAG, "calling onCreate()");
	this.installBinaries();
    }


    public void onTerminate() {
	Log.d(MSG_TAG, "calling onTerminate()");
	this.stopMesh();
    }

    public static int startMesh() {
	if (GuiLibTask.startOlsrd() == 0)
	    return 0;
	else
	    return -1;
    }

    public static int stopMesh() {
	if (GuiLibTask.stopOlsrd() == 0)
	    return 0;
	else
	    return -1;
    }
 
    public void installBinaries() {
	Log.d(MSG_TAG, "Installing binary files to /data/data/net.wlanlj.meshapp...");
	new Thread(new Runnable() {
		public void run() {
		    AssetManager assetManager = getAssets();
		    AssetFileDescriptor assetFd;
		    BufferedWriter assetWriter;
		    String[] bin_files = null;
		    try {
			bin_files = assetManager.list("bin");
			for (String bin : bin_files) {
			    assetFd = assetManager.openFd(bin);
			    assetWriter = new BufferedWriter(new FileWriter(assetFd.getFileDescriptor()));
			    assetWriter.flush();
			    assetWriter.close();
			}
		    } catch (IOException ex) {
			Log.e(MSG_TAG, ex.getMessage());
		    }
		}	    
	    }).start();
	
    }
    
    private void runCommand(String[] commands) {
	ArrayList res = new ArrayList(10);

	try {
	    Process process = Runtime.getRuntime().exec(commands);
	    DataOutputStream os = new DataOutputStream(process.getOutputStream());
	    DataInputStream osRes = new DataInputStream(process.getInputStream());

	    for (String single : commands) {
		os.writeBytes(single + "\n");
		os.flush();
		res.add(osRes.readLine());
	    }
	    os.writeBytes("exit\n");
	    os.flush();
	    process.waitFor();

	} catch(Exception ex) {
	    Log.e(MSG_TAG, ex.getMessage());
	}
    }
    
}
    
 