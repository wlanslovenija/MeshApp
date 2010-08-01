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
import android.content.res.Resources;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {
   
    public static final String MSG_TAG = "MeshApp -> MainActivity ";
   
    public String DATA_PATH = "/data/data/net.wlanlj.meshapp";

    public boolean isMeshActive = false;

    public boolean isInstalled = false;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
	Log.d(MSG_TAG, "Call to onCreate()");
	   
	/* Prepare for button clicks */
	Button button = (Button)findViewById(R.id.start);
        button.setOnClickListener(startMeshListener);
        button = (Button)findViewById(R.id.stop);
        button.setOnClickListener(stopMeshListener);

	/* Verify directory structure, install files if necessary */
	Log.i(MSG_TAG, "Checking directory structure, preparing for installation.");
	if (dirCheck() == 0 && isInstalled == false) {
	    install();
	}

	if (GuiLibTask.init(DATA_PATH) != 0) {
	    Log.e(MSG_TAG, "Error! GuiLib initalization failed.");
	} else {
	    Log.i(MSG_TAG, "Ready to call native GuiLib functions.");
	}
    }

    private OnClickListener startMeshListener = new OnClickListener() {

	    public void onClick(View v) {
		Log.d(MSG_TAG, "startMeshListener activated");
		Log.i(MSG_TAG, "Preparing to connect to mesh network...");

		/* Bind the start button to establishing a connection to the mesh. */
		if (isMeshActive == false) {
		    startMesh();
		} else {
		    displayToastMessage("MeshApp is currently running. Nothing to be done.");
		    Log.i(MSG_TAG, "Cannot start MeshApp when it is currently active.");
		}
	    }
	};
   
    private OnClickListener stopMeshListener = new OnClickListener() {

	    public void onClick(View v) {
		Log.d(MSG_TAG, "stopMeshListener activated");
		Log.i(MSG_TAG, "Attempting to stop Meshing...");

		/* Bind the stop button to disconnecting from the mesh. */
		if (isMeshActive == true) {
		    stopMesh();
		} else {
		    displayToastMessage("MeshApp is not currently running. Nothing to be done.");
		    Log.i(MSG_TAG, "Cannot stop MeshApp when it is currently inactive.");
		}
	    }
	};    
    
    public void startMesh() {
	
	/* Call GuiLibTask to start olsrd. */
	
	if (GuiLibTask.start() > 0) {
	    displayToastMessage("Starting olsrd, connecting to network.");
	    Log.i(MSG_TAG, "olsrd is now running through GuiLibTask.");
	    isMeshActive = true;
	} else {
	    displayToastMessage("Error! Failed to start OLSR.");
	    Log.e(MSG_TAG, "Error! GuiLibTask failed to run olsrd.");
	}
    }
    
    public void stopMesh() {	
	
	/* Call GuiLibTask to stop olsrd. */
	
	if (GuiLibTask.stop() > 0) {
	    displayToastMessage("Stopping olsrd, disconnecting from network.");
	    Log.i(MSG_TAG, "olsrd is no longer running through GuiLibTask.");
	    isMeshActive = false;
	} else {
	    displayToastMessage("Error! Failed to stop OLSR.");
	    Log.e(MSG_TAG, "Error! GuiLibTask failed to stop olsrd.");
	}
    }

    
    private int dirCheck() {

	/* Store the subdirectories we want under DATA_PATH in an array. */
	String[] dirs = {"/lib", "/bin", "/tmp"};
	
	/* Check if each directory exists, creating it if necessary. */
	for(String dir : dirs) {
	    File dirPath = new File(DATA_PATH+dir);
	    Log.i(MSG_TAG, "Checking directory "+dir);
	    if (dirPath.isDirectory()) {
		Log.i(MSG_TAG, dir+": directory already exists.");
	    } else if (dirPath.mkdir()) {
		Log.i(MSG_TAG, "Created new directory "+dir);
	    } else {
		Log.e(MSG_TAG, "Error! Cannot find or create directory "+dir);
		return -1;
	    }
	}
	return 0;
    }	
    

    public void install() {

	/* Install the binary files we need to /data/data/net.wlanlj.meshapp/bin */
	
	Log.i(MSG_TAG, "Starting MeshApp installer...");
	
	new Thread(new Runnable() {
		public void run() {
		    
		    try {
			/* Instantiate an AM and store a list files under /assets/bin in an array. */
			AssetManager assetManager = getAssets();
			String[] sourceFiles = assetManager.list("bin");

			for (String src : sourceFiles) {
			    File targetFile = new File(DATA_PATH+"/bin", src);
			    
			    /* If the target file does not exist, create a copy from the bundled asset. */
			    if (!targetFile.exists()) {
				BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(targetFile));
				BufferedInputStream in = new BufferedInputStream(assetManager.open("bin/"+src, 2));	
				
				int len; 
				byte[] buf = new byte[1024];
				
				while((len = in.read(buf)) != -1) {
				    out.write(buf, 0, len);
				}	
				
				Log.i(MSG_TAG, "Wrote file "+targetFile.toString());
				in.close();
				out.close();
			    } else {
				Log.i(MSG_TAG, src+": File already exists. Nothing to be done.");
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
	    }).start();	    
	isInstalled = true;
	displayToastMessage("MeshApp has successfully been installed!");
    }
    
    private void runCommand(String[] commands) {

	/* Run a shell command. */

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

    private void setFileExecutable(String filePath) {
	
	/* Pipe "chmod +x <file>" through the shell. */

	String[] cmd = {"chmod", "+x", filePath};
	Log.i(MSG_TAG, "Setting "+filePath+" as executable.");
	runCommand(cmd);
    }

    public void displayToastMessage(String message) {
	Toast.makeText(this, message, Toast.LENGTH_LONG).show();
    }
}
