package com.hakudan.myloginapp;

import android.os.AsyncTask;
import android.util.Log;

import java.io.*;
import java.net.*;

public class connect_to_server extends AsyncTask<Void, Void, String> {
    static String LOG_TAG;
    static String connected = "failed";

    String message = "This is a test message is from Client Application.";
    String result = "";
    String toast_message = "Message Sent";

    private final String ip = "192.168.0.106";
    private final int port = 5500;
    private Socket clientSocket;
    private PrintWriter out;
    private BufferedReader in;


    @Override
    protected String doInBackground(Void... voids) {
        //connectToServer();
        return connected;
    }

    void connectToServer() {
        Log.d(LOG_TAG, "entered this activity");
        try
        {
            this.clientSocket = new Socket(this.ip, this.port);
            out = new PrintWriter(this.clientSocket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(this.clientSocket.getInputStream()));
            int i = 0;
            while ((message != null) && (i < 1)) {
                out.println(message);
                System.out.println("echo: " + in.readLine());
                i++;
            }

            toast_message = "This client is connected to " + this.clientSocket.getRemoteSocketAddress();
            Log.d(LOG_TAG, toast_message);
            connected = "connected";
        }
        catch(UnknownHostException u)
        {
            toast_message = "UnknownHostException: " + u;
            Log.d(LOG_TAG, toast_message);
        }
        catch(IOException i)
        {
            toast_message = " IOException: " + i;
            Log.d(LOG_TAG, toast_message );
        }
        catch (Exception e)
        {
            toast_message = "Exception: " + e;
            Log.d(LOG_TAG, toast_message );
        }


    }

    public void sendMessage(String message) throws Exception {
        if (this.clientSocket != null) {
            int i = 0;
            while ((message != null) && (i < 1)) {
                out.println(message);
                System.out.println("echo: " + in.readLine());
                i++;
            }
        } else {
            System.out.println("Error\n");
        }

    }

    public void disconnect() {
        try {
            this.clientSocket.close();
        } catch (Exception e) {
            System.out.println("Error disconnect");
            System.out.println(e);
        }
    }

    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);
        //Toast.makeText(context, toast_message, Toast.LENGTH_SHORT).show();
    }
}