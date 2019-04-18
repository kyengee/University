package com.example.soundexample;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.media.MediaPlayer;
import android.media.SoundPool;
import android.view.KeyEvent;
import android.view.View;

public class SoundExampleView extends View {
    MediaPlayer m_Sound_BackGround;
    MediaPlayer m_Sound_1;
    MediaPlayer m_Sound_2;

    SoundPool.Builder m_SoundPoolBuilder;
    SoundPool m_SoundPool;
    int	  m_Sound_id_BackGround;
    int	  m_Sound_id_1;
    int	  m_Sound_id_2;

    public SoundExampleView(Context context) {
        super(context);
        //m_SoundPool = new SoundPool(5, AudioManager.STREAM_MUSIC, 0);
        m_SoundPoolBuilder = new SoundPool.Builder();
        m_SoundPoolBuilder.setMaxStreams(5);
        m_SoundPool = m_SoundPoolBuilder.build();

        // MediaPlayer
        m_Sound_BackGround = MediaPlayer.create(context, R.raw.main_stage);
        //m_Sound_1 = MediaPlayer.create(context,R.raw.effect1);
        //m_Sound_2 = MediaPlayer.create(context,R.raw.effect2);

        // SoundPool
        m_Sound_id_BackGround = m_SoundPool.load(context,R.raw.background,1);
        m_Sound_id_1 = m_SoundPool.load(context,R.raw.effect1,1);
        m_Sound_id_2 = m_SoundPool.load(context,R.raw.effect2,1);

        //
        m_Sound_BackGround.start();

        //
        setFocusable(true);
        setFocusableInTouchMode(true);
    }

    @Override
    protected void onDraw(Canvas canvas) {

        //
        Paint p = new Paint();
        p.setTextSize(20);     //
        p.setColor(Color.BLACK); //
        String str;
        // isPlaying
        if(m_Sound_BackGround.isPlaying())
            str = "재생중";
        else
            str = "일시 정지 중";
        canvas.drawText("배경음악 : " + str , 0, 20, p);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        //
        if(keyCode == KeyEvent.KEYCODE_DPAD_LEFT)
            //m_Effect_sound_1.start();
            m_SoundPool.play(m_Sound_id_1, 1, 1, 0, 0, 1);
        //
        if(keyCode == KeyEvent.KEYCODE_DPAD_RIGHT)
            //m_Effect_sound_2.start();
            m_SoundPool.play(m_Sound_id_2, 1, 1, 0, 0, 1);

        //
        if(keyCode == KeyEvent.KEYCODE_DPAD_CENTER){
            if(m_Sound_BackGround.isPlaying())
                m_Sound_BackGround.pause();
            else
                m_Sound_BackGround.start();

            //
            invalidate();
        }

        return super.onKeyDown(keyCode, event);
    }

}
