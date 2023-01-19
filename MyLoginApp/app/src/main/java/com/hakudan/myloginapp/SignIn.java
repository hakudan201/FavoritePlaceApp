package com.hakudan.myloginapp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.StrictMode;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.material.button.MaterialButton;

public class SignIn extends AppCompatActivity {
    private connect_to_server connect;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sign_in);

        TextView username = (TextView) findViewById(R.id.username);
        TextView password = (TextView) findViewById(R.id.password);

        MaterialButton loginbtn = (MaterialButton) findViewById(R.id.loginbtn);
        MaterialButton signupbtn = (MaterialButton) findViewById(R.id.signupbtn);
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
                Toast.makeText(SignIn.this, connect.result, Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(SignIn.this, DashboardActivity.class);
                startActivity(intent);

                connect.disconnect();
            }
        });

        signupbtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent agn = new Intent(getApplicationContext(), SignUp.class);
                startActivity(agn);
            }
        });
    }
}