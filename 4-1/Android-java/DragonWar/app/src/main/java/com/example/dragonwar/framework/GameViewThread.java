package com.example.dragonwar.framework;

import android.graphics.Canvas;
import android.view.SurfaceHolder;

public class GameViewThread extends Thread {
    // 접근을 위한 멤버 변수
    private SurfaceHolder m_surfaceHolder;
    private GameView m_gameview;
    // 스레드 실행 상태 멤버 변수
    private boolean m_run = false;

    public GameViewThread(SurfaceHolder surfaceHolder, GameView gameview){
        m_surfaceHolder = surfaceHolder;
        m_gameview = gameview;
    }
    public void setRunning(boolean run){
        m_run = run;
    }

    @Override
    public void run() {
        Canvas c;
        while(m_run){
            c = null;
            try{
                m_gameview.Update();
                c=m_surfaceHolder.lockCanvas(null);
                synchronized (m_surfaceHolder){
                    m_gameview.myDraw(c);
                }
            }finally {
                if(c != null) {
                    m_surfaceHolder.unlockCanvasAndPost(c);
                }
            }
        }
    }
}
