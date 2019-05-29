package com.example.dragonwar.game;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Rect;

import com.example.dragonwar.framework.SpriteAnimaion;


public class Player extends SpriteAnimaion {

	Rect m_BoundBox = new Rect();
	
	public Player(Bitmap bitmap) {
		super(bitmap);
		this.InitSpriteData(300	, 360, 4, 4);
		this.SetPosition(140, 380);
	}

	@Override
	public void Update(long GameTime){
		 super.Update(GameTime);
		m_BoundBox.set(m_x,m_y,m_x+42,m_y+44);	
	}

}
