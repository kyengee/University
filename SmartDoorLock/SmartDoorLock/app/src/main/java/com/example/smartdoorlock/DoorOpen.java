package com.example.smartdoorlock;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;

import javax.net.ssl.HttpsURLConnection;

import cz.msebera.android.httpclient.client.ClientProtocolException;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.methods.HttpPost;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;

import static cz.msebera.android.httpclient.HttpHeaders.USER_AGENT;

public class DoorOpen extends AppCompatActivity {
    Button Open;
    EditText WebDomain;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_door_open);

        WebDomain = (EditText)findViewById(R.id.WebDomain);
        Open = (Button)findViewById(R.id.open);
        Open.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    URL url = new URL("http://" + WebDomain.getText().toString() + "/on");
                    HttpsURLConnection con = (HttpsURLConnection) url.openConnection();
                    con.setRequestMethod("POST"); // HTTP POST 메소드 설정
                    con.setRequestProperty("User-Agent", USER_AGENT);
                    con.setDoOutput(true); // POST 파라미터 전달을 위한 설정
                    //Send post request
                    DataOutputStream wr = new DataOutputStream(con.getOutputStream());
                    wr.writeBytes("");
                    wr.flush();
                    wr.close();

                } catch (ClientProtocolException e) {
                    // TODO Auto-generated catch block
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                }
            }
        });
    }
}
