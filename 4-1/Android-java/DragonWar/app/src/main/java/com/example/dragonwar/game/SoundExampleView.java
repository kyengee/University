package com.example.dragonwar.game;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.media.MediaPlayer;
import android.media.SoundPool;
import android.view.KeyEvent;
import com.example.dragonwar.R;
import android.view.View;

public class SoundExampleView extends View {
    MediaPlayer m_Sound_BackGroubd;
    MediaPlayer m_sound_intro;
    MediaPlayer m_Sound_menu;
    MediaPlayer m_Sound_effect1;

    SoundPool.Builder m_SoundPoolBuilder;
    SoundPool m_SoundPool;
    int m_Sound_id_BackGround;
    int m_Sound_id_intro;
    int m_Sound_id_menu;

    public SoundExampleView(Context context) {
        super(context);
        //m_SoundPool = new SoundPool(5, AudioManager.STREAM_MUSIC, 0);
        //m_SoundPoolBuilder = new SoundPool.Builder();
        //m_SoundPoolBuilder.setMaxStreams(5);
        //m_SoundPool = m_SoundPoolBuilder.build();

        // MediaPlayer
        m_Sound_BackGroubd = MediaPlayer.create(context, R.raw.bg);
        m_sound_intro = MediaPlayer.create(context,R.raw.intro);
        m_Sound_menu = MediaPlayer.create(context,R.raw.menu);
        m_Sound_effect1=MediaPlayer.create(context,R.raw.get_dragon02);

        // SoundPool
        //m_Sound_id_BackGround = m_SoundPool.load(context,R.raw.bg,1);
        //m_Sound_id_intro = m_SoundPool.load(context,R.raw.effect1,1);
        //m_Sound_id_menu = m_SoundPool.load(context,R.raw.effect2,1);

        //
        //m_sound_intro.start();

        //
        //setFocusable(true);
        //setFocusableInTouchMode(true);
    }

}
