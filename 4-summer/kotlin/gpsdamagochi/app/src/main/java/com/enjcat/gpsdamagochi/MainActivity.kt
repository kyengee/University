package com.enjcat.gpsdamagochi

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        var bools = true

        button3.setOnClickListener {
            if(bools == true) {
                textView.text = "버튼이 눌렸습니다."
                bools = false
            }
            else{
                textView.text = getString(R.string.hello_world)
                bools = true
            }
        }
    }
}
