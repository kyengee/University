package com.example.dragonwar.game;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;

import com.example.dragonwar.R;
import com.example.dragonwar.framework.AppManager;
import com.example.dragonwar.framework.GraphicObject;

public class gold extends GraphicObject {

    public gold() {
        super(AppManager.getInstance().getBitmap(R.drawable.gold_));


    }

    public void Draw(Canvas canvas) {
        Bitmap b = BitmapFactory.decodeResource(AppManager.getInstance().getResources(), R.drawable.gold_);
        Bitmap resize_bitmap = Bitmap.createScaledBitmap(b, 80, 80, true);
        canvas.drawBitmap(resize_bitmap, 2600, 0, null);
    }


   /* public void AddLife() {
        m_Life += 10;
    }

    public int getLife() {
        return m_Life;
    }
    */
}
