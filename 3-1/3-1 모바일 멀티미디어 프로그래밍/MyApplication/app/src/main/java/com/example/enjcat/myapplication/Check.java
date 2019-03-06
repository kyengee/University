package com.example.enjcat.myapplication;

import android.app.Activity;
import android.content.Intent;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_check);
        text = (TextView) findViewById(R.id.total);
        i=0;
        Customlist adapter = new Customlist(Check.this);
        list = (ListView) findViewById(R.id.list);
        list.setAdapter(adapter);
        Intent intent = new Intent(this.getIntent());
        final String type = intent.getStringExtra("text");
        list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {

                i++;
                text.setText(i+"개 선택");
                if(type == "Mix"){
                    int[] checklist = new int[6];
                    view.setBackgroundColor(getResources().getColor(R.color.colorAccent));
                    checklist[position]++;

                }else{
                    int[] checklist = new int[6];
                    view.setBackgroundColor(getResources().getColor(R.color.colorAccent));
                    checklist[position]++;

                }
            }
        });
    }


    public class Customlist extends ArrayAdapter<String>{
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
            count.setText(""+1);
            return rowView;
        }
    }
}
