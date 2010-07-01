package net.wlanlj.meshapp;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.InputStream;

import android.util.Log;

public class ShellCommand {
    private static final String MSG_TAG = "[[MeshApp]]::[ShellCommand] -> ";
    private Boolean hasRoot;    
    
    public Shell sh;
    public Shell su;
    
    public ShellCommand() {
        sh = new Shell("sh");
        su = new Shell("su");
    }
    
    public boolean hasRoot() {
        return hasRoot(false);
    }
    
    public boolean hasRoot(boolean force) {
        if (hasRoot == null || force) {
            CommandResult result = su.runWaitFor("id");
            StringBuilder out = new StringBuilder();
            
            if (result.stdout != null)
                out.append(result.stdout).append(" ; ");
            if (result.stderr != null)
                out.append(result.stderr);
            
            Log.i(MSG_TAG, "call to hasRoot():: su[" + result.exitValue + "]: " + out);
            hasRoot = result.success();
        }
        return hasRoot;
    }

    public Shell getShell() {
        return hasRoot() ? su : sh;
    }
    
    public class CommandResult {
        public final String stdout;
        public final String stderr;
        public final Integer exitValue;
        
        CommandResult(Integer exitValueIn, String stdoutIn, String stderrIn) {
            exitValue = exitValueIn;
            stdout = stdoutIn;
            stderr = stderrIn;
        }
        
        CommandResult(Integer exitValueIn) {
            this(exitValueIn, null, null);
        }
        
        public boolean success() {
            return exitValue != null && exitValue == 0;
        }
    }

    public class Shell {
        private String SHELL = "sh";

        public Shell(String shell) {
            SHELL = shell;
        }

        public Process run(String s) {
            Process process = null;
            try {
                process = Runtime.getRuntime().exec(SHELL);
                DataOutputStream toProcess = new DataOutputStream(process.getOutputStream());
                toProcess.writeBytes("exec " + s + "\n");
                toProcess.flush();
            } catch(Exception e) {
                Log.e(MSG_TAG, "Exception thrown while trying to run: '" + s + "' " + e.getMessage());
                process = null;
            }
            return process;
        }
        
        private String getStreamLines(InputStream in) {
            String out = null;
            StringBuffer buffer = null;
            DataInputStream data = new DataInputStream(in);

            try {
                if (data.available() > 0) { 
                    buffer = new StringBuffer(data.readLine());
                    while(data.available() > 0)
                        buffer.append("\n").append(data.readLine());
                }
                data.close();
            } catch (Exception ex) {
                Log.e(MSG_TAG, ex.getMessage());
            }
            if (buffer != null)
                out = buffer.toString();
            return out;
        }

        public CommandResult runWaitFor(String cmd) {
            Process process = run(cmd);
            Integer exitValue = null;
            String stdout = null;
            String stderr = null;
            if (process != null) {
                try {
                    exitValue = process.waitFor();
                    
                    stdout = getStreamLines(process.getInputStream());
                    stderr = getStreamLines(process.getErrorStream());
                    
                } catch(InterruptedException ex) {
                    Log.e(MSG_TAG, "runWaitFor " + ex.toString());
                } catch(NullPointerException ex) {
                    Log.e(MSG_TAG, "runWaitFor " + ex.toString());
                }
            }
            return new CommandResult(exitValue, stdout, stderr);
        }
    }
}
