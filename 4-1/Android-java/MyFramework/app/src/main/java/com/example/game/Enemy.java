package com.example.game;

import android.graphics.Bitmap;
import android.graphics.Rect;

import com.example.myframework.AppManager;
import com.example.myframework.SpriteAnimation;

public class Enemy extends SpriteAnimation {

	public static final int STATE_NORMAL = 0;
	public static final int STATE_OUT = 1;
	
	public int state =  STATE_NORMAL;

	Rect m_BoundBox = new Rect();
	
	public static final int MOVE_PATTERN_1 = 0;
	public static final int MOVE_PATTERN_2 = 1;
	public static final int MOVE_PATTERN_3 = 2;

	protected int movetype;
	
	protected int hp;
	protected float speed;
	

	long LastShoot = System.currentTimeMillis();
	
	public Enemy(Bitmap bitmap) {
		super(bitmap);
	}
	public void Damage(int damage){
		hp -= damage; 
	}
	public int GetHP(){
		return hp;
	}
	
	void Move(){
		// 움직이는 로직
		if(movetype == MOVE_PATTERN_1){
			// 첫번째패턴
			if(m_y<=200){
				m_y+= speed;    // 중간지점전까지 기본속도로이동 
			}
			else {
				m_y+= speed *2; // 중간지점이후로는 두배의 속도로 이동
			}
			
		}
		else if(movetype == MOVE_PATTERN_2){
			// 두번째패턴
			if(m_y<=200){
				m_y+= speed;    // 중간지점전까지 일자로이동
			}
			else {
				m_x+= speed;    // 중간지점이후로는 +대각선으로이동
				m_y+= speed;   
			}
			
		}
		else if(movetype == MOVE_PATTERN_3){
			// 세번째패턴
			if(m_y<=200){
				m_y+= speed;    // 중간지점전까지 일자로이동
			}
			else {
				m_x-= speed;    // 중간지점이후로는 -대각선으로이동
				m_y+= speed;   
			}
			
		}
		if(m_y> 350)
			state = STATE_OUT;
		
	}
	
	void Attack(){
		if(System.currentTimeMillis() - LastShoot >=400){
			LastShoot = System.currentTimeMillis();
			// 미사일을 발사하는 로직
			AppManager.getInstance().m_gamestate.
					m_enemmslist.add(new Missile_Enemy(m_x+10, m_y+90));
		}
	}
	
	@Override
	public void Update(long GameTime){
		super.Update(GameTime);
		Attack();
		Move();
	}
	
}
