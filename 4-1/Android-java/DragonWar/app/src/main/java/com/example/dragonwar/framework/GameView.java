package com.example.dragonwar.framework;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.example.dragonwar.game.GameState;

public class GameView extends SurfaceView implements SurfaceHolder.Callback{
    private GameViewThread m_thread;
    private IState m_state;

    public GameView(Context context) {
        super(context);
        // 키 입력 처리를 받기 위해서
        setFocusable(true);

        AppManager.getInstance().setGameView(this);
        AppManager.getInstance().setResources(getResources());

        ChangeGameState(new GameState());

        getHolder().addCallback(this);
        m_thread = new GameViewThread(getHolder(),this);

    }

    @Override
    protected void onDraw(Canvas canvas) {
        canvas.drawColor(Color.BLACK);
        m_state.Render(canvas);
   }

    protected void myDraw(Canvas canvas) {
        canvas.drawColor(Color.BLACK);
        m_state.Render(canvas);
    }

    public void Update(){
        m_state.Update();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
       m_state.onKeyDown(keyCode,event);
       return super.onKeyDown(keyCode, event);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        m_state.onTouchEvent(event);
        return true;

    }

    public void ChangeGameState(IState _state){
        if(m_state !=null)
            m_state.Destroy();
        _state.Init();
        m_state = _state;

    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        m_thread.setRunning(true);
        m_thread.start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        boolean retry = true;
        m_thread.setRunning(false);
        while(retry){
            try{
                m_thread.join();
                retry=false;
            }catch (InterruptedException e){
            }
        }
    }
}
