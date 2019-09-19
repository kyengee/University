package com.example.dragonwar.game;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;

import com.example.dragonwar.R;
import com.example.dragonwar.framework.AppManager;
import com.example.dragonwar.framework.GraphicObject;

public class menu extends GraphicObject {
    public menu()
    {
        super(AppManager.getInstance().getBitmap(R.drawable.menu_back));

    }

    public void Draw(Canvas canvas){

        int width = canvas.getWidth();
        int height = canvas.getHeight();
        Bitmap b=BitmapFactory.decodeResource(AppManager.getInstance().getResources(), R.drawable.menu_back);
        Bitmap resize_bitmap=Bitmap.createScaledBitmap(b,width,height,true);
        canvas.drawBitmap(resize_bitmap,0,0,null);

    }
}
