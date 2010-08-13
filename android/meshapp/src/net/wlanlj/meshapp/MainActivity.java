package net.wlanlj.meshapp;

import java.io.File;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.util.ArrayList;
import java.util.Properties;

import android.app.PendingIntent;
import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.res.Resources;
import android.content.res.AssetManager;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {
   
    public static final String MSG_TAG = "MainActivity ";

    public String DATA_PATH = "/data/data/net.wlanlj.meshapp";
    
    public AssetManager assetManager;

    public boolean isMeshActive = false;

    public boolean isInstalled = false;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);    

	displayToastMessage("MeshApp-0.5-test");
	
	Log.i(MSG_TAG, "Checking permissions...");
	permCheck("android.permission.CHANGE_WIFI_STATE");
	permCheck("net.wlanlj.meshapp.permission.WPA_SUPPLICANT_CLIENT");
	Log.i(MSG_TAG, "Checking files...");
	install();
	
	Button button = (Button)findViewById(R.id.start);
        button.setOnClickListener(startMeshListener);
        button = (Button)findViewById(R.id.stop);
        button.setOnClickListener(stopMeshListener);
    }
	
    private OnClickListener startMeshListener = new OnClickListener() {

	    public void onClick(View v) {
		if (isMeshActive == false) {
		    GuiLibTask.init(DATA_PATH);
		    startMesh();
		} else {
		    displayToastMessage("Meshapp is already running, cannot start again.");
		    Log.i(MSG_TAG, "Attempt to start MeshApp while already active.");
		
		}
	    }
	};
	
    private OnClickListener stopMeshListener = new OnClickListener() {
		
	    public void onClick(View v) {
		    
		if (isMeshActive == true) {
		    stopMesh();
		} else {
		    displayToastMessage("There is nothing to stop.");
		    Log.i(MSG_TAG, "Attempt to stop MeshApp while inactive.");
		}
	    }
	};    
	
    public void startMesh() {
	
	/* Call GuiLibTask to start olsrd. */
	
	if (GuiLibTask.start() != 0) {
	    displayToastMessage("Error! MeshApp did not start..");
	} else {
	    displayToastMessage("MeshApp has started!");
	    isMeshActive = true;
	}
    }
    
    public void stopMesh() {	
	    
	/* Call GuiLibTask to stop olsrd. */
	    
	if (GuiLibTask.stop() != 0) {
	    displayToastMessage("Error! MeshApp did not stop!");
	} else {
	    displayToastMessage("MeshApp has stopped.");
	    isMeshActive = false;
		
	}
    }
    
    public void permCheck(String permName) {
	
	try {
	    PackageManager pm = getPackageManager();
	    if (pm.checkPermission(permName, "net.wlanlj.meshapp") == 0) {
		Log.i(MSG_TAG, "has permission "+permName+": true.");
	    } else {
		Log.e(MSG_TAG, "has permission "+permName+": false.");
	    }

	    for (int i : pm.getPackageGids("net.wlanlj.meshapp")) {
		    Log.i(MSG_TAG, "net.wlanlj.meshapp: assigned to gid "+i);
		}
	} catch (Exception ex) {
	    Log.e(MSG_TAG, "Error! "+ex.getMessage());
	}
    }

    public void dirCheck() {
	
	/* Store the subdirectories we want under DATA_PATH in an array. */
	String[] dirs = {"/lib", "/bin", "/tmp"};
	
	/* Check if each directory exists, creating it if necessary. */
	for(String dir : dirs) {
	    File dirPath = new File(DATA_PATH+dir);
	    Log.i(MSG_TAG, "Checking for directory "+dir);
	    if (dirPath.isDirectory()) {
		Log.i(MSG_TAG, dir+": already exists.");
	    } else if (dirPath.mkdir()) {
		Log.i(MSG_TAG, "Created new directory "+dir);
	    } else {
		Log.e(MSG_TAG, "Error! Cannot find or create directory "+dir);
	    }
	}
    }	
    

    public void install() {

	try {
	    
	    assetManager = getAssets();
	    String[] binFiles = assetManager.list("bin");
	    //	    String[] libFiles = assetManager.list("lib");
	    
	    dirCheck();
	    writeFiles(binFiles, "bin");
	    //    writeFiles(libFiles, "lib");

	} catch (IOException io) {
	    Log.e(MSG_TAG, "Error! Install failed.");
	    Log.e(MSG_TAG, io.getMessage());
	}
	isInstalled = true;
	displayToastMessage("MeshApp is installed!");
    }

    public void writeFiles(String[] sourceFiles, String sourceDirectoryName) {

	try {
	    
	    for (String src : sourceFiles) {
		
		File targetDirectory = new File(DATA_PATH+'/'+sourceDirectoryName);
		File targetFile = new File(targetDirectory, src);

		File sourceFile = new File(sourceDirectoryName, src);
		
		/* If the target file does not exist, create a copy from the bundled asset. */
		if (!targetFile.exists()) {
		    BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(targetFile));
		    BufferedInputStream in = new BufferedInputStream(assetManager.open(sourceFile.toString(), 2));	
		    
		    int len; 
		    byte[] buf = new byte[1024];
		    
		    while((len = in.read(buf)) != -1) {
			out.write(buf, 0, len);
		    }	
		    
		    Log.i(MSG_TAG, "Wrote new file "+targetFile.toString());
		    in.close();
		    out.close();
		} else {
		    Log.i(MSG_TAG, src+": is already installed.");
		}
	    }
	    
	} catch (IOException io) {
	    Log.e(MSG_TAG, "Error! Install failed.");
	    Log.e(MSG_TAG, io.getMessage());
	} catch (Exception ex) {
	    Log.e(MSG_TAG, "Error! Install failed.");
	    Log.e(MSG_TAG, ex.getMessage());
	}
    }	        
    
    public void displayToastMessage(String message) {
	Toast.makeText(this, message, Toast.LENGTH_LONG).show();
    }
}