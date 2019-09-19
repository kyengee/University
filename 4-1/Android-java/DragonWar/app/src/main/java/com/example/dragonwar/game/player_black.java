package com.example.dragonwar.game;

import android.graphics.Canvas;

import com.example.dragonwar.R;
import com.example.dragonwar.framework.AppManager;

import java.util.Random;

public class player_black extends player {

    private long mFrameTimer;
    Random random = new Random();

    public player_black(){
        super(AppManager.getInstance().getBitmap(R.drawable.playerblackdragon));
        mFrameTimer = 0;
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
                int j = 0;
                for (int i = 0; i < 3; i++) {
                    j = random.nextInt(2);
                    if(j == 0) j = -1;
                    m_pmslist.add(new Missile(AppManager.getInstance().getBitmap(R.drawable.dark_lightning), m_x + 350, m_y + 135, random.nextInt(17) + 1, j * (random.nextInt(5) + 1)));
                    m_pmslist.get(m_pmslist.size() -1).missiletype = 4;
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
