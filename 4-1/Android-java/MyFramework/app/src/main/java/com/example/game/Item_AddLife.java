package com.example.game;

import com.example.myframework.AppManager;
import com.example.myframework.R;

public class Item_AddLife extends Item {
	
	public Item_AddLife(int x,int y) {
		super(AppManager.getInstance().getBitmap(R.drawable.item2));
		this.InitSpriteData(51	, 51, 3, 4);		
		
		m_x = x;
		m_y = y;
	}

	@Override
	void GetItem(){
		AppManager.getInstance().m_gamestate.GetPlayer().AddLife();
	}
}
