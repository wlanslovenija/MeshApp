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
     * This is the controller class for OlsrService.
     * Also this is the default activity for MeshApp.
     */

public class MainActivity extends Activity {
   
    /** Useful for debugging. */
    public static final String MSG_TAG = "[[MeshApp]]::[MainActivity] -> ";
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.olsr_service_controller);
	Log.i(MSG_TAG, "Call to onCreate()");

	// Prepare for button clicks.
	Button button = (Button)findViewById(R.id.start);
        button.setOnClickListener(olsrStartListener);
        button = (Button)findViewById(R.id.stop);
        button.setOnClickListener(olsrStopListener);
    }

    private OnClickListener olsrStartListener = new OnClickListener() {
	    public void onClick(View v) {
		startService(new Intent(MainActivity.this,
					OlsrService.class));
		Log.i(MSG_TAG, "olsrStartListener::onClick()");
		Log.i(MSG_TAG, "Starting olsrd...");
	    }
	};
    
    private OnClickListener olsrStopListener = new OnClickListener() {
	    public void onClick(View v) {
		stopService(new Intent(MainActivity.this,
				       OlsrService.class));
		Log.i(MSG_TAG, "olsrStopListener::onClick()");
		Log.i(MSG_TAG, "Stopping olsrd...");
	    }
	};
}    