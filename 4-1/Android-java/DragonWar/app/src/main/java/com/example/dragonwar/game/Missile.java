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
    int missiletype = 0;

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

        if(m_x > 3000 || m_x < 40 || m_y < 40 || m_y > 1400)
            state = STATE_OUT;
        if (missiletype == 0)
            m_BoundBox.set(m_x, m_y, m_x + 166, m_y + 95);
        else if(missiletype == 3)
            m_BoundBox.set(m_x, m_y, m_x + 350, m_y + 80);
        else if(missiletype == 4)
            m_BoundBox.set(m_x, m_y, m_x + 436, m_y + 127);
        else
            m_BoundBox.set(m_x, m_y, m_x + 64, m_x + 64);


    }
}
