package com.hakudan.myloginapp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.StrictMode;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.material.button.MaterialButton;

import java.io.File;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {
    private connect_to_server connect;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView username = (TextView) findViewById(R.id.username);
        TextView password = (TextView) findViewById(R.id.password);

        MaterialButton loginbtn = (MaterialButton) findViewById(R.id.loginbtn);

        //admin

        loginbtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                connect = new connect_to_server();
                connect.connectToServer();

                try {
                    connect.sendMessage("LOGIN " + username.getText().toString() + " " + password.getText().toString());
                } catch (Exception e) {
                    e.printStackTrace();
                }
                Toast.makeText(MainActivity.this, connect.result, Toast.LENGTH_SHORT).show();

                connect.disconnect();
            }
        });

    }
}