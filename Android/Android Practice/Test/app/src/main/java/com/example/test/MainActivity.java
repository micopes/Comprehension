package com.example.test;

import androidx.appcompat.app.AppCompatActivity; // androidx 는 현재 버전 안드로이드. 이것을 Refactor 에들어가서 자동변환으로바꿀수있음

import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}
