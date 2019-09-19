package com.example.dragonwar.game;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.view.KeyEvent;
import android.view.MotionEvent;

import com.example.dragonwar.framework.AppManager;
import com.example.dragonwar.framework.IState;


public class MenuState implements IState {
    private menu m_menu;
    SoundExampleView myView;


    public void Destroy() {

    }

    @Override
    public void Init() {
        m_menu = new menu();
    }

    @Override
    public void Render(Canvas canvas) {
        m_menu.Draw(canvas);

        Paint p = new Paint();
        p.setTextSize(70);
        p.setColor(Color.BLACK);
        canvas.drawText("게임시작", 205, 740, p);

        Paint e = new Paint();
        e.setTextSize(70);
        e.setColor(Color.BLACK);
        canvas.drawText("환경설정", 205, 910, e);

        Paint c = new Paint();
        c.setTextSize(70);
        c.setColor(Color.BLACK);
        canvas.drawText("캐릭터", 230, 1075, c);
    }

    @Override
    public void Update() {

    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        return false;
    }

    public boolean onTouchEvent(MotionEvent event) {

        int action = event.getAction();

        int _x, _y;

        _x = (int) event.getX();
        _y = (int) event.getY();

        Rect rt = new Rect();

        rt.set(40, 400, 300, 800);
        if (rt.contains(_x, _y)) //게임시작을 터치했을경우 #변경필요
        {
            AppManager.getInstance().getGameVies().ChangeGameState(new GameState());
            return true;
        }

        rt.set(50, 300, 80, 300); //캐릭터능력치상승 터치했을경우
        if (rt.contains(_x, _y))
            return false;

        rt.set(100, 200, 300, 400); //환경설절을 터치했을경우
        if (rt.contains(_x, _y))
            return false;

        return true;

    }

}







