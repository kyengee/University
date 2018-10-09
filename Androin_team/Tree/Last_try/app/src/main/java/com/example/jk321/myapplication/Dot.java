package com.example.jk321.myapplication;

import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.support.annotation.Nullable;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.TextView;



public class Dot extends View {
    //private final Context Dotcontext;

    private static double finalx=0, prex=0 , midx=0 , changedx=0;
    private static double finaly=0, prey=0 , midy=0 , changedy=0;



    private final int r = 5;
    private final Paint mPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private Paint drawText = new Paint();
    private Paint linePaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private Paint settedPaint = new Paint(Paint.ANTI_ALIAS_FLAG);

    public static boolean nametrigger = false;

    private static DisplayMetrics dm;

    private static Button mButton;
    private static FrameLayout frameLayout;
    private static FrameLayout.LayoutParams pm;
    private static TextView textView;

    static treemap treemapcxt;


    public static areainformation info;

    public Dot(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public Dot(Context context) {
        super(context);
        treemapcxt = (treemap) context;

        mPaint.setColor(0xFFFF0000);

        linePaint.setColor(Color.GREEN);

        drawText.setColor(Color.BLUE); drawText.setTextSize(20);
        settedPaint.setColor(Color.GREEN);

        dm = treemapcxt.getApplicationContext().getResources().getDisplayMetrics();

        finalx = dm.widthPixels/2;
        finaly = dm.heightPixels/2;
        info = new areainformation();
        info.setDotPoint();

        setBackgroundResource(R.drawable.ic_launcher_background);

    }
    void setDotLocation(double x , double y) {
        String numx = String.format("%.4f", x);
        String numy = String.format("%.4f", y);

        prex = Double.parseDouble(numx);
        prey = Double.parseDouble(numy);
        midx = prex; midy = prey;

    }
    void changeLocation(double x , double y){
        String numx = String.format("%.4f" , x);
        String numy = String.format("%.4f" , y);
        prex = Double.parseDouble(numx);
        prey = Double.parseDouble(numy);
        /*if((midx-Double.parseDouble(numx))*10000<=-1||1<=(midy-Double.parseDouble(numx))*10000) {
            changedx = (midx - Double.parseDouble(numx)) * 10000;
            changedy = (midy - Double.parseDouble(numy)) * 10000;
        }*/

        for (int i = 0; i < 10; i++)
        {
            if(prex==info.realGPSx[i])
            {
                finalx = info.rangex[i];
                info.currentx=i;
            }
            if(prey==info.realGPSy[i])
            {
                finaly = info.rangey[i];
                info.currenty=i;
            }
        }
        double treex=info.realGPSx[4];
        double treey=info.realGPSy[4];

        boolean check = false; boolean area;

        SharedPreferences first_settings = treemapcxt.getSharedPreferences(treemapcxt.PREF_FIRST,0);
        SharedPreferences.Editor first_Editor = first_settings.edit();
        first_Editor.putBoolean("isfirst",check); first_Editor.commit();

        SharedPreferences x_settings = treemapcxt.getSharedPreferences(treemapcxt.PRE_X,0);
        SharedPreferences.Editor x_Editor = x_settings.edit();
        x_Editor.putFloat("location_x",(float) treex); x_Editor.commit();

        SharedPreferences y_settings = treemapcxt.getSharedPreferences(treemapcxt.PRE_Y,0);
        SharedPreferences.Editor y_Editor = y_settings.edit();
        y_Editor.putFloat("location_y",(float) treey); y_Editor.commit();


    }

    @Override
    protected void onDraw(final Canvas canvas) {
        super.onDraw(canvas);

        canvas.drawCircle((float) finalx, (float) finaly, r, mPaint);

        /*canvas.drawText("위도는 "+prex+"경도는 "+prey+
                "\n 이전 위도 경도 차이는"+changedx+"\t"+changedy,200,200,drawText);*/


        for(int i=0;i<10;i++)
        {
            canvas.drawLine(0,(dm.heightPixels/10)*i+(dm.heightPixels/20),dm.widthPixels,(dm.heightPixels/10)*i+(dm.heightPixels/20),linePaint);
            canvas.drawLine((dm.widthPixels/10)*i+(dm.widthPixels/20),0,(dm.widthPixels/10)*i+(dm.widthPixels/20),dm.heightPixels,linePaint);
        }

        frameLayout = new FrameLayout(treemapcxt);
        mButton = new Button(treemapcxt);
        textView = new TextView(treemapcxt);

        frameLayout.setLayoutParams(new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT));

        pm = new FrameLayout.LayoutParams
                (FrameLayout.LayoutParams.WRAP_CONTENT, FrameLayout.LayoutParams.WRAP_CONTENT);

        pm.gravity = Gravity.CENTER;

        mButton.setLayoutParams(pm);
        if(info.isnamed[info.currentx][info.currenty]==1/*&&
                info.rangex[info.currentx]==finalx&&info.rangey[info.currenty]==finaly*/)
        {
            mButton.setText("들어가기"); //textView.setVisibility(INVISIBLE);
            textView.setText(info.name[info.currentx][info.currenty]);
        }
        else if(info.isnamed[info.currentx][info.currenty]==0)
        {
            mButton.setText("나무심기"); textView.setText("default");
        }
        mButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                if(mButton.getText().toString().equals("나무심기")) {
                    final Dialog nameDialog = new Dialog(treemapcxt);
                    nameDialog.setContentView(R.layout.tree_select_dialog);
                    nameDialog.setTitle("이름 설정하기");
                    Button done = nameDialog.findViewById(R.id.btn_done);
                    final EditText treename = nameDialog.findViewById(R.id.name);
                    done.setOnClickListener(new OnClickListener() {
                        @Override
                        public void onClick(View view)
                        {
                            if (treename.getText().toString().trim().length() > 0) {
                                //info.setName(finalx, finaly, treename.getText().toString());
                                info.setName2(info.currentx , info.currenty ,treename.getText().toString());
                                textView.setText(info.name[info.tempx][info.tempy]);
                                nameDialog.dismiss();
                               // canvas.drawCircle((float) finalx, (float) finaly,30,settedPaint);
                                //treemapcxt.firstarea = true;
                            }
                        }
                    });
                    nameDialog.show();
                }
                else if(mButton.getText().toString().equals("들어가기")) {
                    Intent intent = new Intent(treemapcxt,MainActivity.class);
                    intent.putExtra("tree_name", textView.getText().toString());
                    intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                    treemapcxt.startActivity(intent);
                }
                //float[] circlearea = returncircle.getCirclearea();
            }
        });
        textView.setLayoutParams(new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
                FrameLayout.LayoutParams.WRAP_CONTENT));
        //textView.setWidth(dm.widthPixels/2); textView.setHeight(dm.heightPixels/4);
         textView.setGravity(Gravity.TOP);
        //textView.setVisibility(INVISIBLE);

        ((FrameLayout)this.getParent()).addView(mButton);
        ((FrameLayout)this.getParent()).addView(textView);
        //invalidate();
        for(int i=0; i<10;i++)
        {
            for(int j=0; j<10; j++)
            {
                if(info.isnamed[i][j]==1)
                {
                    canvas.drawCircle((float)info.rangex[i],(float)info.rangey[j],30,settedPaint);
                }
            }
        }
    }


    static class areainformation
    {
        int mid ;

        static double rangex[] = new double[10] , realGPSx[] = new double[10]; public int tempx=0;
        static double rangey[] = new double[10] , realGPSy[] = new double[10]; public int tempy=0;
        String name[][] = new String[10][10]; int isnamed[][] = new int[10][10];
        int currentx , currenty;
        void firstLocation(double x , double y)
        {
            String numx = String.format("%.4f" , x);
            String numy = String.format("%.4f" , y);

            realGPSx[4] = Double.parseDouble(numx);
            realGPSy[4] = Double.parseDouble(numy);
            currentx = 4; currenty = 4;
        }
        double returnfirstx()
        {
            return info.realGPSx[4];
        }
        double returnfirsty()
        {
            return info.realGPSy[4];
        }
        void GPSareaSetting()
        {
            double j=2;
            for(int i=3 ; i>=0 ; i--)
            {
                mid = (int)(realGPSx[4]*10000);
                realGPSx[i] = (mid-j)/10000.0; j+=2;
            } j=2;
            for(int i=5 ; i<10 ; i++)
            {
                mid = (int)(realGPSx[4]*10000);
                realGPSx[i] = (mid+j)/10000.0; j+=2;
            } j=2;
            for(int i=3 ; i>=0 ; i--)
            {
                mid = (int)(realGPSy[4]*10000);
                realGPSy[i] = (mid-j)/10000.0; j+=2;
            } j=2;
            for(int i=5 ; i<10 ; i++)
            {
                mid = (int)(realGPSy[4]*10000);
                realGPSy[i] = (mid+j)/10000.0; j+=2;
            } j=2;
        }

        void setDotPoint()
        {
            for(int i=0; i<10; i++)
            {
                rangex[i]=(dm.widthPixels/10)*(i+1);
                rangey[i]=(dm.heightPixels/10)*(i+1);
            }
        }

        void setName(double x , double y ,String s)
        {
            for(int i=0; i<10; i++)
            {
                if(rangex[i]==x)
                {
                    tempx=i;
                }
                if(rangey[i]==y)
                {
                    tempy=i;
                }
            }


            name[tempx][tempy]=s;
            isnamed[tempx][tempy] = 1;currentx=tempx; currenty=tempy;
            treemapcxt.insert(name[tempx][tempy],tempx,tempy);
            nametrigger = true; treemapcxt.firstarea = true;
        }
        void getName(String s , int x, int y)
        {

            name[x][y] = s;
            isnamed[x][y] = 1;

        }
        void setName2(int x , int y , String s)
        {
            name[x][y] = s; isnamed[x][y] = 1;
            treemapcxt.insert(name[x][y],x,y);
        }

    }

}

