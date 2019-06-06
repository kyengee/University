package com.example.dragonwar.game;

import android.graphics.Bitmap;
import android.graphics.Rect;

import com.example.dragonwar.framework.GraphicObject;

public class Missile extends GraphicObject {
    Rect m_BoundBox = new Rect();
    int speed_x = 0;
    int speed_y = 0;
    public static final int STATE_NORMAL = 0;
    public static final int STATE_OUT = 1;

    public int state =  STATE_NORMAL;

    public Missile(Bitmap bitmap,int x, int y, int s_x, int s_y) {
        super(bitmap);
        speed_x = s_x;
        speed_y = s_y;
        this.SetPosition(x, y);
        // TODO Auto-generated constructor stub
    }

    public void Update() {
        // TODO Auto-generated method stub
        m_x += speed_x;
        m_y += speed_y;

        if(m_x > 1000)
            state = STATE_OUT;

        m_BoundBox.set(m_x,m_y,m_x+43,m_y+43);

    }
}
