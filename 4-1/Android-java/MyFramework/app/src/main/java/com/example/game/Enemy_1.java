package com.example.game;

import com.example.myframework.AppManager;
import com.example.myframework.R;

public class Enemy_1 extends Enemy {
	
	public Enemy_1(){
		super(AppManager.getInstance().getBitmap(R.drawable.enemy1));
		this.InitSpriteData(104	, 62, 3, 6);
		hp = 10;
		speed = 2.5f;
		
		//movetype = Enemy.MOVE_PATTERN_3;
	}
	
	@Override
	public void Update(long GameTime){
		super.Update(GameTime);
		
		m_BoundBox.set(m_x,m_y,m_x+62,m_y+104);		
	}
	
}
