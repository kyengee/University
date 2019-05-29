package com.example.dragonwar.game;

import com.example.dragonwar.R;
import com.example.dragonwar.framework.AppManager;

public class Missle_red1 extends Missile {
    Missle_red1(int x, int y ){
        super(AppManager.getInstance().getBitmap(R.drawable.red_1));
        this.SetPosition(x,y);
    }

    public void Update(){

    }
}
