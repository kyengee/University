package com.example.dragonwar.game;

import android.graphics.Bitmap;
import android.graphics.Canvas;

import com.example.dragonwar.R;
import com.example.dragonwar.framework.AppManager;
import com.example.dragonwar.framework.GraphicObject;
import com.example.dragonwar.framework.SpriteAnimaion;

public class background1 extends GraphicObject {
    static final float SCROLL_SPEED = 20.0f;
    private float m_scroll=-7667+3040;

    public background1() {
        super(null);
        m_bitmap=(AppManager.getInstance().getBitmap(R.drawable.background_1));
        SetPosition((int)m_scroll,0);
    }

    void Update(long GameTime){
        m_scroll = m_scroll+SCROLL_SPEED;
        if(m_scroll>=0)
            m_scroll = -7667+3040;
        SetPosition((int)m_scroll,0);
    }

    @Override
    public void Draw(Canvas canvas) {
        canvas.drawBitmap(m_bitmap,m_x,m_y,null);
    }
}

