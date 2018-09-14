package com.example.jk321.myapplication;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Toast;

public class Mix extends AppCompatActivity {
    static final int GET_RESULT = 1;
    int[] result;
    SharedPreferences account;
    int mix;
    int basic1;
    int basic2;
    int basic3;
    int apple;
    int banana;
    int grape;
    int[] seeds;
    int count;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mix);
        setTitle("새로운 씨앗을 얻으세요");
        count = 0;
        seeds = new int[6];

        account = getSharedPreferences("account",0);
        mix = account.getInt("mix",1);
        seeds[2] = basic1 = account.getInt("basic1",1);
        seeds[1] = basic2 = account.getInt("basic2",0);
        seeds[0] = basic3 = account.getInt("basic3",0);
        seeds[3] = apple = account.getInt("apple",0);
        seeds[4] = banana = account.getInt("banana",0);
        seeds[5] = grape = account.getInt("grape",0);

    }

    public void check(View view) {
        Intent intent;
        intent = new Intent(Mix.this, Check.class);
        intent.putExtra("text","Mix");
        startActivityForResult(intent, GET_RESULT);
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
                if(count>1) {
                    String[] titles = {"파란열매","노란열매","빨간열매","사과","바나나","포도"};
                    int rand = (int) (Math.random()*5);
                    seeds[rand] = seeds[rand] +1;
                    Toast.makeText(getApplicationContext(),titles[rand]+"를 얻었다.", Toast.LENGTH_SHORT).show();
                }
            }
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        SharedPreferences.Editor editor;
        editor = account.edit();
        editor.putInt("basic1",seeds[2]);
        editor.putInt("basic2",seeds[1]);
        editor.putInt("basic3",seeds[0]);
        editor.putInt("apple",seeds[3]);
        editor.putInt("banana",seeds[4]);
        editor.putInt("grape",seeds[5]);
        editor.commit();
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        SharedPreferences.Editor editor;
        editor = account.edit();
        editor.putInt("basic1",seeds[2]);
        editor.putInt("basic2",seeds[1]);
        editor.putInt("basic3",seeds[0]);
        editor.putInt("apple",seeds[3]);
        editor.putInt("banana",seeds[4]);
        editor.putInt("grape",seeds[5]);
        editor.commit();
    }

}
