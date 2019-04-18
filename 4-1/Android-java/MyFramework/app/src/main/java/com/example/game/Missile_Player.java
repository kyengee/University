package com.example.game;

import com.example.myframework.AppManager;
import com.example.myframework.R;

public class Missile_Player extends Missile {
	
	Missile_Player(int x,int y){
		super(AppManager.getInstance().getBitmap(R.drawable.missile_1));
		this.SetPosition(x, y);
	}
	
	public void Update(){
		// 誘몄궗�쇱씠 �꾨줈 諛쒖궗�섎뒗 �④낵瑜�以�떎.
		m_y-=2;
		if(m_y < 50)
			state = STATE_OUT;
		
		m_BoundBox.set(m_x,m_y,m_x+43,m_y+43);
		
	}
}
