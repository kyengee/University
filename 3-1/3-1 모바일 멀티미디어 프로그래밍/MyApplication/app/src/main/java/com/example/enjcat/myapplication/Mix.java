package com.example.enjcat.myapplication;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class Mix extends AppCompatActivity {
    static final int GET_RESULT = 1;
    int[] result;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mix);
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
                result = data.getIntArrayExtra("INPUT_VALUE");
            }
        }
    }
}
