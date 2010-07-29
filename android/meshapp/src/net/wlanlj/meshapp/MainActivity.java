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


/**
 * A simple class which controls the OLSR Daemon.
 */

public class MainActivity extends Activity {
   
    public static final String MSG_TAG = "MeshApp -> MainActivity ";
   
    public static final String DATA_PATH = "/data/data/net.wlanlj.meshapp";


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
	Log.d(MSG_TAG, "Call to onCreate()");

	/* Prepare for button clicks */
	Button button = (Button)findViewById(R.id.start);
        button.setOnClickListener(olsrStartListener);
        button = (Button)findViewById(R.id.stop);
        button.setOnClickListener(olsrStopListener);
    }

    private OnClickListener olsrStartListener = new OnClickListener() {
	    public void onClick(View v) {
		Log.d(MSG_TAG, "olsrStartListener activated");
		Log.i(MSG_TAG, "Attempting to start olsrd...");
		if (startMesh() == -1)
		    Log.e(MSG_TAG, "Error! Unable to start olsrd.");
		else
		    Log.i(MSG_TAG, "olsrd is now running.");
	    }
	};
   
    private OnClickListener olsrStopListener = new OnClickListener() {
	    public void onClick(View v) {
		Log.d(MSG_TAG, "olsrStopListener activated");
		Log.i(MSG_TAG, "Attempting to stop olsrd...");
		if (stopMesh() == -1)
		    Log.e(MSG_TAG, "Error! Unable to stop olsrd.");
		else
		    Log.i(MSG_TAG, "olsrd has been stopped.");
	    }
	};    


    public int startMesh() {

	Log.i(MSG_TAG, "Installing binaries...");
	install();

	if (GuiLibTask.startOlsrd() == -1) {
	    Log.e(MSG_TAG, "Error! Native method startOlsrd() returned -1.");
	    return -1;
	}

	/*
	  A default way to start olsrd, if Native method fails for some reason.

	  String[] cmd = {"su", "-c", "olsrd"};
	  runCommand(cmd);
	*/


	return 0;
    }
    
    public int stopMesh() {
	
	if (GuiLibTask.stopOlsrd() == -1) {
	    return -1;
	}
	return 0;
    }

    private void chmod(String filePath, String permission) {
	String[] cmd = {"chmod", permission, filePath};
	Log.i(MSG_TAG, "Setting "+filePath+" with permission "+permission);
	runCommand(cmd);
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
    
    public void install() {
	Log.i(MSG_TAG, "Starting MeshApp installer...");

	if (dirCheck() == 0) {
	    new Thread(new Runnable() {
		    public void run() {
			
			try {
			    AssetManager assetManager = getAssets();
			    String[] sourceFiles = assetManager.list("bin");
	

			    for (String src : sourceFiles) {
				File targetFile = new File(DATA_PATH+"/bin", src);

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
			    }	    
  
		    } catch (IOException io) {
			Log.e(MSG_TAG, io.getMessage());
		    } catch (Exception ex) {
			Log.e(MSG_TAG, ex.getMessage());
		    }
		}	    
	    }).start();

	} else {
	    Log.e(MSG_TAG, "Error! Unable to install files to /bin directory.");
	}	
    }

    private int dirCheck() {
	String[] dirs = {"/lib", "/bin", "/etc", "/tmp"};

	for(String dir : dirs) {
	    File dirPath = new File(DATA_PATH+dir);
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
}