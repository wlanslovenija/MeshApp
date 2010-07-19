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
		// Here is where we call OlsrNative.startOlsr()
	    }
	};
   
    private OnClickListener olsrStopListener = new OnClickListener() {
	    public void onClick(View v) {
		Log.i(MSG_TAG, "olsrStopListener activated");
		Log.i(MSG_TAG, "Attempting to stop olsrd...");
		// Here is where we call OlsrNative.stopOlsr()
	    }
	};    
}
