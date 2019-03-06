package com.example.enjcat.myapplication;

import android.content.SharedPreferences;
import android.graphics.drawable.Drawable;
import android.os.AsyncTask;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Timer;
import java.util.TimerTask;

public class Water extends AppCompatActivity {
    long now;
    int gap,time;
    ImageButton btn;
    TextView result_text;
    TextView text;
    int move;
    int result;
    int count;
    boolean use;

    SharedPreferences account;
    int AC_water;
    int pump;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_water);
        setTitle("제한시간안에 펌프를 움직이세요");
        now = System.currentTimeMillis();
        text = (TextView) findViewById(R.id.timer);
        btn = (ImageButton) findViewById(R.id.pump);
        result_text = (TextView) findViewById(R.id.result);
        move = 0;
        result = 0;
        count = 0;
        use = false;

        account = getSharedPreferences("account",0);
        AC_water = account.getInt("water",0);
        pump = account.getInt("pump",1);
        time =(int) account.getLong("water_time",System.currentTimeMillis()-36000);


        gap = (int)(now-time)/(1000);
        if (gap>30){
            use = true;
            new CounterTask().execute(pump*15);
        }else {
            text.setText((30 - gap) + "초 남았습니다.");
            result_text.setText(""+AC_water);
        }


    }
    public void moving(View view){
        if(move == 0){
            move = 1;
            btn.setBackgroundResource(R.drawable.pump2);
        }
        else{
            move = 0;
                btn.setBackgroundResource(R.drawable.pump1);
            AC_water++;
            result_text.setText(""+AC_water);
        }

    }

    class CounterTask extends AsyncTask<Integer, Integer, Integer>{
        protected void onPreExecute(){}

        @Override
        protected Integer doInBackground(Integer... integers) {
            count = integers[0];
            while(count > 0){
                try{
                    Thread.sleep(1000);
                }catch (Exception e){}
                count --;
                publishProgress(count);
            }
            return count;
        }


        @Override
        protected void onProgressUpdate(Integer... values) {
            text.setText(""+values[0]);
        }

        @Override
        protected void onPostExecute(Integer integer) {

            finish();
        }


    }




    @Override
    protected void onPause() {
        super.onPause();
        if(use == true) {
            SharedPreferences.Editor editor;
            editor = account.edit();
            editor.putLong("water_time", System.currentTimeMillis());
            editor.putInt("water", AC_water);
            editor.commit();
        }
    }

}
