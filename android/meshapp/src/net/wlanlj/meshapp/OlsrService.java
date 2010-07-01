/**
 * Written by charles on June 28, 2010. 
 * Last modified by charles on June 30, 2010.
 */


package net.wlanlj.meshapp;
import android.R.drawable;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.os.Parcel;
import android.util.Log;
import android.widget.Toast;
import net.wlanlj.meshapp.ShellCommand;
import net.wlanlj.meshapp.ShellCommand.CommandResult;


public class OlsrService extends Service {    

    // Useful for debugging.
    public static final String MSG_TAG = "[[MeshApp]]::[OlsrService] -> ";

    // The notification manager.
    private NotificationManager olsrNotifyManager;

    // Instance of binding class for olsrd.
    private final IBinder olsrBinder = new OlsrBinder();

    // Run OLSR daemon through a ShellCommand instance.
    private ShellCommand olsrd = new ShellCommand();

    /**
     * Subclass accessible to client. OLSR daemon will run as part of the process which calls it.
     * No need for IPC this way, but this may change in the future if there is good reason.
     */

    public class OlsrBinder extends Binder {
	OlsrService getService() {
	    return OlsrService.this;
	}
    }
   
    // @Override
    public void onCreate() {
	olsrNotifyManager = (NotificationManager)getSystemService(NOTIFICATION_SERVICE);
	showNotification();
	Log.i(MSG_TAG, "Call to onCreate()");
	CommandResult result = olsrd.sh.runWaitFor("echo olsr");
	if(!result.success()) {
	    Log.d(MSG_TAG, "Error! " + result.stderr);
	} else {
	    Log.i(MSG_TAG, "Success! " + result.stdout);
	}
    }


    //@Override
    public void onDestroy() {
	olsrNotifyManager.cancel(R.string.local_service_started);
        Toast.makeText(this, R.string.local_service_stopped, Toast.LENGTH_SHORT).show();
	Log.i(MSG_TAG, "Call to onDestroy()");
    }
    
    // @Override
    public IBinder onBind(Intent intent) {
	return olsrBinder;
    }

    private void showNotification() {
        CharSequence text = getText(R.string.local_service_started);
        Notification notification = new Notification(R.drawable.stat_happy, text, 
						     System.currentTimeMillis());

        PendingIntent contentIntent = PendingIntent.getActivity(this, 0, 
								new Intent(this, MainActivity.class), 0);

        notification.setLatestEventInfo(this, getText(R.string.local_service_label),
					text, contentIntent);

        olsrNotifyManager.notify(R.string.local_service_started, notification);
    }
}
