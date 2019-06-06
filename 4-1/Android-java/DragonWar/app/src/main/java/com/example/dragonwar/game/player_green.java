package com.example.dragonwar.game;

import android.graphics.Canvas;

import com.example.dragonwar.R;
import com.example.dragonwar.framework.AppManager;

import java.util.ArrayList;
import java.util.Random;

public class player_green extends player {

    ArrayList<Missile> m_pmslist = new ArrayList<Missile>();
    private long mFrameTimer;
    Random random = new Random();

    public player_green(){
        super(AppManager.getInstance().getBitmap(R.drawable.playergreendragon));
        mFrameTimer = 0;
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
        if(GameTime > mFrameTimer + 2000){
            mFrameTimer = GameTime;
            m_pmslist.add(new Missile(AppManager.getInstance().getBitmap(R.drawable.ice_bolt), m_x + 350, m_y + 135, 5, 0));
            int j = 0;
            for (int i = 0; i < 10; i++) {
                j = random.nextInt(2);
                if(j == 0) j = -1;
                m_pmslist.add(new Missile(AppManager.getInstance().getBitmap(R.drawable.ice_1), m_x + 350, m_y + 135, random.nextInt(4) + 1, j * (random.nextInt(4) + 1)));
            }
        }
        for (int i = m_pmslist.size()-1; i >= 0; i--) {
            Missile pms = m_pmslist.get(i);
            pms.Update();
            if(pms.state == Missile.STATE_OUT){
                m_pmslist.remove(i);
            }
        }
    }
}
