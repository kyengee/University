package com.example.dragonwar.game;

import android.graphics.Bitmap;
import android.graphics.Rect;

import com.example.dragonwar.framework.SpriteAnimaion;

import java.util.ArrayList;

public class player extends SpriteAnimaion {

    public ArrayList<Missile> m_pmslist = new ArrayList<Missile>();
    Rect m_BoundBox = new Rect();

    private boolean bMove = false;
    private int _dirX = 0;
    private int _dirY = 0;
    boolean shoot = false;
    public int hp;

    public player(Bitmap bitmap){
        super(bitmap);
        this.InitSpriteData(300	, 360, 6, 4);
        this.SetPosition(0, 580);
    }

    @Override
    public void Update(long GameTime){
        super.Update(GameTime);
        m_BoundBox.set(m_x,m_y + 145,m_x + 350,m_y + 145 + 80);
        if(bMove){
            this.m_x += _dirX;
            this.m_y += _dirY;
        }
    }

    public void startMove(int dirX,int dirY){
        bMove = true;
        _dirX = dirX;
        _dirY = dirY;
    }

    public void stopMove(){
        bMove =false;
        _dirX = 0;
        _dirY = 0;
    }
}
