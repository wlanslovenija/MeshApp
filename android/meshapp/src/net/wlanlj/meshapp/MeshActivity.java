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
import java.util.Properties;

import android.app.Activity;
import android.app.PendingIntent;
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

public class MeshActivity extends Activity {
   
    static final private String MSG_TAG = "MeshApp ";

    static final public String DATA_PATH = "/data/data/net.wlanlj.meshapp";

    public AssetManager assetManager;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.mesh_activity);    
	
	checkDataDir();	
	install();
	
	((Button) findViewById(R.id.start)).setOnClickListener(startButtonListener);
	((Button) findViewById(R.id.stop)).setOnClickListener(stopButtonListener);

	GuiLibTask.init(DATA_PATH);
    }

    @Override
    protected void onResume() {
	super.onResume();
    }

    public void install() {
	try {
	    assetManager = getAssets();
	    String[] binFiles = assetManager.list("bin");
	    writeFiles(binFiles, "bin");
	} catch (IOException io) {
	    Log.e(MSG_TAG, "Error! Install failed: "+io.getMessage());
	}
    }

    public void checkDataDir() {
	String[] dirs = {"/lib", "/bin", "/tmp"};
	
	for(String dir : dirs) {
	    File dirPath = new File(DATA_PATH+dir);
	    if (dirPath.isDirectory())
		Log.i(MSG_TAG, dir+": already exists.");
	    else if (dirPath.mkdir())
		Log.i(MSG_TAG, "Created new directory "+dir);
	    else
		Log.e(MSG_TAG, "Error! Cannot find or create directory "+dir);
	}
    }	   

    public void writeFiles(String[] sourceFiles, String sourceDirectoryName) {
	try {
	    for (String src : sourceFiles) {
		File targetDirectory = new File(DATA_PATH+'/'+sourceDirectoryName);
		File targetFile = new File(targetDirectory, src);
		File sourceFile = new File(sourceDirectoryName, src);
		
		if (!targetFile.exists()) {
		    int len; 
		    byte[] buf = new byte[1024];
		    BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(targetFile));
		    BufferedInputStream in = new BufferedInputStream(assetManager.open(sourceFile.toString(), 2));	
		    
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
	    Log.e(MSG_TAG, "Error! Install failed: "+io.getMessage());
	} catch (Exception ex) {
	    Log.e(MSG_TAG, "Error! Install failed: "+ex.getMessage());
	}
    }	        

    private OnClickListener startButtonListener = new OnClickListener() {
	    public void onClick(View v) {
		startMesh();
	    }
	};
    
    
    private OnClickListener stopButtonListener = new OnClickListener() {
	    public void onClick(View v) {
		stopMesh();
	    }
	};    
    
    public void startMesh() {
	if (GuiLibTask.start() != 0) {
	    Log.d(MSG_TAG, "Something did not start correctly...");
	} else {
	    displayToastMessage("MeshApp has started!");

	}
    }
    
    public void stopMesh() {	
	if (GuiLibTask.stop() != 0) {
	    Log.d(MSG_TAG, "Something did not stop correctly...");
	} else {
	    displayToastMessage("MeshApp has stopped!");
	}
    }
    
    public void displayToastMessage(String message) {
	Toast.makeText(this, message, Toast.LENGTH_LONG).show();
    }
}