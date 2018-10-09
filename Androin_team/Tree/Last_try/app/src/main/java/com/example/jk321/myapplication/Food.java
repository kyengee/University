package com.example.jk321.myapplication;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class Food extends AppCompatActivity {
    static final int GET_RESULT = 1;
    int[] result;
    SharedPreferences account;
    int AC_food;
    int food_mc;
    int basic1;
    int basic2;
    int basic3;
    int apple;
    int banana;
    int grape;
    TextView time;
    int remaintime;
    int gap;
    Button button;
    int[] seeds;
    int count;
    boolean ismaking;
    long now;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_food);
        setTitle("씨앗으로 비료를 만드세요");
        // 현재시간을 msec 으로 구한다.
        now = System.currentTimeMillis();
        seeds = new int[6];

        account = getSharedPreferences("account",0);
        AC_food = account.getInt("food",0);
        food_mc = account.getInt("food_mc",1);
        seeds[2] = basic1 = account.getInt("basic1",1);
        seeds[1] = basic2 = account.getInt("basic2",0);
        seeds[0] = basic3 = account.getInt("basic3",0);
        seeds[3] = apple = account.getInt("apple",0);
        seeds[4] = banana = account.getInt("banana",0);
        seeds[5] = grape = account.getInt("grape",0);
        ismaking = account.getBoolean("ismaking",false);
        remaintime =(int) account.getLong("food_time", System.currentTimeMillis()-36000);
        count = account.getInt("count",0);
        button = (Button) findViewById(R.id.food_Button);
        time = (TextView) findViewById(R.id.remainTime);

        gap = (int)(now-remaintime)/(1000);
        if (gap>30){
            button.setVisibility(View.VISIBLE);
            if(ismaking == true) {
                AC_food += 20 * count;
                ismaking = false;
            }


        }else {
            button.setVisibility(View.INVISIBLE);
            time.setText((30 - gap) + "초 남았습니다.");
        }


    }

    public void check(View view) {
        Intent intent;
        intent = new Intent(Food.this, Check.class);
        intent.putExtra("text","Food");
        startActivityForResult(intent, GET_RESULT);
    }

    @Override
    protected void onResume() {
        super.onResume();
        gap = (int)(now-remaintime)/(1000);
        if (gap>30){
            button.setVisibility(View.VISIBLE);
            if(ismaking == true) {
                AC_food += 20 * count;
                ismaking = false;
            }


        }else {
            button.setVisibility(View.INVISIBLE);
            time.setText((30 - gap) + "초 남았습니다.");
        }

    }


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == GET_RESULT) {
            if (resultCode == RESULT_OK) {
                result = data.getIntArrayExtra("result");
                for(int i=0;i<6;i++){
                    seeds[i] = seeds[i] - result[i];
                    count+=result[i];
                }
                if(count>0) {
                    ismaking = true;
                    remaintime = (int) System.currentTimeMillis();
                }


            }
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        SharedPreferences.Editor editor;
        editor = account.edit();
        editor.putInt("food",AC_food);
        editor.putInt("food_mc",food_mc);
        editor.putInt("basic1",seeds[2]);
        editor.putInt("basic2",seeds[1]);
        editor.putInt("basic3",seeds[0]);
        editor.putInt("apple",seeds[3]);
        editor.putInt("banana",seeds[4]);
        editor.putInt("grape",seeds[5]);
        editor.putLong("food_time",remaintime);
        editor.putInt("count",count);
        editor.putBoolean("ismaking",ismaking);
        editor.commit();
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        SharedPreferences.Editor editor;
        editor = account.edit();
        editor.putInt("food",AC_food);
        editor.putInt("food_mc",food_mc);
        editor.putInt("basic1",seeds[2]);
        editor.putInt("basic2",seeds[1]);
        editor.putInt("basic3",seeds[0]);
        editor.putInt("apple",seeds[3]);
        editor.putInt("banana",seeds[4]);
        editor.putInt("grape",seeds[5]);
        editor.putLong("food_time",remaintime);
        editor.putInt("count",count);
        editor.putBoolean("ismaking",ismaking);
        editor.commit();
    }
}
