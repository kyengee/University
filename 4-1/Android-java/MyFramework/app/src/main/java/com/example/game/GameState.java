package com.example.game;

import java.util.ArrayList;
import java.util.Random;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.view.KeyEvent;
import android.view.MotionEvent;

import com.example.myframework.AppManager;
import com.example.myframework.Collision;
import com.example.myframework.CollisionManager;
import com.example.myframework.GraphicObject;
import com.example.myframework.IState;
import com.example.myframework.R;

public class GameState implements IState {
	
	private long m_LastShoot = System.currentTimeMillis();
	private Player m_player;
	private BackGround m_background;
	
	private GraphicObject m_keypad;
    private GraphicObject m_shootpad;
	
	ArrayList<Missile> m_pmslist = new ArrayList<Missile>();
	ArrayList<Missile> m_enemmslist = new ArrayList<Missile>();
	ArrayList<Item> m_itemlist = new ArrayList<Item>();
	ArrayList<Enemy> m_enemlist = new ArrayList<Enemy>();
	ArrayList<Effect_Explosion> m_explist = new ArrayList<Effect_Explosion>();
	
	private int m_scroll = 0;
	private final static int SCROLL_SPEED = 1;
	
	public int m_score = 0;
	
	long m_LastRegenEnemy = System.currentTimeMillis();
	
	Random m_randEnem = new Random();
	Random m_randItem = new Random();
	
	public Player GetPlayer(){
		return m_player;
	}
	
	public GameState(){
		// �꾩뿭蹂�닔泥섎읆 �깅줉
		AppManager.getInstance().m_gamestate = this;
	}
	
	public void CreateItem(int x , int y){
		// �곸씠 二쎌뿀�꾨븣 �꾩씠�쒖쓣 �앹꽦�댁���
		int rand = m_randItem.nextInt(100);
		
		if(rand >= 90)
			m_itemlist.add(new Item_AddLife(x,y));
		else 
			m_itemlist.add(new Item_AddScore(x,y));
	
	}
	@Override
	public void Init() {
        m_player = new Player(AppManager.getInstance().getBitmap(R.drawable.player));
        m_keypad=new GraphicObject(AppManager.getInstance().getBitmap(R.drawable.keypad));
        m_shootpad = new GraphicObject(AppManager.getInstance().getBitmap(R.drawable.missile_1));
        m_background=new BackGround(1);
        // �ㅽ뙣���꾩튂 
        m_keypad.SetPosition(0,460-120);
        m_shootpad.SetPosition(270, 385);
	}
	
	public void CheckCollision(){
		for (int i = m_pmslist.size()-1; i >= 0; i--) {
			for (int j = m_enemlist.size()-1; j >= 0; j--) {
	    		if(CollisionManager.CheckBoxToBox(m_pmslist.get(i).m_BoundBox,m_enemlist.get(j).m_BoundBox)){
	    			m_explist.add(new Effect_Explosion(m_enemlist.get(j).GetX(),m_enemlist.get(j).GetY()));
	    			CreateItem(m_enemlist.get(j).GetX(),m_enemlist.get(j).GetY());
	    			
	    			m_pmslist.remove(i);
	    			
	    			m_enemlist.get(j).Damage(m_player.GetPower());
	    			if(m_enemlist.get(j).GetHP() <= 0)
	    				m_enemlist.remove(j);
	    			
	    			return;
	    		}
	        }
        }
		
		for (int i = m_enemlist.size()-1; i >= 0; i--) {
    		if(CollisionManager.CheckBoxToBox(m_player.m_BoundBox,m_enemlist.get(i).m_BoundBox)){
    			m_explist.add(new Effect_Explosion(m_enemlist.get(i).GetX(),m_enemlist.get(i).GetY()));
    			m_enemlist.remove(i);
    			
    			
 //   			m_player.destroyPlayer();
    			if(m_player.getLife()<=0)
    				System.exit(0);

    		}
        }
		
		for (int i = m_enemmslist.size()-1; i >= 0; i--) {
    		if(CollisionManager.CheckBoxToBox(m_player.m_BoundBox,m_enemmslist.get(i).m_BoundBox)){
    			m_enemmslist.remove(i);	
    			
//    			m_player.destroyPlayer();
    			if(m_player.getLife()<=0){
    				System.exit(0);
    			}

    		}
        }
		for (int i = m_itemlist.size()-1; i >= 0; i--) {
    		if(CollisionManager.CheckBoxToBox(m_player.m_BoundBox,m_itemlist.get(i).m_BoundBox)){
    			m_itemlist.get(i).GetItem();
    			m_itemlist.remove(i);
    		}

			return;
        }
		
	}

	public void MakeEnemy(){
				
		if(System.currentTimeMillis() - m_LastRegenEnemy >= 1000 ){
			m_LastRegenEnemy = System.currentTimeMillis();
			
			int enemtype = m_randEnem.nextInt(3);
			Enemy enem = null;
			if(enemtype == 0){
				// 1踰덊����곴뎔
				enem = new Enemy_1();				
			}
			else if(enemtype == 1){
				// 2踰덊����곴뎔
				enem = new Enemy_2();				
			}
			else if(enemtype == 2){
				// 3踰덊����곴뎔
				enem = new Enemy_3();			
			}
			
			enem.SetPosition(m_randEnem.nextInt(280), -60);
			enem.movetype = m_randEnem.nextInt(3);
			
			m_enemlist.add(enem);
		}
			
	}
	
	
	@Override
	public void Render(Canvas canvas) {
    	m_background.Draw(canvas);
    	for (Missile pms : m_pmslist) {
    		pms.Draw(canvas);
        }
    	for (Missile enemms : m_enemmslist) {
    		enemms.Draw(canvas);
        }
    	for (Enemy enem : m_enemlist) {
    		enem.Draw(canvas);
        }
    	for (Effect_Explosion exp : m_explist) {
    		exp.Draw(canvas);
        }
    	for (Item item : m_itemlist) {
    		item.Draw(canvas);
        }
    	m_player.Draw(canvas);
    	m_keypad.Draw(canvas);
        m_shootpad.Draw(canvas);
    	
    	Paint p = new Paint();
    	p.setTextSize(20); p.setColor(Color.BLACK); 
    	canvas.drawText("Life :"+String.valueOf(m_player.getLife()),0,20,p);
    	canvas.drawText("Score :"+String.valueOf(m_score),0,40,p);
	}


    @Override
    public void Update() {
        long GameTime = System.currentTimeMillis();
        m_player.Update(GameTime);
        m_background.Update(GameTime);

        for (int i = m_pmslist.size()-1; i >= 0; i--) {
            Missile pms = m_pmslist.get(i);
            pms.Update();
            if(pms.state == Missile.STATE_OUT){
                m_pmslist.remove(i);
            }
        }
        for (int i = m_enemmslist.size()-1; i >= 0; i--) {
            Missile enemms = m_enemmslist.get(i);
            enemms.Update();
            if(enemms.state == Missile.STATE_OUT){
                m_enemmslist.remove(i);
            }
        }
        for (int i = m_enemlist.size()-1; i >= 0; i--) {
            Enemy enem = m_enemlist.get(i);
            enem.Update(GameTime);
            if(enem.state == Enemy.STATE_OUT)
                m_enemlist.remove(i);
        }
        for (int i = m_explist.size()-1; i >= 0; i--) {
            Effect_Explosion exp = m_explist.get(i);
            exp.Update(GameTime);
            if(exp.getAnimationEnd())
                m_explist.remove(i);
        }
        for (int i = m_itemlist.size()-1; i >= 0; i--) {
            Item item = m_itemlist.get(i);
            item.Update(GameTime);
            if(item.bOut == true)
                m_itemlist.remove(i);
        }
        MakeEnemy();
        CheckCollision();
    }

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// �ㅼ엯�μ뿉�곕Ⅸ �뚮젅�댁뼱�대룞
		
		int x = m_player.GetX();
		int y = m_player.GetY();
		
		if(keyCode == KeyEvent.KEYCODE_DPAD_LEFT) // �쇱そ
			m_player.SetPosition(x-3, y);
		if(keyCode == KeyEvent.KEYCODE_DPAD_RIGHT)// �ㅻⅨ履�
			m_player.SetPosition(x+3, y);
		if(keyCode == KeyEvent.KEYCODE_DPAD_UP)  // �
			// �
			m_player.SetPosition(x, y-3);
		if(keyCode == KeyEvent.KEYCODE_DPAD_DOWN) // �꾨옒
			m_player.SetPosition(x, y+3);
		if(keyCode == KeyEvent.KEYCODE_DPAD_CENTER) // �ㅽ럹�댁뒪瑜��뚮��꾨븣
			m_pmslist.add(new Missile_Player(x+10,y));
		
		return true;
	}


	
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		

		for(int i =0; i<event.getPointerCount();i++){
			int _x = (int) event.getX(i);
			int _y = (int) event.getY(i);
			
			if(Collision.CollisionCheckPointToBox(_x,_y, 5, 385, 45, 425)){
				m_player.startMove(-1, 0);
			}
			// �꾩そ諛⑺뼢
			if(Collision.CollisionCheckPointToBox(_x,_y, 40, 345, 80, 385)){
				m_player.startMove(0, -1);
			}
			// �ㅻⅨ履쎈갑��
			if(Collision.CollisionCheckPointToBox(_x,_y, 80, 385, 120, 425)){
				m_player.startMove(1, 0);
			}
			// �꾨옒履쎈갑��
			if(Collision.CollisionCheckPointToBox(_x,_y, 40, 425, 80, 465)){
				m_player.startMove(0, 1);
			}
			
			if(event.getAction() == MotionEvent.ACTION_UP )
				m_player.stopMove();
			
			if(event.getAction() == MotionEvent.ACTION_DOWN){
				if(Collision.CollisionCheckPointToBox(_x,_y, 270, 385, 313, 428)){
					if(System.currentTimeMillis()-m_LastShoot>500){
						m_LastShoot = System.currentTimeMillis();
						m_pmslist.add(new Missile_Player(m_player.GetX()+10,m_player.GetY()));
					}
				}
			}
			
		}
			
		
		// Move ��Up ���대깽�몃� 諛쏄린�꾪빐 true 瑜�由ы꽩�댁���
		return true;
	}

	@Override
	public void Destroy() {
		// TODO Auto-generated method stub
		
	}

}
