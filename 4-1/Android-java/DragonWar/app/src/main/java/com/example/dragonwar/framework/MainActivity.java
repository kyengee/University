package com.example.dragonwar.framework;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.example.dragonwar.framework.GameView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(new GameView(this));
    }
}
