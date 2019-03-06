package com.example.enjcat.myapplication;

import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    long now;
    SharedPreferences tree;
    long time;
    int gap;
    int water;
    int food;
    int exp;
    int level;
    String TreeName;

    SharedPreferences account;
    int AC_water;
    int AC_food;
    /*int pump;
    int mix;
    int food_mc;
    int basic1;
    int basic2;
    int basic3;
    int apple;
    int banana;
    int grape;*/
    String resName;
    int resID;

    ProgressBar water_pg;
    ProgressBar food_pg;
    ProgressBar exp_pg;
    Button receive;
    ImageView Image;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle("Grid name");
        now = System.currentTimeMillis();

        tree = getSharedPreferences("tree",0);
        time = tree.getLong("time",System.currentTimeMillis());
        gap = (int)(now-time)/(1000);
        water = tree.getInt("water",0)-(gap/10);
        food = tree.getInt("food",0)-(gap/10);
        exp = tree.getInt("exp",0);
        level = tree.getInt("level",1);
        TreeName = tree.getString("treeName","basic1");

        exp += (gap/10)*3;


        account = getSharedPreferences("account",0);
        AC_water = account.getInt("water",0);
        AC_food = account.getInt("food",0);
        /*pump = account.getInt("pump",1);
        mix = account.getInt("mix",1);
        food_mc = account.getInt("food",1);
        basic1 = account.getInt("basic1",0);
        basic2 = account.getInt("basic2",0);
        basic3 = account.getInt("basic3",0);
        apple = account.getInt("apple",0);
        banana = account.getInt("banana",0);
        grape = account.getInt("grape",0);*/

        water_pg = (ProgressBar) findViewById(R.id.water);
        food_pg = (ProgressBar) findViewById(R.id.food);
        exp_pg = (ProgressBar) findViewById(R.id.exp);
        receive = (Button) findViewById(R.id.receive);

        resName = "@drawable/"+ TreeName +"_"+level;
        resID = getResources().getIdentifier(resName,"drawable",this.getPackageName());
        Image = (ImageView) findViewById(R.id.treeImage);
        Image.setImageResource(resID);


        if(water < 0){
            exp-=water;
            water=0;
        }
        water_pg.setProgress(water);
        if(food < 0){
            exp-=food;
            food=0;
        }
        food_pg.setProgress(food);
        if(exp >= 100*level){
            exp = 100*level;
                if (level == 4) {
                    receive.setText("수확하기");
                }else
                    receive.setText("나무진화");
            }else
                receive.setText("");
        exp_pg.setMax(100*level);
        exp_pg.setProgress(exp);
    }


    public void onclick(View view){
        switch (view.getId()){
            case R.id.givewater:
                if(AC_water>5) {
                    if(water <= 100){
                    AC_water -= 5;
                    water +=5;
                    water_pg.setProgress(water);}
                }
            case R.id.givefood:
                if(AC_food>5){
                    if(food <= 100){
                    AC_food -= 5;
                    food +=5;
                    food_pg.setProgress(water);}
                }
            case R.id.receive:
                if(receive.getText() == "나무진화"){
                    exp = 0;
                    level++;
                    resName = "@drawable/"+ TreeName +"_"+level;
                    resID = getResources().getIdentifier(resName,"drawable",this.getPackageName());
                    Image.setImageResource(resID);
                }else{
                    exp = 0;
                    SharedPreferences.Editor editor;
                    editor=tree.edit();
                    editor.putInt(TreeName,account.getInt(TreeName,0)+1);
                    editor.commit();
                }



        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.mainmenu, menu);


        return true;
    }



    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        Intent intent;
        switch (item.getItemId()){
            case R.id.menu_water:
                intent = new Intent(MainActivity.this, Water.class);
                startActivity(intent);
                return true;

            case R.id.menu_food:
                intent = new Intent(MainActivity.this, Food.class);
                startActivity(intent);
                return true;

            case R.id.menu_mix:
                intent = new Intent(MainActivity.this, Mix.class);
                startActivity(intent);
                return true;

                default:
                    return true;

        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        SharedPreferences.Editor editor;
        editor=tree.edit();
        gap = (int)(now-System.currentTimeMillis())/1000;
        editor.putLong("time",System.currentTimeMillis());
        editor.putInt("water",water-(gap/10));
        editor.putInt("food",food-(gap/10));
        editor.putInt("exp",exp+(gap/10)*3);
        editor.putInt("level",level);
        editor.putString("treeName",TreeName);
        editor.commit();

        editor=account.edit();
        editor.putInt("water",AC_water);
        editor.putInt("food",AC_food);
        editor.commit();
    }


    @Override
    protected void onResume() {
        super.onResume();
        now = System.currentTimeMillis();

        tree = getSharedPreferences("tree",0);
        time = tree.getLong("time",System.currentTimeMillis());
        gap = (int)(now-time)/(1000);
        water = tree.getInt("water",0)-(gap/10);
        food = tree.getInt("food",0)-(gap/10);
        exp = tree.getInt("exp",0);
        level = tree.getInt("level",1);
        TreeName = tree.getString("treeName","basic1");

        exp += gap/10*3;


        account = getSharedPreferences("account",0);
        AC_water = account.getInt("water",0);
        AC_food = account.getInt("food",0);
        /*pump = account.getInt("pump",1);
        mix = account.getInt("mix",1);
        food_mc = account.getInt("food",1);
        basic1 = account.getInt("basic1",0);
        basic2 = account.getInt("basic2",0);
        basic3 = account.getInt("basic3",0);
        apple = account.getInt("apple",0);
        banana = account.getInt("banana",0);
        grape = account.getInt("grape",0);*/

        resName = "@drawable/"+ TreeName +"_"+level;
        resID = getResources().getIdentifier(resName,"drawable",this.getPackageName());
        Image = (ImageView) findViewById(R.id.treeImage);
        Image.setImageResource(resID);

        if(water < 0){
            exp-=water;
            water=0;
        }
        water_pg.setProgress(water);
        if(food < 0){
            exp-=food;
            food=0;
        }
        food_pg.setProgress(food);
        if(exp >= 100*level){
            exp = 100*level;
            if (level == 4) {
                receive.setText("수확하기");
            }else
                receive.setText("나무진화");
        }else
            receive.setText("");
        exp_pg.setMax(100*level);
        exp_pg.setProgress(exp);
    }
}
