package com.example.dragonwar.game;

import android.graphics.Bitmap;
import android.graphics.Canvas;

import com.example.dragonwar.R;
import com.example.dragonwar.framework.AppManager;

import java.util.ArrayList;
import java.util.Random;

public class MonsterA extends Monster{
    private long mFrameTimer;
    Random random = new Random();

    public MonsterA() {
        super(AppManager.getInstance().getBitmap(R.drawable.monster_green));
        mFrameTimer = 0;
        hp =10;
        speed = 10f;

        movetype = Monster.MOVE_PATTERN_1;
    }

    @Override
    public void Draw(Canvas canvas) {
        super.Draw(canvas);
        for(Missile_Monster pms : m_Alist){
            pms.Draw(canvas);
        }
    }

    @Override
    public void Update(long GameTime) {
        super.Update(GameTime);
        if(GameTime > mFrameTimer + 2000){
            mFrameTimer = GameTime;
            m_Alist.add(new Missile_Monster(AppManager.getInstance().getBitmap(R.drawable.monster_attack_green), m_x - 350, m_y + 135, 15, 0));
        }
        for (int i = m_Alist.size()-1; i >= 0; i--) {
            Missile_Monster pms = m_Alist.get(i);
            pms.Update();
            if(pms.state == Missile.STATE_OUT){
                m_Alist.remove(i);
            }
        }
    }


}
