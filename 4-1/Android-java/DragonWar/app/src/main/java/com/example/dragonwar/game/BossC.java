package com.example.dragonwar.game;

import android.graphics.Bitmap;
import android.graphics.Canvas;

import com.example.dragonwar.R;
import com.example.dragonwar.framework.AppManager;

import java.util.ArrayList;
import java.util.Random;

public class BossC extends Monster{
    ArrayList<Missile_Monster> m_Alist = new ArrayList<Missile_Monster>();
    private long mFrameTimer;
    Random random = new Random();

    public BossC(Bitmap bitmap) {
        super(bitmap);
        hp = 20;
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
        if (m_y < 0)
            speed = 3f;
        else if(m_y > 985)
            speed = -3f;
        else if (GameTime > mFrameTimer + 500){
            if(random.nextInt(2) == 1)
                speed = 3f;
            else
                speed = -3f;
            m_Alist.add(new Missile_Monster(AppManager.getInstance().getBitmap(R.drawable.monster_attack_red), m_x, m_y, 15, 0));
            mFrameTimer = GameTime;
        }
        for (int i = m_Alist.size()-1; i >= 0; i--) {
            Missile_Monster pms = m_Alist.get(i);
            pms.Update();
            if (pms.state == Missile.STATE_OUT) {
                m_Alist.remove(i);
            }
        }
    }

    public BossC() {
        super(AppManager.getInstance().getBitmap(R.drawable.boss_red));
        hp =20;
        speed = 3f;
        mFrameTimer = 0;
        movetype = Monster.BOSS_PATTERN_1;
    }
}
