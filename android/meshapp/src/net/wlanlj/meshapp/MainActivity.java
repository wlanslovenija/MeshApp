package net.wlanlj.meshapp;

import android.R.drawable;
import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

/**
 * A simple class which controls the OLSR Daemon.
 */

public class MainActivity extends Activity {
   
    /** Useful for debugging. */
    public static final String MSG_TAG = "[[MeshApp]]::[MainActivity] -> ";

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.olsr_main);
	Log.i(MSG_TAG, "Call to onCreate()");

	// Prepare for button clicks.
	Button button = (Button)findViewById(R.id.start);
        button.setOnClickListener(olsrStartListener);
        button = (Button)findViewById(R.id.stop);
        button.setOnClickListener(olsrStopListener);
    }

    private OnClickListener olsrStartListener = new OnClickListener() {
	    public void onClick(View v) {
		Log.i(MSG_TAG, "olsrStartListener activated");
		Log.d(MSG_TAG, "Attempting to start olsrd...");
		if (runRootCommand("olsrd") == true) {
		    Log.i(MSG_TAG, "OLSR Daemon has started successfully!");
		} else {
		    Log.d(MSG_TAG, "Unable to start OLSR Daemon.");
		}
	    }
	};   
    private OnClickListener olsrStopListener = new OnClickListener() {
	    public void onClick(View v) {
		Log.i(MSG_TAG, "olsrStopListener activated");
		Log.i(MSG_TAG, "Attempting to stop olsrd...");
	    }
	};
    
    public boolean runRootCommand(String command) {
	Log.d(MSG_TAG, "Running command as root ==> su -c \""+command+"\"");
	int exit = OlsrNative.runCommand("su -c \""+command+"\"");
	if (exit == 0) {
	    return true;
	} else {
	    Log.d(MSG_TAG, "Failed to run command "+command+"as root: returns "+exit);
	    return false;
	}
    }
}