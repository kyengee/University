package com.example.jk321.myapplication;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

public class Check extends AppCompatActivity {
    ListView list;
    String[] titles = {"파란열매","노란열매","빨간열매","사과","바나나","포도"};
    Integer[] images = {
            R.drawable.basic3_1,
            R.drawable.basic2_1,
            R.drawable.basic1_1,
            R.drawable.apple_1,
            R.drawable.banana_1,
            R.drawable.grape_1,
    };
    TextView text;
    int i;
    int[] checklist;
    Button commit;

    SharedPreferences account;
    int basic1;
    int basic2;
    int basic3;
    int apple;
    int banana;
    int grape;
    int[] seeds;
    String result_name;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_check);
        setTitle("씨앗을 선택하세요");

        seeds = new int[6];

        account = getSharedPreferences("account",0);
        seeds[2] = basic1 = account.getInt("basic1",20);
        seeds[1] = basic2 = account.getInt("basic2",0);
        seeds[0] = basic3 = account.getInt("basic3",0);
        seeds[3] = apple = account.getInt("apple",0);
        seeds[4] = banana = account.getInt("banana",0);
        seeds[5] = grape = account.getInt("grape",0);


        text = (TextView) findViewById(R.id.total);
        i=0;
        checklist = new int[6];
        Customlist adapter = new Customlist(Check.this);
        list = (ListView) findViewById(R.id.list);
        list.setAdapter(adapter);
        Intent intent = new Intent(this.getIntent());
        final String type = intent.getStringExtra("text");
        list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {

                if(seeds[position]>0) {
                    i++;
                    text.setText(i + "개 선택");
                    switch (type){
                        case "Mix":
                            setTitle("씨앗을 두개이상 선택하세요");
                            view.setBackgroundColor(getResources().getColor(R.color.colorAccent));
                            checklist[position]++;
                            break;
                        case "Food":
                            setTitle("씨앗하나당 20의 비료 생성");
                            view.setBackgroundColor(getResources().getColor(R.color.colorAccent));
                            checklist[position]++;
                            break;
                            case "create":
                                setTitle("심을 나무를 고르세요");
                                view.setBackgroundColor(getResources().getColor(R.color.colorAccent));
                                switch (position){
                                    case 0:
                                        result_name = "basic3";
                                        break;
                                    case 1:
                                        result_name = "basic2";
                                        break;
                                    case 2:
                                        result_name = "basic1";
                                        break;
                                    case 3:
                                        result_name = "apple";
                                        break;
                                    case 4:
                                        result_name = "banana";
                                        break;
                                    case 5:
                                        result_name = "grape";
                                        break;
                                }
                                SharedPreferences.Editor editor;
                                editor=account.edit();
                                editor.putInt(result_name,seeds[position]-1);
                                editor.commit();
                                Intent intent = new Intent();
                                intent.putExtra("result_name",result_name);
                                setResult(RESULT_OK,intent);
                                finish();
                                break;

                    }

                }
            }
        });

        commit = (Button)findViewById(R.id.commit);
        commit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent.putExtra("result",checklist);
                setResult(RESULT_OK,intent);
                finish();
            }
        });
    }


    public class Customlist extends ArrayAdapter<String> {
        private final Activity context;
        public Customlist(Activity context){
            super(context,R.layout.listitem,titles);
            this.context = context;
        }

        @NonNull
        @Override
        public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
            LayoutInflater inflater = context.getLayoutInflater();
            View rowView = inflater.inflate(R.layout.listitem,null,true);
            ImageView imageView = (ImageView) rowView.findViewById(R.id.image);
            TextView title = (TextView) rowView.findViewById(R.id.title);
            TextView count = (TextView) rowView.findViewById(R.id.count);

            title.setText(titles[position]);
            imageView.setImageResource(images[position]);
            count.setText(""+seeds[position]);
            return rowView;
        }
    }


}
