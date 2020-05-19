package com.example.campingcalendar;

import android.os.Bundle;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
//import androidx.support.v4.app.AppCompatActivity;
//import androidx.support.v7.app.AppCompatActivity;

import android.util.Log;
import android.widget.CalendarView;


public class CalendarActivity extends AppCompatActivity {
    private static final String TAG = "CalendarActivity";

    private CalendarView mCalendarView;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.calendar_layout);
        mCalendarView = (CalendarView)findViewById(R.id.calendarView);

        mCalendarView.setOnDateChangeListener(new CalendarView.OnDateChangeListener(){
            @Override
            public void onSelectedDayChange(CalendarView calendarView, int i, int i1, int i2){
                String date = i + "/" + i1 + "/" + i2;
                Log.d(TAG, "onSelectedDayChanged: date : " + date);
            }
        });
    }
}
