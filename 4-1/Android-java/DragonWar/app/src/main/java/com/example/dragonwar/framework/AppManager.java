package com.example.dragonwar.framework;

import android.app.Activity;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import com.example.dragonwar.game.GameState;

public class AppManager {
    // Main GameView
    private GameView m_gameview;
    // Main GameView의 Resources
    private Resources m_resoucres;
    private Activity m_activity;
    private Thread m_thread;

    public GameState m_gamestate;

    void setGameView(GameView _gameview){
        m_gameview = _gameview;
    }
    void setResources(Resources _resources){
        m_resoucres= _resources;
    }
    public  GameView getGameVies(){
        return m_gameview;
    }
    public Resources getResources(){
        return m_resoucres;
    }

    public Bitmap getBitmap(int r){
        return BitmapFactory.decodeResource(m_resoucres,r);
    }


    private static AppManager s_instance;

    public static AppManager getInstance(){
        if(s_instance ==null){
            s_instance = new AppManager();
        }
        return s_instance;
    }
}
