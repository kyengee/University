package com.example.dragonwar.game;

import android.graphics.Bitmap;
import android.graphics.Rect;

import com.example.dragonwar.framework.SpriteAnimaion;

public class item extends SpriteAnimaion {
    Rect m_BoundBox = new Rect();
    public boolean bOut=false;

    public  item(Bitmap bitmap)
    {
        super(bitmap);
    }

    @Override
    public  void Update(long GameTime)
    {
        super.Update(GameTime);
        m_x+=5;
        if(m_x>350)
            bOut=true;


        m_BoundBox.set(m_x,m_y,m_x +51,m_y+51); //좌표 재설정 필요
    }

    void GetItem()
    {

    }

}
