package com.example.game;


import android.graphics.Bitmap;
import android.graphics.Rect;

import com.example.myframework.SpriteAnimation;

public class Item extends SpriteAnimation {

	Rect m_BoundBox = new Rect();
	
	public boolean bOut = false;
	
	public Item(Bitmap bitmap) {
		super(bitmap);
	}
	
	@Override
	public void Update(long GameTime){
		super.Update(GameTime);
		
		m_y += 2;
		if(m_y> 350)
			bOut = true;
		
		m_BoundBox.set(m_x, m_y, m_x +51, m_y+51);
	}
	
	void GetItem(){
		
	}
	
}
