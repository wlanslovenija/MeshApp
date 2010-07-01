
package net.wlanlj.meshapp;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class OlsrServiceBinding extends Activity {

    public static final String MSG_TAG = "[[MeshApp]]::[OlsrServiceBinding] -> ";
    private boolean olsrIsBound;
    private OlsrService olsrBoundService;   

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.olsr_service_binding);

        // Prepare buttons.
        Button button = (Button)findViewById(R.id.bind);
        button.setOnClickListener(olsrBindListener);
        button = (Button)findViewById(R.id.unbind);
        button.setOnClickListener(olsrUnbindListener);
    }
	
    // Private connection to OLSR daemon.
    private ServiceConnection olsrConnection = new ServiceConnection() {
		
	    // Do this when we connect to olsrd.
	    public void onServiceConnected(ComponentName className, IBinder service) {
		olsrBoundService = ((OlsrService.OlsrBinder)service).getService();
		Log.i(MSG_TAG, "Call to onServiceConnected()");

		Toast.makeText(OlsrServiceBinding.this, R.string.local_service_connected,
			       Toast.LENGTH_SHORT).show();
	    }
		
	    // Do this in the (hopefully rare) event that we are disconnected from olsrd.
	    public void onServiceDisconnected(ComponentName className) {
		olsrBoundService = null;
		Log.i(MSG_TAG, "Call to onServiceDisconnected()");
		Log.d(MSG_TAG, "Connection to olsrd unexpectedly interrupted.");
		Toast.makeText(OlsrServiceBinding.this, R.string.local_service_disconnected,
			       Toast.LENGTH_SHORT).show();
	    }
	};
	
   private OnClickListener olsrBindListener = new OnClickListener() {
        public void onClick(View v) {
            bindService(new Intent(OlsrServiceBinding.this, 
                    OlsrService.class), olsrConnection, Context.BIND_AUTO_CREATE);
            olsrIsBound = true;
        }
    };

    private OnClickListener olsrUnbindListener = new OnClickListener() {
        public void onClick(View v) {
            if (olsrIsBound) {
                // Detach our existing connection.
                unbindService(olsrConnection);
                olsrIsBound = false;
            }
        }
    };
}
