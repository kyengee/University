package com.example.dragonwar.game;

import android.graphics.Bitmap;

import com.example.dragonwar.R;
import com.example.dragonwar.framework.AppManager;
import com.example.dragonwar.framework.GraphicObject;
import com.example.dragonwar.framework.SpriteAnimaion;

public class background1 extends GraphicObject {
    public background1() {
        super(AppManager.getInstance().getBitmap(R.drawable.background_1));

    }
}
