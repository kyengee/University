package com.enjcat.mycalculator

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import kotlinx.android.synthetic.main.activity_main.*
import java.util.*
import kotlin.concurrent.timer

class MainActivity : AppCompatActivity() {
    private var option : Int? = 0
    private var timerTask : Timer? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        timerTask = timer(period = 500){
            runOnUiThread {
                update()
            }
        }
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.select, menu)
        return true
    }

    private fun update(){
        if (num1.text.toString() == "" || num2.text.toString() == "")
            return
        else {
            var numone= num1.text.toString().toInt()
            var numtwo= num2.text.toString().toInt()
            when (option) {
                1 -> {
                    result.text = "덧셈결과 : ${numone + numtwo}"
                }
                2 -> {
                    result.text = "곱셈결과 : ${numone * numtwo}"
                }
                3 -> {
                    result.text = "나눗셈결과 : ${numone / numtwo}"
                }
            }
        }
    }

    override fun onStart() {
        super.onStart()
        Log.i("LifecycleTest", "onStart_Main")
    }

    override fun onPause() {
        super.onPause()
        Log.i("LifecycleTest", "onPause_Main")
    }

    override fun onStop() {
        super.onStop()
        Log.i("LifecycleTest", "onStop_Main")
    }

    override fun onOptionsItemSelected(item: MenuItem?): Boolean {
        when(item?.itemId){
            R.id.add ->{
                option = 1
                return true
            }
            R.id.mix ->{
                option = 2
                return true
            }
            R.id.div ->{
                option = 3
                return true
            }
        }
        return super.onOptionsItemSelected(item)
    }
}
