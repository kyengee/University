package com.example.dragonwar.game;

import android.graphics.Canvas;
import android.view.KeyEvent;
import android.view.MotionEvent;

import com.example.dragonwar.framework.AppManager;
import com.example.dragonwar.framework.IState;

public class IntroState implements IState {
    private intro m_backintro;
    SoundExampleView myView;

    public void Destroy() {

    }

    @Override
    public void Init() {
        m_backintro=new intro();
    }

    @Override
    public void Render(Canvas canvas) {

        myView.m_sound_intro.start();
        m_backintro.Draw(canvas);
    }

    @Override
    public void Update() {

    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        return false;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        AppManager.getInstance().getGameVies().ChangeGameState(new MenuState());
        myView.m_sound_intro.stop();
        return true;
    }
}



