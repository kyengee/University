package com.example.smartdoorlock;

import android.app.DatePickerDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.DatePicker;
import android.widget.TextView;

import org.w3c.dom.Text;

public class LogLookUp extends AppCompatActivity {

    TextView start;
    TextView end;
    int mYear, mMonth, mDay;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_log_look_up);

        final DatePickerDialog.OnDateSetListener mDateSetListener = new DatePickerDialog.OnDateSetListener() {
            @Override
            public void onDateSet(DatePicker view, int year, int month, int dayOfMonth) {
                mYear = year;
                mMonth = month;
                mDay = dayOfMonth;
            }
        };

        start = (TextView) findViewById(R.id.Start);
        start.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new DatePickerDialog(LogLookUp.this,mDateSetListener, mYear, mMonth, mDay).show();
                start.setText(String.format("%d-%d-%d",mYear,mMonth +1, mDay));
            }
        });

        end = (TextView) findViewById(R.id.End);
        end.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new DatePickerDialog(LogLookUp.this,mDateSetListener, mYear, mMonth, mDay).show();
                end.setText(String.format("%d-%d-%d",mYear,mMonth +1, mDay));
            }
        });
    }
}
