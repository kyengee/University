package com.example.game;

import android.graphics.Bitmap;

import com.example.myframework.AppManager;
import com.example.myframework.R;

public class Item_AddScore extends Item {

	public Item_AddScore(int x,int y) {
		super(AppManager.getInstance().getBitmap(R.drawable.item1));
		this.InitSpriteData(51	, 51, 3, 4);		
		
		m_x = x;
		m_y = y;
	}

	@Override
	void GetItem(){
		AppManager.getInstance().m_gamestate.m_score += 100;
	}
}
