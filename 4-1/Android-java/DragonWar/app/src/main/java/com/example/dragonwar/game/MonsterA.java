package com.example.dragonwar.game;

import android.graphics.Bitmap;

import com.example.dragonwar.R;
import com.example.dragonwar.framework.AppManager;

public class MonsterA extends Monster{

    @Override
    public void Update(long GameTime) {
        super.Update(GameTime);
    }

    public MonsterA() {
        super(AppManager.getInstance().getBitmap(R.drawable.monster));
        this.InitSpriteData(235,155,3,1);
        hp =10;
        speed = 2.5f;

        movetype = Monster.MOVE_PATTERN_1;
    }
}
