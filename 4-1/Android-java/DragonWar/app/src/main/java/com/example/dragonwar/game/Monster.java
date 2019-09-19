package com.example.dragonwar.game;

import android.graphics.Bitmap;
import android.graphics.Rect;

import com.example.dragonwar.framework.GraphicObject;
import com.example.dragonwar.framework.SpriteAnimaion;

import java.util.ArrayList;

public class Monster extends GraphicObject {
    public static final int MOVE_PATTERN_1 = 0;   // 속도 증가
    public static final int MOVE_PATTERN_2 = 1;   // 대각선 위 이동
    public static final int MOVE_PATTERN_3 = 2;   // 대각선 아래
    public static final int BOSS_PATTERN_1 = 3;


    public ArrayList<Missile_Monster> m_Alist = new ArrayList<Missile_Monster>();
    Rect m_BoundBox = new Rect();

    protected int movetype;

    public int hp;
    protected float speed;

    void Move(){
        // 몬스터 이동 패턴
        if(movetype == MOVE_PATTERN_1){
            if(m_x>2500){
                m_x-=speed;
            }
            else {
                m_x -= speed*2;
            }
        }
        else if(movetype == MOVE_PATTERN_2){
            if(m_x>2500) {
                m_x -= speed;
            }
            else{
                m_x-=speed;
                m_y-=speed/2;
            }
        }
        else if(movetype == MOVE_PATTERN_3){
            if(m_x>2500) {
                m_x -= speed;
            }
            else{
                m_x-=speed;
                m_y+=speed/2;
            }
        }
        else if(movetype == BOSS_PATTERN_1){
            m_y += speed;
        }

    }

    void Attack(){
        // 몬스터 공격 패턴

    }

//    @Override
    public void Update(long GameTime) {
     //   super.Update(GameTime);
        Move();
        if(movetype == 3)
            m_BoundBox.set(m_x,m_y ,m_x + 300,m_y + 455);
        else
            m_BoundBox.set(m_x,m_y ,m_x + 155,m_y + 235);
    }

    public Monster(Bitmap bitmap) {

        super(bitmap);
    }
}
