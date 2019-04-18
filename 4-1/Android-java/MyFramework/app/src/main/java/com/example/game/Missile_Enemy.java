package com.example.game;

import com.example.myframework.AppManager;
import com.example.myframework.R;

public class Missile_Enemy extends Missile {
	Missile_Enemy(int x,int y){
		super(AppManager.getInstance().getBitmap(R.drawable.missile_2));
		this.SetPosition(x, y);
	}
	
	public void Update(){
		// 미사일이 아래로 발사되는 효과를 준다
		m_y+=4;
		if(m_y > 350)
			state = STATE_OUT;
		
		m_BoundBox.set(m_x,m_y,m_x+43,m_y+43);
		
	}
}
