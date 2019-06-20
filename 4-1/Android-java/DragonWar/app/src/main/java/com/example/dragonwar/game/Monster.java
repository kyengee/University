package com.example.dragonwar.game;

import android.graphics.Bitmap;

import com.example.dragonwar.framework.GraphicObject;
import com.example.dragonwar.framework.SpriteAnimaion;

public class Monster extends SpriteAnimaion {
    public static final int MOVE_PATTERN_1 = 0;
    public static final int MOVE_PATTERN_2 = 1;
    public static final int MOVE_PATTERN_3 = 2;

    protected int movetype;

    protected int hp;
    protected float speed;

    void Move(){
        // 몬스터 이동 패턴
        if(movetype == MOVE_PATTERN_1){
            if(m_x<1220){
                m_x+=speed;
            }
            else {
                m_x += speed*2;
            }

        }
        else if(movetype == MOVE_PATTERN_1){

        }
        else if(movetype == MOVE_PATTERN_1){

        }

    }

    void Attack(){
        // 몬스터 공격 패턴

    }

    @Override
    public void Update(long GameTime) {
        super.Update(GameTime);
        Move();
    }

    public Monster(Bitmap bitmap) {

        super(bitmap);
    }
}
