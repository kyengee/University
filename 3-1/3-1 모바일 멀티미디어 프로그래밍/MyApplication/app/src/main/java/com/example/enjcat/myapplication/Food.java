package com.example.enjcat.myapplication;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Food extends AppCompatActivity {
    static final int GET_RESULT = 1;
    int[] result;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_food);
        // 현재시간을 msec 으로 구한다.
        long now = System.currentTimeMillis();
        // 현재시간을 date 변수에 저장한다.
        Date date = new Date(now);
        // 시간을 나타냇 포맷을 정한다 ( yyyy/MM/dd 같은 형태로 변형 가능 )
        SimpleDateFormat sdfNow = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
        // nowDate 변수에 값을 저장한다.
        String formatDate = sdfNow.format(date);

        TextView time = (TextView) findViewById(R.id.remainTime);
        time.setText(formatDate);

    }

    public void check(View view) {
        Intent intent;
        intent = new Intent(Food.this, Check.class);
        intent.putExtra("text","Food");
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
