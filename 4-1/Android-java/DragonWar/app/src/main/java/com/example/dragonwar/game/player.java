package com.example.dragonwar.game;

import android.graphics.Bitmap;
import android.graphics.Rect;

import com.example.dragonwar.framework.SpriteAnimaion;

public class player extends SpriteAnimaion {

    Rect m_BoundBox = new Rect();

    public player(Bitmap bitmap){
        super(bitmap);
        this.InitSpriteData(300	, 360, 6, 4);
        this.SetPosition(0, 580);
    }

    @Override
    public void Update(long GameTime){
        super.Update(GameTime);
        m_BoundBox.set(m_x,m_y,m_x+42,m_y+44);
    }
}
