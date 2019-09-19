package com.example.dragonwar.game;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.KeyEvent;
import android.view.MotionEvent;

import com.example.dragonwar.R;
import com.example.dragonwar.framework.AppManager;
import com.example.dragonwar.framework.Collision;
import com.example.dragonwar.framework.CollisionManager;
import com.example.dragonwar.framework.GraphicObject;
import com.example.dragonwar.framework.IState;


import java.util.ArrayList;
import java.util.Random;

public class GameState implements IState {

    private static GameState s_instance;

    public static GameState getInstance(){
        return s_instance;
    }
    // 멤버 변수 추가할 곳
    private background1 m_background;
    private player m_player;
    Random randEnem = new Random();
    long playtime = System.currentTimeMillis();

    float m_glod_score = 0;


    private long m_LastShoot = System.currentTimeMillis();
    long LastMonster = System.currentTimeMillis();
    ArrayList<Monster> monsterlist = new ArrayList<Monster>();
    private ArrayList<GraphicObject> m_keypad = new ArrayList<GraphicObject>();;

    private MonsterA enem = new MonsterA();

    public void CheckCollision() {

        //플레이어 미사일과 몬스터의 충돌체크
        for (int i = m_player.m_pmslist.size() - 1; i >= 0; i--) {
            for (int j = monsterlist.size() - 1; j >= 0; j--) {
                if (CollisionManager.CheckBoxToBox(m_player.m_pmslist.get(i).m_BoundBox, monsterlist.get(j).m_BoundBox)) {
                    m_player.m_pmslist.remove(i);
                    if(monsterlist.get(j).movetype == 3)
                        monsterlist.get(j).hp -= 2;
                    else
                        monsterlist.remove(j);
                    return;
                }
            }
        }

        //몬스터 미사일과 플레이어와의 충돌체크
        for(int i = monsterlist.size() -1; i >= 0; i--){
            for(int j = 0; j < monsterlist.get(i).m_Alist.size(); j++){
                if(CollisionManager.CheckBoxToBox(m_player.m_BoundBox, monsterlist.get(i).m_Alist.get(j).m_BoundBox)){
                    monsterlist.get(i).m_Alist.remove(j);
                    if(monsterlist.get(j).movetype == 3)
                        m_player.hp -= 2;
                    else
                        m_player.hp -= 1;

                }
            }
        }
    }

    public void SetMonster() {
        if (System.currentTimeMillis() - LastMonster >= 2000) {
            LastMonster = System.currentTimeMillis();

            int enemtype = randEnem.nextInt(3);
            Monster enem = null;
            if(enemtype==0) {
                enem = new MonsterA();
            }
            if(enemtype==1){
                enem = new MonsterB();
            }
            if(enemtype==2){
                enem = new MonsterC();
            }

            enem.SetPosition(3300, randEnem.nextInt(1200));
            enem.movetype = randEnem.nextInt(3);

            monsterlist.add(enem);
        }
    }



    @Override
    public void Destroy() {
    }

    @Override
    public void Init() {
        s_instance = this;
        m_background = new background1();
        m_player = new player_green();
        Monster enem = new BossA();
        enem.SetPosition(2500, randEnem.nextInt(1000));
        monsterlist.add(enem);
        m_keypad.add(new GraphicObject(AppManager.getInstance().getBitmap(R.drawable.up)));
        m_keypad.get(m_keypad.size()-1).SetPosition(200,880);
        m_keypad.add(new GraphicObject(AppManager.getInstance().getBitmap(R.drawable.down)));
        m_keypad.get(m_keypad.size()-1).SetPosition(200,1240);
        m_keypad.add(new GraphicObject(AppManager.getInstance().getBitmap(R.drawable.left)));
        m_keypad.get(m_keypad.size()-1).SetPosition(20, 1060);
        m_keypad.add(new GraphicObject(AppManager.getInstance().getBitmap(R.drawable.right)));
        m_keypad.get(m_keypad.size()-1).SetPosition(380, 1060);
        m_keypad.add(new GraphicObject(AppManager.getInstance().getBitmap(R.drawable.shoot)));
        m_keypad.get(m_keypad.size()-1).SetPosition(2610, 1010);

    }

    @Override
    public void Render(Canvas canvas) {
        m_background.Draw(canvas);
        for( Monster enem : monsterlist){
            enem.Draw(canvas);
        }
        m_player.Draw(canvas);
        for( GraphicObject key : m_keypad){
            key.Draw(canvas);
        }

        Paint g = new Paint();
        g.setTextSize(70); g.setColor(Color.BLACK);
        canvas.drawText("HP : " + String.valueOf(m_player.hp),0,100,g); //유저체력
        canvas.drawText(""+String.valueOf(m_glod_score),2700,100,g); //골드 점수
    }

    @Override
    public void Update() {
        long GameTime = System.currentTimeMillis();
        m_player.Update(GameTime);
        m_background.Update(GameTime);
        for(Monster enem : monsterlist){
            enem.Update(GameTime);
        }
        SetMonster();
        CheckCollision();

        if (System.currentTimeMillis() - playtime >= 10000){
            AppManager.getInstance().getGameVies().ChangeGameState(new GameState1());
        }

    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {

        int x = m_player.GetX();
        int y = m_player.GetY();

        if(keyCode == KeyEvent.KEYCODE_DPAD_LEFT)
            m_player.SetPosition(x-10, y);
        if(keyCode == KeyEvent.KEYCODE_DPAD_RIGHT)
            m_player.SetPosition(x+10, y);
        if(keyCode == KeyEvent.KEYCODE_DPAD_UP)
            m_player.SetPosition(x, y-10);
        if(keyCode == KeyEvent.KEYCODE_DPAD_DOWN)
            m_player.SetPosition(x, y+10);

        return true;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        for(int i =0; i<event.getPointerCount();i++){
            int _x = (int) event.getX(i);
            int _y = (int) event.getY(i);

            if(Collision.CollisionCheckPointToBox(_x,_y, 20, 1060, 20 + 180, 1060 + 180)){
                m_player.startMove(-5, 0);
            }
            if(Collision.CollisionCheckPointToBox(_x,_y, 200, 880, 200 + 180, 880 + 180)){
                m_player.startMove(0, -5);
            }
            if(Collision.CollisionCheckPointToBox(_x,_y, 380, 1060, 380 + 180, 1060 + 180)){
                m_player.startMove(5, 0);
            }
            if(Collision.CollisionCheckPointToBox(_x,_y, 200, 1240, 200 + 180, 1240 + 180)){
                m_player.startMove(0, 5);
            }

            if(event.getAction() == MotionEvent.ACTION_UP ) {
                m_player.stopMove();
                m_player.shoot = false;
            }

            if(event.getAction() == MotionEvent.ACTION_DOWN){
                if(Collision.CollisionCheckPointToBox(_x,_y, 2610, 1010, 2610 + 400, 1010 + 400)){
                    if(System.currentTimeMillis()-m_LastShoot>500){
                        m_LastShoot = System.currentTimeMillis();
                        m_player.shoot = true;

                    }
                }
            }


        }

        return true;
    }
}
