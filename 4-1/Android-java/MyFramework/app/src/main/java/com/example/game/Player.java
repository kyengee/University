package com.example.game;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Rect;

import com.example.myframework.SpriteAnimation;

public class Player extends SpriteAnimation {


	Rect m_BoundBox = new Rect();
	
	int m_Life = 3;
	int m_power = 10;
	
	public Player(Bitmap bitmap) {
		super(bitmap);
		// �좊땲硫붿씠���뺣낫瑜��명똿�댁���
		this.InitSpriteData(104	, 62, 3, 6);
		// 珥덇린 �꾩튂媛믪쓣 �ㅼ젙�댁���
		this.SetPosition(140, 380);
	}
	
	
	public int GetPower(){
		return m_power;
	}
	public void SetPower(int _power){
		m_power = _power;
	}
	
	// ��쭅�대뒗 �곹깭媛믪쓣 媛�����뚮옒洹�
	private boolean bMove = false;
	// 諛⑺뼢媛믪쓣 媛����蹂�닔
	private int _dirX = 0;
	private int _dirY = 0;
	
	public int getLife(){
		return m_Life;
	}
	public void destroyPlayer(){
		m_Life--;
	}
	public void AddLife(){
		m_Life++;
	}
	
	// onTouchEvent �먯꽌 DOWN 硫붿꽭吏�� 諛쏆븯�꾨븣 �몄텧��硫붿꽌��
	public void startMove(int dirX,int dirY){
		// ��쭅�꾩쓣 �쒖꽦�붿떆耳쒖���
		bMove = true;
		// 諛⑺뼢媛믪쓣 ��옣�쒕떎
		_dirX = dirX;
		_dirY = dirY;		
	}
	// onTouchEvent �먯꽌 UP 硫붿꽭吏�� 諛쏆븯�꾨븣 �몄텧��硫붿꽌��
	public void stopMove(){
		// ��쭅�꾩쓣 鍮꾪솢�깊솕�쒖폒以�떎
		bMove =false;
		// 諛⑺뼢媛믪쓣 珥덇린�붿떆�⑤떎
		_dirX = 0;
		_dirY = 0;
	}
	// �꾨젅�꾩썙��Update�먯꽌 吏�냽�곸쑝濡��몄텧�쒗궗硫붿꽌��
	@Override
	public void Update(long GameTime){
		// �ㅻ쾭濡쒕뱶����븳 泥섎━
		 super.Update(GameTime);
		
		// ��쭅�꾩씠 �쒖꽦�붾릺�덉쓣寃쎌슦
		if(bMove){
			this.m_x += _dirX;
			this.m_y += _dirY;
		}
		
		m_BoundBox.set(m_x,m_y,m_x+42,m_y+44);	
	}

}
