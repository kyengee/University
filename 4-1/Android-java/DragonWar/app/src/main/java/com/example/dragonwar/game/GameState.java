package com.example.dragonwar.game;

import android.graphics.Canvas;
import android.view.KeyEvent;
import android.view.MotionEvent;

import com.example.dragonwar.framework.IState;


public class GameState implements IState {
    // 멤버 변수 추가할 곳
    private background1 m_background;
    private player m_player;

    @Override
    public void Destroy() {

    }

    @Override
    public void Init() {
        m_background = new background1();
        m_player = new player_red();
    }

    @Override
    public void Render(Canvas canvas) {
        m_background.Draw(canvas);
        m_player.Draw(canvas);

    }

    @Override
    public void Update() {
        long GameTime = System.currentTimeMillis();
        m_player.Update(GameTime);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {

        int x = m_player.GetX();
        int y = m_player.GetY();

        if(keyCode == KeyEvent.KEYCODE_DPAD_LEFT)
            m_player.SetPosition(x-10, y);
        if(keyCode == KeyEvent.KEYCODE_DPAD_RIGHT)
            m_player.SetPosition(x+10, y);
        if(keyCode == KeyEvent.KEYCODE_DPAD_UP)
            m_player.SetPosition(x, y-10);
        if(keyCode == KeyEvent.KEYCODE_DPAD_DOWN)
            m_player.SetPosition(x, y+10);

        return true;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return false;
    }
}
