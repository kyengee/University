package com.example.dragonwar.game;

import android.graphics.Canvas;

import com.example.dragonwar.R;
import com.example.dragonwar.framework.AppManager;

import java.util.ArrayList;

public class player_red extends player {

    private long mFrameTimer;

    public player_red(){
        super(AppManager.getInstance().getBitmap(R.drawable.playerreddragon));
        mFrameTimer = 0;
        m_pmslist.add(new Missile(AppManager.getInstance().getBitmap(R.drawable.fire_4), m_x + 350, m_y + 130, 0, 0));
        m_pmslist.get(m_pmslist.size() -1).missiletype = 3;
        hp = 100;
    }

    @Override
    public void Draw(Canvas canvas) {
        super.Draw(canvas);
        for (Missile pms : m_pmslist) {
            pms.Draw(canvas);
        }
    }

    @Override
    public void Update(long GameTime){
        super.Update(GameTime);
        if(shoot == true)
        if(GameTime > mFrameTimer + 1000){
            mFrameTimer = GameTime;
            m_pmslist.add(new Missile(AppManager.getInstance().getBitmap(R.drawable.fire_1), m_x + 350, m_y + 135, 15, 1));
            m_pmslist.get(m_pmslist.size() -1).missiletype = 2;
            m_pmslist.add(new Missile(AppManager.getInstance().getBitmap(R.drawable.fire_1), m_x + 350, m_y + 135, 15, -1));
            m_pmslist.get(m_pmslist.size() -1).missiletype = 2;
        }
        for (int i = m_pmslist.size()-1; i >= 1; i--) {
            Missile pms = m_pmslist.get(i);
            pms.Update();
            if(pms.state == Missile.STATE_OUT){
                m_pmslist.remove(i);
            }
        }
        m_pmslist.get(0).SetPosition(m_x + 350, m_y + 130);

    }
}
