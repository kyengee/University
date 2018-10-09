package com.example.jk321.myapplication;


import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteException;
import android.database.sqlite.SQLiteOpenHelper;
import android.os.Build;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.MotionEvent;
import android.widget.Toast;

import static com.example.jk321.myapplication.Dot.info;


public class treemap extends AppCompatActivity {

    private final int PERMISSIONS_ACCESS_FINE_LOCATION = 1000;
    private final int PERMISSIONS_ACCESS_COARSE_LOCATION = 1001;
    private boolean isAccessFineLocation = false;
    private boolean isAccessCoarseLocation = false;
    private boolean isPermission = false;
    public static Dot dot;
    public static  GpsInfo gps;
    NameDBHelper helper;
    SQLiteDatabase db;

    public static String TREENAME;
    public static final String PREF_FIRST = "first_location";
    public static final String PRE_X = "prev_x";
    public static final String PRE_Y = "prev_y";
    private static final String PRE_AREA="prev_area";
    private boolean isitfirst;
    public boolean firstarea;


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        dot = new Dot(this);

        SharedPreferences first_settings = getSharedPreferences(PREF_FIRST,0);
        SharedPreferences x_settings = getSharedPreferences(PRE_X,0);
        SharedPreferences y_settings = getSharedPreferences(PRE_Y,0);
        isitfirst=first_settings.getBoolean("isfirst",true);

        callPermission();
        gps = new GpsInfo(treemap.this);
        startService(new Intent(this,GpsInfo.class));

        helper = new NameDBHelper(this);

        try {
            db = helper.getWritableDatabase();
        }catch (SQLiteException e)
        {
            db = helper.getReadableDatabase();
        }



        if (gps.isGetLocation()) {

            double latitude = gps.getLatitude();
            double longitude = gps.getLongitude();
            dot.setDotLocation(latitude , longitude);

            if(isitfirst)
            {
                info.firstLocation(latitude,longitude);
            }

            Toast.makeText(
                    getApplicationContext(),
                    "당신의 위치 - \n위도: " +  latitude +
                            "\n경도: " + longitude ,
                    Toast.LENGTH_LONG).show();
        } else {
            // GPS 를 사용할수 없으므로
            gps.showSettingsAlert();
        }
        if(!isitfirst)
        {
            info.firstLocation(x_settings.getFloat("location_x", 0),
                    y_settings.getFloat("location_y", 0));

        }
        info.GPSareaSetting();

        if(!isitfirst){
            String name;
            int x = -1, y = -1;
            Cursor cursor;
            cursor = db.rawQuery("SELECT * FROM contacts", null);
            while (cursor.moveToNext()) {
                name = cursor.getString(1);
                x = cursor.getInt(2);
                y = cursor.getInt(3);
                if (name != null)
                    info.getName(name, x, y);
            }
        }

        setContentView(dot);
    }
    public void invlidating()
    {
        dot.invalidate();
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        dot.invalidate();
        return true;
    }
    public void insert(String dname , int dx , int dy){
        String name = dname; int x =dx , y = dy;
        db.execSQL("INSERT INTO contacts VALUES (null, '"+name+"', '"
                +x+"', '"+y+"');");
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        double x , y;
        x=info.realGPSx[4];
        y=info.realGPSy[4];


        boolean check = false; boolean area;
        if(x==0&&y==0)
        {check = true;}
        SharedPreferences first_settings = getSharedPreferences(PREF_FIRST,0);
        SharedPreferences.Editor first_Editor = first_settings.edit();
        first_Editor.putBoolean("isfirst",check); first_Editor.commit();

        SharedPreferences x_settings = getSharedPreferences(PRE_X,0);
        SharedPreferences.Editor x_Editor = x_settings.edit();
        x_Editor.putFloat("location_x",(float) x); x_Editor.commit();

        SharedPreferences y_settings = getSharedPreferences(PRE_Y,0);
        SharedPreferences.Editor y_Editor = y_settings.edit();
        y_Editor.putFloat("location_y",(float) y); y_Editor.commit();
    }

    @Override
    protected void onResume() {
        super.onResume();
        if(!isitfirst){
            String name;
            int x = -1, y = -1;
            Cursor cursor;
            cursor = db.rawQuery("SELECT * FROM contacts", null);
            while (cursor.moveToNext()) {
                name = cursor.getString(1);
                x = cursor.getInt(2);
                y = cursor.getInt(3);
                if (name != null)
                    info.getName(name, x, y);
            }
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        double x , y;
        x=info.realGPSx[4];
        y=info.realGPSy[4];

        boolean check = false; boolean area;
        if(x==0&&y==0)
        {check = true;}
        SharedPreferences first_settings = getSharedPreferences(PREF_FIRST,0);
        SharedPreferences.Editor first_Editor = first_settings.edit();
        first_Editor.putBoolean("isfirst",check); first_Editor.commit();

        SharedPreferences x_settings = getSharedPreferences(PRE_X,0);
        SharedPreferences.Editor x_Editor = x_settings.edit();
        x_Editor.putFloat("location_x",(float) x); x_Editor.commit();

        SharedPreferences y_settings = getSharedPreferences(PRE_Y,0);
        SharedPreferences.Editor y_Editor = y_settings.edit();
        y_Editor.putFloat("location_y",(float) y); y_Editor.commit();

    }

    @Override
    protected void onStop() {
        super.onStop();
        double x , y;
        x=info.realGPSx[4];
        y=info.realGPSy[4];


        boolean check = false; boolean area;
        if(x==0&&y==0)
        {check = true;}
        SharedPreferences first_settings = getSharedPreferences(PREF_FIRST,0);
        SharedPreferences.Editor first_Editor = first_settings.edit();
        first_Editor.putBoolean("isfirst",check); first_Editor.commit();

        SharedPreferences x_settings = getSharedPreferences(PRE_X,0);
        SharedPreferences.Editor x_Editor = x_settings.edit();
        x_Editor.putFloat("location_x",(float) x); x_Editor.commit();

        SharedPreferences y_settings = getSharedPreferences(PRE_Y,0);
        SharedPreferences.Editor y_Editor = y_settings.edit();
        y_Editor.putFloat("location_y",(float) y); y_Editor.commit();

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        double x , y;
        x=info.realGPSx[4];
        y=info.realGPSy[4];

        boolean check = false; boolean area;
        if(x==0&&y==0)
        {check = true;}
        SharedPreferences first_settings = getSharedPreferences(PREF_FIRST,0);
        SharedPreferences.Editor first_Editor = first_settings.edit();
        first_Editor.putBoolean("isfirst",check); first_Editor.commit();

        SharedPreferences x_settings = getSharedPreferences(PRE_X,0);
        SharedPreferences.Editor x_Editor = x_settings.edit();
        x_Editor.putFloat("location_x",(float) x); x_Editor.commit();

        SharedPreferences y_settings = getSharedPreferences(PRE_Y,0);
        SharedPreferences.Editor y_Editor = y_settings.edit();
        y_Editor.putFloat("location_y",(float) y); y_Editor.commit();
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions,
                                           int[] grantResults) {
        if (requestCode == PERMISSIONS_ACCESS_FINE_LOCATION
                && grantResults[0] == PackageManager.PERMISSION_GRANTED) {

            isAccessFineLocation = true;

        } else if (requestCode == PERMISSIONS_ACCESS_COARSE_LOCATION
                && grantResults[0] == PackageManager.PERMISSION_GRANTED){

            isAccessCoarseLocation = true;
        }

        if (isAccessFineLocation && isAccessCoarseLocation) {
            isPermission = true;
        }
    }

    // 전화번호 권한 요청
    private void callPermission() {
        // Check the SDK version and whether the permission is already granted or not.
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M
                && checkSelfPermission(Manifest.permission.ACCESS_FINE_LOCATION)
                != PackageManager.PERMISSION_GRANTED) {

            requestPermissions(
                    new String[]{Manifest.permission.ACCESS_FINE_LOCATION},
                    PERMISSIONS_ACCESS_FINE_LOCATION);

        } else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M
                && checkSelfPermission(Manifest.permission.ACCESS_COARSE_LOCATION)
                != PackageManager.PERMISSION_GRANTED){

            requestPermissions(
                    new String[]{Manifest.permission.ACCESS_COARSE_LOCATION},
                    PERMISSIONS_ACCESS_COARSE_LOCATION);
        } else {
            isPermission = true;
        }
    }

}


class NameDBHelper extends SQLiteOpenHelper
{
    private static final String DB_NAME = "treename.db";
    private static final int DATABASE_VERSION = 2;

    public NameDBHelper(Context context) {
        super(context, DB_NAME,null,DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("CREATE TABLE contacts (_id INTEGER PRIMARY KEY"+
        " AUTOINCREMENT,name TEXT , coorx INTEGER , coory INTEGER);");
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldversion, int newversion) {
        db.execSQL("DROP TABLE IF EXISTS contacts");
        onCreate(db);
    }
}