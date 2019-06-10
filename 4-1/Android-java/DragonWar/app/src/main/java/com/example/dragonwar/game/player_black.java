package com.example.dragonwar.game;

import com.example.dragonwar.R;
import com.example.dragonwar.framework.AppManager;

public class player_black extends player {

    public player_black(){
        super(AppManager.getInstance().getBitmap(R.drawable.playerblackdragon));
    }

    @Override
    public void Update(long GameTime){
        super.Update(GameTime);
    }
}
